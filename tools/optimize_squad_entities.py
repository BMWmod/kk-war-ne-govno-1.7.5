"""Resolve optional vehicle crew slots and reuse proven identical entity types.

Uses existing vehicle templates as the source of country/crew ordering. Keeps
purchase IDs, prices, timers, groups, tags and explicit crew entries unchanged.
Legacy DEF names remain available to maps/saves; new purchases use canonical IDs.
Default is a dry run; --apply writes files, --check validates the installed result.
"""
import argparse
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
UNITS = ROOT / 'resource/set/multiplayer/units'
ALIASES = {
    '2c1_rus': '2c1', 'tochka_y_wagner': 'tochka_y',
    'brdm2_un': 'brdm2', 'brdm2kz': 'brdm2', 'btr4e1i': 'btr4e1',
    'milan_stan_un': 'milan_stan_2', '2b11_odkb': '2b11_isis',
    'metis_m_odkb': 'metis_m', 'ptur_tow_un': 'ptur_tow_nato',
    '9k33_osa_akm_isis': '9k33_osa_akm', 'ypr_765_un': 'ypr_765',
}
EXPLICIT = '''; Exact content is supplied by the purchasing squad: no optional crew slots.
(define "v_explicit"
    ("generic_v" c(%c) sc(%sc) t(%t %s %brig) g(%g) i(%i) b(%b) cw(%cw) cp(%cp))
)

'''.replace('\n', '\r\n')


def mask_comments(text):
    # Preserve offsets and quoted semicolons. GEM comments start with ';'.
    return re.sub(r'"(?:[^"\\]|\\.)*"|;[^\r\n]*',
                  lambda m: m[0] if m[0].startswith('"') else ' ' * len(m[0]), text)


def closing(text, start):
    depth, quoted = 0, False
    for i in range(start, len(text)):
        c = text[i]
        if c == '"' and (i == 0 or text[i-1] != '\\'):
            quoted = not quoted
        if quoted:
            continue
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if depth == 0:
                return i + 1
    raise ValueError(f'Unclosed macro at {start}')


def arguments(call):
    args = {}
    pos = re.match(r'\(\s*"[^"]+"', call).end()
    while True:
        match = re.search(r'([A-Za-z][A-Za-z0-9_]*)\s*\(', call[pos:])
        if not match:
            break
        start = pos + match.end() - 1
        end = closing(call, start)
        args[match[1]] = call[start+1:end-1].strip()
        pos = end
    return args


def templates(text):
    clean = mask_comments(text)
    result = {}
    for m in re.finditer(r'\(define\s+"([^"]+)"', clean):
        body = clean[m.start():closing(clean, m.start())]
        content = re.search(r'\{content\s+"([^"]*)"\}', body)
        if content:
            result[m[1]] = content[1]
    return result


def resolve_content(template, args):
    result, missing = [], 0
    for token in re.findall(r'[()]|[^\s()]+', template):
        variables = re.findall(r'%([A-Za-z0-9_]+)', token)
        absent = [key for key in variables if not args.get(key)]
        if absent:
            # A wholly unspecified optional soldier must produce no entity ID.
            if all(re.fullmatch(r'n[1-9ab]', key) for key in absent):
                missing += 1
                continue
            raise ValueError(f'Missing required arguments {absent}')
        result.append(re.sub(r'%([A-Za-z0-9_]+)', lambda m: args[m[1]], token))
    return ' '.join(result), missing


def canonical_content(content):
    tokens = content.split()
    for i, token in enumerate(tokens):
        name, sep, count = token.partition(':')
        if name in ALIASES:
            tokens[i] = ALIASES[name] + (sep + count if sep else '')
    return ' '.join(tokens)


def verify_aliases():
    paths = subprocess.check_output(['git', 'ls-files', '-z'], cwd=ROOT).decode().split('\0')
    definitions = {}
    for path in paths:
        if path.endswith('.def') and '/-vehicle/' in path:
            definitions.setdefault(Path(path).stem, []).append(ROOT / path)
    for alias, canonical in ALIASES.items():
        assert len(definitions.get(alias, [])) == len(definitions.get(canonical, [])) == 1, (alias, canonical)
        a, b = definitions[alias][0], definitions[canonical][0]
        # Same folder is essential for relative includes/materials/model lookup.
        assert a.parent == b.parent, (alias, canonical)
        normalize = lambda p: re.findall(r'"[^"]*"|[^\s]+', mask_comments(p.read_bytes().decode('latin-1')))
        assert normalize(a) == normalize(b), (alias, canonical, 'different definition')
        assert re.search(r'\{extension\s+"[^"]+\.mdl"', a.read_bytes().decode('latin-1'), re.I)


