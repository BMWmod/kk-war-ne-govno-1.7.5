"""Install Mirage 2000D gameplay integration; preserves existing text encodings.

350 purchase points (sc), 600-second recharge (c), NATO aviation (nrf_hqcar).
AIM-9L uses the stock weapon, ammunition, carrier and warhead.
Storm Shadow reuses the existing pointer/damage, with an independent neutral skin.
"""
from pathlib import Path
import re, shutil, io, struct, zipfile
from PIL import Image

ROOT=Path(__file__).resolve().parents[1]
WORK=ROOT/'_mirage_work'
PLANE=ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
STUFF=ROOT/'resource/set/stuff/air_stuff'
STORM=ROOT/'resource/entity/-inventory/air_stuff/nato/storm_nato'
for d in [PLANE,STORM]:d.mkdir(parents=True,exist_ok=True)
ref=WORK/'reference';ref.mkdir(parents=True,exist_ok=True)
base=ROOT.parent/'cold war 1_7_5/resource'
with zipfile.ZipFile(base/'set/stuff.pak') as z:
    for n in ['stuff/air_stuff/aim-9lx2.weapon','stuff/atgm/aim-9l_impactor']:
        (ref/Path(n).name).write_bytes(z.read(n))
with zipfile.ZipFile(base/'entity/-vehicle/-modern/vp_proj.pak') as z:
    (ref/'aim-9l_carrier.def').write_bytes(z.read('proj_2/sam_carrier/aim-9l_carrier.def'))

def enc(data):
    if data.startswith(b'\xef\xbb\xbf'):return 'utf-8-sig'
    try:data.decode('utf-8');return 'utf-8'
    except UnicodeDecodeError:return 'cp1251'
def read(p):return p.read_bytes().decode(enc(p.read_bytes())).replace('\r','')
def write(p,s):
    e=enc(p.read_bytes()) if p.exists() else 'cp1251'
    p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(s.replace('\r','').replace('\n','\r\n').encode(e))
def append(p,s,marker):
    old=read(p)
    if marker not in old:write(p,old.rstrip()+'\n\n'+s.strip()+'\n')
def insert(p,anchor,s,marker):
    old=read(p)
    if marker in old:return
    assert anchor in old,(p,anchor)
    write(p,old.replace(anchor,s+anchor,1))
