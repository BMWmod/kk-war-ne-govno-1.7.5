"""Build the marine BMP-2 field armour kit in native GEM formats.

Run from the mod root. Reuses the installed Cold War BMP-2 skeleton and
materials; only this variant gets the new model, collision volumes and armour.
This is a game-specific field conversion, not a factory BMP-2D replica.
"""
from pathlib import Path
import math
import re
import struct
import zipfile

ROOT = Path(__file__).resolve().parents[1]
DEST = ROOT / 'resource/entity/-vehicle/-modern/btr_modern/rus/bmp2_new'
PAK = ROOT.parent / 'cold war 1_7_5/resource/entity/-vehicle/-modern/btr_modern.pak'


def box(center, size):
    x, y, z = center
    a, b, c = (v / 2 for v in size)
    return [(x+dx*a, y+dy*b, z+dz*c) for dx,dy,dz in
            [(-1,-1,-1),(1,-1,-1),(1,1,-1),(-1,1,-1),
             (-1,-1,1),(1,-1,1),(1,1,1),(-1,1,1)]]


QUADS = [(0,3,2,1),(4,5,6,7),(0,1,5,4),
         (1,2,6,5),(2,3,7,6),(3,0,4,7)]


def painted_metal_uv(points):
    """Map each face proportionally inside an inspected, unadorned paint patch.

    body_bmp2.dds is 1024 square. The rectangle x=108..246, y=124..260
    contains only painted steel: no hatches, hinges, seams or empty atlas.
    GEM V runs downwards. Thin edges and bars must sample thin strips, rather
    than stretching the same square atlas fragment across every face.
    """
    width = math.dist(points[0], points[1])
    height = math.dist(points[0], points[3])
    density = min(6.0, 138.0 / width, 136.0 / height)
    u0, v0 = 108.0 / 1024, 124.0 / 1024
    u1, v1 = u0 + width * density / 1024, v0 + height * density / 1024
    return [(u0, v0), (u1, v0), (u1, v1), (u0, v1)]


