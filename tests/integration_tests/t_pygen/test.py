import sys
from pathlib import Path

dir = Path(__file__).parent / "../../../build/source/runners/py_gen_montesinos"

sys.path.append(str(dir.absolute()))

import py_gen_montesinos
...
py_gen_montesinos.start_job()
...