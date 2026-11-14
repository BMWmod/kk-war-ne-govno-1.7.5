"""Regression checks for squad content migration, without launching the game."""
import re
import subprocess
import unittest

from optimize_squad_entities import (
    ROOT, UNITS, ALIASES, arguments, closing, mask_comments,
    templates, transform, verify_aliases,
)


def source(path):
    return subprocess.check_output(['git', 'show', 'HEAD:' + path.relative_to(ROOT).as_posix()], cwd=ROOT).decode('latin-1')


def calls(text):
    text = mask_comments(text)
    for m in re.finditer(r'\(\s*"([^"]+)"', text):
        end = closing(text, m.start())
        yield m[1], arguments(text[m.start():end]), end, text[m.start():end]


class SquadMigrationTests(unittest.TestCase):
    def test_missing_slots_do_not_inherit_numeric_n(self):
        before = '{"test" ("v3" s(rus) c1(bmp2) n(2) n1(tankman:2) n3(mso_rpg:1))}'
        defs = {'v3': '%c1 ( mp2/%s/%n1 mp2/%s/%n2 mp2/%s/%n3 mp2/%s/%na)'}
        after, rows = transform(before, defs)
        self.assertIn('{content "bmp2 ( mp2/rus/tankman:2 mp2/rus/mso_rpg:1 )"}', after)
        self.assertEqual(rows[0][3], 2)

    def test_mixed_country_crew_and_comments(self):
        before = '; ("v3" n(999))\r\n{"test" ("v3bgcz" s(nato) c1(tank) n1(driver:1) n2(gunner:2))}'
        defs = {'v3bgcz': '%c1 ( mp2/brit/%n1 mp2/cz/%n2 mp2/cz/%n3)'}
        after, _ = transform(before, defs)
        self.assertTrue(after.startswith('; ("v3" n(999))\r\n'))
        self.assertIn('{content "tank ( mp2/brit/driver:1 mp2/cz/gunner:2 )"}', after)

    def test_alias_crew_and_purchase_identity(self):
        before = '{"brdm2kz" {fore 1} ("vs" s(odkb) n(4) sc(45) c(420))}'
        after, _ = transform(before, {})
        self.assertTrue(after.startswith('{"brdm2kz" {fore 1}'))
        self.assertIn('"vs_nation1" s(odkb) n(4) sc(45) c(420)', after)
        self.assertIn('c1(brdm2) crew_nation(odkb)', after)

    def test_alias_definitions_and_model_resolution(self):
        verify_aliases()

    def test_entire_catalog_preserves_defined_crew_and_purchase_parameters(self):
        definitions = templates(source(UNITS/'vehicles.set'))
        nz_definitions = templates(source(UNITS/'vehicles_nz.set'))
        for name in definitions.keys() & nz_definitions.keys():
            if name.startswith('v3'):
                self.assertEqual(definitions[name], nz_definitions[name])
        definitions.update(nz_definitions)
        checked, substitutions = 0, 0
        for path in sorted(UNITS.glob('nz_*.set')):
            before, after = source(path), path.read_bytes().decode('latin-1')
            original_calls = list(calls(before))
            result_calls = list(calls(after))
            self.assertEqual(len(original_calls), len(result_calls), path.name)
            cleaned_after = mask_comments(after)
            for old, new in zip(original_calls, result_calls):
                kind, old_args, _, _ = old
                new_kind, new_args, end, _ = new
                if kind.startswith('v3') and kind in definitions:
                    self.assertEqual(new_kind, 'v_explicit')
                    self.assertEqual(old_args, new_args)  # Includes all economy/UI metadata.
                    content_match = re.match(r'\s*\{content\s+"([^"]*)"\}', cleaned_after[end:])
                    self.assertIsNotNone(content_match, path.name)
                    actual_tokens = content_match[1].split()
                    # Independently enumerate only the explicitly supplied crew
                    # keys, following the country/order in the old template.
                    expected_crew = []
                    for country, slot in re.findall(r'mp2/([^ /]+)/%(n[1-9ab])', definitions[kind]):
                        if old_args.get(slot):
                            country = old_args['s'] if country == '%s' else country
                            expected_crew.append('mp2/' + country + '/' + old_args[slot])
                    self.assertEqual([t for t in actual_tokens if t.startswith('mp2/')], expected_crew, path.name)
                    vehicle = old_args['c1']
                    self.assertEqual(actual_tokens[0], ALIASES.get(vehicle, vehicle), path.name)
                    self.assertEqual(actual_tokens.count('('), 1)
                    self.assertEqual(actual_tokens.count(')'), 1)
                    checked += 1
                    substitutions += vehicle in ALIASES
                elif new_kind in ('v_nation1', 'vs_nation1') and kind in ('v', 'vs'):
                    self.assertEqual({k:v for k,v in new_args.items() if k not in ('c1','crew_nation')}, old_args)
                    self.assertEqual(new_args['crew_nation'], old_args['s'])
                    self.assertIn(new_args['c1'], ALIASES.values())
                    substitutions += 1
                else:
                    self.assertEqual(old[:2], new[:2])
            # New content clauses/macros are the only permitted changes. This
            # catches moved braces, edits to purchase names, timing and comments.
            expected, _ = transform(before, definitions)
            self.assertEqual(after.replace('\r\n', '\n'), expected.replace('\r\n', '\n'), path.name)
        self.assertEqual(checked, 311)
        self.assertEqual(substitutions, 10)

    def test_idempotent_migration(self):
        definitions = templates((UNITS/'vehicles_nz.set').read_bytes().decode('latin-1'))
        for path in UNITS.glob('nz_*.set'):
            text = path.read_bytes().decode('latin-1')
            updated, rows = transform(text, definitions)
            self.assertEqual(updated, text)
            self.assertEqual(rows, [])


if __name__ == '__main__':
    unittest.main()
