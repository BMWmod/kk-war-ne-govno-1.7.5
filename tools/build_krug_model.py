"""Build the supplied Krug FBX in live Blender/Gemwerk. Game assets only.

The source scene is preserved. Reuses one missile mesh for both rails and flight.
Run with exec(compile(Path(...).read_text(), ..., 'exec')) through Blender MCP.
"""
from pathlib import Path
import bpy, bmesh, importlib, math, json, copy
from mathutils import Matrix, Vector

ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
SOURCE=Path(r'C:\Users\Vsevoloden\Desktop\2k11m3_krug')
DEST=ROOT/'resource/entity/-vehicle/-modern/tank_modern/irg/2k11_krug'
WORK=ROOT/'_krug_work'
DEST.mkdir(parents=True,exist_ok=True);WORK.mkdir(exist_ok=True)
pkg='bl_ext.user_default.gemwerk_io'
ex=importlib.import_module(pkg+'.export_mdl');md=importlib.import_module(pkg+'.formats.mdl')
ut=importlib.import_module(pkg+'.utils');pf=importlib.import_module(pkg+'.formats.ply')
an=importlib.import_module(pkg+'.formats.anm')
source=bpy.data.scenes.get('Krug - source')
if not source:
    source=bpy.data.scenes.new('Krug - source');bpy.context.window.scene=source
    bpy.ops.import_scene.fbx(filepath=str(SOURCE/'2k11m3_krug.FBX'))
    for o in source.objects:o['krug_source_name']=o.name.split('.')[0]
scene=bpy.data.scenes.get('Krug - game assembly') or bpy.data.scenes.new('Krug - game assembly')
bpy.context.window.scene=scene
for o in list(scene.objects):bpy.data.objects.remove(o,do_unlink=True)
sources={o['krug_source_name']:o for o in source.objects if o.type=='MESH'}
# FBX carries an inherited translation twice on the child parts. Normalize
# independent parts to the supplied assembled preview, preserving mesh/UV data.
expected={'2k11m3':(-8.499,-3.747,.121),'trackl':(-7.893,2.421,0),
          'trackr':(-7.893,-3.599,0),'3m8':(-7.061,-5.290,3.629),
          '3m8m':(-6.848,-.568,3.814)}
for name,o in sources.items():
    w=o.matrix_world.copy();pts=[w@v.co for v in o.data.vertices]
    lo=Vector([min(p[i] for p in pts) for i in range(3)])
    w.translation+=Vector(expected[name])-lo
    o.parent=None;o.matrix_world=w
# Supplied FBX has a twofold scale excess. 8 GEM units per source world unit.
S=8.0
model=md.Model();bones={};world={};objects={};stats={}

def bone(name,parent=None,mat=None,kind='',params=None,limits=None,speed=None):
    b=md.Bone(name);b.kind=kind;b.parameters=params;b.limits=limits;b.speed=speed
    w=mat or Matrix.Identity(4)
    local=world[parent].inverted()@w if parent else w
    b.matrix=ut.matrix_to_gem(local)
    if parent:bones[parent].children.append(b)
    else:model.bones.append(b)
    bones[name]=b;world[name]=w
    return b

def tr(p):return Matrix.Translation(Vector(p)*S)
bone('basis',params='Wheelradius=0.32;')
bone('body','basis',params='ID=body;')
bone('body_systems','body')
turret_p=Vector((-.17,.017,3.48))
gun_p=Vector((-6.95,.017,5.35))
bone('turret','body',tr(turret_p),'revolute','ID=turret;',speed=.007)
bone('turret_systems','turret',tr(turret_p))
# GEM's positive elevation must raise the nose, as on the native Buk.
# Y reflection in matrix_to_gem reverses the Blender preview's angle sign.
gun_world=tr(gun_p)@Matrix.Rotation(-math.pi/2,4,'X')
# The supplied rails already point 3.5 degrees up at zero joint rotation.
# Permit a level/slightly depressed line of sight, plus steep nearby targets.
# Sight and launch axes remain parallel; do not compensate only the sight bone.
bone('rocket_rot','turret',gun_world,'revolute','ID=gun2;',limits=[-5,80],speed=.006)
# The hull-mounted travelling support is independent of both aiming axes.
# Export the combat-ready pose: its upper rack folds forwards, clear of the
# missiles. Retain the closed pose as an animation for inspection/transport.
frame_rest=tr((5.969,.017,3.141))
bone('travel_support','body',frame_rest,params='ID=body;')

materials={}
for key,tex in [('krug_body','2k11_krug.dds'),('krug_tracks','tracks.dds'),('krug_missile','3m8_missile.dds')]:
    m=bpy.data.materials.get(key) or bpy.data.materials.new(key);m.use_nodes=True
    bs=next(n for n in m.node_tree.nodes if n.type=='BSDF_PRINCIPLED')
    bs.inputs['Roughness'].default_value=.72
    tx=next((n for n in m.node_tree.nodes if n.type=='TEX_IMAGE'),None) or m.node_tree.nodes.new('ShaderNodeTexImage')
    tx.image=bpy.data.images.load(str(SOURCE/tex),check_existing=True)
    m.node_tree.links.new(tx.outputs['Color'],bs.inputs['Base Color'])
    m.gem.mtl_name=key+'.mtl';m.gem.flags=0x404;m.gem.fvf=0x112
    materials[key]=m

def export(name,ob,mat,meshfile=None):
    ob.data.materials.clear();ob.data.materials.append(materials[mat])
    for f in ob.data.polygons:f.material_index=0
    # Vertices in the bone's local Blender coordinates; conversion mirrors Y.
    p=DEST/((meshfile or name)+'.ply')
    ex.export_ply(bpy.context,ob,str(p));data=pf.read(str(p))
    for i in range(0,len(data.indices),3):data.indices[i+1],data.indices[i+2]=data.indices[i+2],data.indices[i+1]
    pf.write(str(p),data);stats[name]=len(data.indices)//3
    bones[name].views=[md.VolumeView(p.name)]
    objects[name]=ob

def part(name,src,faces,parent,mat,pose=None,kind='',params=None):
    if name not in bones:bone(name,parent,pose,kind,params)
    me=src.data.copy();ob=bpy.data.objects.new('Krug '+name,me);scene.collection.objects.link(ob)
    bm=bmesh.new();bm.from_mesh(me);bm.faces.ensure_lookup_table()
    if faces is not None:
        keep=set(faces);bmesh.ops.delete(bm,geom=[f for f in bm.faces if f.index not in keep],context='FACES')
        bmesh.ops.delete(bm,geom=[v for v in bm.verts if not v.link_faces],context='VERTS')
    bm.to_mesh(me);bm.free()
    me.transform(world[name].inverted()@Matrix.Scale(S,4)@src.matrix_world)
    ob.matrix_world=world[name]
    export(name,ob,mat)
    return ob

src=sources['2k11m3'];groups={};wheel_x=[7.308,5.648,3.812,2.078,.353,-1.391,-3.223,-5.483,-7.244]
# Group connected surfaces before classification so no mechanical part is sliced.
adj=[[] for _ in src.data.vertices]
for e in src.data.edges:
    a,b=e.vertices;adj[a].append(b);adj[b].append(a)
seen=set();membership={};component_groups=[]
for vert in src.data.vertices:
    if vert.index in seen:continue
    q=[vert.index];seen.add(vert.index)
    for a in q:
        for b in adj[a]:
            if b not in seen:seen.add(b);q.append(b)
    pts=[src.matrix_world@src.data.vertices[i].co for i in q]
    lo=Vector([min(p[i] for p in pts) for i in range(3)]);hi=Vector([max(p[i] for p in pts) for i in range(3)]);c=(lo+hi)/2
    name='body'
    if lo.z>=3.31 and abs(c.x)<7.95:
        name='turret'
        if lo.z>4.85 or (lo.z>3.72 and hi.x<-6.0):name='rocket_rot'
    # Explicit assemblies in the supplied FBX. A height threshold alone puts
    # raised hatch lids, hinges and periscopes into the rotating superstructure.
    if vert.index<9499:name='body'
    if lo.x>5.5 and hi.x<6.4 and vert.index>=18700:
        name='travel_support' if hi.z>3.41 else 'body'
    if hi.z<2.09 and abs(c.y)>2.40 and hi.x-lo.x<1.5:
        wi=min(range(9),key=lambda i:abs(c.x-wheel_x[i]))
        if abs(c.x-wheel_x[wi])<.5:
            side='l' if c.y>0 else 'r';name=f'wheel{side}{wi+1}'
    for i in q:membership[i]=name
    component_groups.append({'first_vertex':vert.index,'vertices':len(q),'bone':name})
for f in src.data.polygons:groups.setdefault(membership[f.vertices[0]],[]).append(f.index)
for name,faces in groups.items():
    pose=None;parent='body';kind='';params=None
    if name.startswith('wheel'):
        side=name[5];idx=int(name[6:])-1;z=1.256 if idx==0 else 1.417 if idx==8 else .777
        pose=tr((wheel_x[idx],3.01 if side=='l' else -3.01,z))@Matrix.Rotation(math.pi/2,4,'X')
        kind='revolute';params='ID=trackleft;' if side=='l' else 'ID=trackright;'
    part(name,src,faces,parent,'krug_body',pose,kind,params)
# Fold the entire rack together; its struts must not remain on the hull while
# its top follows the missiles. Geometry was exported in its closed local pose.
frame_open=frame_rest@Matrix.Rotation(math.radians(100),4,'Y')
bones['travel_support'].matrix=ut.matrix_to_gem(frame_open)
world['travel_support']=frame_open
objects['travel_support'].matrix_world=frame_open
for side,sn in [('l','trackl'),('r','trackr')]:
    part('track'+side,sources[sn],None,'body','krug_tracks',Matrix.Identity(4),params='ID=trackleft;' if side=='l' else 'ID=trackright;')
    bone('wheels'+side,'basis',tr((0,3.01 if side=='l' else -3.01,.78)),params='ID=trackleft;' if side=='l' else 'ID=trackright;')

# Level the missile's long axis; use that one mesh in every model.
src=sources['3m8'];pts=[src.matrix_world@v.co for v in src.data.vertices]
angle=math.radians(3.5)
rot=Matrix.Rotation(-angle,4,'Y')
aligned=[rot.inverted()@p for p in pts]
center=Vector([(min(p[i] for p in aligned)+max(p[i] for p in aligned))/2 for i in range(3)])
rocket_pose=Matrix.Translation((rot@center)*S)@rot
ob=part('rocket00',src,None,'rocket_rot','krug_missile',rocket_pose,params='ID=ammo_storage_main;')
# Store the common mesh with a unique global basename.
(DEST/'rocket00.ply').replace(DEST/'3m8_krug.ply')
bones['rocket00'].views=[md.VolumeView('3m8_krug.ply')]
delta=sources['3m8m'].matrix_world@sources['3m8m'].data.vertices[0].co-src.matrix_world@src.data.vertices[0].co
pose2=Matrix.Translation(delta*S)@rocket_pose
bone('rocket01','rocket_rot',pose2,params='ID=ammo_storage_main;').views=[md.VolumeView('3m8_krug.ply')]
ob2=bpy.data.objects.new('Krug rocket01',ob.data);scene.collection.objects.link(ob2);ob2.matrix_world=pose2;objects['rocket01']=ob2
localpts=[v.co for v in ob.data.vertices];rmin=min(p.x for p in localpts);rmax=max(p.x for p in localpts)
for i,pose in enumerate([rocket_pose,pose2]):
    # The carrier's nose sensor starts clear of the launcher and other rocket.
    bone(f'shooter{i:02}','rocket_rot',pose@Matrix.Translation((rmax+14,0,0)))
    bone(f'tail{i:02}','rocket_rot',pose@Matrix.Translation((rmin,0,0))@Matrix.Rotation(math.pi,4,'Z'))