def transform(text, defs):
    source_lines = text.splitlines(keepends=True)
    clean = mask_comments(text)
    edits, rows = [], []
    for m in re.finditer(r'\(\s*"([^"]+)"', clean):
        kind = m[1]
        end = closing(clean, m.start())
        call = clean[m.start():end]
        args = arguments(call)
        if kind.startswith('v3') and kind in defs:
            content, missing = resolve_content(defs[kind], args)
            updated = canonical_content(content)
            original_call = text[m.start():end]
            changed_call = re.sub(r'^(\(\s*")[^"]+"', r'\1v_explicit"', original_call)
            edits.append((m.start(), end, changed_call + ' {content "' + updated + '"}'))
            rows.append((kind, content, updated, missing))
            continue
        # Implicit '*' templates use the purchase ID as the vehicle ID.
        # Keep the ID/UI but use existing explicit-vehicle nation templates.
        if kind not in ('v', 'vs'):
            continue
        prefix = clean[:m.start()]
        match = re.search(r'\{\s*"([^"\r\n]+)"[^\r\n]*$', prefix)
        if not match or match[1] not in ALIASES:
            continue
        alias = match[1]
        assert args.get('s') and args.get('n'), (alias, args)
        old = text[m.start():end]
        new = re.sub(r'^(\(\s*")[^"]+"', lambda t: t[1] + kind + '_nation1"', old)
        new = new[:-1] + f' c1({ALIASES[alias]}) crew_nation({args["s"]}) )'
        edits.append((m.start(), end, new))
        rows.append((kind, alias, ALIASES[alias], 0))
    for start, end, replacement in reversed(edits):
        text = text[:start] + replacement + text[end:]
    updated_lines = text.splitlines(keepends=True)
    assert len(source_lines) == len(updated_lines)
    text = ''.join(re.sub(r'[ \t]+(\r?\n|$)', r'\1', new) if old != new else new
                   for old, new in zip(source_lines, updated_lines))
    return text, rows


def check_installed():
    verify_aliases()
    count = 0
    for path in UNITS.glob('nz_*.set'):
        text = mask_comments(path.read_bytes().decode('latin-1'))
        assert not re.search(r'\(\s*"v3[^"\s]*"', text), path
        for content in re.findall(r'\{content\s+"([^"]*)"\}', text):
            assert '%' not in content, (path, content)
            for token in content.split():
                if token.startswith('mp2/'):
                    breed = token.split('/')[-1].split(':')[0]
                    assert breed and not re.fullmatch(r'[0-9]+[a-z]?', breed), (path, content)
            assert content.count('(') == content.count(')'), (path, content)
            assert not any(t.split(':')[0] in ALIASES for t in content.split()), (path, content)
            count += 1
    for name in ('vehicles.set', 'vehicles_nz.set'):
        assert (UNITS/name).read_bytes().count(b'(define "v_explicit"') == 1
    print(f'Validated {count} explicit vehicle squads and {len(ALIASES)} identical-definition mappings')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        check_installed()
        return
    verify_aliases()
    defs = templates((UNITS/'vehicles.set').read_bytes().decode('latin-1'))
    defs.update(templates((UNITS/'vehicles_nz.set').read_bytes().decode('latin-1')))
    planned, all_rows = {}, []
    for path in sorted(UNITS.glob('nz_*.set')):
        text = path.read_bytes().decode('latin-1')
        new, rows = transform(text, defs)
        if rows:
            planned[path] = new.encode('latin-1')
            all_rows.extend(rows)
            print(path.name, len(rows), 'squads;', sum(r[3] for r in rows), 'undefined crew slots removed')
    for name in ('vehicles.set', 'vehicles_nz.set'):
        path = UNITS/name
        data = path.read_bytes()
        if b'(define "v_explicit"' not in data:
            marker = b';plane'
            assert marker in data
            planned[path] = data.replace(marker, EXPLICIT.encode() + marker, 1)
    print('Total squads:', len(all_rows), 'missing crew slots:', sum(r[3] for r in all_rows),
          'canonical vehicle substitutions:', sum(r[1] != r[2] for r in all_rows))
    if args.apply:
        for path, data in planned.items():
            path.write_bytes(data)
        check_installed()


if __name__ == '__main__':
    main()
