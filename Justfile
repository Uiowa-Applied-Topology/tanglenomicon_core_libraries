set export

@_default:
    just --list

buildTrgt := "Release"
buildTrgt_dbg := "Debug"
buildDir := "./.build"
buildDir_dbg := "./.build_dbg"

# Set up development environment
bootstrap build_dir=buildDir:
    git submodule update --init --recursive
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

html: bootstrap
    source .venv/bin/activate && \
    sphinx-build -M html docs docs/.build

build_all : bootstrap
    if test -e {{buildDir}}; then \
        rip {{buildDir}}; \
    fi
    source .venv/bin/activate && \
    cmake -B{{buildDir}} -DCMAKE_BUILD_TYPE={{buildTrgt}} -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir}}

test_all: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir}} && \
    ctest -C {{buildTrgt}}

build_dbg : bootstrap
    if test -e {{buildDir_dbg}}; then \
        rip {{buildDir_dbg}}; \
    fi
    source .venv/bin/activate && \
    cmake -B{{buildDir_dbg}} -DCMAKE_BUILD_TYPE={{buildTrgt_dbg}} -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_dbg}}

test_dbg: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir_dbg}} && \
    ctest -C {{buildTrgt_dbg}}

do-cmakeformat:
    find . -name 'CMakeLists.txt' -exec cmake-format -i {} \;

check-cmakeformat:
    find . -name 'CMakeLists.txt' -exec cmake-format --check {} \;

do-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
check-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;

check-prettier:
    prettier README.md --check
    prettier "docs/**/*.md" --check
    prettier "source/**/*.md" --check

do-prettier:
    prettier -w README.md
    prettier -w "docs/**/*.md"
    prettier -w "source/**/*.md"

compile_commands:
    cmake -B{{buildDir}} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja 