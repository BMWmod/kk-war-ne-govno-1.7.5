"""Run in Blender with Gemwerk enabled, after build_geran5_textures.py.

Imports both user OBJ parts, builds UVs, separates damage parts, and exports
aircraft/attack models with the distinct GEM coordinate bases.
"""
from pathlib import Path
import bpy, bmesh, importlib, copy, json, math
from mathutils import Matrix, Vector

ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5'
PKG='bl_ext.user_default.gemwerk_io'
ex=importlib.import_module(PKG+'.export_mdl')
imp=importlib.import_module(PKG+'.import_mdl')
md=importlib.import_module(PKG+'.formats.mdl')
af=importlib.import_module(PKG+'.formats.anm')
SCALE=100/(34.5133628845+34.2298202515)  # six-metre in-game asset
# Right-handed source XYZ -> Blender ZXY; exporter mirrors Y for GEM.
TRANSFORM=Matrix(((0,0,SCALE,0),(SCALE,0,0,0),(0,SCALE,0,0),(0,0,0,1)))

def material(name):
    mat=bpy.data.materials.new('GERAN5_'+name);mat.use_nodes=True
    mat.gem.mtl_name='g5_'+name+'.mtl';mat.gem.flags=0x504;mat.gem.fvf=0x112
    bsdf=next(n for n in mat.node_tree.nodes if n.type=='BSDF_PRINCIPLED')
    img=bpy.data.images.load(str(DEST/('g5_'+name+'.tga')),check_existing=True)
    tex=mat.node_tree.nodes.new('ShaderNodeTexImage');tex.image=img
    mat.node_tree.links.new(tex.outputs['Color'],bsdf.inputs['Base Color'])
    bsdf.inputs['Roughness'].default_value=0.67 if name!='metal' else 0.38
    bsdf.inputs['Metallic'].default_value=0.65 if name=='metal' else 0.1
    return mat

materials={n:material(n) for n in ['body','wing','panels','metal','dark']}
staging=bpy.data.collections.new('Geran5 Textured Build')
bpy.context.scene.collection.children.link(staging)
groups={n:[] for n in ['body','panels','wingl1','wingr1','tail','engine','booster']}

for number in [0,1]:
    source=bpy.data.objects.get('GERAN5_SOURCE_'+str(number)+'_model_'+str(number))
    if source is None:
        bpy.ops.wm.obj_import(filepath=str(Path(r'D:\g5')/('model_'+str(number)+'.obj')))
        source=bpy.context.active_object
        source.name='GERAN5_SOURCE_'+str(number)+'_model_'+str(number)
    mesh=source.data.copy()
    bm=bmesh.new();bm.from_mesh(mesh)
    bmesh.ops.remove_doubles(bm,verts=list(bm.verts),dist=0.0001)
    bmesh.ops.recalc_face_normals(bm,faces=list(bm.faces))
    for f in bm.faces:f.smooth=True
    for e in bm.edges:e.smooth=e.is_manifold and e.calc_face_angle(0)<math.radians(40)
    bm.to_mesh(mesh);bm.free();mesh.update()
    # Classify connected components; the flat centre wing splits at the body.
    adj=[[] for _ in mesh.vertices]
    for e in mesh.edges:
        a,b=e.vertices;adj[a].append(b);adj[b].append(a)
    visited=set();category={}
    for v in mesh.vertices:
        if v.index in visited:continue
        stack=[v.index];visited.add(v.index);ids=[]
        while stack:
            i=stack.pop();ids.append(i)
            for j in adj[i]:
                if j not in visited:visited.add(j);stack.append(j)
        lo=[min(mesh.vertices[i].co[k] for i in ids) for k in range(3)]
        hi=[max(mesh.vertices[i].co[k] for i in ids) for k in range(3)]
        if number==0:kind='panels'
        elif max(abs(lo[0]),abs(hi[0]))>10:kind='wing'
        elif max(abs(lo[0]),abs(hi[0]))>5 and hi[2]<-20:kind='tail'
        elif lo[1]>2.3 and hi[2]<-20:kind='engine'
        elif hi[1]<-2.15 and hi[2]<-10 and max(abs(lo[0]),abs(hi[0]))<4:kind='booster'
        else:kind='body'
        for i in ids:category[i]=kind
    for poly in mesh.polygons:
        points=[mesh.vertices[i].co.copy() for i in poly.vertices]
        center=sum(points,Vector())/len(points)
        kind=category[poly.vertices[0]]
        if kind=='wing':kind='wingl1' if center.x>=0 else 'wingr1'
        if kind=='panels':paint='panels'
        elif kind in ['wingl1','wingr1','tail']:paint='wing'
        elif kind=='engine':paint='dark' if center.z<-29.4 or center.z>-23.7 else 'metal'
        elif kind=='booster':paint='dark' if center.z<-23 else 'metal'
        elif center.z<-31:paint='body'
        else:paint='body'
        uvs=[]
        for co in points:
            if kind in ['wingl1','wingr1']:
                u=(co.z+1.3)/6.6;v=(co.x+18)/36
            elif kind=='tail':
                u=(co.z+28.5)/6.2
                v=(co.y+4.5)/8 if abs(poly.normal.x)>.65 else (co.x+9.2)/18.4
            else:
                cy=4.47 if kind=='engine' else (-5 if kind=='booster' else 0)
                u=(co.z+34.23)/68.743
                v=(math.atan2(co.y-cy,co.x)+math.pi)/(2*math.pi)
            uvs.append((u,v))
        # Unwrap cylindrical seam per polygon before interpolation.
        if kind not in ['wingl1','wingr1','tail'] and max(v for u,v in uvs)-min(v for u,v in uvs)>.5:
            uvs=[(u,v+1 if v<.5 else v) for u,v in uvs]
        groups[kind].append((points,uvs,paint))
    bpy.data.meshes.remove(mesh)

