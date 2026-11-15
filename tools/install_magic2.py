"""Install Mirage-only Magic 2 armament using the working stock CWPS lifecycle.

Run build_magic2_model.py in Blender via MCP first. All numbers below are game
balance parameters. Existing AIM-9 weapons used by other aircraft are untouched.
"""
from pathlib import Path
import importlib, types, sys, re, json, shutil, zipfile
from PIL import Image

ROOT=Path(__file__).resolve().parents[1]
PLANE=ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
MISSILE=ROOT/'resource/entity/-vehicle/-modern/missile_modern/magic2'
STUFF=ROOT/'resource/set/stuff'
BASE=ROOT.parent/'cold war 1_7_5/resource'
BACKUP=ROOT/'_mirage_work/pre_magic2_working_aim9'

def read(path):
    b=path.read_bytes()
    if b.startswith(b'\xef\xbb\xbf'):return b.decode('utf-8-sig')
    try:return b.decode('utf-8')
    except UnicodeDecodeError:return b.decode('cp1251')

def write(path,text):
    encoding='utf-8'
    if path.exists():
        old=path.read_bytes()
        if old.startswith(b'\xef\xbb\xbf'):encoding='utf-8-sig'
        else:
            try:old.decode('utf-8')
            except UnicodeDecodeError:encoding='cp1251'
        relative=path.relative_to(ROOT);saved=BACKUP/relative
        if not saved.exists():saved.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(path,saved)
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_bytes(text.replace('\r','').replace('\n','\r\n').encode(encoding))

def model_module():
    package=types.ModuleType('magic_formats')
    package.__path__=[str(Path.home()/'AppData/Roaming/Blender Foundation/Blender/5.2/extensions/user_default/gemwerk_io/formats')]
    sys.modules[package.__name__]=package
    return importlib.import_module(package.__name__+'.mdl')

def apply_magic2_to_plane():
    md=model_module()
    for path in PLANE.glob('*.mdl'):
        saved=BACKUP/path.relative_to(ROOT)
        if not saved.exists():saved.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(path,saved)
        model=md.Model.read(str(path))
        assert not any(v.name=='select' for v in model.volumes),'Do not restore the enclosing collision box'
        for root in model.bones:
            for bone,parent in root.walk():
                if re.fullmatch(r'(aim_9l_|magic2_)\d\d',bone.name):
                    bone.name='magic2_'+bone.name[-2:]
                    if bone.views:bone.views=[md.VolumeView('magic2_pylon.ply')]
        model.write(str(path))