def dds(im,p):
    levels=[];im=im.convert('RGB')
    while True:
        out=io.BytesIO();im.save(out,format='DDS',pixel_format='DXT1');levels.append(out.getvalue())
        if im.size==(1,1):break
        im=im.resize((max(1,im.width//2),max(1,im.height//2)),Image.Resampling.LANCZOS)
    h=bytearray(levels[0][:128]);struct.pack_into('<I',h,8,struct.unpack_from('<I',h,8)[0]|0x20000)
    struct.pack_into('<I',h,28,len(levels));struct.pack_into('<I',h,108,0x401008)
    p.write_bytes(h+b''.join(x[128:] for x in levels))

dds(Image.open(r'D:\m2000d\textures\hull_tex.png'),PLANE/'mirage_body.dds')
# Uniform technical material swatches; no Ukrainian decals or atlas dependency.
for n,c in [('mirage_glass',(47,61,67))]:
    dds(Image.new('RGB',(16,16),c),PLANE/(n+'.dds'))
if (WORK/'storm_nato_generated.png').exists():
    dds(Image.open(WORK/'storm_nato_generated.png').resize((1024,1024),Image.Resampling.LANCZOS),PLANE/'storm_nato.dds')
else:
    assert (PLANE/'storm_nato.dds').stat().st_size>10000,'Neutral Storm Shadow atlas is required'
texture_pak=next((base/'texture').rglob('vtp_aviation.pak'))
with zipfile.ZipFile(texture_pak) as z:
    (PLANE/'aim9l_surface.dds').write_bytes(z.read('a-10c/aim-9l.dds'))

for suffix,model in [('_x','mirage2000d.mdl'),('_xx','mirage2000d_xx.mdl')]:
    write(PLANE/('mirage2000d'+suffix+'.def'),'{game_entity\n {Extension "'+model+'"}\n}\n')
write(PLANE/'mirage2000d.def','''{game_entity
 (include "/properties/airborne_m.ext")
 {PatherID "airborne"}
 (include "/properties/shadow/airborn.inc" scale(1.0))
 (include "/properties/selection/airborne.inc" scale(2.5))
 (include "/properties/car_crew.ext")
 {props "airborne_M" "assault" "vision_lev_plane" "-IR_spo"}
 {Extension "mirage2000d.mdl"}
 ("missile_aimpoint_air")
 {mass 13500}
 {armor
  ("air_armor" body(3) wing(3) avionics(3) engine(3) hydrosystem(3) electronics(3) fuel(3))
 }
 {extender "inventory" {box {clear} {size 6 10}}}
 {Weaponry
  {place "ptur4"
   {weapon "storm_shadowx1" filled}
   {foresight "foresight_storm"}
   {shooter "storm_pointer_"}
   {charger "driver1"} {gunner "driver1"}
   {barrels 1} {basic}
  }
  {place "ptur1"
   {weapon "aim-9lx2" filled}
   {foresight "foresight_aam"}
   {shooter "aam_pointer_"}
   {charger "driver"} {gunner "driver"}
   {barrels 2} {basic}
  }
  {place "flare_dropper"
   {weapon "flare_dropper_64" filled}
   {foresight "foresight_flare_1"}
   {charger "driver"} {gunner "driver"}
  }
 }
 ("Chassis_parameters"
  Speed(90) TurnRadius(34)
  Fuel(4000) Fuel_remain(3100) Fuel_rate(2.4)
  Acc_hor(6.2) Maneuvrability_hor(6.1)
  Acc_ver(5.8) Maneuvrability_ver(5.2)
 )
 {props "cwfs_fuel_4000"}
 {Sensor
  {Visor "radarX" {vision "aircraft_radarX_100km"} {bone "visor_radarx"}}
  {Visor "visor_OLS" {vision "aircraft_optic_IR_2g"} {bone "visor_ols"}}
 }
 {boarder
  {anm "driver"
   {forward {begin "board_plane_left"} {end "seat_driver_car"} {base "driver_open"}}
   {reverse {end "board_plane_left" -1} {base "driver_open" -1}}
  }
  {anm "driver1"
   {forward {begin "board_plane_left"} {end "seat_driver_car"} {base "driver_open"}}
   {reverse {end "board_plane_left" -1} {base "driver_open" -1}}
  }
 }
 ("crew_human" place(driver) bone(driver) door(emit1) animation(driver))
 ("crew_human" place(driver1) bone(driver1) door(emit2) animation(driver1))
 {Placer
  {place "driver" {turnOff {sensor} {shadow} {targetable}}}
  {place "driver1" {turnOff {sensor} {shadow} {targetable}}}
 }
 (mod "mp"
  {Chassis "airborne" {Altitude 25}}
  {ChassisManager {Current "airborne"}}
 )
 {bone "foresight_flare_1" {speed 1}}
 {bone "foresight_flare_1a" {speed 1}}
}
''')

# Neutral Storm Shadow: its flying model is independent of the hidden pylon bone.
src=ROOT/'resource/entity/-inventory/air_stuff/ukr/storm_shadow'
for n in ['body.ply','wingl1.ply','wingr1.ply','on_start.anm']:
    shutil.copyfile(src/n,STORM/n)
shutil.copyfile(PLANE/'storm_nato.dds',STORM/'storm_nato.dds')
write(STORM/'storm_shadow.mtl','{material simple\n {diffuse "storm_nato" {MipMap 1}}\n {blend none}\n}\n')
flight=read(src/'storm_shadow.mdl')
factor=5.1/.06/(50.3470458984375+50.49620056152344)
flight=flight.replace('1\t0\t0\n\t\t\t0\t-1\t0\n\t\t\t0\t0\t1',f'{factor:.9f}\t0\t0\n\t\t\t0\t{-factor:.9f}\t0\n\t\t\t0\t0\t{factor:.9f}',1)
write(STORM/'storm_nato.mdl',flight)
for suffix in ['','_impactor','_impactor_link']:
    s=read(src/('storm_shadow'+suffix+'.def')).replace('"storm_shadow.mdl"','"storm_nato.mdl"')
    write(STORM/('storm_nato'+suffix+'.def'),s)
carrier=ROOT/'resource/entity/-vehicle/-modern/proj_2/agm_carrier'
write(carrier/'storm_nato_carrier.def',read(carrier/'storm_shadow_carrier.def').replace('storm_shadow_impactor_link','storm_nato_impactor_link'))
weapon=read(STUFF/'storm_shadowx2.weapon').replace('"ammo storm_shadow" 2','"ammo storm_shadow" 1').replace('{fillingVisible "storm_shadow"}','{fillingVisible "storm_nato00"}').replace('"Foresight7"','"foresight_storm"')
write(STUFF/'storm_shadowx1.weapon',weapon)

# Air-to-air armament uses the stock aim-9lx2 weapon and aim-9l carrier.

air=ROOT/'resource/set/interaction_entity/Airborne_modern.inc'
append(air,'''{"mirage2000d"
 {on spawn
  {add_view "flash_cannon_big" "storm_shooter_00" "storm_shooter_00"}
  {add_view "flash_cannon_big" "aam_shooter_00" "aam_shooter_00"}
  {add_view "flash_cannon_big" "aam_shooter_01" "aam_shooter_01"}
  ("link_damage_sound_usa")
 }
 {on "link_engine_effects" overload
  {add_view "airstream_exhaust" "engine_exhaust" "engine_exhaust"}
  {add_view "overburn" "engine_overburn" "engine_exhaust"}
 }
 ("air_compact_launcher" weapon(ptur4) foresight(storm_release) missile(storm_nato) flashbarrel(storm_shooter_00))
 ("air_multibarrel_launcher" weapon(ptur1) shooter(aam_shooter_) missile(aim-9l) flashbarrel(aam_shooter_))
 {on "update_weaponry"
  {if not tagged "destroyed"
   {weapon_work "flare_dropper" 1}
   {if not work "flares1"
    {if not work "flares2" {weapon_work "flare_dropper" 0}}
   }
   {if not work "electronics" {weapon_work "flare_dropper" 0}}
  }
 }
 {on "u_w_electronics_damaged"
  {weapon_work "ptur4" 0}
  {weapon_work "ptur1" 0}
 }
 {on "_burn" overload
  {damage_report "engine" "component/burn_fire"}
  {if not burned ("burn_engine" engine(1) engine1(0) engine2(0) enginea(0) engineb(0) enginec(0) engined(0))}
 }
}''','"mirage2000d"')
ms2=ROOT/'resource/set/interaction_entity/missile_settings2.inc'
append(ms2,'''{("CWPS_proj_3stage" missilename(storm_nato) rotation(0) rand_move(0) smoke_vulnerable(0) decoyprob(0) range80plus(40) tail(proj_jet_main) eng_time(3))
 {on "launch_procedures"
  {delay 0.1 {if not tagged "cwps_not_first_stage" {with_linked_entity "missile" {ani_play "on_start"}}}}
  ; The rangefinder extends back into the launch aircraft's guidance marker.
  ; Arm it after separation; later stages are already clear of the aircraft.
  {volumes "rangefinder1" disable overlap}
  {delay 0.1
   {if tagged "cwps_not_first_stage"
    {tags add "storm_launch_clear"}
    {volumes "rangefinder1" enable overlap}
    else
    {delay 0.9
     {tags add "storm_launch_clear"}
     {volumes "rangefinder1" enable overlap}
    }
   }
  }
 }
 {on "top_attack"
  {if tagged "storm_launch_clear" {delay 0.9 {call "detonate"}}}
 }
 {on contact overload
  {if tagged "storm_launch_clear" {inherited}
   else
   {if effector "airborne"
    else effector "proj_point"
    else {inherited}
   }
  }
 }
 {on "destroyed_by_kaz" overload}
}
''','missilename(storm_nato)')
units=ROOT/'resource/set/multiplayer/units/nz_nato.set'
insert(units,'{"tornado_gr4_antirad"','{"mirage2000d" ("air_nation" c(600) sc(350) brig(nrf) t(all_nz aircraft nobot support_frontline) s(nato) n(2) crew_nation(fr) g(air_mirage) b(nrf_hqcar) i(6) cw(0) cp(50)) {fore 0}}\n','"mirage2000d"')
p=ROOT/'resource/set/registry/unit.reg';s=read(p)
if '"mirage2000d"' not in s:write(p,s.replace('{units','{units\n {"mirage2000d" {structure "cwds_plane_attack"}}',1))
append(ROOT/'localization/1.rus/cw/cw_rus_veh.inc','{"mirage2000d" "<c(FFFFFF)e(shadow)>Mirage 2000D</c>"}','"mirage2000d"')
append(ROOT/'localization/1.rus/cw/cw_rus_squads.inc','{"mirage2000d" "<c(FFFFFF)e(shadow)>Mirage 2000D</c>"}','"mirage2000d"')
append(ROOT/'localization/1.rus/cw/kk_war_speciality.inc','{"mirage2000d" "<c(FFFF00)>Тактический ударный самолёт</c>"}','"mirage2000d"')
ammo=ROOT/'localization/1.rus/custom/custom_rus_ammo_weapon_stuff.inc'
# This include contains separate weapon and ammo maps; insert alongside equivalent existing keys.
s=read(ammo)
for anchor,line,marker in [('"storm_shadowx2"','{"storm_shadowx1" "Storm Shadow / SCALP-EG"}','"storm_shadowx1"')]:
    if marker not in s:
        idx=s.index(anchor);idx=s.rfind('{',0,idx);s=s[:idx]+line+'\n\t\t'+s[idx:]
write(ammo,s)
p=ROOT/'localization/info.lng';s=read(p)
if '"mirage2000d"' not in s:
    anchor='{"mv22"';idx=s.index(anchor)
    desc='{"mirage2000d" "Mirage 2000D — французский двухместный тактический ударный самолёт. Вооружение: одна крылатая ракета Storm Shadow / SCALP-EG для поражения наземных целей и две УРВВ AIM-9L Sidewinder с ИК-наведением для самообороны.\\n\\nЭкипаж: пилот и оператор вооружения. 64 тепловые ловушки. Встроенная пушка отсутствует. Игровая скорость: 90; дальность пуска Storm Shadow: 650 м. Стоимость: 350 очков."}\n'
    s=s[:idx]+desc+s[idx:];write(p,s)
print('Installed Mirage 2000D: NATO aviation, 350 points, 2 AIM-9L + 1 Storm Shadow.')
