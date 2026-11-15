"""Install the uncrewed IDF Harpy PRR into the working mod."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
from build_an196_config import ROOT, read, write, block_at, named_block, append_once

DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/harpy'
STUFF=ROOT/'resource/set/stuff/air_stuff'
INTER=ROOT/'resource/set/interaction_entity'

def install():
    s=read(ROOT/'resource/entity/-vehicle/-modern/air_modern/ir/shahed136/shahed136_base.def')
    s=s.replace('shahed136_base','harpy_prr').replace('shahed136','harpy')
    s=s.replace('{props "ecm_vulnerable_rus"}','; Passive seeker: no remote command-link controller.')
    s=s.replace('{targetSelector "cannon_bullet"}','{targetSelector "missile_antirad"}')
    s=s.replace('"harpy_mark" filling "harpy_ammo ammo" 1','"harpy_prr_mark" filling "harpy_prr_seeker ammo" 1')
    start=s.index('{place "straight"');s=s[:start]+s[start:].replace(block_at(s,start),'',1)
    # Keep Shahed's hold-fire default: the player commits the one-way attack.
    s=s.replace('{Altitude 4}','{Altitude 25}')
    start=s.index('{Sensor');s=s.replace(block_at(s,start),'''{Sensor
 {Visor "harpy_passive" {vision "harm_passive_radar"} {bone "visor_ols"}}
}''',1)
    write(DEST/'harpy_prr.def',s)
    write(STUFF/'harpy_prr_seeker.ammo','''{from "pattern proj_pointer"
 {entity "harpy_prr_ammo"}
 {inventory {weight 100} {size 6 2}}
 {tag "no_ricochet" "fg" "big" "size4" "88to105" "missile_antirad_usa"}
}
''')
    write(STUFF/'harpy_prr_mark.weapon','''{from "pattern proj_weapon_air"
 {tag "gun"}
 {filling "ammo harpy_prr_seeker" 1}
 {preloaded}
 {ammoLocked}
 {Automatic}
 {foresight "Foresight8"}
 {mass 1}
 {recoveryTime 1}
 {rechargeTime 9999}
 {inventory {noView}}
 {maxRange 350}
 {aimRange 350}
 {AimingTolerance 2}
 {cursor "antiradar"}
 {spreading 4
		{SpreadRadius 4}
		{radiusTable 
			{0 10000}
		}
		{SpreadXYRatio	2.0}
		{SpreadPower	0.1}
	}
}
''')
    write(DEST/'harpy_prr_ammo.def','''{Game_entity
 (include "/properties/Projectile_ammo.ext")
 {Extension "harpy_ammo.mdl"}
 {extender "stuff" {item "harpy_prr_seeker ammo"}}
}
''')
    warhead='''{from "pattern proj_impactor"
 {entity "harpy_prr_impactor"}
 {inventory {weight 100} {size 6 2}}
 {tag "no_ricochet" "fg" "big" "size4" "88to105" "ptrk" "fx_upto50kg" "he_over30"}
 {damage blastwave {energy 0.7} {area 14 16.1}}
 {damage add blastwave {energy 1.2} {area 11.9 13.7}}
 {damage add blastwave {energy 2.5} {area 7 8}}
 {damage add blastwave {energy 6.5} {area 2.6 3}}
 {damage add blastwave {energy 16} {area 1 1.5}}
}
'''
    write(STUFF/'harpy_prr_impactor',warhead)
    write(STUFF/'harpy_prr_impactor_direct_hit.fg.ammo',warhead)
    impactor='''{actor
 (include "/properties/projectile_impactor.ext")
 {Extension "harpy_ammo.mdl"}
 {props "projectile_impactor" "propfan"}
 {extender "stuff" {item "harpy_prr_impactor"}}
 {volume "body" {able {contact} {bullet} {blast} {contact_ground}}}
 %TARGET%
}
'''
    write(DEST/'harpy_prr_impactor.def',impactor.replace('%TARGET%','; Terminal entity: targetable macro would interrupt detonation.'))
    write(DEST/'harpy_prr_impactor_link.def',impactor.replace('%TARGET%','("targetable_impactor_antirad")'))
    write(ROOT/'resource/entity/-vehicle/-modern/proj_2/atgm_carrier/harpy_prr_carrier.def','''{actor
 (include "/properties/projectile.ext")
 {Extension "atgm_carrier_forward.mdl"}
 ("missile_placer" missile("harpy_prr_impactor_link") country(usa) type(antirad) calibre(250) speed(slow) guidance(prop))
 ("maneuvrability_cwps3" deg_per_s(27))
 {sensor
  {Visor "htc-pod" {vision "harm_passive_radar"} {bone "missle_foresight"}}
 }
 ("missile_antirad" country(usa) type(antirad))
 ("targetable_missile")
}
''')
    air='''; Harpy PRR: player-directed launch, followed by USA antiradar homing.
{"harpy"
 {on spawn
  {weapon_work "mark" 0}
 }
 {on "takeoff" {weapon_work "mark" 1}}
 {on "specability" overload}
 {on "add_movement_sound" overload
  {link_sound "engine_start" "vehicle/airborne/small_uav/shahed136_start"}
  {link_sound "engine_work" "vehicle/airborne/small_uav/shahed136_engine"}
  {link_sound "engine_stop" "vehicle/airborne/small_uav/shahed136_engine_end"}
 }
 {on "link_flare_fx" overload}
 {on "engine_on"
  {if not "engine_started"
   {set "engine_started" 1}
   {play_sound "engine_start"}
   {ani_play "engine_start" callback}
  }
 }
 {on animation_end "engine_start"
  {ani_play "engine_work" loop}
  {play_sound "engine_work" 1}
 }
 ("loitering_munition" missilename(harpy_prr))
 {on "detonate" overload {inherited} {stuff_detonate}}
 {on "underground_detonate" overload {inherited} {stuff_detonate}}
}
'''
    air_path=INTER/'Airborne_modern.inc'
    existing=read(air_path)
    if 'missilename(harpy_prr)' in existing:
        write(air_path,existing.replace(named_block(existing,'harpy'),named_block(air,'harpy'),1))
    else:
        append_once(air_path,air,'missilename(harpy_prr)')
    link=named_block(read(INTER/'Missile_M.inc'),'shahed136_base_impactor_link')
    link=link.replace('"shahed136_base_impactor_link"','"harpy_prr_impactor_link"')
    append_once(INTER/'Missile_M.inc',link,'"harpy_prr_impactor_link"')
    append_once(INTER/'missile_settings2.inc','''{("CWPS_proj_2stage" missilename(harpy_prr) rotation(0) rand_move(0) smoke_vulnerable(0) decoyprob(0) range40plus(21) tail(none) eng_time(1))}
; Specialize the base carrier in a more specific selector: events from the macro
; cannot be defined twice inside the same interaction block, even with overload.
{"harpy_prr_carrier antirad"
 ; Match AGM-88's flight budget, retaining the UAV's slow flight speed.
 {on "link_effects" overload
  {tags add "cwps_extended_range"}
  {delay 0.1 {with_linked_entity "missile" {ani_play "move" loop}}}
 }
 ; A slow UAV must reach the target, not detonate on AGM-88's 0.7 s proximity timer.
 {on "top_attack" overload}
 ; No rocket booster or wing-deployment animation on the second flight segment.
 {on "spawn_second_stage" overload
  {spawn "harpy_prr_carrier" "missile_point" x
   {tags add "cwps_not_first_stage"}
   {delay 0.1 {tags remove "cwps_extended_range"}}
   {delay 0.2 {tags remove "cwps_extended_range"}}
   {delay 0.3 {tags remove "cwps_extended_range"}}
  }
  {with_linked_entity "missile" {delete}}
  {delete}
 }
}
{"harpy_prr_impactor"
 {on "detonate" overload
  {if altitude 0
   {spawn "proj_restrictor" "root" x}
   {delay 0.05 {stuff_detonate}}
   else
   {gravity 0}
   {impulse up 2}
   {call "underground_detonate"}
  }
 }
}
''','missilename(harpy_prr)')
    append_once(ROOT/'resource/set/multiplayer/units/nz_usa.set','''; IDF one-way antiradar UAV: four launches cost 240 vs F-16C PRR 250.
{"harpy_prr" {fore 0}
 ("generic_v" c(600) sc(60) t(all_nz usa idf aircraft support_frontline nobot) g(harpy_prr) i(8) b(idf_hqcar) cw(0) cp(5))
 {content "harpy_prr"}
}
''','"harpy_prr"')
    append_once(ROOT/'localization/1.rus/cw/cw_rus_veh.inc','''{"harpy_prr" "<c(FFFFFF)e(shadow)>Harpy ПРР</c>"}
{"harpy_prr_carrier" "<c(FFFFFF)e(shadow)>Harpy ПРР</c>"}
{"harpy_prr_mark" "Пассивное противорадиолокационное наведение"}
{"harpy_prr_seeker" "Harpy: захват излучателя"}
''','"harpy_prr"')
    append_once(ROOT/'localization/1.rus/cw/kk_war_speciality.inc','''{"harpy_prr" "<c(FFFF00)e(shadow)>Одноразовый противорадиолокационный БПЛА. Прямое управление; клик задаёт направление пуска, затем работает пассивное наведение на РЛС.</c>"}
{"harpy_prr_carrier" "<c(FFFF00)e(shadow)>Атака излучателя РЛС</c>"}
''','"harpy_prr"')
    print('Harpy PRR installed: USA / IDF, cost 60, entity harpy_prr')

if __name__=='__main__':install()
