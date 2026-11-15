"""Static package checks for meshes, animation continuity and weapon integration.

Does not substitute for a launch/landing/destruction test in the game engine.
Uses the installed Gemwerk binary format readers without importing Blender.
"""
from pathlib import Path
import importlib, types, sys, re, math, json, struct, zipfile
from collections import Counter
from itertools import product
ROOT=Path(__file__).resolve().parents[1]
FMT=Path.home()/'AppData/Roaming/Blender Foundation/Blender/5.2/extensions/user_default/gemwerk_io/formats'
pkg=types.ModuleType('m2k_formats');pkg.__path__=[str(FMT)];sys.modules[pkg.__name__]=pkg
md=importlib.import_module('m2k_formats.mdl');ply=importlib.import_module('m2k_formats.ply');anm=importlib.import_module('m2k_formats.anm')
vol=importlib.import_module('m2k_formats.vol')
PLANE=ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
STORM=ROOT/'resource/entity/-inventory/air_stuff/nato/storm_nato'
def read(p):
    b=p.read_bytes()
    try:return b.decode('utf-8-sig')
    except UnicodeDecodeError:return b.decode('cp1251')
def balanced(s):
    s=re.sub(r'"(?:\\.|[^"\\])*"','""',s)
    s=re.sub(r';[^\r\n]*','',s)
    stack=[]
    for c in s:
        if c in '{(':stack.append(c)
        elif c in '})':assert stack and stack.pop()==('{' if c=='}' else '('),'Unbalanced SDL'
    assert not stack,'Unbalanced SDL'
count={'models':0,'meshes':0,'triangles':0,'animations':0,'textures':0,'collision_hulls':0}
for directory in [PLANE,STORM]:
    for p in directory.glob('*.mdl'):
        model=md.Model.read(str(p));count['models']+=1
        bs=[b for r in model.bones for b,pa in r.walk()];names={b.name.lower():b for b in bs}
        assert len(bs)==len(names),p
        for b in bs:
            for v in b.views:assert (directory/v.file).is_file(),(p,v.file)
        for v in model.volumes:assert v.bone.lower() in names,(p,v.bone)
        for seq in model.sequences:
            path=directory/(seq.name+'.anm');anim=anm.read(str(path));count['animations']+=1
            assert all(n.lower() in names for n in anim.bones),(p,seq.name)
            if seq.name=='wheels':
                for i,n in enumerate(anim.bones):
                    track=anim.evaluate()[i]
                    assert max(abs(a-b) for a,b in zip(track[0][0],names[n.lower()].matrix))<.0001,(n,'Gear jumps at animation start')
                    assert track[0][1]==1 and track[-1][1]==0,(n,'Gear visibility endpoints')
    for p in directory.glob('*.ply'):
        mesh=ply.read(str(p));count['meshes']+=1;count['triangles']+=len(mesh.indices)//3
        assert mesh.indices and max(mesh.indices)<mesh.vert_count,(p,'Invalid triangle index')
        assert len(mesh.indices)%3==0,p
        assert all(math.isfinite(x) for v in mesh.vertices()['pos'] for x in v),p
        for section in mesh.meshes:
            for tex in section.textures:
                assert (directory/tex).exists() or (directory/(tex+'.mtl')).exists(),(p,tex)
            if directory==PLANE:assert section.flags & ply.FLAG_LIGHT,(p,'Unlit material')
        if directory==PLANE:
            vertices=mesh.vertices();pos=vertices['pos'];normals=vertices['normal']
            wrong=0;checked=0
            for a,b,c in zip(mesh.indices[::3],mesh.indices[1::3],mesh.indices[2::3]):
                u=[pos[b][i]-pos[a][i] for i in range(3)]
                v=[pos[c][i]-pos[a][i] for i in range(3)]
                cross=[u[1]*v[2]-u[2]*v[1],u[2]*v[0]-u[0]*v[2],u[0]*v[1]-u[1]*v[0]]
                dot=sum(cross[i]*sum(normals[j][i] for j in [a,b,c]) for i in range(3))
                if abs(dot)>1e-7:checked+=1;wrong+=dot<0
            assert checked and wrong/checked<0.01,(p,'GEM winding opposes outward normals',wrong,checked)
    for p in directory.glob('*.mtl'):
        for n in re.findall(r'\{diffuse\s+"([^"]+)"',read(p),re.I):
            assert any((directory/(n+ext)).exists() for ext in ['.dds','.tga','.ebm']),(p,n)
    for p in directory.glob('*.dds'):
        b=p.read_bytes();assert b[:4]==b'DDS ',p
        count['textures']+=1
    for p in directory.glob('*.def'):balanced(read(p))
    for p in directory.glob('*.vol'):
        hull=vol.read(str(p));edges=Counter();signed_volume=0
        assert hull.indices and max(hull.indices)<len(hull.verts),p
        assert len(hull.indices)%3==0 and len(hull.sides)==len(hull.indices)//3,p
        assert all(math.isfinite(x) for v in hull.verts for x in v),p
        for a,b,c in hull.triangles():
            for edge in [(a,b),(b,c),(c,a)]:edges[tuple(sorted(edge))]+=1
            u,v,w=[hull.verts[i] for i in (a,b,c)]
            signed_volume+=sum(u[i]*(v[(i+1)%3]*w[(i+2)%3]-v[(i+2)%3]*w[(i+1)%3]) for i in range(3))/6
        assert all(n==2 for n in edges.values()),(p,'Open/non-manifold collision hull')
        assert signed_volume>0,(p,'Inverted/degenerate collision hull')
        count['collision_hulls']+=1
