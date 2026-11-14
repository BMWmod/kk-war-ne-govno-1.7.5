"""Shared legacy DDS textures with full mip chains.

AN-196 retains its source resolution and packed normal map. Geran-5 uses
one 1024x1024 diffuse atlas; its procedural source art is rebuilt on demand.
Runtime materials reference only $/model/... DDS files.
"""
import io
import struct
from pathlib import Path
from PIL import Image, ImageChops, ImageStat

ROOT = Path(__file__).resolve().parents[1]
TEXTURES = ROOT / 'resource/texture/common/model'
G5 = ROOT / 'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
SU25 = ROOT / 'resource/entity/-vehicle/-modern/air_modern/rus/su-25sm_part1'
AN196 = ROOT / 'resource/entity/-vehicle/-modern/air_modern/ukr/an196'
PARTS = ('body', 'wing', 'panels', 'metal', 'dark')


def save_dds(path, image, fmt):
    levels = []
    level = image.convert('RGBA')
    while True:
        buffer = io.BytesIO()
        level.save(buffer, format='DDS', pixel_format=fmt)
        levels.append(buffer.getvalue())
        if level.size == (1, 1):
            break
        level = level.resize((max(1, level.width // 2), max(1, level.height // 2)),
                             Image.Resampling.BOX)
    header = bytearray(levels[0][:128])
    struct.pack_into('<I', header, 8, struct.unpack_from('<I', header, 8)[0] | 0x20000)
    struct.pack_into('<I', header, 20, len(levels[0]) - 128)
    struct.pack_into('<I', header, 28, len(levels))
    struct.pack_into('<I', header, 108, 0x1000 | 0x8 | 0x400000)
    data = header + b''.join(item[128:] for item in levels)
    assert data[:4] == b'DDS ' and data[84:88] == fmt.encode('ascii')
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    with Image.open(path) as decoded:
        assert decoded.size == image.size
        error = ImageStat.Stat(ImageChops.difference(image.convert('RGB'), decoded.convert('RGB')))
        assert max(error.mean) < 8, (path, error.mean)
    return len(data)


def material(folder, name):
    return ('{material bump\n'
            ' {diffuse "$/model/' + folder + '/' + name + '" {MipMap 1}}\n'
            ' {bump "$/model/' + folder + '/' + name + '_bp"}\n'
            ' {blend none}\n}\n').replace('\n', '\r\n').encode('ascii')


def install_g5():
    from build_geran5_atlas import install
    install()


def install_an196():
    shared = TEXTURES / 'an196'
    with Image.open(AN196 / 'an196_body.tga') as im:
        # Retain the source alpha, even though the current material is opaque.
        save_dds(shared / 'an196_body.dds', im, 'DXT5')
    with Image.open(AN196 / 'an196_body_bp.tga') as im:
        x, y, z = im.convert('RGB').split()
        packed = Image.merge('RGBA', (Image.new('L', im.size, 0), y, z, x))
        save_dds(shared / 'an196_body_bp.dds', packed, 'DXT5')
    (AN196 / 'an196_body.mtl').write_bytes(material('an196', 'an196_body'))


if __name__ == '__main__':
    install_g5()
    install_an196()
    print('Shared DDS assets installed: single Geran-5/Su-25 atlas and original-resolution AN-196.')