def main():
    assert (MISSILE/'magic2.mdl').exists() and (PLANE/'magic2_pylon.ply').exists(),'Build the model through Blender MCP first'
    stats=json.loads((ROOT/'tools/magic2_asset.json').read_text())
    for name,color in stats['materials']:
        for folder in [MISSILE,PLANE]:
            Image.new('RGBA',(4,4),tuple(round(c*255) for c in color)).save(folder/(name+'.dds'))
            write(folder/(name+'.mtl'),'{material simple\n {diffuse "'+name+'"}\n {blend none}\n}\n')
    write(MISSILE/'magic2_ammo.def','''{game_entity
 (include "/properties/stuff_small.ext")
 (include "/properties/shadow/round.inc")
 {collider "ammo"}
 {extender "stuff" {item "magic2_ammo ammo"}}
 {extension "magic2.mdl"}
}
''')
    write(MISSILE/'magic2_impactor.def','''{actor
 (include "/properties/projectile_impactor.ext")
 {extension "magic2.mdl"}
 {props "projectile_impactor"}
 {extender "stuff" {item "magic2_impactor"}}
 {volume "body" {able {contact} {bullet} {blast} {contact_ground}}}
}
''')
    write(STUFF/'air_stuff/magic2_ammo.ammo','''{from "pattern proj_pointer"
 {entity "magic2_ammo"}
 {mass 89}
 {inventory {weight 100} {size 6 1}}
 {tag "big" "size3" "88to105" "AA_missile_2gen" "-ap" "-rocketlauncher" "no_ricochet" "-low_speed"}
}
''')
    write(STUFF/'atgm/magic2_impactor','''{from "pattern proj_impactor"
 {entity "magic2_impactor"}
 {inventory {weight 100} {size 6 1}}
 {tag "big" "size3" "88to105" "AA_missile" "-ap" "-rocketlauncher" "-low_speed" "fx_111_145"}
 ; Game balance: denser damage close to the target, slightly smaller outer zone.
 {damage blastwave {energy 0.78} {area 12.6 14.5}}
 {damage add blastwave {energy 1.35} {area 10.8 12.4}}
 {damage add blastwave {energy 2.75} {area 5.4 6.2}}
 {damage add blastwave {energy 6.8} {area 1.35 1.55}}
}
''')
    write(STUFF/'air_stuff/magic2x2.weapon','''{from "pattern proj_weapon_air"
 {tag "gun"}
 {filling "ammo magic2_ammo" 2}
 {fillingVisible "magic2_"}
 {foresight "foresight_aam"}
 {fireSound "reactive/missile_small/"}
 {mass 50}
 {recoveryTime 2}
 {rechargeTime 145}
 {inventory {noView}}
 {maxRange 220}
 {aimRange 185}
 {cursor "cannon_on_aa"}
 {cursorReloading "cannon_reload_fg"}
}
''')
    carrier=read(ROOT/'_mirage_work/reference/aim-9l_carrier.def')
    carrier=carrier.replace('aim-9l_impactor','magic2_impactor').replace('calibre(127)','calibre(157)').replace('deg_per_s(53)','deg_per_s(62)')
    write(ROOT/'resource/entity/-vehicle/-modern/proj_2/sam_carrier/magic2_carrier.def',carrier)
    settings=ROOT/'resource/set/interaction_entity/missile_settings2.inc';s=read(settings)
    if 'missilename(magic2)' not in s:
        s+='\n; Mirage Magic 2: stock AIM-9 lifecycle, independent game balance.\n{("CWPS_proj" missilename(magic2) rotation(0) rand_move(0) smoke_vulnerable(1) decoyprob(0.13) range(19) tail(proj_jet_sam) eng_time(3)) ("speed_fast" coeff(0.90)) ("antislip")}\n'
    write(settings,s)
    pointer=ROOT/'resource/set/interaction_entity/missile_settings1.inc';s=read(pointer)
    if 'stuff "magic2_ammo ammo"' not in s:
        anchor='else stuff "aim-9l_ammo ammo"';assert anchor in s
        s=s.replace(anchor,'else stuff "magic2_ammo ammo"\n ("spawn_proj_7" country(usa) type(ir) weapon_tag(magic2_target) decoytype(flare) decoyprob(0.07) min_alt(4))\n\t'+anchor,1)
    write(pointer,s)
    definition=PLANE/'mirage2000d.def';write(definition,read(definition).replace('{weapon "aim-9lx2" filled}','{weapon "magic2x2" filled}'))
    air=ROOT/'resource/set/interaction_entity/Airborne_modern.inc';s=read(air)
    start=s.index('{"mirage2000d"');s=s[:start]+s[start:].replace('missile(aim-9l)','missile(magic2)')
    write(air,s)
    supply=ROOT/'resource/set/resupply_generic.inc';s=read(supply)
    for name in ['air_stuff_usa','air_stuff_nato']:
        anchor='(define "'+name+'"';assert anchor in s
        segment=s.split(anchor,1)[1].split('(define ',1)[0]
        if 'magic2_ammo' not in segment:s=s.replace(anchor,anchor+'\n {item "magic2_ammo ammo" 2 {max 4}{value 7}}',1)
    write(supply,s)
    loc=ROOT/'localization/1.rus/custom/custom_rus_ammo_weapon_stuff.inc';s=read(loc)
    for group,key,label in [('ammo','magic2_ammo','Matra R.550 Magic 2'),('weapon','magic2x2','Matra Magic 2 x2')]:
        if '"'+key+'"' not in s:
            anchor='{"'+group+'"';assert anchor in s
            s=s.replace(anchor,anchor+'\n\t\t{"'+key+'" "'+label+'"}',1)
    write(loc,s)
    info=ROOT/'localization/info.lng';s=read(info)
    s=re.sub(r'(\{"mirage2000d"[^\r\n]*)',lambda m:m[0].replace('AIM-9L Sidewinder','Matra Magic 2'),s)
    write(info,s)
    apply_magic2_to_plane()
    print('Installed: 2 Magic 2 + Storm Shadow; NATO aviation resupply; original AIM-9 definitions unchanged.')

if __name__=='__main__':main()