model=md.Model.read(str(PLANE/'mirage2000d.mdl'))
bones={b.name.lower():b for r in model.bones for b,pa in r.walk()}
assert bones['basis'].matrix==md.IDENTITY
assert bones['storm_yaw'].limits==[-35,35]
# A fixed bone accepts transforms, but GEM rejects a speed override on it.
# Balanced braces alone cannot catch this model/definition mismatch.
for name in re.findall(r'\{bone\s+"([^"]+)"\s*\{speed\b',read(PLANE/'mirage2000d.def'),re.I):
    assert name.lower() in bones,('Missing overridden bone',name)
    assert bones[name.lower()].kind=='revolute',('Speed override on non-revolute bone',name)
for p in PLANE.glob('*.mdl'):
    m=md.Model.read(str(p))
    flare_bones={b.name:b for r in m.bones for b,pa in r.walk() if b.name in ['foresight_flare_1','foresight_flare_1a']}
    assert len(flare_bones)==2 and all(b.kind=='revolute' and b.speed==1 for b in flare_bones.values()),(p,'Invalid flare bone type/speed')
stuff=ROOT/'resource/set/stuff/air_stuff'
for weapon,prefix,ammo in [('storm_shadowx1','storm_nato',1),('aim-9lx2','aim_9l_',2)]:
    path=stuff/(weapon+'.weapon')
    text=read(path if path.exists() else ROOT/'_mirage_work/reference'/(weapon+'.weapon'));balanced(text)
    # A single round uses an exact bone name; multiple rounds use a prefix.
    visible_key=prefix+'00' if ammo==1 else prefix
    assert '{fillingVisible "'+visible_key+'"}' in text
    assert re.search(r'\{filling\s+"[^"]+"\s+'+str(ammo)+r'\}',text)
    visible=[b for n,b in bones.items() if re.fullmatch(re.escape(prefix)+r'\d\d',n)]
    assert len(visible)==ammo and all(b.views for b in visible),(weapon,'Pylon count/visibility mismatch')
for n in ['storm_shooter_00','aam_shooter_00','aam_shooter_01','foresight_storm','foresight_aam','driver','driver1']:assert n in bones,n
def determinant(m):
    return m[0]*(m[4]*m[8]-m[7]*m[5])-m[3]*(m[1]*m[8]-m[7]*m[2])+m[6]*(m[1]*m[5]-m[4]*m[2])
