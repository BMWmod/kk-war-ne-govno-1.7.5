"""Create Su-25 with two visible Geran-5 racks, retaining its original rig."""
from pathlib import Path
import bpy,importlib,copy,sys
from mathutils import Vector

ROOT=Path(r'C:\Program Files (x86)\Steam\steamapps\common\Men of War Assault Squad 2\mods\kk-war-ne-govno-1.7.5')
STAGE=ROOT/'tools/geran5_preview/su25'
DEST=ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/su-25sm_part1'
DEST.mkdir(parents=True,exist_ok=True)
sys.dont_write_bytecode=True
if str(ROOT/'tools') not in sys.path:sys.path.insert(0,str(ROOT/'tools'))
from localize_geran5_payload import copy_payload
copy_payload(DEST)
copy_payload(STAGE)
md=importlib.import_module('bl_ext.user_default.gemwerk_io.formats.mdl')
imp=importlib.import_module('bl_ext.user_default.gemwerk_io.import_mdl')
model=md.Model.read(str(STAGE/'su-25sm_support.mdl'))
bones={b.name.lower():b for r in model.bones for b,p in r.walk()}
for name,b in bones.items():
    if name.startswith(('x-25_','r60_','rbk250_','bomb_')) or name in ['b-8l','b-8r']:
        b.views=[]
for index,side in enumerate([55,-55]):
    payload=md.Bone(f'geran5_{index:02}')
    payload.matrix=md.IDENTITY[:9]+(-40,side,0)
    for part in ['body','panels','wingl1','wingr1','tail','engine','booster']:
        child=md.Bone(f'g5_{index:02}_{part}')
        child.views=[md.VolumeView(f'g5_payload_{part}.ply')]
        payload.children.append(child)
    bones['body'].children.append(payload)
    # Release sockets are independent of fillingVisible. Slightly below each rack.
    socket=md.Bone(f'geran5_launch_{index:02}')
    socket.matrix=md.IDENTITY[:9]+(-40,side,-12)
    bones['body'].children.append(socket)
model.write(str(DEST/'su-25sm_geran5.mdl'))
model.write(str(STAGE/'su-25sm_geran5.mdl'))
for collection in bpy.data.collections:
    if collection.name.startswith(('geran5','su-25sm_geran5')):collection.hide_viewport=True
root,warnings=imp.import_mdl(bpy.context,str(STAGE/'su-25sm_geran5.mdl'),show_volumes=False,import_animations=True)
root.name='Su-25 - TWO GERAN-5';root.scale=(.06,)*3
# Use the same Russian skin selected by the game definition.
for mat in bpy.data.materials:
    if not mat.use_nodes:continue
    for node in mat.node_tree.nodes:
        if node.type=='TEX_IMAGE' and node.image and Path(node.image.filepath).name.lower()=='body.dds' and 'su25' in node.image.filepath.lower():
            node.image=bpy.data.images.load(str(STAGE/'textures/body#vksred10.dds'),check_existing=True)
for obj in bpy.context.view_layer.objects:obj.select_set(False)
root.select_set(True);bpy.context.view_layer.objects.active=root
bpy.context.view_layer.update()
for window in bpy.context.window_manager.windows:
    for area in window.screen.areas:
        if area.type=='VIEW_3D':
            space=area.spaces.active;space.shading.type='MATERIAL'
            space.overlay.show_extras=False;space.overlay.show_relationship_lines=False
            space.region_3d.view_location=(-1.2,0,1.5);space.region_3d.view_distance=23
            space.region_3d.view_rotation=Vector((6,-8,5)).to_track_quat('Z','Y');area.tag_redraw()
print({'root':root.name,'warnings':warnings,'payloads':['geran5_00','geran5_01'],'model':str(DEST/'su-25sm_geran5.mdl')})
