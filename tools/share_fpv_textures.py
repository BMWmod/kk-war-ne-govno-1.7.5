"""Route byte-identical FPV DDS textures through one global cache key.

Original local files are retained for external model authoring. Only explicit
material diffuse references are changed; different-resolution images stay separate.
"""
import hashlib
import re
import shutil
from collections import defaultdict
from pathlib import Path

from optimize_mod_dds import ROOT, tracked_files


def install():
    files = tracked_files()
    groups = defaultdict(list)
    materials = [p for p in files if p.suffix == '.mtl' and 'fpv' in str(p).lower()]
    for p in files:
        if p.suffix != '.dds' or 'fpv' not in str(p).lower() or p.stat().st_size < 500000:
            continue
        # Skinned textures need a family-wide redirect, not an individual copy.
        if '#' in p.name or list(p.parent.glob(p.stem + '#*')):
            continue
        groups[hashlib.sha256(p.read_bytes()).hexdigest()].append(p)
    total, edits, shared_count = 0, 0, 0
    for digest, paths in groups.items():
        if len(paths) < 2:
            continue
        names = {p.parent: p.name[:-4] for p in paths}
        used = set()
        changes = []
        shared_name = paths[0].stem.replace('.tga', '') + '_' + digest[:12]
        target = ROOT / 'resource/texture/common/model/fpv_shared' / (shared_name + '.dds')
        for material in materials:
            if material.parent not in names:
                continue
            old = material.read_bytes()
            pattern = rb'(\{diffuse\s+")' + re.escape(names[material.parent].encode()) + rb'(")'
            new = re.sub(pattern, lambda m: m[1] + ('$/model/fpv_shared/' + shared_name).encode() + m[2], old)
            if new != old:
                used.add(material.parent)
                changes.append((material, new))
        if len(used) < 2:
            continue
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(paths[0], target)
        assert hashlib.sha256(target.read_bytes()).hexdigest() == digest
        for material, data in changes:
            material.write_bytes(data)
        total += (len(used) - 1) * (paths[0].stat().st_size - 128)
        edits += len(changes)
        shared_count += 1
        print(f'{shared_name}: {len(used)} local texture identities -> 1')
    print(f'{edits} materials, {shared_count} shared DDS; {total/1048576:.2f} MiB duplicate payload avoided if all variants load')


if __name__ == '__main__':
    install()