for name in ['driver','driver1']:
    assert abs(determinant(bones[name].matrix)+1)<1e-5,(name,'Native crew needs a reflected attachment basis')
    assert 15<bones[name].matrix[11]<25,(name,'Crew anchor above the cockpit floor')
    animation=anm.read(str(PLANE/('eject' if name=='driver' else 'eject1'))+'.anm')
    for matrix,visible in animation.evaluate()[0]:
        assert abs(determinant(matrix)+1)<1e-5,(name,'Ejection changes crew handedness')
# missile_placer calibre(900) creates a radius-9 contact cylinder. The release
# must clear even the lowest gear hull; matching only the visible hull is unsafe.
release=bones['storm_release'].matrix[9:]
parents={b.name:pa for r in model.bones for b,pa in r.walk()}
def transform(m,p):return [sum(m[j*3+i]*p[j] for j in range(3))+m[9+i] for i in range(3)]
def world_point(name,p):
    while name:
        p=transform(bones[name.lower()].matrix,p)
        parent=parents[name]
        name=parent.name if parent is not None else None
    return p
collision_points=[]
assert not any(v.name=='select' for v in model.volumes),'Unconfigured enclosing selection box intersects departing missiles'
for v in model.volumes:
    points=(vol.read(str(PLANE/v.file)).verts if v.shape=='polyhedron' else
            list(product(*[(-s/2,s/2) for s in v.size])))
    collision_points.extend(world_point(v.bone,transform(v.matrix,p)) for p in points)
lowest=min(p[2] for p in collision_points)
assert release[2]+9<lowest,('Storm carrier intersects aircraft collision hulls',release[2]+9,lowest)
# The visible missile/carrier and CWPS targeting bullet have separate origins.
# game.log confirmed that an omitted shooter resolves to missing shooter00.
# Each barrel must resolve to an explicit shooter on its aimed foresight chain,
# not to the physical rail or to an engine fallback.
definition=read(PLANE/'mirage2000d.def')
for prefix,barrels,place in [('storm',1,'ptur4'),('aam',2,'ptur1')]:
    weapon_place=definition.split('{place "'+place+'"',1)[1].split('\n  }',1)[0]
    assert '{shooter "'+prefix+'_pointer_"}' in weapon_place,('Missing explicit targeting shooter',place)
    assert '{barrels '+str(barrels)+'}' in weapon_place
    for path in PLANE.glob('*.mdl'):
        tree={b.name:(b,pa) for r in md.Model.read(str(path)).bones for b,pa in r.walk()}
        for i in range(barrels):
            name=f'{prefix}_pointer_{i:02}'
            assert name in tree,(path,'Missing targeting barrel',name)
            b,pa=tree[name]
            assert pa.name=='foresight_'+prefix and b.matrix==md.IDENTITY,(path,'Shooter must follow aimed foresight',name)
front=max(p[0] for p in collision_points)
for prefix in ['aam','storm']:
    yaw=bones[prefix+'_yaw'];pitch=bones[prefix+'_pitch']
    origin=world_point(yaw.name,(0,0,0))
    # Every allowed yaw/pitch is strictly forward. Starting beyond the maximum
    # X of ALL aircraft colliders proves the entire ray cannot enter any of them.
    assert origin[0]>front+5,(prefix,'Foresight pivot behind the nose',origin[0],front)
    assert all(-90<a<90 for a in yaw.limits+pitch.limits),(prefix,'Aiming cone points backwards')
    assert bones['foresight_'+prefix].matrix[9]>0
    for ya in [yaw.limits[0],0,yaw.limits[1]]:
        for pi in [pitch.limits[0],0,pitch.limits[1]]:
            direction=(math.cos(math.radians(ya))*math.cos(math.radians(pi)),
                       math.sin(math.radians(ya))*math.cos(math.radians(pi)),math.sin(math.radians(pi)))
            point=[origin[i]+3*direction[i] for i in range(3)]
            assert point[0]>front and direction[0]>0,(prefix,ya,pi)
