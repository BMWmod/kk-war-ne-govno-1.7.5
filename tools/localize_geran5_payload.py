"""Keep Su-25 payload meshes and their materials in the carrier's asset folder.

GEM's runtime VolumeView loader cannot be treated like Gemwerk's filesystem
resolver: avoid parent-directory paths in the carrier's payload views.
"""
from pathlib import Path
import shutil

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/su-25sm_part1'
PARTS=('body','panels','wingl1','wingr1','tail','engine','booster')

def copy_payload(destination):
    destination=Path(destination)
    destination.mkdir(parents=True,exist_ok=True)
    for part in PARTS:
        shutil.copy2(SOURCE/(part+'.ply'),destination/('g5_payload_'+part+'.ply'))
    # Both carriers share the same global atlas; local texture copies are unused.
    shutil.copy2(SOURCE/'g5_atlas.mtl',destination/'g5_atlas.mtl')

def install():
    copy_payload(DEST)
    path=DEST/'su-25sm_geran5.mdl'
    data=path.read_bytes()
    for part in PARTS:
        data=data.replace(('../geran5/'+part+'.ply').encode('ascii'),('g5_payload_'+part+'.ply').encode('ascii'))
    assert b'../geran5/' not in data
    path.write_bytes(data)
    print('Carrier payload: 7 local meshes, 1 material, 1 shared atlas; no parent-directory VolumeView references.')

if __name__=='__main__':install()
