"""Build the supplied M2K FBX as Mirage 2000D. Run in Blender 5.2/Gemwerk.

Source: D:/m2000d/source/mirage2000.rar, extracted to _mirage_work/source.
Gemwerk performs the Blender-to-GEM handedness conversion on meshes and matrices.
"""
from pathlib import Path
import bpy, bmesh, importlib, math, json, copy
from mathutils import Matrix, Vector

ROOT = Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
WORK = ROOT/'_mirage_work'
DEST = ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
DEST.mkdir(parents=True, exist_ok=True)
PKG = 'bl_ext.user_default.gemwerk_io'
ex = importlib.import_module(PKG+'.export_mdl')
md = importlib.import_module(PKG+'.formats.mdl')
an = importlib.import_module(PKG+'.formats.anm')
ut = importlib.import_module(PKG+'.utils')
imp = importlib.import_module(PKG+'.import_mdl')
plyfmt = importlib.import_module(PKG+'.formats.ply')
volfmt = importlib.import_module(PKG+'.formats.vol')
mesh_io = importlib.import_module(PKG+'.mesh_io')
S = 1/.06
T = Matrix(((0,-S,0,0),(S,0,0,0),(0,0,S,1.8*S),(0,0,0,1)))

def write(p,t): p.write_bytes(t.replace('\r','').replace('\n','\r\n').encode('cp1251'))

def export_game_ply(context, ob, path):
    # Gemwerk mirrors Y but retains Blender's index order. Our skeleton has no
    # mirrored basis, so reverse the triangles for GEM backface culling.
    # Vertex normals already point outwards and must not be negated.
    ex.export_ply(context,ob,path)
    mesh=plyfmt.read(path)
    for i in range(0,len(mesh.indices),3):
        mesh.indices[i+1],mesh.indices[i+2]=mesh.indices[i+2],mesh.indices[i+1]
    plyfmt.write(path,mesh)
def mat(name, texture=None, color=(.45,.47,.48,1)):
    m=bpy.data.materials.get(name) or bpy.data.materials.new(name)
    m.use_nodes=True;m.gem.mtl_name=name+'.mtl';m.gem.flags=0x404;m.gem.fvf=0x112
    bs=next(n for n in m.node_tree.nodes if n.type=='BSDF_PRINCIPLED')
    bs.inputs['Base Color'].default_value=color;bs.inputs['Roughness'].default_value=.5
    if texture:
        tx=m.node_tree.nodes.new('ShaderNodeTexImage');tx.image=bpy.data.images.load(str(texture),check_existing=True)
        tx.image.reload()
        m.node_tree.links.new(tx.outputs['Color'],bs.inputs['Base Color'])
    return m

source_scene=bpy.data.scenes.get('Mirage 2000D - assembly')
if source_scene is None:
    source_scene=bpy.data.scenes.new('Mirage 2000D - assembly');bpy.context.window.scene=source_scene
    bpy.ops.import_scene.fbx(filepath=str(WORK/'source/M2K.FBX'))
    for o in source_scene.objects: o['mirage_source_name']=o.name
source=[o for o in source_scene.objects if o.type=='MESH' and 'mirage_source_name' in o]
scene=bpy.data.scenes.get('Mirage 2000D - game build')
if scene:
    for o in list(scene.objects): bpy.data.objects.remove(o,do_unlink=True)
else: scene=bpy.data.scenes.new('Mirage 2000D - game build')
bpy.context.window.scene=scene
bodymat=mat('mirage_body',Path(r'D:\m2000d\textures\hull_tex.png'))
glassmat=mat('mirage_glass',color=(.055,.085,.10,1))
grey=mat('storm_nato',DEST/'storm_nato.dds',color=(.36,.39,.41,1))
aammat=mat('aim9l_surface',DEST/'aim9l_surface.dds',color=(.66,.67,.65,1))

