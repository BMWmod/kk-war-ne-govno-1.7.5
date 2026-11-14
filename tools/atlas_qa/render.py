import bpy,sys
from pathlib import Path
from mathutils import Vector
ROOT=Path('C:\\Program Files (x86)\\Steam\\steamapps\\common\\Men of War Assault Squad 2\\mods\\kk-war-ne-govno-1.7.5')
sys.dont_write_bytecode=True
sys.path.insert(0,str(ROOT/'tools'))
from build_geran5_atlas import ply_module,PARTS,SOURCE
ply=ply_module();tmp=ROOT/'tools/atlas_qa'
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)
materials={}
for name in ('body','wing','panels','metal','dark','atlas'):
 mat=bpy.data.materials.new(name);mat.use_nodes=True
 bs=next(n for n in mat.node_tree.nodes if n.type=='BSDF_PRINCIPLED')
 tex=mat.node_tree.nodes.new('ShaderNodeTexImage')
 tex.image=bpy.data.images.load(str(tmp/('atlas.png' if name=='atlas' else 'g5_'+name+'.tga')))
 mat.node_tree.links.new(tex.outputs['Color'],bs.inputs['Base Color'])
 mat.node_tree.links.new(tex.outputs['Color'],bs.inputs['Emission Color'])
 bs.inputs['Emission Strength'].default_value=1
 bs.inputs['Roughness'].default_value=.67;materials['g5_'+name+'.mtl']=mat
for label,folder,offset in [('BEFORE',tmp,65),('AFTER',SOURCE,-65)]:
 for part in PARTS:
  obj=ply.read(str(folder/(part+'.ply')));v=obj.vertices()
  mesh=bpy.data.meshes.new(label+part);mesh.from_pydata(v['pos'],[],list(obj.triangles()));mesh.update()
  uv=mesh.uv_layers.new(name='UVMap')
  for loop in mesh.loops:
   u,t=v['uv'][0][loop.vertex_index];uv.data[loop.index].uv=(u,1-t)
  for i,m in enumerate(obj.meshes):
   mesh.materials.append(materials[m.textures[0]])
   for poly in list(mesh.polygons)[m.first_face:m.first_face+m.face_count]:poly.material_index=i;poly.use_smooth=True
  mesh.normals_split_custom_set_from_vertices(v['normal'])
  ob=bpy.data.objects.new(label+part,mesh);bpy.context.collection.objects.link(ob);ob.location.y=offset
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=16
scene.render.resolution_x=1100;scene.render.resolution_y=850;scene.render.resolution_percentage=100
scene.world.color=(.22,.22,.22)
for loc,power,size in [((20,-50,180),500000,120),((-80,100,100),350000,100)]:
 data=bpy.data.lights.new('Area','AREA');data.energy=power;data.shape='DISK';data.size=size
 light=bpy.data.objects.new('Area',data);bpy.context.collection.objects.link(light);light.location=loc
 light.rotation_euler=(-light.location).to_track_quat('-Z','Y').to_euler()
camdata=bpy.data.cameras.new('Camera');cam=bpy.data.objects.new('Camera',camdata);bpy.context.collection.objects.link(cam)
cam.location=(150,-190,240);cam.rotation_euler=(-cam.location).to_track_quat('-Z','Y').to_euler();camdata.type='ORTHO';camdata.ortho_scale=220;scene.camera=cam
scene.render.filepath=str(tmp/'comparison.png');bpy.ops.render.render(write_still=True)
