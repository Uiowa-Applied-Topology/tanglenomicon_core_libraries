from pathlib import Path,PurePath
# from rich import print
from tqdm import tqdm
import os
from shutil import copyfile, rmtree


class CopyFileNameDriver:
    def __init__(self, cfg):
        self.config = cfg

    def run(self):
        self.info("Copy folder...")

        if not self.config["source"].exists():
            self.error("Source {} does not exist".format(self.config["source"]))
            return
        try:
            for use_case in tqdm(
                    list(Path(self.config['source']).glob(f"**/{self.config['file-name']}"))):
                print("")
                print(str(self.config["target"].absolute()))
                print(str(use_case))
                dest = Path(str(self.config["target"].absolute()) + str(use_case))
                print(str(dest))
                # dest.parent.mkdir(parents=True, exist_ok=True)
                # copyfile(use_case, str(dest))
                ...
        except IOError as e:
            self.error("Problems during copying folder.", e)

    def clean(self):
        try:
            for file in Path(self.config["target"]).glob(f"./**/{self.config['file-name']}"):
                file.unlink()
            for dir in Path(self.config["target"]).glob("./**"):
                rmtree(dir)
            self.info("Folder deleted: {}".format(self.config["target"]))
        except FileNotFoundError:
            pass  # Already cleaned? I'm okay with it.
        except IOError as e:
            self.error("Problems during cleaning for collection {}".format(self.config["name"]), e)

    def info(self, data: str):
        print(data)

    def error(self, data: str):
        print(f"[italic red]{data}[/italic red]")


if __name__ == "__main__":
    DOCS_PATH = Path(__file__).parent / "../.."
    print(DOCS_PATH)
    collections = [
        CopyFileNameDriver(
            {
                'source': DOCS_PATH / "../source",
                'target':  DOCS_PATH / './use_cases/.cp_from_source',
                'file-name': "use-case.md",
            }),
        CopyFileNameDriver(
            {
                'source': DOCS_PATH / "source",
                'target':  DOCS_PATH / './unit_description/.cp_from_source',
                'file-name': "unit-description.md",
            }),
    ]
    for collection in collections:
        collection.run()
        ...
