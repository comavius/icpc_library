#!/usr/bin/env python3
"""Run every oj-verify test, preserving both timestamp caches exactly as they were."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent


def main():
    files = [ROOT / '.verify-helper' / f'timestamps.{kind}.json' for kind in ['local', 'remote']]
    saved = {path: path.read_bytes() if path.exists() else None for path in files}
    try:
        for path in files:
            path.unlink(missing_ok=True)
        return subprocess.run(['oj-verify', 'run'], cwd=ROOT).returncode
    finally:
        for path, content in saved.items():
            if content is None:
                path.unlink(missing_ok=True)
            else:
                path.write_bytes(content)


if __name__ == '__main__':
    raise SystemExit(main())