bounds={};parts=[]
for kind,faces in groups.items():
    verts=[];polys=[];uvs=[];paintids=[];names=list(materials)
    for points,tex,paint in faces:
        start=len(verts);verts.extend(points);polys.append(tuple(range(start,start+len(points))))
        uvs.extend(tex);paintids.append(names.index(paint))
    mesh=bpy.data.meshes.new('geran5_'+kind)
    mesh.from_pydata(verts,[],polys);mesh.update()
    uv=mesh.uv_layers.new(name='UVMap')
    for datum,value in zip(uv.data,uvs):datum.uv=value
    for mat in materials.values():mesh.materials.append(mat)
    for poly,index in zip(mesh.polygons,paintids):poly.material_index=index
    # Weld duplicate face vertices, retaining per-corner UVs; reconstruct sharp edges.
    bm=bmesh.new();bm.from_mesh(mesh);bmesh.ops.remove_doubles(bm,verts=list(bm.verts),dist=0.00001)
    for f in bm.faces:f.smooth=True
    for e in bm.edges:e.smooth=e.is_manifold and e.calc_face_angle(0)<math.radians(40)
    bm.to_mesh(mesh);bm.free();mesh.update()
    bounds[kind]=[[min(v.co[k] for v in mesh.vertices),max(v.co[k] for v in mesh.vertices)] for k in range(3)]
    mesh.transform(TRANSFORM);mesh.update()
    ob=bpy.data.objects.new('GERAN5_BUILD_'+kind,mesh);staging.objects.link(ob)
    ex.export_ply(bpy.context,ob,str(DEST/(kind+'.ply')))
    ob.scale=(.06,)*3;parts.append(ob)

# Keep the proven aircraft rig, including reflection and projectile aiming axes.
model=md.Model.read(str(ROOT/'resource/entity/-vehicle/-modern/air_modern/ukr/an196/an196.mdl'))
model.header=['; Geran-5: user-supplied geometry, original mod UVs/materials.']
bones={b.name:b for root in model.bones for b,parent in root.walk()}
for b in bones.values():b.views=[];b.matrix=md.IDENTITY;b.visibility=None
bones['basis'].matrix=(1,0,0,0,-1,0,0,0,1,0,0,0)
def bone(name,parent='body',position=(0,0,0),view=None):
    if name not in bones:
        b=md.Bone(name);bones[parent].children.append(b);bones[name]=b
    b=bones[name];b.matrix=md.IDENTITY[:9]+tuple(position)
    if view:b.views=[md.VolumeView(view+'.ply')]
    return b
