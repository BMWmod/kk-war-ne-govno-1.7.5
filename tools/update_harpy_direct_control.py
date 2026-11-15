"""Migrate existing Harpy files to click-to-launch PRR control, without rebuilding geometry."""
from pathlib import Path
import sys
sys.dont_write_bytecode=True
from build_an196_config import ROOT, read, write, named_block

def update():
    path=ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/harpy/harpy_prr.def'
    text=read(path)
    text=text.replace('; Automatic fire uses antiradar target filtering.','{fire_mode hold}')
    write(path,text)
    path=ROOT/'resource/set/interaction_entity/Airborne_modern.inc'
    text=read(path);old=named_block(text,'harpy');new=old
    new=new.replace('  {call "harpy_no_manual"}\n','')
    if '{on "harpy_no_manual"' in new:
        from build_an196_config import block_at
        start=new.index('{on "harpy_no_manual"');new=new.replace(block_at(new,start),'',1)
    new=new.replace(' {on "check_altitude" {reset_manual_control}}\n','')
    text=text.replace(old,new,1).replace('; Harpy PRR: autonomous attack with stock USA antiradar targeting.','; Harpy PRR: player-directed launch, followed by USA antiradar homing.')
    write(path,text)
    # Update the inherited rig only. The PLY meshes, textures and animations stay intact.
    addon=Path.home()/'AppData/Roaming/Blender Foundation/Blender/5.2/extensions/user_default/gemwerk_io'
    sys.path.insert(0,str(addon))
    from formats import mdl as md
    folder=ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/harpy'
    for filename in ['harpy.mdl','harpy_ammo.mdl']:
        path=folder/filename;model=md.Model.read(str(path))
        bones={b.name:b for root in model.bones for b,parent in root.walk()}
        launch=bones['foresight_spawn']
        for parent in bones.values():
            if launch in parent.children:parent.children.remove(launch)
        bones['foresight1'].children.append(launch)
        launch.matrix=(1,0,0,0,0,1,0,-1,0,0,0,0)
        bones['foresight1_rot'].matrix=md.IDENTITY
        bones['foresight1_rot'].limits=[-180,180]
        model.write(str(path))
    description='Одноразовый противорадиолокационный БПЛА. Прямое управление; клик задаёт направление пуска, затем работает пассивное наведение на РЛС.'
    path=ROOT/'localization/1.rus/cw/kk_war_speciality.inc'
    text=read(path);old=named_block(text,'harpy_prr')
    write(path,text.replace(old,'{"harpy_prr" "<c(FFFF00)e(shadow)>'+description+'</c>"}',1))
    # Keep the installer text in sync so a later rebuild cannot restore the obsolete tooltip.
    path=ROOT/'tools/build_harpy_config.py';text=read(path)
    import re
    text=re.sub(r'(\{"harpy_prr" "<c\(FFFF00\)e\(shadow\)>)[^\n]*?(</c>"\})',lambda m:m[1]+description+m[2],text)
    write(path,text)
    print('Harpy: direct control enabled; hold fire; PRR cursor; launch follows sight; passive PRR carrier retained.')

if __name__=='__main__':update()
