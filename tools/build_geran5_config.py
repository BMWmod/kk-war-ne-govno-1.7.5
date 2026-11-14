"""Install Geran-5 aircraft and the Russian Su-25 carrier, using Tu-141 controls."""
import re,sys
sys.dont_write_bytecode=True
from build_an196_config import ROOT, read, write, block_at, named_block, append_once

DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
SOURCE=ROOT/'resource/entity/-vehicle/-spizdili/Tu-141'
STUFF=ROOT/'resource/set/stuff/air_stuff'
INTER=ROOT/'resource/set/interaction_entity'

def convert(text):
    return text.replace('tu141','geran5').replace('Tu-141','Geran-5')

def install_damage_handlers():
    """Keep stock UAV blast sensitivity and make critical failures terminal."""
    path=INTER/'Airborne_modern.inc'
    text=read(path)
    old=named_block(text,'geran5')
    begin='\t; Geran-5 damage handlers begin\n'
    end='\t; Geran-5 damage handlers end\n'
    handlers='''	{
		on blast_hit overload
		{
			if min_energy 1
			{
				call "geran5_destroy"
			}
		}
		{
			delay 0.1 {call "geran5_check_modules"}
		}
	}
	{
		on pierce overload
		{
			if not stuff "proj_pointer"
			{
				if not stuff "bullet"
				{
					call "geran5_destroy"
				}
			}
		}
		{
			delay 0.1 {call "geran5_check_modules"}
		}
	}
	{
		on break
		{
			delay 0.1 {call "geran5_check_modules"}
		}
	}
	{
		on "geran5_destroy"
		{
			if not "geran5_destroyed"
			{
				set "geran5_destroyed" 1
			}
			{
				tags add "destroyed"
			}
			{
				chassis_work 0
			}
			{
				drop_orders
			}
			{
				call "stat_break"
			}
			{
				call "detonate"
			}
		}
	}
	{
		on "geran5_check_modules"
'''
    for component in ('body','engine','wingl1','wingr1','tail',
                      'fuel_tank_internal_a','fuel_tank_internal_b',
                      'electronics','hydrosystem'):
        handlers+=('\t\t{\n\t\t\tif not work "'+component+'"\n'
                   '\t\t\t{\n\t\t\t\tcall "geran5_destroy"\n\t\t\t}\n\t\t}\n')
    handlers+='\t}\n'
    if begin in old:
        start=old.index(begin)
        stop=old.index(end,start)+len(end)
    elif '\t;damage model:' in old:
        start=old.index('\t;damage model:')
        stop=old.index('\t{\n\t\ton "engine_on"',start)
    else:
        start=stop=old.index('\t{\n\t\ton "engine_on"')
    new=old[:start]+begin+handlers+end+old[stop:]
    if new!=old:
        write(path,text.replace(old,new,1))

def install():
    for suffix in ['', '_ammo', '_loaded', '_impactor', '_impactor_link', '_impactor_direct_hit']:
        name='tu141_base'+suffix+'.def'
        text=convert(read(SOURCE/name)).replace('geran5_base.mdl','geran5.mdl')
        if suffix == '':
            text=text.replace('Speed(77)', 'Speed(80)')
            text=text.replace('{Altitude 25}', '{Altitude 15}\n\t\t\t; Air launch: engage flight speed without the inherited ground-style run-up.\n\t\t\t{locomotion\n\t\t\t\t{Maxspeed 80}\n\t\t\t\t{turnRadius 25}\n\t\t\t\t{StartTime 0.1}\n\t\t\t\t{BrakeTime 6.4}\n\t\t\t\t{StopTime 9.6}\n\t\t\t}')
        write(DEST/name.replace('tu141','geran5'),text)
    for path in sorted(STUFF.glob('tu141*')):
        write(STUFF/path.name.replace('tu141','geran5'),convert(read(path)))
    from balance_geran5_impactor import install as install_warhead
    install_warhead()
    carrier=ROOT/'resource/entity/-vehicle/-modern/proj_2/atgm_carrier/tu141_base_carrier.def'
    write(carrier.with_name('geran5_base_carrier.def'),convert(read(carrier)))

    # Tu-141 preserves manual control and checks damage by individual modules.
    airborne=INTER/'Airborne_modern.inc'
    append_once(airborne,convert(named_block(read(airborne),'tu141')),'"geran5"')
    install_damage_handlers()
    links=INTER/'Missile_M.inc'
    append_once(links,convert(named_block(read(links),'tu141_base_impactor_link')),'"geran5_base_impactor_link"')
    settings=INTER/'missile_settings2.inc'
    text=read(settings)
    start=text.index('{("CWPS_proj" missilename(tu141_base)')
    append_once(settings,convert(block_at(text,start)+'\n'+named_block(text,'tu141_base_impactor')),'missilename(geran5_base)')
    settings=INTER/'missile_settings1.inc'
    text=read(settings)
    if 'geran5_base_ammo' not in text:
        match=re.search(r'(?m)^[ \t]*else stuff "tu141_base_ammo ammo"[ \t]*(?:\n[ \t]*)?\("spawn_proj_5"[^\n]+',text)
        assert match
        write(settings,text[:match.end()]+'\n'+convert(match.group())+text[match.end():])

    targets=ROOT/'resource/set/target/ammo.set'
    text=read(targets)
    if '{geran5_uav' not in text:
        start=text.index('{tu141_uav')
        block=block_at(text,start)
        write(targets,text[:start]+convert(block)+'\n\t'+text[start:])
    for file in ['cw_rus_veh.inc','kk_war_speciality.inc']:
        path=ROOT/'localization/1.rus/cw'/file
        text=read(path)
        if '"geran5_base"' in text:continue
        for old in ['shahed136_base','shahed136_base_carrier']:
            anchor=next(line for line in text.splitlines() if '{"'+old+'"' in line)
            line=anchor.replace(old,old.replace('shahed136','geran5'))
            if file=='cw_rus_veh.inc':line=line.replace('Shahed-136','Герань-5')
            text=text.replace(anchor,anchor+'\n'+line,1)
        write(path,text)
    # The carrier installer replaces the former standalone purchase.
    from build_su25_geran5_config import install as install_carrier
    install_carrier()

if __name__=='__main__':install()