for name in groups:bone(name,view=name)
bone('visor_ols',position=(44,0,0));bone('aiming_mark',position=(48,0,0))
bone('foresight1_rot',position=(45,0,0))
bones['foresight1'].matrix=(1,0,0,0,0,-1,0,1,0,0,0,0)
bones['foresight1'].limits=[-80,80]
bone('foresight_spawn',position=(0,0,0))
bone('fx_starter',position=(-37,0,-7))
bone('ir_1gen_emitter',position=(-41,0,6));bone('ir_2gen_emitter',position=(-41,0,6))
bone('pivot_front',position=(35,0,-5));bone('supportfront')
bone('pivot_back',position=(-35,0,-5));bone('supportleft',position=(0,4,0));bone('supportright',position=(0,-4,0))
bones['rudder_proj'].matrix=(1,0,0,0,-1,0,0,0,-1,0,0,0)
bones['elevator_proj'].matrix=(1,0,0,0,0,1,0,-1,0,0,0,0)
model.volumes=[];model.shapes=[]
def box(name,center,size,component=None):
    v=md.Volume(name);v.bone='body_systems';v.shape='box';v.size=list(size)
    v.matrix=md.IDENTITY[:9]+tuple(center);v.component=component;model.volumes.append(v)
box('body',(0,0,0),(88,8.3,8.3))
box('armor1',(0,0,0),(88.2,8.4,8.4))
box('wingl1',(3,-14,-2.9),(9.5,24,1.2))
box('wingr1',(3,14,-2.9),(9.5,24,1.2))
box('tail',(-35,0,-.7),(6.5,26,1.0))
box('tail1',(-36,-13.2,-.7),(9,.4,11.4),'tail')
box('tail2',(-36,13.2,-.7),(9,.4,11.4),'tail')
box('engine',(-39,0,6.5),(9.5,4.4,4.4))
box('fuel_tank_internal_a',(5,0,0),(29,6,6))
box('fuel_tank_internal_b',(-21,0,0),(20,6,6))
box('electronics',(35,0,0),(9,5,5))
box('hydrosystem',(-4,0,0),(6,3,3))
box('ammo_storage_autocannon',(22,0,0),(16,6,6))
for name in ['pilot_panel','ppu','ptur','ptur1','ols']:
    box(name,(30,0,0),(2,2,2))
model.sequences=[]
for name in ['basis','on_start','engine_start','engine_work','engine_stop','fly','damage_fly','move']:
    seq=md.Sequence(name);seq.speed=1.0;model.sequences.append(seq)
    frames=31 if name=='engine_start' else 2
    anim=af.from_tracks(['body'],frames,{0:[(md.IDENTITY,1)]*frames})
    af.write(str(DEST/(name+'.anm')),anim)
model.write(str(DEST/'geran5.mdl'))
ammo=copy.deepcopy(model);ammo.bones[0].matrix=(1,0,0,0,0,1,0,1,0,0,0,0)
ammo.sequences=[s for s in ammo.sequences if s.name=='move']
ammo.write(str(DEST/'geran5_ammo.mdl'))
staging.hide_viewport=True
for c in bpy.data.collections:
    if c.name.startswith(('an196','shahed136','Geran5 Sources')):c.hide_viewport=True
root,warnings=imp.import_mdl(bpy.context,str(DEST/'geran5.mdl'),show_volumes=False,import_animations=True)
root.name='Geran-5 - GAME MODEL';root.scale=(.06,)*3
for o in bpy.context.view_layer.objects:o.select_set(False)
root.select_set(True);bpy.context.view_layer.objects.active=root
for w in bpy.context.window_manager.windows:
    for a in w.screen.areas:
        if a.type=='VIEW_3D':
            s=a.spaces.active;s.shading.type='MATERIAL';s.overlay.show_extras=False
            s.overlay.show_relationship_lines=False;s.region_3d.view_location=(0,0,0)
            s.region_3d.view_distance=10;s.region_3d.view_rotation=Vector((5,-8,7)).to_track_quat('Z','Y');a.tag_redraw()
print(json.dumps({'parts':{k:len(v) for k,v in groups.items()},'source_bounds':bounds,'warnings':warnings}))
