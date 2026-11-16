"""Install NSO Krug: native cannon deployment and external CWPS illumination."""
from pathlib import Path
import re, shutil, io, struct
from PIL import Image

ROOT=Path(__file__).resolve().parents[1]
DEST=ROOT/'resource/entity/-vehicle/-modern/tank_modern/irg/2k11_krug'
REF=ROOT/'_krug_work/reference'
STUFF=ROOT/'resource/set/stuff/atgm'
SOURCE=Path(r'C:\Users\Vsevoloden\Desktop\2k11m3_krug')

def encoding(data):
    if data.startswith(b'\xef\xbb\xbf'):return 'utf-8-sig'
    try:data.decode('utf-8');return 'utf-8'
    except UnicodeDecodeError:return 'cp1251'
def read(p):return p.read_bytes().decode(encoding(p.read_bytes())).replace('\r','')
def write(p,s):
    enc=encoding(p.read_bytes()) if p.exists() else 'cp1251'
    p.parent.mkdir(parents=True,exist_ok=True)
    data=s.replace('\r','').replace('\n','\r\n').encode(enc)
    if p.exists() and p.read_bytes()==data:return
    if p.exists() and not str(p).startswith(str(DEST)):
        bak=ROOT/'_krug_work/backups'/p.relative_to(ROOT);bak.parent.mkdir(parents=True,exist_ok=True)
        if not bak.exists():shutil.copy2(p,bak)
    p.write_bytes(data)
def append(p,s,marker):
    old=read(p)
    if marker not in old:write(p,old.rstrip()+'\n\n'+s.strip()+'\n')
def insert(p,anchor,s,marker):
    old=read(p)
    if marker in old:return
    assert anchor in old,(p,anchor)
    write(p,old.replace(anchor,s+anchor,1))

def drop_block(s,header):
    start=s.index(header);depth=0;quoted=False
    for i in range(start,len(s)):
        c=s[i]
        if c=='"':quoted=not quoted
        if not quoted:
            if c=='{':depth+=1
            elif c=='}':
                depth-=1
                if not depth:return s[:start]+s[i+1:]
    raise ValueError(header)

