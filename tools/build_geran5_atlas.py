"""One 1024x1024 diffuse atlas/material for Geran-5 and both Su-25 payloads.

Run after exporting the seven original meshes. Geometry, normals, triangle
indices, skeletons and flight definitions are untouched. UVs include the original
repeat range, preventing seam triangles from crossing into neighbouring tiles.
Requires Pillow, numpy, and Gemwerk's standalone formats/ply.py (no live Blender).
The procedural source textures can be recreated with build_geran5_textures.py.
"""
import importlib.util
import io
import os
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
CARRIER = ROOT / 'resource/entity/-vehicle/-modern/air_modern/rus/su-25sm_part1'
SHARED = ROOT / 'resource/texture/common/model/geran5'
PARTS = ('body', 'panels', 'wingl1', 'wingr1', 'tail', 'engine', 'booster')
PAINTS = ('body', 'wing', 'panels', 'metal', 'dark')
RECTS = {'body': (0, 0, 512, 768), 'panels': (0, 768, 512, 256),
         'wing': (512, 0, 512, 512), 'metal': (512, 512, 512, 256),
         'dark': (512, 768, 512, 256)}
SIZE, PAD = 1024, 8


def ply_module():
    paths = list((Path(os.environ['APPDATA']) / 'Blender Foundation/Blender').glob(
        '*/extensions/user_default/gemwerk_io/formats/ply.py'))
    if not paths:
        raise RuntimeError('Install Gemwerk or run from a machine with its standalone PLY reader')
    spec = importlib.util.spec_from_file_location('gem_atlas_ply', sorted(paths)[-1])
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def save_atlas(image):
    from PIL import Image
    levels = []
    while True:
        buffer = io.BytesIO()
        image.convert('RGBA').save(buffer, format='DDS', pixel_format='DXT1')
        levels.append(buffer.getvalue())
        if image.size == (1, 1):
            break
        image = image.resize((max(1, image.width // 2), max(1, image.height // 2)), Image.Resampling.BOX)
    header = bytearray(levels[0][:128])
    struct.pack_into('<I', header, 8, struct.unpack_from('<I', header, 8)[0] | 0x20000)
    struct.pack_into('<I', header, 28, len(levels))
    struct.pack_into('<I', header, 108, 0x401008)
    return bytes(header) + b''.join(level[128:] for level in levels)


def install():
    import numpy as np
    from PIL import Image
    ply = ply_module()
    meshes = {part: ply.read(str(SOURCE / (part + '.ply'))) for part in PARTS}
    if all(m.textures == ['g5_atlas.mtl'] for obj in meshes.values() for m in obj.meshes):
        assert (SHARED / 'g5_atlas.dds').exists()
        print('Geran-5 already uses one atlas')
        return
    bounds = {name: [float('inf'), float('inf'), -float('inf'), -float('inf')] for name in PAINTS}
    ownership = {}
    for part, obj in meshes.items():
        assert obj.vsize == 48 and obj.layout().uv_offset == 24
        owners = {}
        uv = obj.vertices()['uv'][0]
        for mesh in obj.meshes:
            name = mesh.textures[0].removeprefix('g5_').removesuffix('.mtl')
            assert name in bounds
            for index in obj.indices[mesh.first_face * 3:(mesh.first_face + mesh.face_count) * 3]:
                assert index not in owners or owners[index] == name, 'Shared vertex across materials'
                owners[index] = name
                u, v = uv[index]
                b = bounds[name]
                b[:] = min(b[0], u), min(b[1], v), max(b[2], u), max(b[3], v)
        assert len(owners) == obj.vert_count
        ownership[part] = owners
    # Sample a periodic source over each material's actual UV extent. Padding
    # repeats edge pixels, so filtering never immediately reads another paint.
    atlas = Image.new('RGB', (SIZE, SIZE))
    for name, (x, y, width, height) in RECTS.items():
        with Image.open(SOURCE / ('g5_' + name + '.tga')) as source:
            src = np.asarray(source.convert('RGB'))
        lo_u, lo_v, hi_u, hi_v = bounds[name]
        iw, ih = width - 2 * PAD, height - 2 * PAD
        us = lo_u + (np.arange(iw) + .5) / iw * (hi_u - lo_u)
        vs = lo_v + (np.arange(ih) + .5) / ih * (hi_v - lo_v)
        # Bilinear periodic resampling; raw GEM V is already top-to-bottom.
        sx, sy = us * src.shape[1] - .5, vs * src.shape[0] - .5
        ix, iy = np.floor(sx).astype(int), np.floor(sy).astype(int)
        fx, fy = (sx - ix)[None, :, None], (sy - iy)[:, None, None]
        tile = ((1-fy)*((1-fx)*src[iy[:,None] % src.shape[0], ix[None,:] % src.shape[1]] +
                       fx*src[iy[:,None] % src.shape[0], (ix[None,:]+1) % src.shape[1]]) +
                fy*((1-fx)*src[(iy[:,None]+1) % src.shape[0], ix[None,:] % src.shape[1]] +
                    fx*src[(iy[:,None]+1) % src.shape[0], (ix[None,:]+1) % src.shape[1]]))
        tile = np.pad(np.uint8(np.clip(np.round(tile), 0, 255)), ((PAD,PAD),(PAD,PAD),(0,0)), mode='edge')
        atlas.paste(Image.fromarray(tile), (x, y))
    encoded = save_atlas(atlas)
    planned = {}
    for part, obj in meshes.items():
        before = obj.vertices()
        original_indices = obj.indices[:]
        raw = bytearray()
        for i in range(obj.vert_count):
            name = ownership[part][i]
            lo_u, lo_v, hi_u, hi_v = bounds[name]
            x, y, w, h = RECTS[name]
            u, v = before['uv'][0][i]
            au = (x + PAD + (u-lo_u)/(hi_u-lo_u)*(w-2*PAD))/SIZE
            av = (y + PAD + (v-lo_v)/(hi_v-lo_v)*(h-2*PAD))/SIZE
            assert 0 < au < 1 and 0 < av < 1
            raw += obj.vert_raw[i*48:i*48+24] + struct.pack('<2f', au, av)
        obj.vert_raw, obj.vsize = bytes(raw), 32
        # All contiguous face runs now use the same material: one draw per part.
        mesh = obj.meshes[0]
        mesh.flags &= ~0x100
        mesh.textures = ['g5_atlas.mtl']
        mesh.first_face, mesh.face_count = 0, len(obj.indices)//3
        obj.meshes = [mesh]
        obj.order = ply.default_order(obj)
        data = ply.serialize(obj)
        check = ply.parse(data)
        assert check.indices == original_indices
        assert check.vertices()['pos'] == before['pos']
        assert check.vertices()['normal'] == before['normal']
        planned[part] = data
    SHARED.mkdir(parents=True, exist_ok=True)
    (SHARED / 'g5_atlas.dds').write_bytes(encoded)
    material = b'{material simple\r\n {diffuse "$/model/geran5/g5_atlas" {MipMap 1}}\r\n {blend none}\r\n}\r\n'
    for part, data in planned.items():
        (SOURCE / (part + '.ply')).write_bytes(data)
        (CARRIER / ('g5_payload_' + part + '.ply')).write_bytes(data)
    for folder in (SOURCE, CARRIER):
        (folder / 'g5_atlas.mtl').write_bytes(material)
    # Exact known obsolete generated files only; source art is reproducible.
    for folder in (SOURCE, CARRIER, SHARED):
        for name in PAINTS:
            for suffix in ('.tga', '.dds', '.mtl', '_bp.tga', '_bp.dds'):
                (folder / ('g5_' + name + suffix)).unlink(missing_ok=True)
    print(f'Geran-5: one {SIZE}x{SIZE} DXT1 atlas, {len(encoded)} bytes; 14 meshes verified')


if __name__ == '__main__':
    install()
