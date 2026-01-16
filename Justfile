set export

@_default:
    just --list

buildTrgt := "Release"
buildTrgt_dbg := "Debug"
buildDir := "./.build"

# Set up development environment
bootstrap:
    git submodule update --init --recursive
    prek install -f
    if test ! -e docs/.build/doxygen; then \
      mkdir -p docs/.build/doxygen; \
    fi
    if test ! -e .venv; then \
      uv venv --python 3.13 && uv pip install -r requirements.txt && \
      uv pip install "git+https://github.com/Joecstarr/mkdocs-bibtex"; \
    fi


test: bootstrap
    uv run pytest


clion:
    sh clion ./

bib:
    curl http://127.0.0.1:23119/better-bibtex/export/collection\?/1/Thesis.bibtex > ./docs/refs/zotero.bib



live: bootstrap
    source .venv/bin/activate && \
    mkdocs serve --livereload

pdf: bootstrap
    source .venv/bin/activate && \
    sphinx-build -M latex docs docs/.build
    cp -r docs/resources/coloremoji/coloremoji docs/.build/latex
    cp docs/resources/coloremoji/coloremoji.sty docs/.build/latex
    cd docs/.build/latex && \
    nextonic compile tanglenomiconcorelibraries.tex --keep-logs --keep-intermediates

html: bootstrap
    source .venv/bin/activate && \
    mkdocs build -d .site

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

run TRGT: build_all
    source .venv/bin/activate && \
    .build/{{TRGT}}

do-cmakeformat:
    find ./source/ -name 'CMakeLists.txt' -exec cmake-format -i {} \;
    cmake-format -i ./libraries/CMakeLists.txt

check-cmakeformat:
    find ./source/ -name 'CMakeLists.txt' -exec cmake-format --check {} \;
    cmake-format --check ./libraries/CMakeLists.txt

do-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
check-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;

check-mdformat: 
    mdformat docs --check && \
    mdformat source --check 

do-mdformat:
    mdformat  docs && \
    mdformat source

check: check-cmakeformat check-cmakeformat check-uncrustify 
    @echo "🚀 Checked the files"
    

compile_commands:
    cmake -B{{buildDir}} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja 