# Regression: the previous pivot was outside the hull at rest, yet its upward
# targeting ray hit the nose. Test the actual convex body, not only its AABB.
def sub(a,b):return [x-y for x,y in zip(a,b)]
def dot(a,b):return sum(x*y for x,y in zip(a,b))
def cross(a,b):return [a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]]
def ray_hits_hull(origin,direction,vertices,triangles):
    lo,hi=0.,float('inf')
    for a,b,c in triangles:
        normal=cross(sub(vertices[b],vertices[a]),sub(vertices[c],vertices[a]))
        offset=dot(normal,sub(origin,vertices[a]));slope=dot(normal,direction)
        if abs(slope)<1e-8:
            if offset>1e-6:return False
        elif slope<0:lo=max(lo,-offset/slope)
        else:hi=min(hi,-offset/slope)
        if lo>hi:return False
    return True
body_volume=next(v for v in model.volumes if v.name=='body')
body_hull=vol.read(str(PLANE/body_volume.file))
body_points=[world_point(body_volume.bone,transform(body_volume.matrix,p)) for p in body_hull.verts]
d=(math.cos(math.radians(30)),0,math.sin(math.radians(30)))
assert ray_hits_hull([100+3*d[0],0,22+3*d[2]],d,body_points,body_hull.triangles()),'Old upward-shot regression no longer exercises fuselage collision'
assert not ray_hits_hull([130+3*d[0],0,22+3*d[2]],d,body_points,body_hull.triangles())
count['targeting_cones_clear']=2
air=read(ROOT/'resource/set/interaction_entity/Airborne_modern.inc')
assert '("air_compact_launcher" weapon(ptur4) foresight(storm_release) missile(storm_nato) flashbarrel(storm_shooter_00))' in air
assert bones['storm_nato00'].matrix==bones['storm_shooter_00'].matrix
for i in range(2):
    mount=bones[f'aim_9l_{i:02}'].matrix;launch=bones[f'aam_shooter_{i:02}'].matrix
    assert launch[:9]==mount[:9] and launch[10:]==mount[10:]
    assert abs(launch[9]-mount[9]-23)<.001,'AIM-9L launch must clear the rail'
# Test the stock carrier's contact-cylinder center against EVERY plane volume,
# including boxes. The old blanket exclusion of 'select' missed an overlap at
# x=48.418, y=+/-55.42, z=20.8 inside a 240x150x80 enclosing box.
def point_inside_volume(point,v):
    if v.shape=='polyhedron':
        hull=vol.read(str(PLANE/v.file))
        vertices=[world_point(v.bone,transform(v.matrix,p)) for p in hull.verts]
        return all(dot(cross(sub(vertices[b],vertices[a]),sub(vertices[c],vertices[a])),sub(point,vertices[a]))<=1e-5
                   for a,b,c in hull.triangles())
    assert v.shape=='box',('Unhandled collision shape',v.name,v.shape)
    center=world_point(v.bone,transform(v.matrix,(0,0,0)))
    for axis,size in enumerate(v.size):
        unit=[0,0,0];unit[axis]=1
        direction=sub(world_point(v.bone,transform(v.matrix,unit)),center)
        if abs(dot(sub(point,center),direction))>size/2:return False
    return True
old_select=md.Volume('select');old_select.shape='box';old_select.bone='body'
old_select.size=[240,150,80];old_select.matrix=md.IDENTITY[:9]+(0,0,42)
for i in range(2):
    center=world_point(f'aam_shooter_{i:02}',(39.8117457+24.6063,0,0))
    assert point_inside_volume(center,old_select),'Selection-box regression no longer exercises the original launch overlap'
    hits=[v.name for v in model.volumes if point_inside_volume(center,v)]
    assert not hits,('AIM-9 contact cylinder starts inside plane volumes',i,hits)