for i in range(2,8):
    bone(f'tail{i:02}','rocket_rot',world['tail01']);bone(f'shooter{i:02}','rocket_rot',world['shooter01'])
center_pose=rocket_pose.copy();center_pose.translation.y=(rocket_pose.translation.y+pose2.translation.y)/2
bone('foresight1','rocket_rot',center_pose@Matrix.Translation((rmax+20,0,0)))

for name,pos in {'engine':(-5,0,1.5),'driver':(5.8,1.0,2.2),'commander':(3.3,-.9,2.1),'gunner':(3.3,.9,2.1),
 'charger':(1.5,-.9,2.1),'visor2':(6.2,1,3.3),'visor3':(4,-1,3.3),'visor4':(3,-1,3.3),
 'headlightl':(7.5,2.7,2.6),'headlightr':(7.5,-2.7,2.6),'fxlight':(8,0,2.5),
 'fxsmoke1':(-6,2,2.5),'fxsmoke2':(-6,2,2.5),'fxsteam':(-5,0,3),'fxfire1':(-5,0,2),'fxfire2':(0,0,2),
 'fxstop1':(-8,2.5,2),'fxstop2':(-8,-2.5,2),'fxtracel1':(6,3,0),'fxtracel2':(-6,3,0),'fxtracer1':(6,-3,0),'fxtracer2':(-6,-3,0)}.items():
    bone(name,'body',tr(pos))
# Door approach points stand outside the tracks; local X faces into the hull.
bone('emit0','body',tr((4.5,5,0))@Matrix.Rotation(-math.pi/2,4,'Z'))
bone('emit1','body',tr((4.5,-5,0))@Matrix.Rotation(math.pi/2,4,'Z'))
bone('visor1','turret',tr((0,0,4.6)))

def box(name,pos,size,parent='body_systems',component=None):
    v=md.Volume(name);v.bone=parent;v.shape='box';v.size=[x*S for x in size]
    v.matrix=ut.matrix_to_gem(world[parent].inverted()@tr(pos));v.component=component;model.volumes.append(v)
box('body1',(0,0,1.65),(15.4,4.75,2.0),'body','body')
box('body2',(0,0,2.8),(15.8,6.65,1.0),'body','body')
box('turret',(-.1,0,3.85),(3,2.5,1.0),'turret','turret')
box('turret2',(-3,0,4.5),(8,2.1,.7),'turret','turret')
for name,pos,size in [('engine',(-5,0,1.8),(3.5,3.3,1.8)),('transmission',(-6.5,0,1),(1.5,3.5,1)),
 ('fuel_tank_internal_a',(-3,1.9,1.8),(3,.7,1.5)),('fuel_tank_internal_b',(-3,-1.9,1.8),(3,.7,1.5)),
 ('driver_place',(5.7,1,1.9),(1.3,1.3,2)),('commander_place',(3.4,-1,1.9),(1.3,1.3,2)),('gunner_place',(3.4,1,1.9),(1.3,1.3,2)),
 ('driver_panel',(6.5,1,2.5),(.5,1,.5)),('driver_triplex',(6.4,1,3.2),(.6,1,.3)),
 ('additional_triplex',(3,-1,3.2),(.6,1,.3)),('panel_engine_connectors',(4,0,1),(1,1,1)),
 ('ppu',(-3,0,2),(1,1,1)),('apu',(-4,-1,2),(1,1,1)),('hull_integrity',(0,0,1),(1,1,1)),
 ('front_wheels',(7,0,1),(1,4,1))]:box(name,pos,size)
for name,pos,size in [('commander_triplex',(0,0,4.4),(1.5,1,.6)),('gun2',(-3,0,5),(6,4,.4)),
 ('stabilizer',(-.2,0,3.8),(2,2,.5)),('turret_ring',(-.17,0,3.5),(2.2,2.2,.3))]:box(name,pos,size,'turret',None)
