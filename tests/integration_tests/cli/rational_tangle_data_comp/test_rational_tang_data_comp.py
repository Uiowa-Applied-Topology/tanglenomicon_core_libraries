""" Rational tangle generation integration Test for the CLI runner."""

import subprocess
import os
from pathlib import Path
import json

BUILD_PATH = os.environ.get("BUILD_DIR")

json_test_data = """
{
    "[1 3 2]": {
        "numerator": "9",
        "denominator": "4",
        "numerator_eq":"1",
        "denominator_eq":"4",
        "parity": "infty"
    }
}
"""


exepath = Path.cwd() / BUILD_PATH

if os.name == "nt":
    exepath = exepath / r"cli.exe"
else:
    exepath = exepath / r"cli"


def test_tangles():
    out_file = Path.cwd() / "test_rational_tang_data_comp_res.json"

    assert exepath.is_file() == True

    if out_file.is_file():
        os.remove(out_file)

    assert out_file.is_file() == False

    args = [str(exepath), "-dj", "-t","[1 3 2]","-f",f"{out_file}"]

    proc = subprocess.call(args)
    assert proc ==0

    assert out_file.is_file() == True

    test_json_content = json.loads(json_test_data)
    with open(out_file, "r") as out_file_stream:
        out_json_content = json.loads(out_file_stream.read())
        print(out_json_content)
        for tangle in test_json_content:

            assert tangle in out_json_content
            assert out_json_content[tangle] == test_json_content[tangle]

            ...
        ...

