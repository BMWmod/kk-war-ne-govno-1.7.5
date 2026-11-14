"""Replace the standalone Geran-5 purchase with a two-drone Su-25 carrier."""
import sys,re
sys.dont_write_bytecode=True
from build_an196_config import ROOT,read,write,archive,block_at,named_block

DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/su-25sm_part1'
STUFF=ROOT/'resource/set/stuff/air_stuff'

def replace_named(path,name,block):
    block=block.rstrip()
    text=read(path)
    try:old=named_block(text,name)
    except ValueError:write(path,text.rstrip()+'\n\n'+block+'\n')
    else:write(path,text.replace(old,block,1))

def install():
    definition=archive('entity/-vehicle/-modern/air_modern.pak','air_modern/RUS/Su-25sm_part1/su-25sm_support.def')
    definition=definition.replace('su-25sm_support.mdl','su-25sm_geran5.mdl')
    definition=definition.replace('"vision_lev_plane" "su-25sm"','"vision_lev_plane" "su-25sm" "su-25sm_geran5"')
    # Keep the cannon, countermeasures, crew and aircraft systems; replace the loadout.
    for place in ['nar1','bomber','bomber1','ptur2']:
        match=re.search(r'\{place "'+place+'"',definition)
        old=block_at(definition,match.start());definition=definition.replace(old,'',1)
    definition=definition.replace('"x_25ml_su25x2"','"geran5_airlaunch_x2"')
    # Enforce the release cone with the aimed sight; spawn drones from the fixed sockets.
    definition=definition.replace('{barrels 2}','{shooter "x-25_shooter_"}\n\t\t\t{barrels 2}',1)
    # Launch only on the player's order; spawned drones keep their own user-controlled brain.
    definition=definition[:-2]+'''\n    {brain {properties {control user} {fire_mode hold}}}
    ; Release cone: 35 degrees left/right, at most 35 degrees below the nose.
    {bone "missile_rot" {limits -35 35} {speed 100}}
    {bone "missile_rot1" {limits -5 35} {speed 100}}
}
'''
    write(DEST/'su-25sm_geran5.def',definition)

    weapon=archive('set/stuff.pak','stuff/air_stuff/x_25ml_su25x2.weapon')
    weapon=weapon.replace('ammo x_25ml_su25_ammo','ammo geran5_launch').replace('"X-25_"','"geran5_"')
    weapon=weapon.replace('{recoveryTime 1}','{recoveryTime 3}')
    weapon=weapon.replace('{mass 25}','{mass 25}\n\t{entity "geran5_launch_item"}')
    weapon=weapon.replace('{maxRange 140}','{maxRange 10000}')
    weapon=weapon.replace('{aimRange 140}','{aimRange 10000}\n\t{AimingTolerance 0.01}\n\t{aimtype direct}')
    weapon=weapon.replace(';{cursor "Su253"}','; Two independent aircraft; 160-second magazine reload from supplied ammunition.')
    write(STUFF/'geran5_airlaunch_x2.weapon',weapon)
    write(STUFF/'geran5_launch.ammo','''{bullet
    {entity "geran5_launch_item"}
    {tag "ammo" "shell" "dropboxed" "low_speed" "no_ricochet" "proj_pointer" "fx_proj_pointer" "ground_other_rus"}
    {inventory {weight 100} {size 6 4}}
    {mass 200}
    {damage blastwave {energy 0} {area 0 0}}
}
''')
    # Both inventory and weapon HUD previews use a visible static item model.
    # Projectile damage remains zero in the launch ammunition.
    write(ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5/geran5_launch_item.def','''{game_entity
    (include "/properties/Projectile_ammo.ext")
    {collider "ammo"}
    {Extension "geran5_launch_item.mdl"}
    {extender "stuff" {item "geran5_launch ammo"}}
}
''')

    # Static inventory mesh: no steering bones, helpers or flight animations.
    preview='{Skeleton\n {bone "basis"\n  {Orientation 1 0 0 0 -1 0 0 0 1}\n'
    for part in ('body','panels','wingl1','wingr1','tail','engine','booster'):
        preview+='  {bone "'+part+'" {VolumeView "'+part+'.ply"}}\n'
    preview+=' }\n}\n'
    write(ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5/geran5_launch_item.mdl',preview)

    # Spawn selectable aircraft directly, not a timed missile carrier. The release
    # sockets face forward and sit below the racks to clear the aircraft's collider.
    interaction='''{
    "su-25sm_geran5"
    {on fire "ptur1"
        ("low_speed_bullet")
        (define "g5_release"
            name "%0"
            {delay 0.1
                {spawn "geran5_base" "geran5_launch_%0" x no_normal no_position
                    {set "booster_used" 1}
                    {tags add "g5_air_launched"}
                    {impulse up -10 forward 70 com}
                    {chassis_work 1}
                    ; End the ballistic release phase after half a second.
                    {delay 0.5
                        {if not tagged "destroyed"
                            {physics_work 0}
                            {chassis_work 1}
                        }
                    }
                }
            }
        )
        {if ("g5_release" args 00) else ("g5_release" args 01)}
        ("cw_check_shooting" weap_id(ptur1))
    }
    {on "u_w_electronics_damaged" {weapon_work "ptur1" 0}}
}
'''
    replace_named(ROOT/'resource/set/interaction_entity/Airborne_modern.inc','su-25sm_geran5',interaction)
    units=ROOT/'resource/set/multiplayer/units/nz_rus.set'
    text=read(units)
    text=re.sub(r'(?m)^.*"geran5_base"[^\n]*\n?','',text)
    entry=' {"su-25sm_geran5" {fore 0} ("p" c(720) sc(200) g(extra01) b(extra) brig(vvs) s(rus) i(223) cw(0) cp(20) t(all_nz additional aircraft nobot geran5_carrier) n(1))}'
    if '"su-25sm_geran5"' not in text:
        anchor=next(line for line in text.splitlines() if '"shahed136_base"' in line)
        text=text.replace(anchor,anchor+'\n'+entry,1)
    write(units,text.rstrip()+'\n')
    # Preserve the one-carrier cap in both game modes, including test presets.
    for name in ('presets.inc', 'presets_nz.inc'):
        presets=ROOT/'resource/set/multiplayer/games'/name
        def carrier_limit(match):
            values=[v for v in match[1].split(';')
                    if v and not re.match(r'geran5(?:_carrier)?=', v)]
            return '{unitLimits "' + ';'.join(values + ['geran5_carrier=1']) + '"}'
        write(presets,re.sub(r'\{unitLimits "([^"]*)"\}',carrier_limit,read(presets)))
    supply=ROOT/'resource/set/resupply_generic.inc'
    text=read(supply)
    if '"geran5_launch ammo"' not in text:
        anchor='(define "air_stuff_rus"'
        assert anchor in text
        text=text.replace(anchor,anchor+'\n\t{item "geran5_launch ammo" 1 {max 2}{value 40}}\n',1)
        write(supply,text)
    for file,label in [('cw_rus_veh.inc','Су-25 Герань-5'),('kk_war_speciality.inc','')]:
        path=ROOT/'localization/1.rus/cw'/file;text=read(path)
        if '"su-25sm_geran5"' in text:
            text=re.sub(r'(\{"su-25sm_geran5"\s+)"[^"\n]*"',lambda m:m[1]+'"'+label+'"',text)
            write(path,text)
        else:
            anchor=next(line for line in text.splitlines() if '{"su-25sm_support_light"' in line)
            line=re.sub(r'(\{"su-25sm_support_light"\s+)".*"\}',lambda m:m[1].replace('su-25sm_support_light','su-25sm_geran5')+'"'+label+'"}',anchor)
            assert '"su-25sm_geran5"' in line
            text=text.replace(anchor,anchor+'\n'+line,1);write(path,text)
    labels=ROOT/'localization/1.rus/custom/custom_rus_ammo_weapon_stuff.inc'
    text=read(labels)
    for category,key,label in [('ammo','geran5_launch','Герань-5 — запускаемый БПЛА'),('weapon','geran5_airlaunch_x2','Пуск Герани-5 (2 подвески)')]:
        if '"'+key+'"' not in text:
            anchor='{"'+category+'"'
            assert anchor in text
            text=text.replace(anchor,anchor+'\n\t\t{"'+key+'" "'+label+'"}',1)
    write(labels,text)
    from optimize_aircraft_textures import install_g5
    install_g5()
    print('Su-25 installed: RF, 200 special points, two selectable Geran-5 aircraft, reload 160 s, supply cap 2.')

if __name__=='__main__':install()
