#!/usr/bin/env python3
"""Compile tests and execute Hello World assertion tests without network or caches."""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parent.parent
HELLO = 'ITP1_1_A'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('paths', nargs='*', help='test files or directories (default: test/)')
    parser.add_argument('--unit', action='store_true', help='only *.unit.test.cpp tests')
    parser.add_argument('--list', action='store_true', help='list discovered tests without compiling')
    args = parser.parse_args()
    found = set()
    for item in args.paths or ['test']:
        path = ROOT / item
        if not path.exists():
            parser.error(f'path does not exist: {item}')
        for file in path.rglob('*.cpp') if path.is_dir() else [path]:
            if '.test.' in file.name and (not args.unit or file.name.endswith('.unit.test.cpp')):
                found.add(file.resolve())
    if not found:
        parser.error('no tests found')
    failed = 0
    with tempfile.TemporaryDirectory(prefix='icpc-tests-') as directory:
        for index, file in enumerate(sorted(found)):
            label = str(file.relative_to(ROOT))
            if args.list:
                print(label)
                continue
            command = shlex.split(os.environ.get('CXX', 'g++'))
            command += ['-std=c++20', '-Wall', '-Wextra', '-Wshadow', '-O2']
            command += shlex.split(os.environ.get('CXXFLAGS', ''))
            # Assertions are the oracle for unit tests, even with inherited release flags.
            command += ['-UNDEBUG', '-I', str(ROOT), str(file), '-o', f'{directory}/{index}']
            result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
            if result.returncode:
                print(f'FAIL compile {label}\n{result.stderr}', flush=True)
                failed += 1
                continue
            if HELLO not in file.read_text():
                print(f'COMPILED {label} (judge input required)', flush=True)
                continue
            try:
                result = subprocess.run([f'{directory}/{index}'], input='', cwd=ROOT,
                                        capture_output=True, text=True, timeout=60)
                if result.returncode or result.stdout.split() != ['Hello', 'World']:
                    print(f'FAIL run {label} (exit={result.returncode})\n{result.stdout}{result.stderr}', flush=True)
                    failed += 1
                else:
                    print(f'PASS {label}', flush=True)
            except subprocess.TimeoutExpired:
                print(f'FAIL timeout {label}', flush=True)
                failed += 1
    if not args.list:
        print(f'{len(found)} tests, {failed} failed')
    return bool(failed)


if __name__ == '__main__':
    raise SystemExit(main())
