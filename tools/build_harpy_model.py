"""Build the supplied Harpy OBJ into GEM without requiring a live Blender session."""
from pathlib import Path
import sys, math, copy, importlib, json
sys.dont_write_bytecode = True
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageEnhance

ROOT = Path(__file__).resolve().parents[1]
ADDON = Path.home()/'AppData/Roaming/Blender Foundation/Blender/5.2/extensions/user_default/gemwerk_io'
sys.path.insert(0, str(ADDON))
from formats import ply, mdl as md, anm as af
DEST = ROOT/'resource/entity/-vehicle/-modern/air_modern/usa/harpy'
TEX = ROOT/'resource/texture/common/model/harpy'
DEST.mkdir(parents=True, exist_ok=True)
TEX.mkdir(parents=True, exist_ok=True)
SOURCE = Path.home()/'Desktop/model_0.obj'

def build():
    vertices=[]; normals=[]; faces=[]
    for line in SOURCE.read_text().splitlines():
        parts=line.split()
        if not parts: continue
        if parts[0]=='v': vertices.append(tuple(map(float,parts[1:4])))
        elif parts[0]=='vn': normals.append(tuple(map(float,parts[1:4])))
        elif parts[0]=='f':
            corners=[]
            for field in parts[1:]:
                ids=field.split('/')
                vi=int(ids[0]);vi=vi-1 if vi>0 else len(vertices)+vi
                ni=int(ids[2])-1 if len(ids)>2 and ids[2] else None
                corners.append((vi,ni))
            for i in range(1,len(corners)-1):faces.append([corners[0],corners[i],corners[i+1]])
    v=np.array(vertices);ns=np.array(normals)
    # One atlas shared by the aircraft and its terminal-flight representation.
    rng=np.random.default_rng(17)
    pixels=np.empty((1024,1024,3),dtype=np.int16)
    pixels[:,:768]=(170,164,141);pixels[:512,768:]=(40,43,43);pixels[512:,768:]=(93,96,92)
    pixels+=rng.integers(-4,5,size=(1024,1024,1))
    atlas=Image.fromarray(pixels.astype('uint8'));draw=ImageDraw.Draw(atlas)
    def xy(x,y):return ((x+525)/1050*.748*1023,(426-y)/852*1023)
    for y in [-345,-245,-100,150,280]:draw.line([xy(-480,y),xy(480,y)],fill=(139,135,117),width=2)
    for x in [-340,-180,180,340]:draw.line([xy(x,-390),xy(x,140)],fill=(145,140,122),width=2)
    for x in [-300,300]:
        # Draw in native model coordinates, then project to the anisotropic atlas.
        # An ellipse in texture space becomes a circle on the planar wing.
        cx,cy=xy(x,-240);rx=35/1050*.748*1023;ry=35/852*1023
        draw.ellipse((cx-rx,cy-ry,cx+rx,cy+ry),fill=(207,205,184))
        for phase in [-math.pi/2,math.pi/2]:
            pts=[xy(x+28*math.cos(phase+i*2*math.pi/3),-240+28*math.sin(phase+i*2*math.pi/3)) for i in range(3)]
            draw.line(pts+[pts[0]],fill=(47,72,92),width=4)
    font=ImageFont.truetype('C:/Windows/Fonts/arialbd.ttf',18)
    draw.text(xy(-28,80),'H-017',font=font,fill=(60,62,55))
    atlas.save(TEX/'harpy_atlas.dds')
    (DEST/'harpy_atlas.mtl').write_text('{material simple\n {diffuse "$/model/harpy/harpy_atlas" {MipMap 1}}\n {blend none}\n}\n')
    groups={name:[] for name in ['body','wingl1','wingr1','engine','propeller']}
    preview=[];scale=50/1048.93;prop=np.array([-19.75,0,-.62])
    for face in faces:
        pts=v[[i for i,n in face]];c=pts.mean(axis=0)
        fn=np.cross(pts[1]-pts[0],pts[2]-pts[0]);length=np.linalg.norm(fn)
        if length<1e-8:continue
        fn/=length
        if abs(c[0])>110:kind='wingl1' if c[0]<0 else 'wingr1'
        elif c[1]<-402:kind='propeller'
        elif c[1]<-280:kind='engine'
        else:kind='body'
        region='dark' if c[1]>350 or kind=='propeller' else ('metal' if kind=='engine' else 'paint')
        uvs=[];norm=[]
        for (vi,ni),co in zip(face,pts):
            if region=='paint':
                u=(co[0]+525)/1050*.748;vv=(co[1]+426)/852
                if abs(fn[2])<.25:u=.32+(co[2]+77)/154*.1
            elif region=='dark':u=.78+(co[0]+100)/200*.17;vv=.6+(co[2]+77)/154*.3
            else:u=.78+(co[0]+100)/200*.17;vv=.05+(co[2]+77)/154*.3
            uvs.append((u,1-vv))
            n=ns[ni] if ni is not None else fn
            norm.append((n[1],n[0],n[2]))
        # Same handedness as the existing aircraft exporter, with original face winding.
        points=pts[:,[1,0,2]]*scale
        if kind=='propeller':points=points-prop
        groups[kind].append((points,norm,uvs))
        world=pts[:,[1,0,2]]*scale*.06;world[:,1]*=-1
        worldnorm=np.array(norm);worldnorm[:,1]*=-1
        preview.append((world,worldnorm,np.array(uvs)))
    for name,triangles in groups.items():
        pos=[];nrm=[];uv=[];indices=[];lookup={}
        for ps,nn,tex in triangles:
            ids=[]
            for p,n,t in zip(ps,nn,tex):
                key=tuple(p)+tuple(n)+tuple(t)
                if key not in lookup:
                    lookup[key]=len(pos);pos.append(tuple(p));nrm.append(tuple(n));uv.append(tuple(t))
                ids.append(lookup[key])
            indices.append(tuple(ids))
        section=ply.MeshSection();section.textures=['harpy_atlas.mtl'];section.face_count=len(indices)
        section.flags=ply.FLAG_MATERIAL|ply.FLAG_LIGHT
        data=ply.build([section],pos,nrm,[uv],indices)
        ply.write(str(DEST/(name+'.ply')),data)
    model=md.Model.read(str(ROOT/'resource/entity/-vehicle/-modern/air_modern/rus/geran5/geran5.mdl'))
    model.header=['; Harpy PRR: model_0.obj supplied by user.']
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
    bone('propeller',position=tuple(prop),view='propeller')
    for name in ['part1','part4','tail1','tail2','body3','body4']:bone(name)
    bone('visor_ols',position=(18,0,0));bone('aiming_mark',position=(20,0,0))
    bone('foresight1_rot',position=(0,0,0));bones['foresight1_rot'].limits=[-180,180]
    bones['foresight1'].matrix=(1,0,0,0,0,-1,0,1,0,0,0,0);bones['foresight1'].limits=[-80,80]
    launch=bone('foresight_spawn')
    for parent in bones.values():
        if launch in parent.children:parent.children.remove(launch)
    bones['foresight1'].children.append(launch)
    # Cancel the sight's fixed pitch-axis basis while retaining its live aiming rotation.
    launch.matrix=(1,0,0,0,0,1,0,-1,0,0,0,0)
    bone('fx_starter',position=(-19,0,-1))
    for name in ['ir_1gen_emitter','ir_2gen_emitter']:bone(name,position=(-17,0,0))
    bone('pivot_front',position=(14,0,-3.7));bone('pivot_back',position=(-14,0,-3.7))
    bone('supportfront');bone('supportleft',position=(0,6,0));bone('supportright',position=(0,-6,0))
    bones['rudder_proj'].matrix=(1,0,0,0,-1,0,0,0,-1,0,0,0)
    bones['elevator_proj'].matrix=(1,0,0,0,0,1,0,-1,0,0,0,0)
    model.volumes=[];model.shapes=[]
    def box(name,center,size,component=None):
        vol=md.Volume(name);vol.bone='body_systems';vol.shape='box';vol.size=list(size)
        vol.matrix=md.IDENTITY[:9]+tuple(center);vol.component=component;model.volumes.append(vol)
    box('body',(0,0,-.6),(38,5,5));box('armor1',(0,0,-.6),(38.1,5.1,5.1))
    box('wingl1',(-9,13,-.4),(14,24,.8));box('wingr1',(-9,-13,-.4),(14,24,.8))
    box('tail',(-16,0,-.4),(5,12,1))
    box('tail1',(-15,-16,1),(7,.5,5),'tail');box('tail2',(-15,16,1),(7,.5,5),'tail')
    box('engine',(-16,0,-.5),(5,5,4))
    for name,center,size in [('fuel_tank_internal_a',(-3,0,0),(10,3,3)),('fuel_tank_internal_b',(-10,0,0),(5,3,3)),('electronics',(16,0,0),(5,3,3)),('hydrosystem',(0,0,0),(3,2,2)),('ammo_storage_autocannon',(8,0,0),(8,3,3))]:box(name,center,size)
    for name in ['pilot_panel','ppu','ptur','ptur1','ols']:box(name,(13,0,0),(2,2,2))
    model.sequences=[]
    for name in ['basis','on_start','engine_start','engine_work','engine_stop','fly','damage_fly','move']:
        seq=md.Sequence(name);seq.speed=1;model.sequences.append(seq)
        spin=name in ['engine_start','engine_work','move'];frames=31 if name=='engine_start' else (9 if spin else 2)
        tracks={0:[(md.IDENTITY,1)]*frames};names=['body']
        if spin:
            names.append('propeller');tracks[1]=[]
            for i in range(frames):
                a=2*math.pi*i/(frames-1)
                tracks[1].append(((1,0,0,0,math.cos(a),math.sin(a),0,-math.sin(a),math.cos(a),*prop),1))
        af.write(str(DEST/(name+'.anm')),af.from_tracks(names,frames,tracks))
    model.write(str(DEST/'harpy.mdl'))
    ammo=copy.deepcopy(model);ammo.bones[0].matrix=(1,0,0,0,0,1,0,1,0,0,0,0)
    ammo.sequences=[s for s in ammo.sequences if s.name=='move'];ammo.write(str(DEST/'harpy_ammo.mdl'))
    render_icons(preview,atlas)
    print('Harpy model written:',sum(len(x) for x in groups.values()),'triangles;',DEST)

