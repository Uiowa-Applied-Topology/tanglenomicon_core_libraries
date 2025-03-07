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

live: bootstrap
    .venv/bin/sphinx-autobuild docs docs/build/html


pdf: bootstrap
    .venv/bin/sphinx-build -M latex docs docs/build/latex
    cd docs/build/latex/latex && \
    latexmk -synctex=1 -interaction=nonstopmode -file-line-error -shell-escape -lualatex tanglenomiconcorelibraries.tex


build_all build_dir=buildDir build_tgt=buildTrgt : bootstrap
    if test -e {{build_dir}}; then \
        rip {{build_dir}}; \
    fi
    cmake -B{{build_dir}} -DCMAKE_BUILD_TYPE={{build_tgt}}
    cmake --build {{build_dir}}


test_all build_dir=buildDir build_tgt=buildTrgt: bootstrap build_all
    cd {{build_dir}} && ctest -C {{build_tgt}}