for side in ['l','r']:box('trackleft' if side=='l' else 'trackright',(0,3.01 if side=='l' else -3.01,1),(15.2,1.05,1.9),'track'+side)
for i in [0,1]:
    v=md.Volume('ammo_storage_main'+('' if i==0 else '2'));v.bone=f'rocket{i:02}';v.size=[rmax-rmin,8,8];model.volumes.append(v)

def anim(name,tracks,speed=1):
    names=list(tracks);count=len(tracks[names[0]])
    an.write(str(DEST/(name+'.anm')),an.from_tracks(names,count,{i:tracks[n] for i,n in enumerate(names)}))
    seq=md.Sequence(name);seq.speed=speed;model.sequences.append(seq)
for name in ['start','stop','open','open1']:
    anim(name,{'body':[(bones['body'].matrix,1)]*2},.6)
anim('travel_support_release',{'travel_support':[
    (ut.matrix_to_gem(frame_rest@Matrix.Rotation(math.radians(100*i/30),4,'Y')),1)
    for i in range(31)]})
# Native cannon extender plays this forward to pack, backwards to deploy.
# Aim is restored to the forward rest position before the travelling rack closes.
anim('krug_close',{
    'travel_support':[(ut.matrix_to_gem(frame_rest@Matrix.Rotation(math.radians(100*(1-i/120)),4,'Y')),1) for i in range(121)],
    'turret':[(bones['turret'].matrix,1)]*121,
    'rocket_rot':[(bones['rocket_rot'].matrix,1)]*121,
})
model.write(str(DEST/'2k11_krug.mdl'))
wreck=copy.deepcopy(model)
for r in wreck.bones:
    for b,parent in r.walk():
        if b.name.startswith('rocket0'):b.views=[]
        elif b.views:b.color='0xff454545'
wreck.write(str(DEST/'2k11_krug_xx.mdl'))

missile=md.Model();root=md.Bone('basis');body=md.Bone('body');body.parameters='ID=body;';root.children=[body];missile.bones=[root]
body.views=[md.VolumeView('3m8_krug.ply')]
for name,x in [('tail',rmin),('nose',rmax)]:
    b=md.Bone(name);b.matrix=tuple(md.IDENTITY[:9])+(x,0,0);body.children.append(b)
v=md.Volume('body');v.bone='body';v.size=[rmax-rmin,7,7];missile.volumes=[v]
missile.write(str(DEST/'3m8_krug.mdl'))
for name in materials:
    (DEST/(name+'.mtl')).write_text('{material simple\n {diffuse "'+name+'" {MipMap 1}}\n {blend '+('test' if name=='krug_tracks' else 'none')+'}\n}\n')
(WORK/'model_stats.json').write_text(json.dumps({'triangles':stats,'bones':list(bones),'missile_bounds':[rmin,rmax],'source_scale':.48},indent=2))
(WORK/'component_groups.json').write_text(json.dumps(component_groups,indent=2))
for ob in objects.values():
    ob.matrix_world=Matrix.Scale(.06,4)@ob.matrix_world
for area in bpy.context.screen.areas:
    if area.type=='VIEW_3D':
        sp=area.spaces.active
        if 'MATERIAL' in [i.identifier for i in sp.shading.bl_rna.properties['type'].enum_items]:sp.shading.type='MATERIAL'
        sp.overlay.show_extras=False;sp.overlay.show_relationship_lines=False
        sp.region_3d.view_location=(0,0,2);sp.region_3d.view_rotation=Vector((13,-20,10)).to_track_quat('Z','Y');sp.region_3d.view_distance=14
bpy.data.libraries.write(str(WORK/'krug_asset.blend'),{scene,source},fake_user=True)
print('KRUG MODEL EXPORTED',sum(stats.values()),'triangles',len(bones),'bones', 'parts',stats)
