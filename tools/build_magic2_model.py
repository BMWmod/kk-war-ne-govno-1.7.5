"""Original Matra Magic 2 game mesh. Execute in Blender through MCP.

Creates a separate scene; does not change any existing objects or aircraft hulls.
Coordinates are visual game-prop dimensions, not a manufacturing specification.
"""
from pathlib import Path
import bpy, bmesh, math, importlib, json
from mathutils import Matrix, Vector

ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
DEST=ROOT/'resource/entity/-vehicle/-modern/missile_modern/magic2'
PLANE=ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
DEST.mkdir(parents=True,exist_ok=True)
scene=bpy.data.scenes.new('Matra Magic 2 - game asset')
bpy.context.window.scene=scene
collection=scene.collection
verts=[];faces=[];colors=[]
palette=[('magic2_shell',(.72,.74,.72,1)),('magic2_seeker',(.10,.19,.16,1)),
         ('magic2_metal',(.26,.29,.30,1)),('magic2_dark',(.035,.045,.05,1)),
         ('magic2_yellow',(.81,.61,.10,1)),('magic2_brown',(.31,.16,.07,1))]

def lathe(profile,material=0,steps=32):
    start=len(verts)
    for x,r in profile:
        for j in range(steps):
            a=2*math.pi*j/steps
            verts.append((x,r*math.cos(a),r*math.sin(a)))
    for k in range(len(profile)-1):
        for j in range(steps):
            faces.append((start+k*steps+j,start+k*steps+(j+1)%steps,
                          start+(k+1)*steps+(j+1)%steps,start+(k+1)*steps+j));colors.append(material)
    faces.extend([tuple(start+j for j in reversed(range(steps))),
                  tuple(start+(len(profile)-1)*steps+j for j in range(steps))]);colors.extend([material,material])

def fin(outline,angle,material=0,thickness=.008):
    start=len(verts)
    for side in [-1,1]:
        for x,r in outline:
            t=side*thickness/2
            verts.append((x,r*math.cos(angle)-t*math.sin(angle),r*math.sin(angle)+t*math.cos(angle)))
    n=len(outline)
    faces.extend([tuple(start+j for j in reversed(range(n))),tuple(start+n+j for j in range(n))]);colors.extend([material]*2)
    for j in range(n):faces.append((start+j,start+(j+1)%n,start+n+(j+1)%n,start+n+j));colors.append(material)

# Short rounded IR dome, two forward cruciform sets, broad clipped tail fins.
lathe([(-1.375,.055),(-1.34,.0785),(-1.13,.0785),(.77,.0785),(1.14,.075),(1.27,.061)],0)
lathe([(1.14,.0755),(1.19,.073),(1.25,.062),(1.30,.047),(1.34,.025),(1.375,.003)],1)
lathe([(-1.38,.056),(-1.365,.056),(-1.365,.038),(-1.33,.030)],2)
lathe([(-1.366,.032),(-1.365,.032)],3)
for x in [-1.13,-.61,.22,.69,1.12]:lathe([(x-.005,.079),(x+.005,.079)],2)
for x,mat in [(.46,4),(-.71,5)]:lathe([(x-.025,.0795),(x+.025,.0795)],mat)
for j in range(4):
    angle=math.pi/4+j*math.pi/2
    fin([(.97,.075),(.82,.19),(.66,.19),(.69,.077)],angle)
    fin([(.65,.078),(.42,.25),(.20,.25),(.27,.078)],angle)
    fin([(-.77,.078),(-.99,.33),(-1.30,.33),(-1.32,.078)],angle)
    # Visible hinge/root strips, separate shading without tiny modifiers.
    fin([(.66,.079),(.21,.079),(.23,.086),(.63,.086)],angle,2,.012)
