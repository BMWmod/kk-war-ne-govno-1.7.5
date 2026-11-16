"""Validate Krug native assets and the complete existing CWPS integration.

Static checks, including launch clearance, are not an in-engine combat test.
"""
from pathlib import Path
import importlib, types, sys, re, math, json, struct
from itertools import product
ROOT=Path(__file__).resolve().parents[1]
FMT=Path(r'C:\Users\Vsevoloden\AppData\Roaming\Blender Foundation\Blender\5.2\extensions\user_default\gemwerk_io\formats')
pkg=types.ModuleType('krug_formats');pkg.__path__=[str(FMT)];sys.modules[pkg.__name__]=pkg
md=importlib.import_module('krug_formats.mdl');ply=importlib.import_module('krug_formats.ply');anm=importlib.import_module('krug_formats.anm')
DEST=ROOT/'resource/entity/-vehicle/-modern/tank_modern/irg/2k11_krug'
STUFF=ROOT/'resource/set/stuff/atgm'
def read(p):
    b=p.read_bytes()
    try:return b.decode('utf-8-sig')
    except UnicodeDecodeError:return b.decode('cp1251')
def balanced(p):
    balanced_text(read(p),p)
def balanced_text(text,label):
    s=re.sub(r'"(?:\\.|[^"\\])*"','""',text);s=re.sub(r';[^\r\n]*','',s);stack=[]
    for c in s:
        if c in '{(':stack.append(c)
        elif c in '})':assert stack and stack.pop()==('{' if c=='}' else '('),(label,'unbalanced SDL')
    assert not stack,(label,'unclosed SDL')
def ident():return [[float(i==j) for j in range(4)] for i in range(4)]
def matrix(m):return [[m[i],m[3+i],m[6+i],m[9+i]] for i in range(3)]+[[0,0,0,1]]
def mult(a,b):return [[sum(a[i][k]*b[k][j] for k in range(4)) for j in range(4)] for i in range(4)]
def point(m,p):return [sum(m[i][j]*p[j] for j in range(3))+m[i][3] for i in range(3)]
def rotz(deg):
    t=math.radians(deg);c=math.cos(t);s=math.sin(t)
    return [[c,-s,0,0],[s,c,0,0],[0,0,1,0],[0,0,0,1]]
def inverse_point(m,p):
    q=[p[i]-m[i][3] for i in range(3)]
    return [sum(m[j][i]*q[j] for j in range(3)) for i in range(3)]

counts={'models':0,'meshes':0,'triangles':0,'textures':0,'animations':0,'launch_checks':0}
groups={c['first_vertex']:c['bone'] for c in json.loads((ROOT/'_krug_work/component_groups.json').read_text())}
for first in [1799,1833,4262,4296,9355,9391,9429,9461]:
    assert groups[first]=='body',('hull hatch/periscope moves with launcher',first)
for first in [18894,19272,19326,19560,20194,20512]:
    assert groups[first]=='travel_support',('split travelling support',first)
for p in DEST.glob('*.mdl'):
    balanced(p);model=md.Model.read(str(p));counts['models']+=1
    bs=[b for r in model.bones for b,parent in r.walk()];names={b.name:b for b in bs}
    assert len(bs)==len(names),(p,'duplicate bone')
    if 'travel_support' in names:
        parents={b.name:parent.name if parent else None for r in model.bones for b,parent in r.walk()}
        assert parents['travel_support']=='body',(p,'travelling support follows aiming')
    for b in bs:
        if b.speed is not None:assert b.kind=='revolute',(p,b.name,'speed on a fixed bone')
        assert all(math.isfinite(x) for x in b.matrix)
        for v in b.views:assert (DEST/v.file).exists(),(p,v.file)
    for v in model.volumes:
        assert v.bone in names,(p,v.name,'missing bone')
        assert v.shape=='box' and len(v.size)==3 and min(v.size)>0,(p,v.name)
    for seq in model.sequences:
        anim=anm.read(str(DEST/(seq.name+'.anm')));counts['animations']+=1
        assert set(anim.bones)<=names.keys(),(p,seq.name,'unknown animated bone')
