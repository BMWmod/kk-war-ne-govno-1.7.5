"""Compress large legacy RGB DDS files, retaining dimensions and every source mip.

Dry run by default; --apply writes only files passing round-trip image checks.
Normal/specular maps, non-2D images and non-RGB formats are deliberately skipped.
Requires Pillow and numpy. Existing compressed DDS files are never recompressed.
"""
import argparse
import io
import json
import re
import struct
import subprocess
from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]


def tracked_files():
    return [ROOT / p for p in subprocess.check_output(
        ['git', 'ls-files', '-z'], cwd=ROOT).decode('utf-8').split('\0') if p]


def compress(data):
    header = data[:128]
    height, width = struct.unpack_from('<II', header, 12)
    mip_count = max(1, struct.unpack_from('<I', header, 28)[0])
    bpp = struct.unpack_from('<I', header, 88)[0] // 8
    # Preserve existing mips instead of deriving them from a lossy top level.
    offset = 128
    images = []
    w, h = width, height
    for _ in range(mip_count):
        size = w * h * bpp
        level_header = bytearray(header)
        struct.pack_into('<II', level_header, 12, h, w)
        struct.pack_into('<I', level_header, 20, w * bpp)
        struct.pack_into('<I', level_header, 28, 1)
        with Image.open(io.BytesIO(level_header + data[offset:offset + size])) as image:
            images.append(image.convert('RGBA'))
        offset += size
        w, h = max(1, w // 2), max(1, h // 2)
    if offset != len(data):
        raise ValueError('Unexpected DDS payload length/padding')
    opaque = all(im.getchannel('A').getextrema() == (255, 255) for im in images)
    fmt = 'DXT1' if opaque else 'DXT5'
    levels = []
    worst_mean = worst_rms = worst_alpha = 0
    for im in images:
        buffer = io.BytesIO()
        im.save(buffer, format='DDS', pixel_format=fmt)
        encoded = buffer.getvalue()
        with Image.open(io.BytesIO(encoded)) as decoded:
            a = np.asarray(im, dtype=np.int16)
            b = np.asarray(decoded.convert('RGBA'), dtype=np.int16)
        error = np.abs(a - b).astype(np.float32)
        mean = float(error[:, :, :3].mean())
        rms = float(np.sqrt(np.mean(error[:, :, :3] ** 2)))
        alpha = float(error[:, :, 3].max())
        worst_mean, worst_rms, worst_alpha = max(worst_mean, mean), max(worst_rms, rms), max(worst_alpha, alpha)
        # Also preserve completely opaque/transparent mask pixels exactly.
        endpoints = (a[:, :, 3] == 0) | (a[:, :, 3] == 255)
        if mean > 3 or rms > 8 or alpha > 8 or np.any(error[:, :, 3][endpoints]):
            raise ValueError(f'Quality gate: mean={mean:.3f}, rms={rms:.3f}, alpha={alpha}')
        levels.append(encoded)
    out = bytearray(levels[0][:128])
    flags = struct.unpack_from('<I', out, 8)[0]
    struct.pack_into('<I', out, 8, flags | (0x20000 if mip_count > 1 else 0))
    struct.pack_into('<I', out, 28, mip_count)
    struct.pack_into('<I', out, 108, 0x1000 | (0x400008 if mip_count > 1 else 0))
    return bytes(out) + b''.join(level[128:] for level in levels), {
        'format': fmt, 'width': width, 'height': height, 'mips': mip_count,
        'rgb_mean_error': worst_mean, 'rgb_rms_error': worst_rms, 'alpha_max_error': worst_alpha,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    files = tracked_files()
    # Resolve auxiliary texture names conservatively, including skin variants.
    auxiliary = set()
    for p in files:
        if p.suffix.lower() == '.mtl':
            for name in re.findall(r'\{(?:bump|specular|normal)\s+"([^"]+)"', p.read_text(errors='replace'), re.I):
                auxiliary.add(Path(name.replace('\\', '/')).name.lower().split('.')[0].split('#')[0])
    changed, skipped = [], []
    for p in files:
        if p.suffix.lower() != '.dds' or not p.exists() or p.stat().st_size < 1024 * 1024:
            continue
        with p.open('rb') as stream:
            header = stream.read(128)
        if header[:4] != b'DDS ' or header[84:88] != b'\0' * 4:
            continue
        flags = struct.unpack_from('<I', header, 80)[0]
        bpp = struct.unpack_from('<I', header, 88)[0]
        caps2 = struct.unpack_from('<I', header, 112)[0]
        base = p.stem.lower().split('#')[0]
        if caps2 or not flags & 0x40 or bpp not in (24, 32) or base in auxiliary or re.search(r'(_bp|_sp|_n|_normal)$', base):
            continue
        data = p.read_bytes()
        try:
            result, metrics = compress(data)
        except (ValueError, OSError) as error:
            skipped.append({'path': p.relative_to(ROOT).as_posix(), 'reason': str(error)})
            continue
        if len(result) >= len(data):
            continue
        row = {'path': p.relative_to(ROOT).as_posix(), 'before': len(data), 'after': len(result), **metrics}
        if args.apply:
            p.write_bytes(result)
        changed.append(row)
        print(f"{len(data)/1048576:.2f} -> {len(result)/1048576:.2f} MiB {row['path']}", flush=True)
    report = {'applied': args.apply, 'changed': changed, 'skipped': skipped,
              'saved_bytes': sum(x['before'] - x['after'] for x in changed)}
    if args.report:
        args.report.write_text(json.dumps(report, indent=2), encoding='utf-8')
    print(f"{len(changed)} textures; {report['saved_bytes']/1048576:.2f} MiB DDS payload saved; {len(skipped)} skipped")


if __name__ == '__main__':
    main()
