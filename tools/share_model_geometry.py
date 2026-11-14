"""Share byte-identical PLY resources in model VolumeView links.

Default: report only. --apply: rewrite links, never meshes or bone transforms.
--check: compare installed models to HEAD; permit only equivalent PLY links.
--cross-folders additionally requires static geometry and identical materials
with absolute texture references; uses the existing standalone Gemwerk reader.
The old PLY files remain available for inherited models and external maps.
"""
import argparse
import hashlib
import re
import subprocess
from collections import Counter, defaultdict
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VIEW = re.compile(rb'(\{VolumeView\s+")([^"\r\n]+)(")', re.I)


def tracked():
    return [ROOT / p.decode('utf-8') for p in subprocess.check_output(
        ['git', 'ls-files', '-z', '--', 'resource/entity'], cwd=ROOT).split(b'\0') if p]


def local_mesh(model, ref):
    # Do not change absolute paths or material lookup directories.
    if b'/' in ref or b'\\' in ref or not ref.lower().endswith(b'.ply'):
        return None
    try:
        return model.parent / ref.decode('ascii')
    except UnicodeDecodeError:
        return None


def mesh_path(model, ref):
    if ref.startswith(b'/entity/') and b'..' not in ref:
        return ROOT / 'resource' / ref[1:].decode('ascii')
    return local_mesh(model, ref)


@lru_cache(None)
def portable_materials(mesh):
    # Cross-directory sharing is limited to static meshes whose local materials
    # are byte-identical and use ONLY absolute texture references. Different
    # camouflage, local texture names, animated/skinned meshes are excluded.
    if 'humanskin' in mesh.parts:
        return None
    from build_geran5_atlas import ply_module
    global PLY_READER
    if 'PLY_READER' not in globals():
        PLY_READER = ply_module()
    try:
        obj = PLY_READER.read(str(mesh))
        materials = []
        for section in obj.meshes:
            if section.flags & PLY_READER.FLAG_SKINNED:
                return None
            for name in section.textures:
                if '/' in name or '\\' in name or not name.lower().endswith('.mtl'):
                    return None
                data = (mesh.parent / name).read_bytes()
                # Comments do not participate in resolution; preserve strings.
                active = re.sub(rb'"[^"\r\n]*"|;[^\r\n]*',
                                lambda m: m[0] if m[0].startswith(b'"') else b'', data)
                refs = re.findall(rb'"([^"\r\n]*)"', active)
                if not refs or any(not r.startswith((b'$/', b'/')) for r in refs):
                    return None
                if b'include' in active.lower() or b'(' in active:
                    return None
                materials.append((name, data))
        return tuple(materials) if materials else None
    except (OSError, ValueError, PLY_READER.PlyError):
        return None


def plan(paths, cross_folders=False):
    models = {p: p.read_bytes() for p in paths if p.suffix.lower() == '.mdl'}
    uses = Counter()
    for model, data in models.items():
        for match in VIEW.finditer(data):
            mesh = mesh_path(model, match[2])
            if mesh and mesh.is_file():
                uses[mesh] += 1
    sizes = defaultdict(list)
    for mesh in uses:
        sizes[(None if cross_folders else mesh.parent, mesh.stat().st_size)].append(mesh)
    aliases = {}
    groups = 0
    for candidates in sizes.values():
        if len(candidates) < 2:
            continue
        hashes = defaultdict(list)
        for mesh in candidates:
            hashes[hashlib.sha256(mesh.read_bytes()).digest()].append(mesh)
        for copies in hashes.values():
            if len(copies) < 2:
                continue
            if cross_folders:
                compatible = defaultdict(list)
                for mesh in copies:
                    signature = portable_materials(mesh)
                    if signature is not None:
                        compatible[signature].append(mesh)
                batches = compatible.values()
            else:
                batches = [copies]
            for batch in batches:
                if len(batch) < 2:
                    continue
                groups += 1
                canonical = min(batch, key=lambda p: (-uses[p], p.as_posix().lower()))
                for mesh in batch:
                    if mesh != canonical:
                        assert mesh.read_bytes() == canonical.read_bytes()
                        aliases[mesh] = canonical
    edits = {}
    references = 0
    for model, data in models.items():
        def replace(match):
            nonlocal references
            target = aliases.get(mesh_path(model, match[2]))
            if target is None:
                return match[0]
            references += 1
            ref = target.name if target.parent == model.parent else '/' + target.relative_to(ROOT / 'resource').as_posix()
            return match[1] + ref.encode('ascii') + match[3]
        updated = VIEW.sub(replace, data)
        if updated != data:
            edits[model] = updated
    print(f'{groups} used duplicate groups; {len(aliases)} redundant PLY paths; '
          f'{references} references in {len(edits)} models; '
          f'{sum(p.stat().st_size for p in aliases):,} duplicate source bytes')
    return edits


def check(paths):
    checked = 0
    before_paths, after_paths = set(), set()
    changed = set(subprocess.check_output(
        ['git', 'diff', '--name-only', '-z', '--', 'resource/entity'], cwd=ROOT).decode().split('\0'))
    for model in paths:
        relative = model.relative_to(ROOT).as_posix()
        if model.suffix.lower() != '.mdl' or relative not in changed:
            continue
        # Git may normalize CRLF while the working model keeps CRLF.
        current = model.read_bytes().replace(b'\r\n', b'\n')
        previous = subprocess.check_output(['git', 'show', 'HEAD:' + relative], cwd=ROOT).replace(b'\r\n', b'\n')
        if current == previous:
            continue
        old_refs, new_refs = list(VIEW.finditer(previous)), list(VIEW.finditer(current))
        before_paths.update(mesh_path(model, m[2]) for m in old_refs)
        after_paths.update(mesh_path(model, m[2]) for m in new_refs)
        assert len(old_refs) == len(new_refs), relative
        assert VIEW.sub(rb'\1<mesh>\3', previous) == VIEW.sub(rb'\1<mesh>\3', current), relative
        for old, new in zip(old_refs, new_refs):
            if old[2] == new[2]:
                continue
            a, b = mesh_path(model, old[2]), mesh_path(model, new[2])
            assert a and b, relative
            assert a.read_bytes() == b.read_bytes(), (relative, old[2], new[2])
            if a.parent != b.parent:
                assert portable_materials(a) is not None, (relative, a)
                assert portable_materials(a) == portable_materials(b), (relative, a, b)
            checked += 1
    print(f'PASS: {checked} changed links resolve to identical geometry and equivalent materials; '
          'all other model bytes unchanged')
    removed = {p for p in before_paths - after_paths if p and p.is_file()}
    print(f'Changed models now reference {len(removed)} fewer unique geometry paths '
          f'({sum(p.stat().st_size for p in removed):,} source bytes). '
          'This is not a measurement of game RAM.')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--apply', action='store_true')
    mode.add_argument('--check', action='store_true')
    parser.add_argument('--cross-folders', action='store_true',
                        help='Only static meshes with identical materials using absolute texture paths')
    args = parser.parse_args()
    paths = tracked()
    if args.check:
        check(paths)
    else:
        edits = plan(paths, args.cross_folders)
        if args.apply:
            for path, data in edits.items():
                path.write_bytes(data)
