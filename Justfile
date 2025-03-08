set export

@_default:
    just --list

buildTrgt := "debug"
buildDir := "./.build"

# Set up development environment
bootstrap build_dir=buildDir:
    if test ! -e {{build_dir}}/flake; then \
      mkdir -p {{build_dir}}/flake; \
    fi
    if test ! -e {{build_dir}}/docs; then \
      mkdir -p {{build_dir}}/docs; \
    fi
    if test ! -e docs/build/sphinx; then \
      mkdir -p docs/build/sphinx; \
    fi
    if test ! -e {{build_dir}}/docs/sphinx; then \
      mkdir -p {{build_dir}}/docs/sphinx; \
    fi
    if test ! -e .venv; then \
      uv venv --python 3.11 && uv pip install -r requirements.txt ; \
    fi


test: bootstrap
    uv run pytest


clion:
    sh clion ./

bib:
    curl http://127.0.0.1:23119/better-bibtex/export/collection\?/1/Thesis.bibtex > ./docs/refs/zotero.bib

pret:
    prettier README.md --check
    prettier "docs/**/*.md" --check

live: bootstrap
    source .venv/bin/activate && \
    sphinx-autobuild docs docs/.build/html


pdf: bootstrap
    source .venv/bin/activate && \
    sphinx-build -M latex docs docs/.build
    cd docs/.build/latex && \
    latexmk -synctex=1 -interaction=nonstopmode -file-line-error -shell-escape -lualatex tanglenomiconcorelibraries.tex

html: bootstrap
    source .venv/bin/activate && \
    sphinx-build -M html docs docs/.build

build_all build_dir=buildDir build_tgt=buildTrgt : bootstrap
    if test -e {{build_dir}}; then \
        rip {{build_dir}}; \
    fi
    source .venv/bin/activate && \
    cmake -B{{build_dir}} -DCMAKE_BUILD_TYPE={{build_tgt}} && \
    cmake --build {{build_dir}}

zip:
    zip -r ./docs/.build/html.zip ./docs/.build/html

test_all build_dir=buildDir build_tgt=buildTrgt: bootstrap build_all
    source .venv/bin/activate && \
    cd {{build_dir}} && \
    ctest -C {{build_tgt}}

