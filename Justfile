set export

@_default:
    just --list

buildTrgt := "debug"
buildDir := "./.build"

# Set up development environment
bootstrap build_dir=buildDir:
    if test ! -e docs/.build/doxygen; then \
      mkdir -p docs/.build/doxygen; \
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
    source .venv/bin/activate && \
    sphinx-autobuild docs docs/.build/html


pdf: bootstrap
    source .venv/bin/activate && \
    sphinx-build -M latex docs docs/.build
    cp -r docs/resources/coloremoji/coloremoji docs/.build/latex
    cp docs/resources/coloremoji/coloremoji.sty docs/.build/latex
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

do-clang-format:
    find ./source -iname "*.c"   -exec  sh -c 'clang-format -i "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'clang-format -i "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'clang-format -i "$0" || kill $PPID' \{\} \;

check-clang-format:
    find ./source -iname "*.c"   -exec sh -c 'clang-format --Werror --dry-run "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec sh -c 'clang-format --Werror --dry-run "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec sh -c 'clang-format --Werror --dry-run "$0" || kill $PPID' \{\} \;

check-prettier:
    prettier README.md --check
    prettier "docs/**/*.md" --check

do-prettier:
    prettier -w README.md
    prettier -w "docs/**/*.md"

zip:
    zip -r ./docs/.build/html.zip ./docs/.build/html

test_all build_dir=buildDir build_tgt=buildTrgt: bootstrap build_all
    source .venv/bin/activate && \
    cd {{build_dir}} && \
    ctest -C {{build_tgt}}

