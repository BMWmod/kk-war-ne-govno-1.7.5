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

def install():
    for suffix in ['', '_ammo', '_loaded', '_impactor', '_impactor_link', '_impactor_direct_hit']:
        name='tu141_base'+suffix+'.def'
        text=convert(read(SOURCE/name)).replace('geran5_base.mdl','geran5.mdl')
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
