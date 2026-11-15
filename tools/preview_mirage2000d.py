"""Round-trip the exported model into the live Blender scene; render UI icons."""
from pathlib import Path
import bpy, importlib, json, math
from mathutils import Vector
ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/fr/mirage2000d'
WORK=ROOT/'_mirage_work'
PKG='bl_ext.user_default.gemwerk_io'
im=importlib.import_module(PKG+'.import_mdl');an=importlib.import_module(PKG+'.formats.anm');ut=importlib.import_module(PKG+'.utils')
scene=bpy.data.scenes.get('Mirage 2000D - exported game model') or bpy.data.scenes.new('Mirage 2000D - exported game model')
bpy.context.window.scene=scene
for o in list(scene.objects):bpy.data.objects.remove(o,do_unlink=True)
root,warnings=im.import_mdl(bpy.context,str(DEST/'mirage2000d.mdl'),show_volumes=False,import_animations=False)
assert not warnings,warnings
root.scale=(.06,)*3
# GEM winding is clockwise after its handedness conversion. Gemwerk's importer
# mirrors Y without swapping indices, so restore Blender's winding for preview.
for ob in scene.objects:
    if ob.type=='MESH':
        ob.data.flip_normals()
        # Blender flips custom normals along with winding; restore their
        # original outward direction while preserving smoothing and UV seams.
        ob.data.normals_split_custom_set([tuple(-n.vector) for n in ob.data.corner_normals])
objects={o.gem.game_name:o for o in scene.objects if o.gem.game_name}
gear=an.read(str(DEST/'wheels.anm'));tracks=gear.evaluate()
for f in range(1,181):
    t=0 if f<30 else min(30,f-30) if f<60 else 30 if f<125 else max(0,30-(f-125))
    for i,n in enumerate(gear.bones):
        ob=objects[n];matrix,vis=tracks[i][t];ob.matrix_basis=ut.gem_to_matrix(matrix)
        ob.rotation_mode='QUATERNION'
        ob.hide_render=not vis;ob.hide_viewport=not vis
        for p in ['location','rotation_quaternion','scale','hide_render','hide_viewport']:ob.keyframe_insert(p,frame=f)
scene.frame_start=1;scene.frame_end=180
for marker in list(scene.timeline_markers):scene.timeline_markers.remove(marker)
for name,frame in [('LANDED',1),('GEAR RETRACT',30),('FLIGHT',60),('GEAR EXTEND',125),('LANDED',155)]:scene.timeline_markers.new(name,frame=frame)
scene.frame_set(80)
for ob in scene.objects:
    if ob.type=='MESH':
        for m in ob.data.materials:m.use_backface_culling=True
camdata=bpy.data.cameras.new('Mirage preview camera');cam=bpy.data.objects.new('Mirage preview camera',camdata);scene.collection.objects.link(cam)
cam.location=(14,-19,11);target=Vector((0,0,1.9));cam.rotation_euler=(target-cam.location).to_track_quat('-Z','Y').to_euler()
camdata.type=next(i.identifier for i in camdata.bl_rna.properties['type'].enum_items if i.identifier=='ORTHO');camdata.ortho_scale=17
scene.camera=cam
area_type=next(i.identifier for i in bpy.data.lights.bl_rna.functions['new'].parameters['type'].enum_items if i.identifier=='AREA')
for name,loc,power,size in [('key',(3,-8,13),2100,8),('fill',(-5,7,9),1600,7),('rim',(-10,-2,6),1100,5)]:
    ld=bpy.data.lights.new('M2K '+name,area_type);ld.energy=power;ld.shape='DISK';ld.size=size
    lo=bpy.data.objects.new('M2K '+name,ld);scene.collection.objects.link(lo);lo.location=loc;lo.rotation_euler=(target-lo.location).to_track_quat('-Z','Y').to_euler()
world=bpy.data.worlds.new('Mirage preview world');world.use_nodes=True
bg=next(n for n in world.node_tree.nodes if n.type=='BACKGROUND');bg.inputs['Color'].default_value=(.18,.18,.18,1);bg.inputs['Strength'].default_value=.6
scene.world=world
try:scene.render.engine='CYCLES'
except TypeError:pass
scene.cycles.samples=24
scene.render.resolution_x=1040;scene.render.resolution_y=640;scene.render.resolution_percentage=100
scene.render.film_transparent=True
scene.render.image_settings.file_format=next(i.identifier for i in scene.render.image_settings.bl_rna.properties['file_format'].enum_items if i.identifier=='PNG')
scene.render.image_settings.color_mode=next(i.identifier for i in scene.render.image_settings.bl_rna.properties['color_mode'].enum_items if i.identifier=='RGBA')
scene.render.filepath=str(WORK/'mirage_icon.png')
for area in bpy.context.screen.areas:
    if area.type=='VIEW_3D':
        sp=area.spaces.active;sp.shading.type='MATERIAL';sp.overlay.show_extras=False;sp.overlay.show_relationship_lines=False
        sp.region_3d.view_location=(0,0,1.5);sp.region_3d.view_rotation=Vector((14,-16,8)).to_track_quat('Z','Y');sp.region_3d.view_distance=18
bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'mirage2000d.blend'),compress=True)
bpy.ops.render.render(write_still=True)
print('Round-trip valid; preview frames 1-180 show landing gear; rendered icon at',scene.render.filepath)
