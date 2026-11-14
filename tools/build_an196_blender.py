"""Run inside Blender with Gemwerk enabled; build AN-196 native GEM assets.

Uses the supplied D:/ddd model and the installed Cold War Shahed as the
behaviour/skeleton reference. Source geometry and UVs are preserved.
"""
from pathlib import Path
import importlib
import copy
import json
import math
import struct
import zipfile
import bpy
import bmesh
from mathutils import Matrix, Quaternion, Vector

ROOT = Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
DEST = ROOT / 'resource/entity/-vehicle/-modern/air_modern/ukr/an196'
DEST.mkdir(parents=True, exist_ok=True)
PKG = 'bl_ext.user_default.gemwerk_io'
ex = importlib.import_module(PKG + '.export_mdl')
mdlfmt = importlib.import_module(PKG + '.formats.mdl')
anmfmt = importlib.import_module(PKG + '.formats.anm')
imp = importlib.import_module(PKG + '.import_mdl')
WORK = Path(r'C:\Users\Vsevoloden\AppData\Local\Temp\an196_work')
WORK.mkdir(exist_ok=True)

def write(path, text):
    path.write_bytes(text.replace('\r', '').replace('\n', '\r\n').encode('cp1251'))

src = bpy.data.objects.get('AN196_SOURCE_model_0')
if src is None:
    bpy.ops.wm.obj_import(filepath=r'D:\ddd\model_0.obj')
    src = bpy.context.active_object
    src.name = 'AN196_SOURCE_model_0'
src.rotation_euler = (0, 0, 0)
src.location = (0, 0, 0)
src.scale = (1, 1, 1)
mat = src.data.materials[0]
mat.gem.mtl_name = 'an196_body.mtl'
mat.gem.flags = 0x504  # MATERIAL, LIGHT, BUMP; Gemwerk exports tangent basis.
mat.gem.fvf = 0x112

# Convert textures without a dependency on the original model folder at runtime.
for source, name in [('1_albedo.png', 'an196_body'), ('1_normal.png', 'an196_body_bp')]:
    image = bpy.data.images.load(str(Path(r'D:\ddd') / source), check_existing=False)
    image.pixels[0]  # Load pixels before replacing the source path.
    image.filepath_raw = str(DEST / (name + '.tga'))
    formats = [i.identifier for i in image.bl_rna.properties['file_format'].enum_items]
    image.file_format = next(f for f in formats if f == 'TARGA_RAW')
    image.save()
    header = Path(image.filepath_raw).read_bytes()[:18]
    if len(header) != 18 or header[2] != 2:
        raise RuntimeError('Texture export did not produce uncompressed true-color TGA')
write(DEST / 'an196_body.mtl', '{material bump\n {diffuse "an196_body" {MipMap 1}}\n {bump "an196_body_bp"}\n {blend none}\n}\n')

# Partition complete disconnected source pieces so UV seams never create holes.
me = src.data
adj = [[] for _ in me.vertices]
for e in me.edges:
    a, b = e.vertices
    adj[a].append(b); adj[b].append(a)
seen = set(); components = []
for v in me.vertices:
    if v.index in seen:
        continue
    stack = [v.index]; seen.add(v.index); ids = []
    while stack:
        i = stack.pop(); ids.append(i)
        for j in adj[i]:
            if j not in seen:
                seen.add(j); stack.append(j)
    components.append(ids)
groups = {n: set() for n in ['body', 'wingl1', 'wingr1', 'tail1', 'tail2', 'part1']}
for ids in components:
    lo = [min(me.vertices[i].co[k] for i in ids) for k in range(3)]
    hi = [max(me.vertices[i].co[k] for i in ids) for k in range(3)]
    cx = (lo[0] + hi[0]) / 2
    if hi[1] > 1.8:
        group = 'tail1' if cx >= 0 else 'tail2'
    elif max(abs(lo[0]), abs(hi[0])) > 1.0 and lo[2] > -0.4:
        group = 'wingl1' if cx >= 0 else 'wingr1'
    elif lo[1] >= 0 and hi[1] < 0.5:
        group = 'part1'
    else:
        group = 'body'
    groups[group].update(ids)