count['launch_centers_clear']=2
missiles=read(ROOT/'resource/set/interaction_entity/missile_settings2.inc')
# Validate macro event declarations as well as braces: overload cannot resolve
# duplicate events in the same entity block.
macro_source=read(ROOT/'resource/set/interaction_entity/Missile_M.inc')
def entity_block(text,marker):
    start=text.rfind('{',0,text.index(marker));depth=0
    for token in re.finditer(r';[^\r\n]*|"(?:\\.|[^"\\])*"|[{}]',text[start:]):
        if token[0]=='{':depth+=1
        elif token[0]=='}':
            depth-=1
            if depth==0:return text[start:start+token.end()]
    raise AssertionError(('Unclosed entity',marker))
def macro_body(name):
    match=re.search(r'\(define\s+"'+re.escape(name)+r'"',macro_source)
    assert match,('Missing missile macro',name)
    depth=0
    for token in re.finditer(r';[^\r\n]*|"(?:\\.|[^"\\])*"|[()]',macro_source[match.start():]):
        if token[0]=='(':depth+=1
        elif token[0]==')':
            depth-=1
            if depth==0:return macro_source[match.end():match.start()+token.end()-1]
    raise AssertionError(('Unclosed macro',name))
def check_event_collisions(parts):
    seen=set()
    for part in parts:
        # Headers end at the first action brace/macro or newline. Definitions
        # considered here declare their events at entity level.
        for m in re.finditer(r'\{\s*on\s+([^{}()\r\n]+)',part):
            header=re.findall(r'"[^"\r\n]*"|\S+',m[1])
            key=tuple(t for t in header if t!='overload')
            # overload affects inherited handlers, not duplicate declarations
            # inside the same entity block after macro expansion.
            assert key not in seen,('Duplicate event in entity block',key)
            seen.add(key)
storm=entity_block(missiles,'missilename(storm_nato)')
check_event_collisions([macro_body(n) for n in ['CWPS_proj_3stage','missile_missed']]+[storm])
aim9=entity_block(missiles,'missilename(aim-9l)')
check_event_collisions([macro_body(n) for n in ['CWPS_proj','missile_missed','speed_fast','antislip']]+[aim9])
for bad_header in ['on spawn','on spawn overload']:
    try:check_event_collisions([macro_body('CWPS_proj_3stage'),'{'+bad_header+' {inherited}}'])
    except AssertionError:pass
    else:raise AssertionError(('Duplicate-spawn regression was not detected',bad_header))
assert '{volumes "rangefinder1" disable overlap}' in storm
assert '{volumes "rangefinder1" enable overlap}' in storm
assert '{if tagged "storm_launch_clear" {delay 0.9 {call "detonate"}}}' in storm
assert '("air_multibarrel_launcher" weapon(ptur1) shooter(aam_shooter_) missile(aim-9l)' in air
assert '{weapon "aim-9lx2" filled}' in read(PLANE/'mirage2000d.def')
assert '{weapon "storm_shadowx1" filled}' in read(PLANE/'mirage2000d.def')
supply=read(ROOT/'resource/set/resupply_generic.inc')
nato=supply[supply.index('(define "air_stuff_nato"'):]
nato=nato[:nato.index('(define ',1)]
assert '{item "aim-9l_ammo ammo"' in nato and '{item "storm_shadow ammo"' in nato
truck=supply[supply.index('(define "mp_cwr_nato_avia"'):]
truck=truck[:truck.index('(define ',1)]
assert '("air_stuff_nato")' in truck
# Weapon filling IDs must match the stock ammo types available from MAN aviation.
assert '{filling "ammo storm_shadow" 1}' in read(stuff/'storm_shadowx1.weapon')
assert '{filling "ammo aim-9l_ammo" 2}' in read(ROOT/'_mirage_work/reference/aim-9lx2.weapon')
# These large shared files also contain unrelated legacy SDL; check our complete
# appended entity blocks without changing existing aircraft/missile definitions.
balanced(air[air.index('{"mirage2000d"'):])
balanced(missiles[missiles.index('{("CWPS_proj_3stage" missilename(storm_nato)'):])
unit=next(l for l in read(ROOT/'resource/set/multiplayer/units/nz_nato.set').splitlines() if '"mirage2000d"' in l)
assert all(x in unit for x in ['sc(350)','b(nrf_hqcar)','s(nato)','n(2)','crew_nation(fr)'])
base=ROOT.parent/'cold war 1_7_5/resource'
with zipfile.ZipFile(base/'engine.pak') as z:
    standard=z.read(next(n for n in z.namelist() if n.lower()=='properties/airborne_m.ext')).decode('cp1251')
