@_default:
    just --list

# Set up development environment
bootstrap:
    if test ! -e build/flake; then mkdir -p build/flake; fi
    if test ! -e build/docs; then mkdir -p build/docs; fi
    if test ! -e .venv; then \
    uv venv --python 3.11 && uv pip install -r requirements.txt ; \
    fi
    source .venv/bin/activate

test: bootstrap
    pytest

clion:
    sh clion ./

bib:
    curl http://127.0.0.1:23119/better-bibtex/export/collection\?/1/Thesis.bibtex > ./docs/refs/zotero.bib


live: bootstrap
    .venv/bin/sphinx-autobuild docs docs/build/html
