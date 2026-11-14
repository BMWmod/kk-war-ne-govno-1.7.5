"""Create UV texture sets for the supplied untextured Geran-5 model.

Diffuse textures use native type-2 TGA. Normal maps use GEM's DXT5
packing (X in alpha, Y in green) and a complete DDS mip chain.
"""
from pathlib import Path
import math
import io
import struct
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter

ROOT = Path(__file__).resolve().parents[1]
DEST = ROOT / 'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
DEST.mkdir(parents=True, exist_ok=True)
SIZE = 1024
RNG = np.random.default_rng(1965)
FONT = Path('C:/Windows/Fonts/arial.ttf')

def font(n):
    return ImageFont.truetype(str(FONT), n)

def canvas(rgb, noise=1.4):
    v = np.array(rgb)[None,None,:] + RNG.normal(0,noise,(SIZE,SIZE,1))
    return Image.fromarray(np.uint8(np.clip(v,0,255)))

def save(name, im):
    path = DEST/(name+'.tga')
    im.convert('RGB').save(path,format='TGA',compression=None)
    assert path.read_bytes()[2] == 2

def save_normal(name, im):
    x,y,z=im.convert('RGB').split()
    packed=Image.merge('RGBA',(Image.new('L',im.size,0),y,z,x))
    levels=[]
    while True:
        buffer=io.BytesIO()
        packed.save(buffer,format='DDS',pixel_format='DXT5')
        levels.append(buffer.getvalue())
        if packed.size == (1,1):break
        packed=packed.resize((max(1,packed.width//2),max(1,packed.height//2)),Image.Resampling.BOX)
    header=bytearray(levels[0][:128])
    struct.pack_into('<I',header,8,struct.unpack_from('<I',header,8)[0]|0x20000)
    struct.pack_into('<I',header,20,len(levels[0])-128)
    struct.pack_into('<I',header,28,len(levels))
    struct.pack_into('<I',header,108,0x1000|0x8|0x400000)
    path=DEST/(name+'.dds')
    path.write_bytes(header+b''.join(level[128:] for level in levels))
    assert path.read_bytes()[84:88] == b'DXT5'
    # Retire this generator's old uncompressed normal, avoiding ambiguous lookup.
    (DEST/(name+'.tga')).unlink(missing_ok=True)

def line(draw, xy, color=(112,120,118), width=1):
    draw.line(xy,fill=color,width=width)

def fasteners(draw, x, y0, y1, spacing=24):
    for y in range(y0,y1,spacing):
        draw.ellipse((x-1,y-1,x+1,y+1),fill=(95,103,101))

# Reference: graphite airframe, subtle seams, pale unpainted engine casing.
body=canvas((37,40,46),0.9);d=ImageDraw.Draw(body)
for x in [76,302,574,872,956]:
    line(d,[(x,0),(x,SIZE)],(25,28,33),1)
    line(d,[(x+2,0),(x+2,SIZE)],(43,46,52),1)
for y in [128,640]:line(d,[(0,y),(SIZE,y)],(32,35,41))
for cy in [256,768]:
    d.rounded_rectangle((462,cy-36,548,cy+36),radius=5,outline=(29,32,37),width=1)
    d.line((474,cy,482,cy),fill=(22,24,29),width=2)
save('g5_body',body)
wing=canvas((34,37,44),0.9);d=ImageDraw.Draw(wing)
for x in [180,800,974]:line(d,[(x,0),(x,SIZE)],(24,27,33),1)
for y in [50,250,750,974]:line(d,[(0,y),(SIZE,y)],(28,31,38),1)
line(d,[(803,0),(803,SIZE)],(45,48,55),1)
save('g5_wing',wing)
# The supplied separate maintenance covers should blend with the fuselage.
panels=canvas((40,43,49),0.8);d=ImageDraw.Draw(panels)
for x in range(24,SIZE,256):line(d,[(x,0),(x,SIZE)],(34,37,43),1)
save('g5_panels',panels)
metal=canvas((184,183,171),1.1);d=ImageDraw.Draw(metal)
for x in range(0,SIZE,32):line(d,[(x,0),(x,SIZE)],(176,176,165),1)
for y in [80,520,940]:line(d,[(0,y),(SIZE,y)],(130,132,125),1)
save('g5_metal',metal)
dark=canvas((16,18,21),0.7);save('g5_dark',dark)

# Subtle tangent-space relief derived from each material's paint/panel detail.
for name,im in [('body',body),('wing',wing),('panels',panels),('metal',metal),('dark',dark)]:
    h=np.asarray(im.convert('L').filter(ImageFilter.GaussianBlur(0.7)),dtype=np.float32)/255
    dy,dx=np.gradient(h);n=np.stack((-dx*1.8,dy*1.8,np.ones_like(h)),axis=2)
    n/=np.linalg.norm(n,axis=2)[:,:,None]
    save_normal('g5_'+name+'_bp',Image.fromarray(np.uint8(np.clip((n+1)*127.5,0,255))))
    text='{material bump\n {diffuse "g5_'+name+'" {MipMap 1}}\n {bump "g5_'+name+'_bp"}\n {blend none}\n}\n'
    (DEST/('g5_'+name+'.mtl')).write_bytes(text.replace('\n','\r\n').encode('ascii'))
print('Created five TGA diffuse textures and five DXT5 normal maps with mipmaps.')
