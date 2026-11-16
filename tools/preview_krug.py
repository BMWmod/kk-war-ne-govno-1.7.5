"""Round-trip native Krug model; animate aim/load states; render purchase icons."""
from pathlib import Path
import bpy, importlib, math, json
from mathutils import Vector, Matrix
ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
DEST=ROOT/'resource/entity/-vehicle/-modern/tank_modern/irg/2k11_krug';WORK=ROOT/'_krug_work'
im=importlib.import_module('bl_ext.user_default.gemwerk_io.import_mdl')
scene=bpy.data.scenes.get('Krug - exported model check') or bpy.data.scenes.new('Krug - exported model check')
bpy.context.window.scene=scene
for o in list(scene.objects):bpy.data.objects.remove(o,do_unlink=True)
root,warnings=im.import_mdl(bpy.context,str(DEST/'2k11_krug.mdl'),show_volumes=False,import_animations=False)
print('IMPORT_WARNINGS',warnings)
root.scale=(.06,)*3
obs={o.gem.game_name:o for o in scene.objects if o.gem.game_name}
for ob in scene.objects:
    if ob.type=='MESH':
        ob.data.flip_normals()
        ob.data.normals_split_custom_set([tuple(-n.vector) for n in ob.data.corner_normals])
        for m in ob.data.materials:m.use_backface_culling=True
rest={n:obs[n].matrix_basis.copy() for n in ['turret','rocket_rot','rocket00','rocket01']}
support=obs['travel_support'];support.rotation_mode='QUATERNION'
support_open=support.matrix_basis.copy()
for f,yaw,pitch,loaded in [(1,0,0,2),(22,0,0,2),(40,35,25,2),(60,35,25,1),(80,35,25,0),(110,0,0,2),(130,0,-5,2),(160,0,80,2)]:
    support.matrix_basis=support_open@Matrix.Rotation(math.radians(-100 if f==1 else 0),4,'Y')
    for key in ['location','rotation_quaternion','scale']:support.keyframe_insert(key,frame=f)
    for name,ang in [('turret',yaw),('rocket_rot',-pitch)]:
        ob=obs[name];ob.rotation_mode='QUATERNION';ob.matrix_basis=rest[name]@Matrix.Rotation(math.radians(ang),4,'Z')
        for key in ['location','rotation_quaternion','scale']:ob.keyframe_insert(key,frame=f)
    for i in [0,1]:
        ob=obs[f'rocket{i:02}'];ob.hide_render=(i>=loaded);ob.hide_viewport=(i>=loaded)
        ob.keyframe_insert('hide_render',frame=f);ob.keyframe_insert('hide_viewport',frame=f)
scene.frame_start=1;scene.frame_end=160;scene.frame_set(22)
for m in list(scene.timeline_markers):scene.timeline_markers.remove(m)
for name,f in [('TRANSPORT',1),('SUPPORT RELEASED',22),('AIM',40),('ONE MISSILE',60),('EMPTY',80),('RELOADED',110),('LOW AIM',130),('HIGH AIM',160)]:scene.timeline_markers.new(name,frame=f)
camdata=bpy.data.cameras.new('Krug icon');cam=bpy.data.objects.new('Krug icon',camdata);scene.collection.objects.link(cam)
target=Vector((0,0,2));cam.location=(13,-19,10);cam.rotation_euler=(target-cam.location).to_track_quat('-Z','Y').to_euler()
camdata.type=next(i.identifier for i in camdata.bl_rna.properties['type'].enum_items if i.identifier=='ORTHO');camdata.ortho_scale=11.6;scene.camera=cam
typ=next(i.identifier for i in bpy.data.lights.bl_rna.functions['new'].parameters['type'].enum_items if i.identifier=='AREA')
for name,pos,power,size in [('key',(3,-7,12),2200,7),('fill',(-5,6,9),1700,8),('rim',(-6,-3,6),1100,5)]:
    ld=bpy.data.lights.new('Krug '+name,typ);ld.energy=power;ld.size=size
    ob=bpy.data.objects.new('Krug '+name,ld);scene.collection.objects.link(ob);ob.location=pos;ob.rotation_euler=(target-ob.location).to_track_quat('-Z','Y').to_euler()
world=bpy.data.worlds.new('Krug preview');world.use_nodes=True
bg=next(n for n in world.node_tree.nodes if n.type=='BACKGROUND');bg.inputs['Color'].default_value=(.2,.2,.2,1);bg.inputs['Strength'].default_value=.6;scene.world=world
try:scene.render.engine='CYCLES'
except TypeError:pass
scene.cycles.samples=24
scene.render.resolution_x=1040;scene.render.resolution_y=640;scene.render.resolution_percentage=100;scene.render.film_transparent=True
for key,value in [('file_format','PNG'),('color_mode','RGBA')]:
    setattr(scene.render.image_settings,key,next(i.identifier for i in scene.render.image_settings.bl_rna.properties[key].enum_items if i.identifier==value))
scene.render.filepath=str(WORK/'krug_icon.png')
for area in bpy.context.screen.areas:
    if area.type=='VIEW_3D':
        sp=area.spaces.active;sp.overlay.show_extras=False;sp.overlay.show_relationship_lines=False
        if 'MATERIAL' in [i.identifier for i in sp.shading.bl_rna.properties['type'].enum_items]:sp.shading.type='MATERIAL'
        sp.region_3d.view_location=(0,0,2);sp.region_3d.view_rotation=Vector((13,-19,10)).to_track_quat('Z','Y');sp.region_3d.view_distance=13
bpy.data.libraries.write(str(WORK/'krug_preview.blend'),{scene},fake_user=True)
(WORK/'roundtrip.json').write_text(json.dumps({'warnings':warnings,'objects':list(obs),'frames':[1,22,40,60,80,110,130,160]},indent=2))
bpy.ops.render.render(write_still=True)
print('KRUG roundtrip completed, aim/load timeline prepared, icon rendered')
