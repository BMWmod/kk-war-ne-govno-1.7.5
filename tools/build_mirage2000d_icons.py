"""Create the eight unit icon states from the exported-model render."""
from pathlib import Path
from PIL import Image, ImageEnhance, ImageOps
ROOT=Path(__file__).resolve().parents[1]
source=Image.open(ROOT/'_mirage_work/mirage_icon.png').convert('RGBA')
source=source.crop(source.getchannel('A').getbbox())
for folder,size in [('unit_icon',(104,52)),('unit_icon_small',(78,39))]:
    dest=ROOT/'resource/interface/scene'/folder;dest.mkdir(parents=True,exist_ok=True)
    resized=ImageOps.contain(source,(size[0]-4,size[1]-4),Image.Resampling.LANCZOS)
    for state,brightness in enumerate([1.1,1.35,.8,.45]):
        canvas=Image.new('RGBA',size)
        colored=ImageEnhance.Brightness(resized).enhance(brightness)
        colored.putalpha(resized.getchannel('A'))
        canvas.alpha_composite(colored,((size[0]-colored.width)//2,(size[1]-colored.height)//2))
        p=dest/f'mirage2000d_{state:02}.tga';canvas.save(p,format='TGA')
        assert p.read_bytes()[2]==2
print('Created eight Mirage 2000D unit icons.')