for p in DEST.glob('*.ply'):
    mesh=ply.read(str(p));counts['meshes']+=1;counts['triangles']+=len(mesh.indices)//3
    assert mesh.indices and max(mesh.indices)<mesh.vert_count,p
    assert len(mesh.indices)%3==0 and mesh.vert_count<65536,p
    verts=mesh.vertices();pos=verts['pos'];normals=verts['normal'];wrong=checked=0
    for a,b,c in zip(mesh.indices[::3],mesh.indices[1::3],mesh.indices[2::3]):
        u=[pos[b][i]-pos[a][i] for i in range(3)];v=[pos[c][i]-pos[a][i] for i in range(3)]
        cross=[u[1]*v[2]-u[2]*v[1],u[2]*v[0]-u[0]*v[2],u[0]*v[1]-u[1]*v[0]]
        dot=sum(cross[i]*sum(normals[j][i] for j in [a,b,c]) for i in range(3))
        if abs(dot)>1e-7:checked+=1;wrong+=dot<0
    assert checked and wrong/checked<.01,(p,'inverted winding',wrong,checked)
    for section in mesh.meshes:
        for tex in section.textures:assert (DEST/tex).exists(),(p,tex)
for p in DEST.glob('*.mtl'):
    balanced(p)
    for tex in re.findall(r'\{diffuse\s+"([^"]+)"',read(p)):assert (DEST/(tex+'.dds')).exists(),(p,tex)
for p in DEST.glob('*.dds'):
    b=p.read_bytes();assert b[:4]==b'DDS ',p;assert struct.unpack_from('<I',b,28)[0]>1,(p,'missing mipmaps');counts['textures']+=1
paths=list(DEST.glob('*.def'))+[STUFF/n for n in ['3m8_krug_x2.weapon','3m8_krug_rocket.ammo','3m8_krug_impactor']]
carrier=ROOT/'resource/entity/-vehicle/-modern/proj_2/sam_carrier/3m8_krug_carrier.def';paths.append(carrier)
for p in paths:balanced(p)
for p in ['resource/set/multiplayer/units/nz_units.set',
          'resource/set/vision/vision_main.inc','resource/set/registry/unit.reg','resource/set/resupply_generic.inc',
          'localization/info.lng','localization/1.rus/custom/custom_rus_ammo_weapon_stuff.inc']:
    balanced(ROOT/p)
model=md.Model.read(str(DEST/'2k11_krug.mdl'));bs=[(b,p) for r in model.bones for b,p in r.walk()];bones={b.name:b for b,p in bs}
assert bones['basis'].matrix==md.IDENTITY
assert bones['rocket_rot'].limits==[-5,80]
for n in ['turret','rocket_rot']:assert bones[n].kind=='revolute'
for n in ['driver','gunner','commander','charger','emit0','emit1','visor1','visor2','visor3','visor4','foresight1']:assert n in bones,n
assert 'radar_foresight' not in bones and 'radar_foresight_rot' not in bones
for i in range(8):assert f'shooter{i:02}' in bones and f'tail{i:02}' in bones
assert bones['rocket00'].views[0].file==bones['rocket01'].views[0].file=='3m8_krug.ply'
flight=md.Model.read(str(DEST/'3m8_krug.mdl'));fb={b.name:b for r in flight.bones for b,p in r.walk()}
assert fb['body'].views[0].file=='3m8_krug.ply' and 'tail' in fb
# Native GEM transforms, independent of Blender conversion. Positive game
# elevation must raise the missile, and both launch carriers must clear the hull.
for yaw in range(-180,181,30):
    for pitch in [-5,-3.5,0,10,25,45,65,80]:
        world={}
        for b,parent in bs:
            m=matrix(b.matrix)
            if b.name=='turret':m=mult(m,rotz(yaw))
            if b.name=='rocket_rot':m=mult(m,rotz(pitch))
            world[b.name]=mult(world[parent.name] if parent else ident(),m)
        for i in range(2):
            shooter=world[f'shooter{i:02}'];direction=[shooter[j][0] for j in range(3)]
            expected_z=math.sin(math.radians(pitch+3.5))
            assert abs(direction[2]-expected_z)<1e-5,(yaw,pitch,'incorrect elevation')
            sight=world['foresight1']
            assert sum(direction[j]*sight[j][0] for j in range(3))>0.99999,'sight and launch axes differ'
            # Native carrier contacts are 39.81 + 24.5 units ahead of the shooter.
            for advance in [39.8117,64.3117,80]:
                p=point(shooter,(advance,0,0))
                for v in model.volumes:
                    w=mult(world[v.bone],matrix(v.matrix));local=inverse_point(w,p)
                    assert any(abs(local[j])>v.size[j]/2+4.1 for j in range(3)),(yaw,pitch,i,v.name,'launch intersects vehicle')
                counts['launch_checks']+=1
# Solve line-of-sight elevation at nearby/low targets with the actual offset
# pivot and foresight. This tests geometric reachability, not missile hit rate.
def sight_height(pitch,range_m):
    w={}
    for b,parent in bs:
        local=matrix(b.matrix)
        if b.name=='rocket_rot':local=mult(local,rotz(pitch))
        w[b.name]=mult(w[parent.name] if parent else ident(),local)
    m=w['foresight1']
    return (m[2][3]+(range_m/.06-m[0][3])*m[2][0]/m[0][0])*.06
counts['aim_cases']=0;counts['previously_unreachable_aim_cases']=0
for distance,height in product([10,30,60,120,250],[4,8,30,80]):
    lo,hi=bones['rocket_rot'].limits
    assert sight_height(lo,distance)<=height<=sight_height(hi,distance),(distance,height,'outside aiming limits')
    if not sight_height(0,distance)<=height<=sight_height(65,distance):
        counts['previously_unreachable_aim_cases']+=1
    for _ in range(35):
        middle=(lo+hi)/2
        if sight_height(middle,distance)<height:lo=middle
        else:hi=middle
    assert abs(sight_height((lo+hi)/2,distance)-height)<.001
    counts['aim_cases']+=1
assert counts['previously_unreachable_aim_cases']>0
definition=read(DEST/'2k11_krug.def')
assert '{Barrels 2}' in definition and '"buk_launcher"' not in definition
assert '"3m8_krug_x2" filling "3m8_krug_rocket ammo" 2' in definition
for removed in ['"sam_radar"','"radar_krug_integrated"','"targeting_radar_krug"','{place "radar"']:
    assert removed not in definition,removed
assert '{extender "cannon"' in definition and '{switch krug_close}' in definition
assert '{move {workers "gunner_travel" "charger_travel"}}' in definition
assert '{attack {workers "gunner" "charger"}}' in definition
assert '{extension "krug_crew.ext"}' in definition
crew=read(DEST/'krug_crew.ext')
balanced_text(crew,'Krug crew')
crew_code=re.sub(r';[^\r\n]*','',crew)
assert 'linkbone' not in crew_code.lower(), 'internal crew must not be visibly attached'
assert 'seat_passenger' not in crew_code, 'internal crew must not retain an external seated pose'
places=re.findall(r'\{place "([^"]+)"',crew_code)
assert places==['driver','commander','gunner_travel','charger_travel','gunner','charger']
for place,door,side in [('driver','emit0','left'),('commander','emit1','right'),
                        ('gunner_travel','emit0','left'),('charger_travel','emit1','right'),
                        ('gunner','emit0','left'),('charger','emit1','right')]:
    link='{link "'+door+'" "'+place+'" {anm "krug_board_'+side+'"} {forward putoff} {reverse puton}}'
    assert crew_code.count(link)==1,(place,'missing or duplicated boarding/exit link')
for worker in ['gunner','charger']:
    assert '{link "'+worker+'_travel" "'+worker+'"}' in crew_code
# A reflected attachment would invert the rendering of an attached human.
crew_world={}
for b,parent in bs:
    crew_world[b.name]=mult(crew_world[parent.name] if parent else ident(),matrix(b.matrix))
for name in ['driver','commander','gunner','charger','emit0','emit1']:
    m=crew_world[name]
    det=(m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1])
         -m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
         +m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]))
    assert abs(det-1)<1e-5,(name,'reflected or scaled crew transform',det)