def ply(filename, boxes):
    vertices, indices = [], []
    for center, size in boxes:
        corners = box(center, size)
        for quad in QUADS:
            points = [corners[i] for i in quad]
            u = [points[1][i]-points[0][i] for i in range(3)]
            v = [points[2][i]-points[0][i] for i in range(3)]
            normal = [u[1]*v[2]-u[2]*v[1], u[2]*v[0]-u[0]*v[2], u[0]*v[1]-u[1]*v[0]]
            length = math.sqrt(sum(n*n for n in normal))
            normal = [n/length for n in normal]
            first = len(vertices)
            for point, uv in zip(points, painted_metal_uv(points)):
                vertices.append((*point, *normal, *uv))
            # GEM uses clockwise faces, opposite to the outward vertex normals.
            indices.extend(first+i for i in [2,1,0,3,2,0])
    bounds = [min(v[i] for v in vertices) for i in range(3)]
    bounds += [max(v[i] for v in vertices) for i in range(3)]
    material = b'body.mtl'
    data = b'EPLYBNDS' + struct.pack('<6f', *bounds)
    data += b'MESH' + struct.pack('<4IB', 0x112, 0, len(indices)//3, 0x404, len(material)) + material
    data += b'VERT' + struct.pack('<IHH', len(vertices), 32, 7)
    data += b''.join(struct.pack('<8f', *v) for v in vertices)
    data += b'INDX' + struct.pack('<I', len(indices))
    data += struct.pack('<'+'H'*len(indices), *indices)
    (DEST / filename).write_bytes(data)


def volume(filename, size):
    vertices = box((0,0,0), size)
    indices = [q[i] for q in QUADS for i in [2,1,0,3,2,0]]
    data = b'EVLMVERT' + struct.pack('<I', len(vertices))
    data += b''.join(struct.pack('<3f', *v) for v in vertices)
    data += b'INDX' + struct.pack('<I', len(indices)) + struct.pack('<36H', *indices)
    data += b'SIDE' + struct.pack('<I', 12) + bytes([6,6,5,5,1,1,2,2,3,3,4,4])
    (DEST / filename).write_bytes(data)


def write_text(name, text):
    (DEST / name).write_bytes(text.replace('\r', '').replace('\n', '\r\n').encode('cp1251'))


def build():
    with zipfile.ZipFile(PAK) as archive:
        names = {n.lower(): n for n in archive.namelist()}
        def base(name):
            return archive.read(names['btr_modern/rus/bmp2_new/'+name]).decode('cp1251').replace('\r', '')
        mdl, definition = base('bmp2_new.mdl'), base('bmp2_new.def')

    # Five spaced steel panels per side, leaving rear doors and roof hatches free.
    plate_size = (0.3, 21.8, 20)
    plate_boxes = [((0,0,0), plate_size)]
    # Reinforcement strips, bolt heads and mounting arms are visible geometry.
    for x in [-0.27, 0.27]:
        for y in [-9,9]:
            plate_boxes.append(((x,y,0), (0.25,0.65,19.5)))
            for z in [-8,8]:
                plate_boxes.append(((x*1.9,y,z), (0.45,0.8,0.8)))
    ply('mor_armor_panel.ply', plate_boxes)
    volume('mor_armor_panel.vol', plate_size)
    ply('mor_armor_mount.ply', [((0,0,0),(4.2,1.1,1.1))])
    body_bones, volumes, components = [], [], []
    for side, x in [('l',32),('r',-32)]:
        for number, y in enumerate([-44,-21,2,25,48],1):
            name = f'mor_armor_{side}{number}'
            body_bones.append(f'''\t\t\t{{bone "{name}"
                {{parameters "ID={name};"}}
                {{Position {x} {y} 0}}
                {{VolumeView "mor_armor_panel.ply"}}
            }}''')
            for dy in [-8,8]:
                body_bones.append(f'''\t\t\t{{bone "{name}_mount_{'a' if dy<0 else 'b'}"
                {{parameters "ID={name};"}}
                {{Position {x-2.1 if x>0 else x+2.1} {y+dy} 7}}
                {{VolumeView "mor_armor_mount.ply"}}
            }}''')
            volumes.append(f'''{{Volume "{name}"
    {{Polyhedron "mor_armor_panel.vol"}}
    {{Bone "{name}"}}
}}''')
            components.append(f'\t{{component "{name}" {{tags "shield"}}}}')

    # Open-front turret-mounted cage. It rotates with the turret, including its
    # collision bars. Holes remain holes: no solid collision plane over the roof.
    bars = []
    for y in [-24,24]:
        bars.append(((1,y,32),(48,0.7,0.7)))
    for x in [-23,25]:
        bars.append(((x,0,32),(0.7,48,0.7)))
    for x in [-14,18]:
        for y in [-23,23]:
            bars.append(((x,y,16),(0.7,0.7,32)))
            bars.append(((x,y*20/23,0),(1.2,7,0.7)))
    for x in range(-20,25,3):
        bars.append(((x,0,32),(0.32,47,0.32)))
    for y in range(-21,24,3):
        bars.append(((1,y,32.35),(47,0.32,0.32)))
    # Shallow side/rear lattice, front remains open for the armament.
    for y in [-24,24]:
        for z in [26,29]:
            bars.append(((1,y,z),(48,0.32,0.32)))
    for z in [26,29]:
        bars.append(((25,0,z),(0.32,48,0.32)))
    ply('mor_cage.ply', bars)
    cage_bone = '''
                {bone "mor_cage"
                    {parameters "ID=mor_cage;"}
                    {VolumeView "mor_cage.ply"}
                }
'''
    components.append('\t{component "mor_cage" {tags "shield"}}')
    shapes = {}
    for index, (center,size) in enumerate(bars):
        if size not in shapes:
            shapes[size] = f'mor_cage_bar_{len(shapes)}.vol'
            volume(shapes[size], size)
        volumes.append(f'''{{Volume "mor_cage_{index:02}"
    {{Polyhedron "{shapes[size]}"}}
    {{Bone "mor_cage"}}
    {{Position {' '.join(map(str,center))}}}
}}''')

    body_marker = '{VolumeView "body.ply"}'
    turret_marker = '{VolumeView "turret.ply"}'
    assert mdl.count(body_marker) == mdl.count(turret_marker) == 1
    mdl = mdl.replace(body_marker, body_marker+'\n'+'\n'.join(body_bones))
    mdl = mdl.replace(turret_marker, turret_marker+cage_bone)
    mdl += '\n; Marine field kit collision geometry\n'+'\n'.join(volumes)+'\n'
    definition = definition.replace('"bmp2_new.mdl"', '"bmp2_ukr_mor.mdl"')
    definition = definition.replace('/properties/tank_amph.ext', '/properties/tank.ext')
    # Same weapons. Added steel has a weight/mobility cost and is not amphibious.
    definition = definition.replace('"amphibia" ', '').replace('{PatherID "amphibia"}', '{PatherID "tank"}')
    definition = re.sub(r'\s*\("CW_amphibia" Waterline\(1\.35\) \)', '', definition)
    definition = definition.replace('{mass 13600}', '{mass 14500}').replace('Mass(13.6)', 'Mass(14.5)')
    definition = definition.replace('Gamespeed(41)', 'Gamespeed(38)')
    armor = '\n; Game-specific field armour kit; nominal steel values.\n'
    armor += '\n'.join(components)+'\n'
    for name in [f'mor_armor_{s}{i}' for s in ['l','r'] for i in range(1,6)]:
        armor += f'\t{{volume "{name}" {{tags "shield"}} {{component "{name}"}}}}\n'
    for i in range(len(bars)):
        armor += f'\t{{volume "mor_cage_{i:02}" {{tags "shield"}} {{component "mor_cage"}}}}\n'
    armor += '''\t{armor
        {setting "mor_armor"
            {thickness 6}
            {durability {blast {value 10}} {pierce {koef 999}}}
            {threshold {blast {value 1}}}
            {volumes "mor_armor_*"}
        }
        {setting "mor_cage"
            {thickness 3}
            {durability {blast {value 5}} {pierce {koef 999}}}
            {threshold {blast {value 1}}}
            {volumes "mor_cage_*"}
        }
    }
'''
    end = definition.rfind('}')
    definition = definition[:end]+armor+definition[end:]
    write_text('bmp2_ukr_mor.mdl', mdl)
    write_text('bmp2_ukr_mor.def', definition)
    print(f'Built marine BMP-2: 10 armour panels, {len(bars)} cage bars, {len(shapes)} shared cage collision shapes.')


if __name__ == '__main__':
    build()
