"""Turn the Blender render into the game's four icon states."""
from pathlib import Path
from PIL import Image, ImageEnhance

ROOT=Path(__file__).resolve().parents[1]
for unit,filename in [('geran5_base','geran5_icon.png'),('su-25sm_geran5','su25_icon.png')]:
    source=Image.open(ROOT/'tools/geran5_preview'/filename).convert('RGBA')
    for folder,size in [('unit_icon',(104,52)),('unit_icon_small',(78,39))]:
        dest=ROOT/'resource/interface/scene'/folder
        for state,brightness in enumerate([1,1.15,.8,.5]):
            icon=source.resize(size,Image.Resampling.LANCZOS)
            alpha=icon.getchannel('A')
            icon=ImageEnhance.Brightness(icon).enhance(brightness);icon.putalpha(alpha)
            path=dest/f'{unit}_{state:02}.tga'
            icon.save(path,format='TGA',compression=None)
            assert path.read_bytes()[2]==2
print('Created Geran-5 and Su-25 icon textures.')
