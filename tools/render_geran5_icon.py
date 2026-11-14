"""Render the exported Geran-5 in the live Blender; keep the main scene visible."""
from pathlib import Path
import bpy
from mathutils import Vector

ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
carrier=globals().get('RENDER_CARRIER',False)
root=bpy.data.objects['Su-25 - TWO GERAN-5' if carrier else 'Geran-5 - GAME MODEL']
center=Vector((-1.5,0,1.4)) if carrier else Vector((0,0,0))
factor=3 if carrier else 1
bpy.context.view_layer.update()
scene=bpy.data.scenes.new('Geran-5 Icon')
for obj in root.children_recursive:
    if obj.type=='MESH' and obj.gem.role in {'BONE','VIEW'} and len(obj.data.polygons):
        duplicate=bpy.data.objects.new('G5 Icon '+obj.name,obj.data)
        scene.collection.objects.link(duplicate)
        duplicate.matrix_world=obj.matrix_world.copy()
scene.world=bpy.data.worlds.new('G5 Studio');scene.world.use_nodes=True
background=next(n for n in scene.world.node_tree.nodes if n.type=='BACKGROUND')
background.inputs['Color'].default_value=(.65,.72,.8,1)
background.inputs['Strength'].default_value=.55
for name,position,energy,size in [('Key',(1,-4,7),900,5),('Fill',(-4,4,4),600,4)]:
    data=bpy.data.lights.new('G5 '+name,'AREA');data.energy=energy*factor**2;data.shape='DISK';data.size=size*factor
    obj=bpy.data.objects.new(data.name,data);scene.collection.objects.link(obj);obj.location=Vector(position)*factor+center
    obj.rotation_euler=(center-obj.location).to_track_quat('-Z','Y').to_euler()
camera=bpy.data.cameras.new('G5 Icon Camera');camera.type='ORTHO';camera.ortho_scale=7.3*factor
obj=bpy.data.objects.new(camera.name,camera);scene.collection.objects.link(obj)
obj.location=Vector((4,-8,5 if carrier else 7))*factor+center;obj.rotation_euler=(center-obj.location).to_track_quat('-Z','Y').to_euler();scene.camera=obj
# Fit the complete silhouette; the Su-25 tail and far wing exceed a fixed crop.
orientation=obj.rotation_euler.to_matrix()
right=orientation.col[0];up=orientation.col[1]
# Legacy GEM meshes contain unused sentinel vertices; frame rendered faces only.
points=[mesh.matrix_world @ mesh.data.vertices[index].co for mesh in scene.objects if mesh.type=='MESH' for index in {i for p in mesh.data.polygons for i in p.vertices}]
points=[p for p in points if all(abs(v)<1000 for v in p)]
left,rightmost=min(p.dot(right) for p in points),max(p.dot(right) for p in points)
bottom,top=min(p.dot(up) for p in points),max(p.dot(up) for p in points)
obj.location+=right*((left+rightmost)/2-center.dot(right))+up*((bottom+top)/2-center.dot(up))
camera.ortho_scale=max(rightmost-left,(top-bottom)*2)/.90
try:scene.render.engine='CYCLES'
except TypeError:scene.render.engine=bpy.context.scene.render.engine
if scene.render.engine=='CYCLES':scene.cycles.samples=24
scene.render.resolution_x=832;scene.render.resolution_y=416;scene.render.resolution_percentage=100
scene.render.film_transparent=True
scene.render.image_settings.file_format='PNG';scene.render.image_settings.color_mode='RGBA'
path=ROOT/'tools/geran5_preview'/('su25_icon.png' if carrier else 'geran5_icon.png')
path.parent.mkdir(parents=True,exist_ok=True);scene.render.filepath=str(path)
bpy.ops.render.render(write_still=True,scene=scene.name)
print('Geran-5 render: '+str(path))