mesh=bpy.data.meshes.new('Magic2_original_mesh');mesh.from_pydata(verts,[],faces);mesh.update()
ob=bpy.data.objects.new('Matra Magic 2',mesh);collection.objects.link(ob)
for name,color in palette:
    mat=bpy.data.materials.new(name);mat.use_nodes=True
    shader=next(n for n in mat.node_tree.nodes if n.type=='BSDF_PRINCIPLED')
    shader.inputs['Base Color'].default_value=color
    shader.inputs['Roughness'].default_value=.32 if name.endswith(('seeker','metal')) else .65
    shader.inputs['Metallic'].default_value=.55 if name.endswith('metal') else .05
    mat.diffuse_color=color
    mat.gem.mtl_name=name+'.mtl';mat.gem.flags=0x404;mat.gem.fvf=0x112
    mesh.materials.append(mat)
for polygon,index in zip(mesh.polygons,colors):polygon.material_index=index
bm=bmesh.new();bm.from_mesh(mesh);bmesh.ops.recalc_face_normals(bm,faces=list(bm.faces));bm.to_mesh(mesh);bm.free()
# Constant UV texels make the same material colors available in GEM.
uv=mesh.uv_layers.new(name='UVMap')
for loop in uv.data:loop.uv=(.5,.5)
for polygon in mesh.polygons:
    polygon.use_smooth=abs(polygon.normal.x)<.95 and polygon.area<.025

pkg='bl_ext.user_default.gemwerk_io'
ex=importlib.import_module(pkg+'.export_mdl');md=importlib.import_module(pkg+'.formats.mdl')
ply=importlib.import_module(pkg+'.formats.ply')
def export_prop(path,rotation=0):
    tmp=ob.copy();tmp.data=mesh.copy();collection.objects.link(tmp)
    tmp.data.transform(Matrix.Scale(1/.06,4)@Matrix.Rotation(rotation,4,'Y'))
    bpy.context.view_layer.update()
    ex.export_ply(bpy.context,tmp,str(path))
    data=ply.read(str(path))
    for i in range(0,len(data.indices),3):data.indices[i+1],data.indices[i+2]=data.indices[i+2],data.indices[i+1]
    ply.write(str(path),data)
    bpy.data.objects.remove(tmp,do_unlink=True)
    return len(data.indices)//3
triangles=export_prop(DEST/'magic2.ply')
export_prop(PLANE/'magic2_pylon.ply',math.radians(3))
model=md.Model();basis=md.Bone('basis');body=md.Bone('body');body.parameters='ID=body;'
body.views=[md.VolumeView('magic2.ply')];basis.children=[body]
for name,pos in [('tail',(-22.7,0,0)),('nose',(22.9,0,0))]:
    b=md.Bone(name);b.matrix=md.IDENTITY[:9]+pos;body.children.append(b)
model.bones=[basis]
volume=md.Volume('body');volume.shape='box';volume.size=[45.6,2.62,2.62];volume.bone='body';model.volumes=[volume]
model.write(str(DEST/'magic2.mdl'))
# A separate reusable .blend contains only this new scene and its dependencies.
bpy.data.libraries.write(str(ROOT/'tools/magic2_asset.blend'),{scene},fake_user=True)
(ROOT/'tools/magic2_asset.json').write_text(json.dumps({'triangles':triangles,'dimensions_m':[2.755,.472347,.472347],'fin_tip_span_m':.66,'materials':palette},indent=2))
for area in bpy.context.screen.areas:
    if area.type=='VIEW_3D':
        sp=area.spaces.active
        modes=[i.identifier for i in sp.shading.bl_rna.properties['type'].enum_items]
        if 'MATERIAL' in modes:sp.shading.type='MATERIAL'
        sp.region_3d.view_location=(0,0,0)
        sp.region_3d.view_rotation=Vector((2,-5,3)).to_track_quat('Z','Y')
        sp.region_3d.view_distance=4.5
print('MAGIC2 EXPORTED',triangles,'triangles; original mesh, flight and mounted models')