def render_icons(triangles,atlas):
    # Orthographic textured rasterizer for the purchase icon, no live app required.
    camera=np.array([4.,-6.,6.]);camera/=np.linalg.norm(camera)
    right=np.cross([0,0,1],camera);right/=np.linalg.norm(right)
    up=np.cross(camera,right)
    points=np.concatenate([t[0] for t in triangles]);coords=np.column_stack((points@right,points@up))
    lo=coords.min(0);hi=coords.max(0);center=(lo+hi)/2
    width,height=832,416;scale=min(width*.9/(hi-lo)[0],height*.9/(hi-lo)[1])
    rgba=np.zeros((height,width,4),dtype=np.uint8);depth=np.full((height,width),-np.inf)
    texture=np.asarray(atlas);light=np.array([1.,-3.,5.]);light/=np.linalg.norm(light)
    for pts,normal,uv in triangles:
        xy=np.column_stack(((pts@right-center[0])*scale+width/2,height/2-(pts@up-center[1])*scale))
        a,b,c=xy;den=(b[1]-c[1])*(a[0]-c[0])+(c[0]-b[0])*(a[1]-c[1])
        if abs(den)<1e-6:continue
        x0=max(0,int(np.floor(xy[:,0].min())));x1=min(width,int(np.ceil(xy[:,0].max()))+1)
        y0=max(0,int(np.floor(xy[:,1].min())));y1=min(height,int(np.ceil(xy[:,1].max()))+1)
        if x1<=x0 or y1<=y0:continue
        yy,xx=np.mgrid[y0:y1,x0:x1];xx=xx+.5;yy=yy+.5
        w0=((b[1]-c[1])*(xx-c[0])+(c[0]-b[0])*(yy-c[1]))/den
        w1=((c[1]-a[1])*(xx-c[0])+(a[0]-c[0])*(yy-c[1]))/den;w2=1-w0-w1
        z=pts@camera;zz=w0*z[0]+w1*z[1]+w2*z[2]
        mask=(w0>=0)&(w1>=0)&(w2>=0)&(zz>depth[y0:y1,x0:x1])
        if not mask.any():continue
        uu=w0*uv[0,0]+w1*uv[1,0]+w2*uv[2,0];vv=w0*uv[0,1]+w1*uv[1,1]+w2*uv[2,1]
        colors=texture[np.clip((vv*1023).astype(int),0,1023),np.clip((uu*1023).astype(int),0,1023)]
        n=normal.mean(0);n/=max(np.linalg.norm(n),1e-8);shade=.65+.35*abs(n@light)
        tile=rgba[y0:y1,x0:x1];tile[mask,:3]=(colors[mask]*shade).astype('uint8');tile[mask,3]=255
        depth[y0:y1,x0:x1][mask]=zz[mask]
    icon=Image.fromarray(rgba)
    for unit in ['harpy_prr','harpy_prr_carrier']:
        for folder,size in [('unit_icon',(104,52)),('unit_icon_small',(78,39))]:
            dest=ROOT/'resource/interface/scene'/folder;dest.mkdir(parents=True,exist_ok=True)
            for state,brightness in enumerate([1,1.15,.8,.5]):
                image=icon.resize(size,Image.Resampling.LANCZOS);alpha=image.getchannel('A')
                image=ImageEnhance.Brightness(image).enhance(brightness);image.putalpha(alpha)
                image.save(dest/f'{unit}_{state:02}.tga',compression=None)

if __name__=='__main__':build()
