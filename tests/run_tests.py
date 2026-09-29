"""Run each C++ regression in isolation, including crashes and timeouts."""
import pathlib
import subprocess
import sys

binary = str(pathlib.Path(__file__).with_name("regression").resolve())
names = subprocess.run([binary], capture_output=True, text=True, check=False).stdout.splitlines()
if not names:
    raise SystemExit("No regression tests discovered")
failures = []
for name in names:
    try:
        result = subprocess.run([binary, name], capture_output=True, text=True, timeout=5)
        if result.returncode:
            failures.append(name)
            print(f"FAIL {name}: exit {result.returncode}\n{result.stderr}")
        else:
            print(f"PASS {name}")
    except subprocess.TimeoutExpired:
        failures.append(name)
        print(f"FAIL {name}: timeout")
print(f"{len(names) - len(failures)}/{len(names)} regression checks passed")
sys.exit(bool(failures))
