"""Stage the existing Su-25 assets for Gemwerk without overriding the original aircraft."""
from pathlib import Path
import sys,zipfile,os,re,shutil
sys.dont_write_bytecode=True
from build_an196_config import ROOT,BASE

TEMP=ROOT/'tools/geran5_preview/su25'
TEMP.mkdir(parents=True,exist_ok=True)
with zipfile.ZipFile(BASE/'entity/-vehicle/-modern/air_modern.pak') as archive:
    for entry in archive.infolist():
        if entry.filename.lower().startswith('air_modern/rus/su-25sm_part1/') and not entry.is_dir():
            (TEMP/Path(entry.filename).name).write_bytes(archive.read(entry))
(TEMP/'textures').mkdir(exist_ok=True)
with zipfile.ZipFile(BASE/'texture/common/model/vtp_aviation.pak') as archive:
    for entry in archive.infolist():
        if entry.filename.lower().startswith('su-25sm/') and not entry.is_dir():
            (TEMP/'textures'/Path(entry.filename).name).write_bytes(archive.read(entry))
for path in TEMP.glob('*.mtl'):
    text=path.read_bytes().decode('cp1251')
    text=re.sub(r'\$/model/Su-25sm/', 'textures/', text, flags=re.I)
    path.write_bytes(text.encode('cp1251'))
g5=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
(TEMP.parent/'geran5').mkdir(exist_ok=True)
for path in g5.iterdir():
    if path.suffix in ['.ply','.mtl','.tga']:shutil.copy2(path,TEMP.parent/'geran5'/path.name)
print(TEMP)
