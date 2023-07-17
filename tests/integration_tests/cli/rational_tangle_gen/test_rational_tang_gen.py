""" Rational tangle generation integration Test for the CLI runner."""

import subprocess
import os
from pathlib import Path
import json

BUILD_PATH = "../../.."

json_test_data = """
{
    "1 1 1 1 1": {
        "twist_vector": "1 1 1 1 1",
        "crossing_num": "5"
    },
    "2 1 1 1 0": {
        "twist_vector": "2 1 1 1 0",
        "crossing_num": "5"
    },
    "1 2 1 1 0": {
        "twist_vector": "1 2 1 1 0",
        "crossing_num": "5"
    },
    "1 1 2 1 0": {
        "twist_vector": "1 1 2 1 0",
        "crossing_num": "5"
    },
    "1 1 1 2 0": {
        "twist_vector": "1 1 1 2 0",
        "crossing_num": "5"
    },
    "3 1 1": {
        "twist_vector": "3 1 1",
        "crossing_num": "5"
    },
    "1 3 1": {
        "twist_vector": "1 3 1",
        "crossing_num": "5"
    },
    "1 1 3": {
        "twist_vector": "1 1 3",
        "crossing_num": "5"
    },
    "2 2 1": {
        "twist_vector": "2 2 1",
        "crossing_num": "5"
    },
    "2 1 2": {
        "twist_vector": "2 1 2",
        "crossing_num": "5"
    },
    "1 2 2": {
        "twist_vector": "1 2 2",
        "crossing_num": "5"
    },
    "3 2 0": {
        "twist_vector": "3 2 0",
        "crossing_num": "5"
    },
    "2 3 0": {
        "twist_vector": "2 3 0",
        "crossing_num": "5"
    },
    "4 1 0": {
        "twist_vector": "4 1 0",
        "crossing_num": "5"
    },
    "1 4 0": {
        "twist_vector": "1 4 0",
        "crossing_num": "5"
    },
    "5": {
        "twist_vector": "5",
        "crossing_num": "5"
    }
}
"""


exepath = Path.cwd() / BUILD_PATH

if os.name == "nt":
    exepath = exepath / r"cli.exe"
else:
    exepath = exepath / r"cli"


def test_tangles():
    out_file = Path.cwd() / "res.json"

    assert exepath.is_file() == True

    if out_file.is_file():
        os.remove(out_file)

    assert out_file.is_file() == False

    args = [str(exepath), "-rj", "-n","5","-f",f"{out_file}"]

    proc = subprocess.call(args)
    assert proc ==0

    assert out_file.is_file() == True

    test_json_content = json.loads(json_test_data)
    with open(out_file, "r") as out_file_stream:
        out_json_content = json.loads(out_file_stream.read())
        for tangle in test_json_content:

            assert tangle in out_json_content
            assert out_json_content[tangle] == test_json_content[tangle]

            ...
        ...