counts['internal_crew_places']=len(places)
assert '{StationaryFiring}' in definition
assert 'krug_close' in [seq.name for seq in model.sequences]
close=anm.read(str(DEST/'krug_close.anm'))
assert set(close.bones)=={'travel_support','turret','rocket_rot'}
close_tracks=close.evaluate()
assert close.frame_count==121
for idx,name in enumerate(close.bones):
    assert max(abs(x-y) for x,y in zip(close_tracks[idx][0][0],bones[name].matrix))<1e-4,(name,'deployment endpoint mismatch')
    if name=='travel_support':
        expected=tuple(md.IDENTITY[:9])+tuple(bones[name].matrix[9:])
        assert max(abs(x-y) for x,y in zip(close_tracks[idx][-1][0],expected))<1e-4,'transport rack does not close'
    else:
        assert all(max(abs(x-y) for x,y in zip(key[0],bones[name].matrix))<1e-4 for key in close_tracks[idx]),name
interaction=read(ROOT/'resource/set/interaction_entity/custom1.inc').split('{"2k11_krug"',1)[1]
balanced_text('{"2k11_krug"'+interaction,'Krug interaction')
assert '("custom_sh_multi_launcher" weapon(gun2)' in interaction
assert '("radar_params"' not in interaction
weapon=read(STUFF/'3m8_krug_x2.weapon')
assert '{fillingVisible "rocket"}' in weapon and '{maxRange 380}' in weapon
assert '{AimingTolerance 0.5}' in weapon
events=read(ROOT/'resource/set/interaction_entity/missile_settings2.inc')
# The inherited file has an unrelated extra ')' on the 9m338 entry. Validate
# both new blocks in isolation, rather than changing legacy missile settings.
balanced_text(events.split('else stuff "3m8_krug_rocket ammo"',1)[1].split('else stuff "9m38 buk ammo"',1)[0],'3M8 probe dispatch')
balanced_text(next(l for l in events.splitlines() if 'missilename(3m8_krug)' in l),'3M8 CWPS lifecycle')
assert events.count('else stuff "3m8_krug_rocket ammo"')==1
assert events.count('missilename(3m8_krug)')==1
assert events.count('spawn "3m8_krug_carrier"')==2
assert 'type(radpassive)' in read(carrier) and '"3m8_krug_impactor"' in read(carrier)
assert 'rus_radpassive_missile' in read(STUFF/'3m8_krug_rocket.ammo')
assert not (STUFF/'targeting_radar_krug').exists()
assert 'targeting_radar_rus ammo' in read(STUFF/'targeting_radar_kub')
assert 'targeting_radar_rus ammo' in read(ROOT/'resource/set/interaction_entity/missile_settings1.inc')
supply=read(ROOT/'resource/set/resupply_generic.inc')
assert '"3m8_krug_rocket ammo" 1 {max 2}' in supply
for name in ['mp_cwr_irg_boep','mp_cwr_irg_heavy_boep']:
    if '(define "'+name+'"' in supply:
        block=supply.split('(define "'+name+'"',1)[1].split('(define ',1)[0]
        assert '("sam_rus")' in block,name
units=read(ROOT/'resource/set/multiplayer/units/nz_units.set')
line=next(l for l in units.splitlines() if l.startswith('{"2k11_krug"'))
assert all(t in line for t in ['sc(240)','b(supl)','s(srbsk)','n(4)'])
registrations=[(p.name,l) for p in (ROOT/'resource/set/multiplayer/units').glob('*.set')
               for l in read(p).splitlines() if l.lstrip().startswith('{"2k11_krug"')]
assert registrations==[('nz_units.set',line)],registrations
radar_lines=[l for l in units.splitlines() if l.lstrip().startswith('{"1s91_kub_radar"')]
assert len(radar_lines)==1 and all(t in radar_lines[0] for t in ['s(srbsk)','b(supl)','brig(common)','sc(140)'])
from PIL import Image
for folder,size in [('unit_icon',(104,52)),('unit_icon_small',(78,39))]:
    for i in range(4):
        p=ROOT/'resource/interface/scene'/folder/f'2k11_krug_{i:02}.tga'
        im=Image.open(p);assert im.size==size and im.getbbox(),p
counts['asset_bytes']=sum(p.stat().st_size for p in DEST.iterdir())
counts['in_engine_test']=False
(ROOT/'_krug_work/validation.json').write_text(json.dumps(counts,indent=2))
print('PASS',json.dumps(counts))