# GEM aircraft face +X; 1 game unit is 0.06 m in this model family.
scale = 1 / 0.06
transform = Matrix(((0, -scale, 0, 0), (scale, 0, 0, 0), (0, 0, scale, 0), (0, 0, 0, 1)))
pivots = {'part1': Vector((-5.8, 0, 1.76))}
stats = {}
for name, ids in groups.items():
    obj = src.copy(); obj.data = me.copy(); obj.name = 'AN196_BUILD_' + name
    bpy.context.collection.objects.link(obj)
    bm = bmesh.new(); bm.from_mesh(obj.data); bm.verts.ensure_lookup_table()
    bmesh.ops.delete(bm, geom=[v for v in bm.verts if v.index not in ids], context='VERTS')
    bm.to_mesh(obj.data); bm.free()
    obj.data.transform(Matrix.Translation(-pivots.get(name, Vector())) @ transform)
    obj.data.update()
    ex.export_ply(bpy.context, obj, str(DEST / (name + '.ply')))
    stats[name] = len(obj.data.polygons)
    bpy.data.objects.remove(obj, do_unlink=True)

# Use the reference propeller (the source OBJ contains the hub, but no blades).
reference = ROOT.parent / 'cold war 1_7_5/resource/entity/-vehicle/-modern/air_modern.pak'
with zipfile.ZipFile(reference) as z:
    for name in ['propeller.ply', 'body.mtl', 'shahed136.mdl']:
        (WORK / name).write_bytes(z.read('air_modern/ir/shahed136/' + name))
prop = imp.import_ply(bpy.context, str(WORK / 'propeller.ply'), merge=True)
if not isinstance(prop, bpy.types.Object):
    prop = bpy.context.active_object
prop.data.materials.clear()
pm = bpy.data.materials.new('AN196_propeller'); pm.gem.mtl_name = 'an196_propeller.mtl'
pm.diffuse_color = (0.045, 0.045, 0.045, 1)
prop.data.materials.append(pm)
ex.export_ply(bpy.context, prop, str(DEST / 'propeller.ply'))
bpy.data.objects.remove(prop, do_unlink=True)
write(DEST / 'an196_propeller.mtl', '{material simple\n {diffuse "an196_propeller" {MipMap 1}}\n {blend none}\n}\n')
# Generated Blender images can retain PNG encoding despite a .tga path.
# Write the constant-color texture directly as a type-2, bottom-origin TGA.
header = struct.pack('<BBBHHBHHHHBB', 0, 0, 2, 0, 0, 0, 0, 0, 16, 16, 24, 0)
(DEST / 'an196_propeller.tga').write_bytes(header + bytes((20, 20, 20)) * (16 * 16))

# Retain all control/sensor bones required by the existing aircraft properties.
model = mdlfmt.Model.read(str(WORK / 'shahed136.mdl'))
bones = {b.name: b for root in model.bones for b, parent in root.walk()}
for b in bones.values():
    b.views = []
    b.matrix = mdlfmt.IDENTITY
    b.visibility = None
# GEM aircraft assets retain the reflected root used by the working Shahed.
# Removing it changes world-space triangle handedness and backface culling.
bones['basis'].matrix = (1,0,0, 0,-1,0, 0,0,1, 0,0,0)
def position(name, xyz):
    bones[name].matrix = mdlfmt.IDENTITY[:9] + tuple(xyz)
for name in ['body', 'tail1', 'tail2', 'part1', 'propeller']:
    bones[name].views = [mdlfmt.VolumeView(name + '.ply')]
for name in ['wingl1', 'wingr1']:
    bone = mdlfmt.Bone(name); bone.parameters = 'ID=body;'
    bone.views = [mdlfmt.VolumeView(name + '.ply')]
    bones['body'].children.append(bone); bones[name] = bone
position('part1', (-5.8, 0, 1.76)); position('kolpak', (-1.4, 0, 0))
position('visor_ols', (33, 0, 0)); position('aiming_mark', (33, 0, 0))
position('foresight1_rot', (32, 0, 0))
bones['foresight1'].matrix = (1,0,0, 0,0,-1, 0,1,0, 0,0,0)
position('foresight_spawn', (0, 0, 0))
position('pivot_front', (31, 0, -13)); position('supportfront', (0,0,0))
position('pivot_back', (4,0,-13)); position('supportleft', (0,12,0)); position('supportright', (0,-12,0))
position('ir_1gen_emitter', (-6,0,2)); position('ir_2gen_emitter', (-6,0,2))