def dds(source,dest,maxsize):
    im=Image.open(source).convert('RGB');im.thumbnail((maxsize,maxsize),Image.Resampling.LANCZOS)
    levels=[]
    while True:
        out=io.BytesIO();im.save(out,format='DDS',pixel_format='DXT1');levels.append(out.getvalue())
        if im.size==(1,1):break
        im=im.resize((max(1,im.width//2),max(1,im.height//2)),Image.Resampling.LANCZOS)
    h=bytearray(levels[0][:128]);struct.pack_into('<I',h,8,struct.unpack_from('<I',h,8)[0]|0x20000)
    struct.pack_into('<I',h,28,len(levels));struct.pack_into('<I',h,108,0x401008)
    dest.write_bytes(h+b''.join(x[128:] for x in levels))
for src,dst,size in [('2k11_krug.dds','krug_body.dds',2048),('3m8_missile.dds','krug_missile.dds',1024),('tracks.dds','krug_tracks.dds',512)]:
    dds(SOURCE/src,DEST/dst,size)

definition=read(REF/'buk_m1.def')
definition=definition.replace('"sam_radar" "buk_launcher"','"2k11_krug"')
definition=definition.replace('turret(7 7 7 7) body(7 7 7 7)','turret(10 10 10 10) body(15 15 8 15)')
definition=definition.replace('"9m38 buk ammo" 4','"3m8_krug_rocket ammo" 2')
definition=definition.replace('"buk_launcher" filling','"3m8_krug_x2" filling')
definition=definition.replace('{Barrels 4}','{Barrels 2}')
definition=definition.replace('{mass 32400}','{mass 28000}').replace('Mass(32.4)','Mass(28)').replace('Width(3.25)','Width(3.6)')
definition=definition.replace('Power(750)','Power(400)').replace('Realspeed(65)','Realspeed(50)').replace('Gamespeed(41)','Gamespeed(35)')
definition=definition.replace('Range(500) Fuelvolume(990)','Range(350) Fuelvolume(800)')
definition=definition.replace('"buk_m1.mdl"','"2k11_krug.mdl"')
definition=definition.replace('{limits -30 30}','{limits -180 180}')
definition=drop_block(definition,'{place "radar"')
definition=drop_block(definition,'{Visor "visor_radar"')
definition=drop_block(definition,'{bone "visor1"')
definition=drop_block(definition,'{bone "radar_foresight_rot"')
definition=definition.replace('("sam_radar" type(rus_large))','')
definition=definition.replace('visor(visor_radar)','visor(passive)')
definition=definition.replace('"vertical_antimissile"','"vertical_antimissile_side"')
# Replace the donor's entire boarding section. Do not use partially supplied
# crew_human macros or leave duplicate links for the cannon's alternate seats.
crew_start=definition.index('\t{boarder')
crew_end=definition.index('\t{extender "inventory"',crew_start)
definition=definition[:crew_start]+'\t{extension "krug_crew.ext"}\n\n'+definition[crew_end:]
deployment='''    {extender "cannon"
        {animation {move "" ""} {reload "" ""} {aim "" ""}}
        {animation {switch krug_close}}
        {move {workers "gunner_travel" "charger_travel"}}
        {attack {workers "gunner" "charger"}}
        {rotate_ik_Limit 0}
    }
'''
definition=definition.replace('\t{extender "inventory"',deployment+'\n\t{extender "inventory"',1)
definition=definition.replace('{charger "gunner"}', '{charger "charger"}')
definition=definition.replace('{RestoreIKAfterAim}\n\t\t}', '{RestoreIKAfterAim}\n            {StationaryFiring}\n\t\t}')
write(DEST/'2k11_krug.def',definition)
for suffix,mdl in [('_x','2k11_krug.mdl'),('_xx','2k11_krug_xx.mdl')]:
    write(DEST/('2k11_krug'+suffix+'.def'),'{game_entity\n {Extension "'+mdl+'"}\n}\n')

write(STUFF/'3m8_krug_x2.weapon','''{from "pattern proj_weapon"
 {tag "gun"}
 {filling "ammo 3m8_krug_rocket" 2}
 {fillingVisible "rocket"}
 {fireSound "bazooka/kub_Launch"}
 {mass 50}
 {recoveryTime 14}
 {rechargeTime 200}
 {AimingTolerance 0.5}
 {inventory {noView}}
 {maxRange 380}
 {aimRange 360}
 {cursor "cannon_on_aa"}
 {cursorReloading "cannon_reload_fg"}
}
''')
ammo=read(STUFF/'9m38.buk.ammo').replace('"9m38"','"3m8_krug_ammo"').replace('{mass 690}','{mass 2450}')
# Preserve the donor's target tags. The old Kub omission is not propagated.
write(STUFF/'3m8_krug_rocket.ammo',ammo)
# The launcher has no illuminator. 3M8 uses the same rus/radpassive markers
# produced by 1S91 and compatible Soviet illumination radars.
write(DEST/'3m8_krug_ammo.def','''{game_entity
 (include "/properties/Projectile_ammo.ext")
 (include "/properties/shadow/round.inc")
 {collider "ammo"}
 {extender "stuff" {item "3m8_krug_rocket ammo"}}
 {Extension "3m8_krug.mdl"}
}
''')
write(DEST/'3m8_krug_impactor.def','''{actor
 (include "/properties/projectile_impactor.ext")
 {Extension "3m8_krug.mdl"}
 {props "projectile_impactor"}
 {extender "stuff" {item "3m8_krug_impactor"}}
 {volume "body" {able {contact} {bullet} {blast} {contact_ground}}}
}
''')
write(STUFF/'3m8_krug_impactor','''{from "pattern proj_impactor"
 {entity "3m8_krug_impactor"}
 {inventory {weight 100} {size 7 1}}
 {tag "big" "size4" "88to105" "AA_missile" "-ap" "-rocketlauncher" "-low_speed" "fx_111_145"}
 {damage blastwave {energy 0.7} {area 20 23}}
 {damage add blastwave {energy 1.2} {area 17 20}}
 {damage add blastwave {energy 2.5} {area 11 13}}
 {damage add blastwave {energy 6.5} {area 8.5 10}}
 {damage add blastwave {energy 12} {area 4.5 5.2}}
}
''')
carrier=read(REF/'9m38_carrier.def').replace('9m38_impactor','3m8_krug_impactor').replace('deg_per_s(25)','deg_per_s(18)')
write(ROOT/'resource/entity/-vehicle/-modern/proj_2/sam_carrier/3m8_krug_carrier.def',carrier)

p=ROOT/'resource/set/interaction_entity/missile_settings2.inc'
insert(p,'\t       else stuff "9m38 buk ammo"','''           else stuff "3m8_krug_rocket ammo"
            {if tagged "shooter00" {with_effector {delay 0.03 {spawn "3m8_krug_carrier" "shooter00" x}} {with_effector}}
             else tagged "shooter01" {with_effector {delay 0.03 {spawn "3m8_krug_carrier" "shooter01" x}} {with_effector}}
            }
''','else stuff "3m8_krug_rocket ammo"')
insert(p,'{("CWPS_proj" missilename(3m9_kub)',
       '{("CWPS_proj" missilename(3m8_krug) rotation(0) rand_move(0) smoke_vulnerable(0) decoyprob(0.48) range(40) tail(proj_jet_sam) eng_time(4))("speed_fast" coeff(0.90)) ("antislip")}\n',
       'missilename(3m8_krug)')
append(ROOT/'resource/set/registry/unit.reg','{"2k11_krug" {structure "cwds_sam"}}','"2k11_krug"')
append(ROOT/'resource/set/interaction_entity/custom1.inc','''{"2k11_krug"
    ("Shilka_sound")
    ("custom_sh_multi_launcher" weapon(gun2) foresight(foresight1) tail(tail) shooter(shooter))
    ; No radar_params/sam_radar: this launcher consumes external illumination.
}
''','{"2k11_krug"')
insert(ROOT/'resource/set/resupply_generic.inc','\t{item "3m9_kub_rocket ammo"',
       '\t{item "3m8_krug_rocket ammo" 1 {max 2}{value 35}}\n','"3m8_krug_rocket ammo"')
append(ROOT/'resource/set/multiplayer/units/nz_units.set','''; NSO medium-range SAM; Shift-Q deployment, external radar illumination.
{"2k11_krug" {fore 0} ("v" c(600) sc(240) g(pvo_krug) b(supl) brig(common) s(srbsk) i(67825) cw(0) cp(20) t(all_nz aat antiair support_frontline) n(4))}
''','"2k11_krug"')
units_path=ROOT/'resource/set/multiplayer/units/nz_units.set'
units=read(units_path)
radar_line=next(l for l in units.splitlines() if l.lstrip().startswith('{"1s91_kub_radar"'))
new_radar_line=radar_line.replace('b(srbs_art_hqcar)','b(supl)').replace('brig(srbs_art)','brig(common)')
write(units_path,units.replace(radar_line,new_radar_line))
for filename in ['cw_rus_veh.inc','cw_rus_squads.inc']:
    append(ROOT/'localization/1.rus/cw'/filename,'{"2k11_krug" "<c(FFFFFF)e(shadow)>2К11 Круг</c>"}','"2k11_krug"')
append(ROOT/'localization/1.rus/cw/kk_war_speciality.inc',
       '{"2k11_krug" "<c(FFFF00)>Зенитный ракетный комплекс средней дальности</c>"}','"2k11_krug"')
description='2К11 <Круг> - гусеничный ЗРК с двумя ракетами 3М8. Собственной РЛС нет: для наведения нужна подсветка цели совместимым союзным радаром, например 1С91 <Куб>.\\n\\nShift-Q: развернуть / свернуть установку. В походном положении стрельба недоступна; перед движением установка складывается. Передняя транспортная рамка отводится отдельно от ракет.\\n\\nДальность пуска: 380 м. Два готовых пуска и две запасные ракеты. Интервал между пусками: 14 с; перезарядка: 200 с. Подсветку цели надо поддерживать во время полёта ракеты. Дальность подсветки зависит от выбранной РЛС. Пополнение: машины снабжения НСО.\\n\\nЭкипаж: 4 человека. Игровая скорость: 35. Стоимость: 240 очков.'
p=ROOT/'localization/info.lng';s=read(p)
if '"2k11_krug"' not in s:
    anchor='\t{"entity"\n';assert anchor in s
    write(p,s.replace(anchor,anchor+'{"2k11_krug" "'+description+'"}\n',1))
p=ROOT/'localization/1.rus/custom/custom_rus_ammo_weapon_stuff.inc'
s=read(p)
if '"3m8_krug_rocket"' not in s:
    s=s.replace('\t{"ammo"\n','\t{"ammo"\n\t\t{"3m8_krug_rocket" "ЗУР 3М8 для ЗРК «Круг»\\nДальность: 380 м. Наведение по работающей РЛС."}\n\t\t{"3m8_krug_impactor" "3М8: боевая часть"}\n',1)
    s=s.replace('\t{"weapon"\n','\t{"weapon"\n\t\t{"3m8_krug_x2" "2П24: две ЗУР 3М8"}\n',1);write(p,s)
print('Installed 2k11_krug: NSO support, 240 points, 380 m, 2+2 missiles, 14/200 s, Shift-Q deployment, external radar.')
