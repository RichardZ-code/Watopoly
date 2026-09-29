"""Run cases in separate processes so a crash is reported as a test failure."""
import pathlib
import subprocess
import tempfile
import unittest

BINARY = pathlib.Path(__file__).resolve().parent / "regressions"
CASES = (
    "initial_level exact_cash insufficient_cash improvement_bounds sell_improvement "
    "mortgaged_improvement money_for_property property_for_money property_exchange "
    "rejected_trade malformed_money self_trade unowned_unmortgage unowned_gym "
    "unowned_residence mortgaged_rent trade_save_load zero_player_save"
).split()

class Regressions(unittest.TestCase):
    pass

def case(name):
    def run(self):
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run([str(BINARY), name], cwd=directory,
                                    capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
    return run

for name in CASES:
    setattr(Regressions, "test_" + name, case(name))

if __name__ == "__main__":
    unittest.main(verbosity=2)
