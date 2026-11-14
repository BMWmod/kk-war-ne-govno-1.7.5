"""Install AN-196 gameplay definitions alongside the existing Shahed system.

Run after build_an196_blender.py. Preserves CP1251 or UTF-8 BOM and CRLF.
The CWPS country(rus) channel is shared with the existing Ukrainian Tu-141;
it denotes a guidance channel, not the multiplayer purchasing faction.
"""
from pathlib import Path
import re
import zipfile

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT.parent / 'cold war 1_7_5/resource'
DEST = ROOT / 'resource/entity/-vehicle/-modern/air_modern/ukr/an196'
STUFF = ROOT / 'resource/set/stuff/air_stuff'

def encoding_of(data):
    if data.startswith(b'\xef\xbb\xbf'):
        return 'utf-8-sig'
    try:
        data.decode('utf-8')
        return 'utf-8'
    except UnicodeDecodeError:
        return 'cp1251'

def read(path):
    data = path.read_bytes()
    return data.decode(encoding_of(data), errors='surrogateescape').replace('\r', '')

def write(path, text):
    encoding = encoding_of(path.read_bytes()) if path.exists() else 'cp1251'
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.replace('\r', '').replace('\n', '\r\n').encode(encoding, errors='surrogateescape'))

def archive(pak, name):
    with zipfile.ZipFile(BASE / pak) as z:
        return z.read(name).decode('cp1251', errors='surrogateescape').replace('\r', '')

def block_at(text, start):
    """Return a balanced SDL block, ignoring quoted braces and comments."""
    depth = 0; quoted = False; comment = False; escaped = False
    for i in range(start, len(text)):
        c = text[i]
        if comment:
            if c == '\n': comment = False
            continue
        if quoted:
            if c == '"' and not escaped: quoted = False
            escaped = c == '\\' and not escaped
            continue
        if c == ';': comment = True; continue
        if c == '"': quoted = True; continue
        if c == '{': depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0: return text[start:i+1]
    raise ValueError('Unbalanced SDL block')

def named_block(text, name):
    m = re.search(r'\{\s*"' + re.escape(name) + r'"(?=\s|\{)', text)
    if not m: raise ValueError(name)
    return block_at(text, m.start())

def append_once(path, text, marker):
    old = read(path)
    if marker not in old:
        clean = '\n'.join(line.rstrip() for line in text.splitlines())
        write(path, old.rstrip() + '\n\n' + clean.rstrip() + '\n')

def install():
    definition = read(ROOT/'resource/entity/-vehicle/-modern/air_modern/ir/shahed136/shahed136_base.def')
    definition = definition.replace('shahed136','an196')
    # Ukrainian EW vulnerability follows the same airborne class as its Tu-141.
    definition = definition.replace('\t{props "ecm_vulnerable_rus"}\n', '')
    write(DEST/'an196_base.def', definition)
    weapon = read(STUFF/'shahed136_mark.weapon').replace('shahed136','an196')
    write(STUFF/'an196_mark.weapon', weapon)
    for name in ['shahed136.base.ammo','shahed136_ammo.base.ammo',
                 'shahed136_base_impactor','shahed136_base_impactor_direct_hit.fg.ammo']:
        text = archive('set/stuff.pak','stuff/air_stuff/'+name).replace('shahed136','an196')
        write(STUFF/name.replace('shahed136','an196'),text)
    for suffix in ['ammo','loaded','impactor','impactor_link','impactor_direct_hit']:
        name = 'shahed136_base_'+suffix+'.def'
        text = archive('entity/-inventory/-ammo/other.pak','shahed136_ammo/'+name)
        text = text.replace('shahed136','an196')
        write(DEST/('an196_base_'+suffix+'.def'),text)
    carrier = archive('entity/-vehicle/-modern/vp_proj.pak','proj_2/atgm_carrier/shahed136_base_carrier.def')
    write(ROOT/'resource/entity/-vehicle/-modern/proj_2/atgm_carrier/an196_base_carrier.def',
          carrier.replace('shahed136','an196'))

    airborne = ROOT/'resource/set/interaction_entity/Airborne_modern.inc'
    block = named_block(read(airborne),'shahed136')
    block = block.replace('"shahed136"','"an196"').replace('missilename(shahed136_base)','missilename(an196_base)')
    # AN-196 has landing gear, no detachable Shahed rocket booster.
    # Locate the opening brace immediately before this event explicitly.
    start = block.rfind('{',0,block.index('on "engine_on"'))
    original = block_at(block,start)
    engine = '''{
        on "engine_on"
        {
            if not "engine_started"
            {set "engine_started" 1}
            {play_sound "engine_start"}
            {ani_play "engine_start" callback}
        }
    }'''
    block = block[:start] + engine + block[start+len(original):]
    append_once(airborne,block,'"an196"')

    settings = ROOT/'resource/set/interaction_entity/missile_settings2.inc'
    text = read(settings)
    start = text.index('{("CWPS_proj" missilename(shahed136_base)')
    controller = block_at(text,start).replace('shahed136','an196')
    impactor = named_block(text,'shahed136_base_impactor').replace('shahed136','an196')
    append_once(settings,controller+'\n'+impactor,'missilename(an196_base)')
    links = ROOT/'resource/set/interaction_entity/Missile_M.inc'
    block = named_block(read(links),'shahed136_base_impactor_link')
    block = block.replace('"shahed136_base_impactor_link"','"an196_base_impactor_link"')
    append_once(links,block,'"an196_base_impactor_link"')
    targeting = ROOT/'resource/set/interaction_entity/missile_settings1.inc'
    text = read(targeting)
    if 'an196_base_ammo' not in text:
        anchor = '\telse stuff "tu141_base_ammo ammo"'
        entry = '\telse stuff "an196_base_ammo ammo"\n\t("spawn_proj_5" country(rus) type(other) weapon_tag(an196_ammo_target) decoytype(optic) decoyprob(0) min_alt(-100))\n'
        assert anchor in text
        write(targeting,text.replace(anchor,entry+anchor,1))

    units = ROOT/'resource/set/multiplayer/units/nz_ukr.set'
    text = read(units)
    if '"an196_base"' not in text:
        anchor = next(line for line in text.splitlines() if line.lstrip().startswith('{"tu141_base"'))
        entry = '\n ;АН-196 «Лютый»: 10 спецочков\n {"an196_base" ("p" c(5) brig(avia_ua) t(all_nz additional aircraft aat nobot an196) s(ukr) n(0) g(extra01) sc(10) b(extra) i(1084) cw(0) cp(2)) {fore -90.0}}\n'
        write(units,text.replace(anchor,anchor+'\n'+entry,1))
    presets = ROOT/'resource/set/multiplayer/games/presets.inc'
    text = read(presets)
    if 'an196=20' not in text:
        write(presets,text.replace('shahed136=20;','shahed136=20;an196=20;',1))
    for file in ['cw_rus_veh.inc','kk_war_speciality.inc']:
        path = ROOT/'localization/1.rus/cw'/file
        text = read(path)
        if '"an196_base"' in text: continue
        for old,new in [('shahed136_base','an196_base'),('shahed136_base_carrier','an196_base_carrier')]:
            anchor = next(line for line in text.splitlines() if '{"'+old+'"' in line)
            line = anchor.replace(old,new)
            if file == 'cw_rus_veh.inc': line = line.replace('Shahed-136','АН-196 «Лютый»')
            text = text.replace(anchor,anchor+'\n'+line,1)
        write(path,text)
    print('AN-196 installed: Ukraine / extra / sc(10); independent flight and impact entities.')

if __name__ == '__main__':
    install()
