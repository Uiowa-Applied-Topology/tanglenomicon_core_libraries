"""@@@TODO:Plz fill out """

import subprocess
import os
from pathlib import Path

BUILD_PATH = "../../.."

exepath = Path.cwd() / BUILD_PATH

if os.name == "nt":
    exepath = exepath / r"cli.exe"
else:
    exepath = exepath / r"cli"


def test_tangles():

    out_file = Path.cwd() / "res.json"
    arg_list = f"{exepath} -r -n 5 -j -f\"{out_file}\""

    with subprocess.Popen(arg_list, stdout=subprocess.PIPE) as proc:
        proc.wait()
        assert proc.returncode == 0
        # @@@ TODO: add checks for correctness
        ...