volumes={v.name:v for v in model.volumes}
assert len(volumes)==len(model.volumes)
for v in model.volumes:
    assert v.component and re.search(r'\{component\s+"'+re.escape(v.component)+'"',standard),(v.name,'Unknown component')
    # Ensure the inherited volume tags, armor and damage routing apply to this name.
    match=re.search(r'\{volume\s+"'+re.escape(v.name)+r'"',standard)
    assert match,(v.name,'No inherited damage volume')
    depth=0
    for end in range(match.start(),len(standard)):
        depth+=(standard[end]=='{')-(standard[end]=='}')
        if depth==0:break
    component=re.search(r'\{component\s+"([^"]+)"',standard[match.start():end+1])
    # Glass has inherited armor/tags but no component; explicitly route it to body.
    assert (component and component[1]==v.component) or (v.name=='glass' and v.component=='body'),(v.name,'Inherited damage binding mismatch')
    if v.shape=='polyhedron':assert (PLANE/v.file).is_file(),v.name
for name,bone in [('wheel_front','wheelfront'),('wheel_left','wheelleft'),('wheel_right','wheelright')]:
    assert volumes[name].bone==bone and volumes[name].shape=='polyhedron'
assert all('fuel_tank_internal_'+s in volumes for s in 'abcd')
assert volumes['ptur1'].component==volumes['ptur1a'].component=='ptur1'
assert volumes['ptur4'].component=='ptur4'
assert all(n in volumes for n in ['engine','electronics','pilot_panel','hydrosystem','hydrosystem_tank','PPU','APU','antifire','OLS','radarX','steering_elev','steering_rudder','steering_eler_l','steering_eler_r','aileron1','aileron2'])
assert '{Visor "radarX"' in read(PLANE/'mirage2000d.def')
assert '{if not work "flares2" {weapon_work "flare_dropper" 0}}' in air
count['damage_zones']=len(volumes)
count['damage_components']=len({v.component for v in model.volumes if v.component})
with zipfile.ZipFile(base/'set/breed.pak') as z:assert 'breed/mp2/fr/pilot.set' in z.namelist()
with zipfile.ZipFile(base/'set/stuff.pak') as z:assert 'stuff/Pistol/flare_dropper_64' in z.namelist()
for p in [PLANE/'mirage2000d.def',STORM/'storm_nato_impactor.def']:
    assert re.search(r'Extension\s+"[^"]+\.mdl"',read(p)),p
assert '"storm_nato_impactor_link"' in read(ROOT/'resource/entity/-vehicle/-modern/proj_2/agm_carrier/storm_nato_carrier.def')
for p in [STORM/'storm_shadow.mtl',PLANE/'storm_nato.mtl']:
    assert '"storm_nato"' in read(p)
    assert '$/model/storm_shadow' not in read(p)
assert (PLANE/'storm_nato.dds').read_bytes()==(STORM/'storm_nato.dds').read_bytes()
assert struct.unpack_from('<II',(PLANE/'storm_nato.dds').read_bytes(),12)==(1024,1024)
for folder,size in [('unit_icon',(104,52)),('unit_icon_small',(78,39))]:
    for i in range(4):
        b=(ROOT/f'resource/interface/scene/{folder}/mirage2000d_{i:02}.tga').read_bytes()
        assert b[2]==2 and struct.unpack_from('<HH',b,12)==size
count['asset_bytes']=sum(p.stat().st_size for d in [PLANE,STORM] for p in d.iterdir() if p.is_file())
print(json.dumps({'result':'PASS','checks':count,'game_runtime_tested':False},indent=2))