# Collision follows the fuselage, separate wings, tail booms and landing gear.
# Retain the reference subsystem names used by aircraft damage events.
model.volumes = []
def box(name, bone, center, size):
    v = mdlfmt.Volume(name); v.bone = bone; v.shape = 'box'; v.size = list(size)
    v.matrix = mdlfmt.IDENTITY[:9] + tuple(center); model.volumes.append(v)
box('body','body',(12,0,0),(42,8.6,7.7))
box('body1','wingl1',(7,-29,-1.6),(14,53,2.2))
box('body2','wingr1',(7,29,-1.6),(14,53,2.2))
box('body3','tail1',(-16,-11.7,1.2),(38,1,6.6))
box('body4','tail2',(-16,11.7,1.2),(38,1,6.6))
box('tail1','tail1',(-34,-6,8),(6,12,8))
box('tail2','tail2',(-34,6,8),(6,12,8))
box('engine','part1',(0,0,0),(6,10,6))
for name, center, size in [
    ('ammo_storage_autocannon',(23,0,0),(15,6,6)),
    ('fuel_tank_internal_a',(7,0,0),(15,6,5)),
    ('electronics',(30,0,1),(4,5,3)), ('pilot_panel',(18,0,2),(3,3,2)),
    ('ppu',(20,0,0),(2,2,2)), ('ptur',(24,0,0),(3,3,2)),
    ('ptur1',(25,0,0),(2,2,2)), ('ols',(34,0,0),(3,3,3)),
    ('steering_eler_l',(5,-40,-2),(3,12,1)),
    ('steering_eler_r',(5,40,-2),(3,12,1)),
    ('steering_elev',(-34,0,9),(3,14,1)),
    ('steering_rudder',(-34,0,10),(3,1,4)),
    ('gear_front',(32,0,-10),(4,2,6)),
    ('gear_left',(4,-11,-10),(4,2,6)),
    ('gear_right',(4,11,-10),(4,2,6))]:
    box(name,'body_systems',center,size)

for name in ['basis','engine_start','engine_work','engine_stop','fly','damage_fly','move']:
    frames = 31 if name not in ['basis','engine_stop'] else 2
    track = []
    for f in range(frames):
        a = f * math.tau / 10 if frames > 2 else 0
        c,s = math.cos(a),math.sin(a)
        track.append(((1,0,0, 0,c,-s, 0,s,c, 0,0,0),1))
    anm = anmfmt.from_tracks(['propeller'], frames, {0:track})
    anmfmt.write(str(DEST / (name+'.anm')), anm)
model.sequences = []
for name in ['basis','engine_start','engine_work','engine_stop','fly','damage_fly','move']:
    seq = mdlfmt.Sequence(name); seq.speed = 1.0; model.sequences.append(seq)
model.write(str(DEST / 'an196.mdl'))

# The CWPS missile attachment uses a different roll basis from an aircraft.
# This is the combined rotation/reflection of the reference ammo's body and
# child meshes: X stays forward; the mesh Y and Z axes exchange places.
ammo_model = copy.deepcopy(model)
ammo_model.bones[0].matrix = (1,0,0, 0,0,1, 0,1,0, 0,0,0)
ammo_model.sequences = [s for s in ammo_model.sequences if s.name == 'move']
ammo_model.shapes = []
ammo_model.write(str(DEST / 'an196_ammo.mdl'))

# Load the exported model in the user's visible scene for round-trip inspection.
root,warnings = imp.import_mdl(bpy.context, str(DEST/'an196.mdl'),show_volumes=False,import_animations=True)
root.name = 'AN-196 Lyutyi - GAME MODEL'; root.scale = (0.06,)*3
root.location = (0,0,0)
src.hide_set(True)
for o in bpy.context.view_layer.objects:
    o.select_set(False)
root.select_set(True); bpy.context.view_layer.objects.active = root
for window in bpy.context.window_manager.windows:
    for area in window.screen.areas:
        if area.type == 'VIEW_3D':
            sp = area.spaces.active
            sp.shading.type = 'MATERIAL'
            sp.overlay.show_relationship_lines = False
            sp.region_3d.view_location = (0,1.8,0)
            sp.region_3d.view_rotation = Quaternion((1,0,0),math.radians(25))
            sp.region_3d.view_distance = 15
print(json.dumps({'parts':stats,'warnings':warnings,'output':str(DEST)}))
