#!/usr/bin/env python3
"""Run every oj-verify test, preserving both timestamp caches exactly as they were."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent


def main():
    files = [ROOT / '.verify-helper' / f'timestamps.{kind}.json' for kind in ['local', 'remote']]
    saved = {path: (path.read_bytes(), path.stat().st_mode) if path.exists() else None for path in files}
    try:
        for path in files:
            path.unlink(missing_ok=True)
        return subprocess.run(['oj-verify', 'run'], cwd=ROOT).returncode
    finally:
        for path, original in saved.items():
            if original is None:
                path.unlink(missing_ok=True)
            else:
                content, mode = original
                path.write_bytes(content)
                path.chmod(mode)


if __name__ == '__main__':
    raise SystemExit(main())