model=md.Model.read(str(ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/f-16c/f-16c_sdb.mdl'))
# Retain the engine's established sensor/support/damage bone names, without F16 geometry.
old={b.name.lower():b for r in model.bones for b,p in r.walk()}
basis=md.Bone('basis')
body=md.Bone('body');body.parameters='ID=body;';basis.children=[body]
bones={'basis':basis,'body':body}
for name,b in old.items():
    if name in bones:continue
    n=md.Bone(name);n.parameters=b.parameters;n.matrix=md.IDENTITY
    body.children.append(n);bones[name]=n
model.bones=[basis];model.sequences=[];model.volumes=[];model.shapes=[]

def bone(name,pos=(0,0,0),parent='body',parameters=None):
    if name in bones:
        n=bones[name]
        for p in bones.values():
            if n in p.children:p.children.remove(n)
    else:n=md.Bone(name);bones[name]=n
    n.matrix=ut.matrix_to_gem(Matrix.Translation(Vector(pos)));n.parameters=parameters or n.parameters
    bones[parent].children.append(n)
    return n

parts={}; pivots={}; stats={}
rename={'hull':'body','nose_gear':'wheelfront','gear_l':'wheelleft','gear_r':'wheelright',
        'flap_l':'elevon_l','flap_r':'elevon_r','Rudder':'rudder','canopy':'canopy',
        'canopy_glass':'canopy_glass','seats':'seats','windshield':'windshield'}
skip={'pyl_inneer','pyl_gpb','pyl_aam_center'}
for src in source:
    sn=src['mirage_source_name']
    if sn in skip:continue
    name=rename.get(sn,sn)
    ob=bpy.data.objects.new('M2KD_'+name,src.data.copy());scene.collection.objects.link(ob)
    ob.data.transform(src.matrix_world)
    # Extend the supplied single-seat canopy rearwards and fit the tandem cockpit.
    if sn in {'canopy','canopy_glass'}:
        for v in ob.data.vertices:v.co.y=-3.593+(v.co.y+3.593)*1.66
    if sn=='hull':
        bm=bmesh.new();bm.from_mesh(ob.data)
        cut=[f for f in bm.faces if abs(f.calc_center_median().x)<.32 and -2.33<f.calc_center_median().y<-1.47 and f.calc_center_median().z>.55]
        bmesh.ops.delete(bm,geom=cut,context='FACES');bm.to_mesh(ob.data);bm.free()
    ob.data.transform(T)
    p=T@src.matrix_world.translation
    if name=='body':p=Vector((0,0,0))
    if name in {'seats','windshield','pyl_center','pyl_outer'}:p=Vector((0,0,0))
    pivots[name]=p.copy();ob.data.transform(Matrix.Translation(-p))
    ob.location=p
    ob.data.materials.clear();ob.data.materials.append(glassmat if sn in {'windshield','canopy_glass'} else bodymat)
    for f in ob.data.polygons:f.material_index=0;f.use_smooth=True
    n=bone(name,p) if name!='body' else body
    n.views=[md.VolumeView(name+'.ply')]
    if name in {'wheelfront','wheelleft','wheelright'}:n.parameters='ID=body;'
    export_game_ply(bpy.context,ob,str(DEST/(name+'.ply')))
    parts[name]=ob;stats[name]=len(ob.data.polygons)

# Split the main hull into actual detachable wing/tail meshes, retaining UV seams.
hull=parts['body'];groups={n:[] for n in ['body','wingl1','wingr1','tail']}
for f in hull.data.polygons:
    c=sum((hull.data.vertices[i].co for i in f.vertices),Vector())/len(f.vertices)
    n='tail' if c.z>51 and c.x<-45 else ('wingl1' if c.y>21 else 'wingr1') if abs(c.y)>21 and c.x<8 and c.z<35 else 'body'
    groups[n].append(f.index)
full=hull.data.copy()
for n,ids in groups.items():
    ob=hull if n=='body' else bpy.data.objects.new('M2KD_'+n,full.copy())
    if n!='body':scene.collection.objects.link(ob)
    else:ob.data=full.copy()
    bm=bmesh.new();bm.from_mesh(ob.data);bm.faces.ensure_lookup_table();keep=set(ids)
    bmesh.ops.delete(bm,geom=[f for f in bm.faces if f.index not in keep],context='FACES')
    bmesh.ops.delete(bm,geom=[v for v in bm.verts if not v.link_faces],context='VERTS')
    bm.to_mesh(ob.data);bm.free()
    nbon=body if n=='body' else bone(n,parameters='ID='+n+';')
    nbon.views=[md.VolumeView(n+'.ply')]
    export_game_ply(bpy.context,ob,str(DEST/(n+'.ply')));parts[n]=ob;stats[n]=len(ids)

# Second ejection seat uses the supplied seat mesh and original UV atlas.
ob=parts['seats'].copy();ob.data=parts['seats'].data.copy();scene.collection.objects.link(ob)
ob.name='M2KD_rear_seat';ob.data.transform(Matrix.Translation((-15.0,0,1.0)))
export_game_ply(bpy.context,ob,str(DEST/'rear_seat.ply'))
bone('rear_seat').views=[md.VolumeView('rear_seat.ply')];parts['rear_seat']=ob

# Assemble the existing Storm Shadow pylon mesh, replacing its material only.
storm=imp.import_ply(bpy.context,str(ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/su24/storm_shadow_pylon.ply'),merge=True)
if not isinstance(storm,bpy.types.Object):storm=bpy.context.active_object
storm.name='M2KD_storm_shadow';storm.data.materials.clear();storm.data.materials.append(grey)
for f in storm.data.polygons:f.material_index=0
coords=[v.co.copy() for v in storm.data.vertices]
lo=Vector(tuple(min(v[i] for v in coords) for i in range(3)));hi=Vector(tuple(max(v[i] for v in coords) for i in range(3)))
print('STORM_RAW_BOUNDS',list(lo),list(hi))
storm.data.transform(Matrix.Scale(5.1*S/(hi.x-lo.x),4))
export_game_ply(bpy.context,storm,str(DEST/'storm_nato_pylon.ply'))
# Match the missile's upper fuselage to the centre pylon's lower mounting face.
sp=Vector((-26.5,0,13.7));storm.location=sp
bone('storm_nato00',sp).views=[md.VolumeView('storm_nato_pylon.ply')]
bone('storm_shooter_00',sp)
# The carrier's contact cylinder is larger than the visible missile and its
# internal missile_point is 39.812 units forward. Release below the aircraft's
# lowest collision box, including the gear, rather than inside its collider.
bone('storm_release',(sp.x,sp.y,-12.0))

# Use stock AIM-9L geometry for the two underwing rails.
aam=imp.import_ply(bpy.context,str(ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/f-15/aim_9l_00.ply'),merge=True)
if not isinstance(aam,bpy.types.Object):aam=bpy.context.active_object
aam.name='M2KD_aim_9l_00'
coords=[v.co.copy() for v in aam.data.vertices]
lo=Vector(tuple(min(v[i] for v in coords) for i in range(3)));hi=Vector(tuple(max(v[i] for v in coords) for i in range(3)))
print('AAM_RAW_BOUNDS',list(lo),list(hi))
# Donor PLY runs along local Z. Orient length along +X and centre it.
extent=hi-lo;longest=max(range(3),key=lambda i:extent[i])
R=Matrix.Identity(4)
if longest==2:R=Matrix.Rotation(math.pi/2,4,'Y')
elif longest==1:R=Matrix.Rotation(-math.pi/2,4,'Z')
aam.data.transform(R@Matrix.Translation(-(lo+hi)/2))
extent_x=max(v.co.x for v in aam.data.vertices)-min(v.co.x for v in aam.data.vertices)
aam.data.transform(Matrix.Scale(2.75*S/extent_x,4))
aam.data.transform(Matrix.Rotation(math.pi/4,4,'X'))
aam.data.materials.clear();aam.data.materials.append(aammat)
for f in aam.data.polygons:f.material_index=0
# Flight entity, guidance and warhead come from the stock AIM-9L.
# The rail slopes down towards the nose. Only the attached copy follows it.
aam.data.transform(Matrix.Rotation(math.radians(3),4,'Y'))
export_game_ply(bpy.context,aam,str(DEST/'aim9l_pylon.ply'))
for i,side in enumerate([-1,1]):
    n=f'aim_9l_{i:02}';p=(-39,side*55.42,20.8)
    parent='wingl1' if side>0 else 'wingr1'
    bone(n,p,parent).views=[md.VolumeView('aim9l_pylon.ply')]
    # Launch from the nose of the rail, as on the donor F-15, not the missile centre.
    bone(f'aam_shooter_{i:02}',(p[0]+23,p[1],p[2]),parent)
    ob=aam if i==0 else aam.copy()
    if i:scene.collection.objects.link(ob)
    ob.location=p
for n,parent in [('elevon_l','wingl1'),('elevon_r','wingr1'),('rudder','tail')]:
    bone(n,pivots[n],parent)

# CWPS's targeting bullet needs an explicit shooter for every barrel. Without
# one the engine requests missing shooter00 (confirmed in game.log), regardless
# of the separate carrier launch bones. Keep these shooters on the aimed chain
# ahead of the nose; the interaction still spawns the carrier on the rail.
# The former x=100 origin crossed the fuselage when aiming 20-40 degrees up.
def aim(prefix,foresight,yaw,pitch):
    a=bone(prefix+'_yaw',(130,0,22));a.kind='revolute';a.limits=yaw;a.speed=1
    b=bone(prefix+'_pitch',parent=a.name);b.kind='revolute';b.limits=pitch;b.speed=1
    b.matrix=(1,0,0,0,0,-1,0,1,0,0,0,0)
    c=bone(foresight,(3,0,0),parent=b.name);c.matrix=(1,0,0,0,0,1,0,-1,0,3,0,0)
aim('storm','foresight_storm',[-35,35],[-85,35])
aim('aam','foresight_aam',[-40,40],[-40,40])
for prefix,count in [('storm',1),('aam',2)]:
    for i in range(count):
        bone(f'{prefix}_pointer_{i:02}',parent='foresight_'+prefix)
for name,pos in {'driver':(53,0,20),'driver1':(38,0,21),'emit1':(47,-16,0),'emit2':(35,-16,0),
 'visor_driver':(57,0,44),'visor_radarx':(104,0,29),'visor_pod':(67,0,20),'visor_ols':(67,0,29),'aiming_mark':(0,0,30),
 'engine_exhaust':(-106,0,32),'engine1_exhaust':(-106,0,32),'ir_1gen_emitter':(-104,0,32),'ir_2gen_emitter':(-104,0,32),
 'foresight_flare_1':(-65,10,27),'foresight_flare_1a':(-65,-10,27),
 'pivot_front':(53,0,0),'supportfront':(53,0,0),'pivot_back':(-30,0,0),'supportleft':(-30,28,0),'supportright':(-30,-28,0)}.items():bone(name,pos)
# Native human meshes expect the reflected attachment basis used by F-16/Su-24.
# This reflection belongs on the crew anchors, not on the corrected airframe.
for name in ['driver','driver1']:
    p=ut.gem_to_matrix(bones[name].matrix).translation
    bones[name].matrix=ut.matrix_to_gem(Matrix.Translation(p)@Matrix.Rotation(math.radians(-15),4,'Y')@Matrix.Diagonal((1,-1,1,1)))
# The .def sets their rotation speed; GEM only accepts that on revolute bones.
for name in ['foresight_flare_1','foresight_flare_1a']:
    bones[name].kind='revolute';bones[name].speed=1
bone('supportfront',(0,0,0),'pivot_front');bone('supportleft',(0,28,0),'pivot_back');bone('supportright',(0,-28,0),'pivot_back')
for n,p in {'flare1_shooter':(-67,10,25),'flare2_shooter':(-67,-10,25),'chaff1_shooter':(-67,10,25),'chaff2_shooter':(-67,-10,25),
 'fxtracefront':(53,0,0),'fxtraceleft':(-30,28,0),'fxtraceright':(-30,-28,0),
 'fxfire_body_1':(10,0,32),'fxfire_body_2':(-40,0,32),'fxfire_body_3':(-20,15,30),'fxfire_body_4':(-20,-15,30),
 'fxfire_wingl1_1':(-37,36,30),'fxfire_wingr1_1':(-37,-36,30),
 'fxfire_wingl1_2':(-50,46,30),'fxfire_wingr1_2':(-50,-46,30),
 'headlight':(53,0,17),'ir_spo':(-50,0,37),'ecm_emitter':(-45,0,37)}.items():bone(n,p)
for n in ['engine_exhaust','engine1_exhaust']:
    p=ut.gem_to_matrix(bones[n].matrix).translation
    bones[n].matrix=ut.matrix_to_gem(Matrix.Translation(p)@Matrix.Rotation(math.pi,4,'Z'))

def box(name,center,size,parent='body_systems',component=None):
    v=md.Volume(name);v.bone=parent;v.shape='box';v.size=list(size)
    v.matrix=ut.matrix_to_gem(Matrix.Translation(Vector(center)));v.component=component
    model.volumes.append(v)

def hull_volume(name,part,component):
    # Small convex collision hulls follow the actual mesh and animated bone.
    # Keep internal modules as separate, cheap boxes, like stock aircraft.
    ob=parts[part];bm=bmesh.new()
    for p in {tuple(round(float(x),3) for x in v.co) for v in ob.data.vertices}:bm.verts.new(p)
    result=bmesh.ops.convex_hull(bm,input=list(bm.verts),use_existing_faces=False)
    inside=[v for v in bm.verts if not v.link_faces]
    if inside:bmesh.ops.delete(bm,geom=inside,context='VERTS')
    bmesh.ops.recalc_face_normals(bm,faces=list(bm.faces))
    me=bpy.data.meshes.new('collision_'+name);bm.to_mesh(me);bm.free()
    tmp=bpy.data.objects.new('collision_'+name,me)
    collision=mesh_io.mesh_to_vol(tmp)
    for i in range(0,len(collision.indices),3):collision.indices[i+1],collision.indices[i+2]=collision.indices[i+2],collision.indices[i+1]
    volfmt.write(str(DEST/(name+'.vol')),collision)
    bpy.data.objects.remove(tmp);bpy.data.meshes.remove(me)
    v=md.Volume(name);v.shape='polyhedron';v.file=name+'.vol';v.bone=part;v.component=component
    model.volumes.append(v)

for name,part,component in [('body','body','body'),('wingl1','wingl1','wingl1'),('wingr1','wingr1','wingr1'),
 ('tail','tail','tail'),('rudder','rudder','rudder'),('aileron1','elevon_l','aileron_l'),('aileron2','elevon_r','aileron_r'),
 ('glass','canopy_glass','body'),('wheel_front','wheelfront','wheel_back'),
 ('wheel_left','wheelleft','retract_wheelL'),('wheel_right','wheelright','retract_wheelR')]:
    hull_volume(name,part,component)
    if component!='body':bones[part].parameters='ID='+component+';'
# Like the F-15/F-16 donors, use the airframe volumes for selection. A separate
# enclosing box without an able-clear override also participates in collisions
# and contains both AIM-9 launch cylinders, despite the physical mesh clearance.
for name,center,size,component in [
 ('engine',(-74,0,32),(55,17,17),'engine'),
 ('fuel_tank_internal_a',(6,0,33),(34,13,15),'fuel_tank_internal_a'),
 ('fuel_tank_internal_b',(-28,0,34),(22,14,14),'fuel_tank_internal_b'),
 ('electronics',(77,-5,30),(12,4,8),'electronics'),
 ('electronics1',(77,5,30),(12,4,8),'electronics'),
 ('electronics2',(25,0,34),(12,10,7),'electronics'),
 ('pilot_panel',(60,0,40),(5,10,6),'pilot_panel'),
 ('pilot_panel1',(45,0,41),(5,10,6),'pilot_panel'),
 ('hydrosystem',(-51,-7,32),(8,5,5),'hydrosystem'),
 ('hydrosystem1',(-51,7,32),(8,5,5),'hydrosystem'),
 ('hydrosystem2',(-35,-18,29),(18,3,3),'hydrosystem'),
 ('hydrosystem3',(-35,18,29),(18,3,3),'hydrosystem'),
 ('hydrosystem4',(-84,0,38),(16,3,3),'hydrosystem'),
 ('hydrosystem_tank',(-18,0,36),(8,7,5),'hydrosystem_tank'),
 ('PPU',(20,-7,33),(7,5,6),'PPU'),('APU',(-47,0,39),(11,8,6),'APU'),
 ('antifire',(-46,0,29),(7,7,6),'antifire'),
 ('OLS',(67,0,24),(8,7,6),'OLS'),('radarX',(98,0,29),(20,12,12),'radarX'),
 ('steering_elev',(-52,0,30),(8,8,5),'steering_elev'),
 ('flares1',(-64,8,28),(7,5,5),'flares1'),('flares2',(-64,-8,28),(7,5,5),'flares2')]:
    box(name,center,size,component=component)
for side,wing,tank,actuator,channel in [(1,'wingl1','c','l','ptur1'),(-1,'wingr1','d','r','ptur1a')]:
    box('fuel_tank_internal_'+tank,(-40,side*33,30),(25,15,3),wing,'fuel_tank_internal_'+tank)
    box('steering_eler_'+actuator,(-60,side*40,29),(12,16,3),wing,'steering_eler_'+actuator)
    box(channel,(-40,side*55.42,24),(38,3,5),wing,'ptur1')
box('ptur4',(-26.5,0,21),(48,3,6),'pyl_center','ptur4')
# Rudder actuator follows the tail; gear damage volumes follow their animated
# legs, so they retract and cannot leave invisible collision boxes in flight.
box('steering_rudder',(-99,0,54),(8,4,12),'tail','steering_rudder')

def anim(name,count,tracks,speed=1):
    names=list(tracks);an.write(str(DEST/(name+'.anm')),an.from_tracks(names,count,{i:tracks[n] for i,n in enumerate(names)}))
    seq=md.Sequence(name);seq.speed=speed;model.sequences.append(seq)
def matrix(p,axis=None,ang=0):
    m=Matrix.Translation(Vector(p))
    if axis:m=m@Matrix.Rotation(ang,4,axis)
    return ut.matrix_to_gem(m)
gear={}
for n in parts:
    if n in {'gear_l_door2','gear_r_door2','gear_nose_door_2','wheelfront','wheelleft','wheelright'}:
        tr=[]
        for f in range(31):
            t=f/30;t=t*t*(3-2*t)
            axis='Y' if n=='wheelfront' else 'X'
            angle=(-1 if '_l' in n or n=='wheelleft' else 1)*math.pi/2*t
            # Main legs retract inboard; doors follow. Final concealment avoids protruding donor seams.
            tr.append((matrix(pivots[n],axis,angle),int(f<29)))
        gear[n]=tr
anim('wheels',31,gear,.8)
anim('basis',2,{'body':[(md.IDENTITY,1)]*2},1)
for name in ['fly','damage_fly','engine_start','engine_work','engine_stop']:
    anim(name,2,{'body':[(md.IDENTITY,1)]*2},1)
anim('driver_open',31,{n:[(matrix(pivots[n],'Y',-.65*f/30),1) for f in range(31)] for n in ['canopy','canopy_glass']},.6)
anim('flaps_off',31,{n:[(matrix(pivots[n],'Y',.18*(1-f/30)),1) for f in range(31)] for n in ['elevon_l','elevon_r']},.6)
anim('nose_up',31,{n:[(matrix(pivots[n],'Y',-.13*f/30),1) for f in range(31)] for n in ['elevon_l','elevon_r']},.5)
anim('air_brake',31,{'rudder':[(matrix(pivots['rudder'],'Z',.15*math.sin(math.pi*f/30)),1) for f in range(31)]},.5)
anim('death',2,{'body':[(md.IDENTITY,1)]*2},1)
for name,seat in [('eject','driver'),('eject1','driver1')]:
    rest=ut.gem_to_matrix(bones[seat].matrix)
    anim(name,16,{seat:[(ut.matrix_to_gem(Matrix.Translation((0,0,f*4))@rest),1) for f in range(16)]},1)
model.write(str(DEST/'mirage2000d.mdl'))
# Destruction events append _xx to the entity name. Share all geometry/textures.
wreck=copy.deepcopy(model)
for r in wreck.bones:
    for b,parent in r.walk():
        if b.name.startswith(('storm_nato','aim_9l_')) or b.name in {'canopy_glass','windshield','seats','rear_seat'}:
            b.views=[]
        elif b.views:b.color='0xff454545'
wreck.write(str(DEST/'mirage2000d_xx.mdl'))
for n in ['mirage_body','mirage_glass','storm_nato','aim9l_surface']:
    write(DEST/(n+'.mtl'),'{material simple\n {diffuse "'+n+'" {MipMap 1}}\n {blend none}\n}\n')
(WORK/'model_stats.json').write_text(json.dumps({'faces':stats,'bones':len(bones),'animations':[s.name for s in model.sequences]},indent=2))
for o in scene.objects:
    if o.type=='MESH':o.scale=(.06,)*3;o.location*=.06
for area in bpy.context.screen.areas:
    if area.type=='VIEW_3D':
        spc=area.spaces.active;spc.shading.type='MATERIAL';spc.overlay.show_relationship_lines=False
        spc.region_3d.view_location=(0,0,1.5);spc.region_3d.view_rotation=Vector((14,-16,10)).to_track_quat('Z','Y');spc.region_3d.view_distance=20
print('EXPORTED',str(DEST),sum(stats.values()),'faces')
# Preserve the installed custom loadout when rebuilding the airframe. The
# collision, aiming and launch bones are deliberately unchanged by this step.
if (ROOT/'tools/magic2_asset.json').exists():
    import sys
    sys.path.insert(0,str(ROOT/'tools'))
    from install_magic2 import apply_magic2_to_plane
    apply_magic2_to_plane()
