set export

@_default:
    just --list

# Set up development environment
bootstrap: 
    if test ! -e .venv; then \
      just refresh-sub ; \
      prek install -f -c .pre-commit-config.yaml ; \
      uv venv --python 3.13 && uv pip install -r requirements.txt && \
      uv pip install "git+https://github.com/Joecstarr/mkdocs-bibtex"; \
      uv pip install "git+https://github.com/Joecstarr/mkdocs-author-plugin"; \
      uv pip install "git+https://github.com/Joecstarr/markdown-gfm-admonition"; \
    fi

# Refresh the submodules in the project
refresh-sub: 
      git submodule deinit -f . 
      git submodule update --init --recursive 

##################################################################################################
## Cmake      ####################################################################################
##################################################################################################

##################################################################################################
####### Windows ##################################################################################
##################################################################################################
buildTrgt_win := "Windows"
buildDir_win := "./.build/Windows"


# Clean the windows build dir
clean_win: bootstrap
    if test -e {{buildDir_win}}; then \
        rip {{buildDir_win}}; \
    fi

# Build for windows 
build_win : bootstrap
    source .venv/bin/activate && \
    cmake -DCMAKE_TOOLCHAIN_FILE=./misc/cmake/mingw-toolchain.cmake -B{{buildDir_win}} -DCMAKE_BUILD_TYPE={{buildTrgt_win}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_win}} -j 


# Test windows 
test_wine: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir_win}} && \
    find . -iname "test*.exe" -exec  sh -c 'wine $0 || kill $PPID' \{\} \;


##################################################################################################
####### Release ##################################################################################
##################################################################################################
buildTrgt_rel := "Release"
buildDir_rel := "./.build/Release"

# Clean the release build dir
clean_rel: bootstrap
    if test -e {{buildDir_rel}}; then \
        rip {{buildDir_rel}}; \
    fi

# Build for release 
build_rel : bootstrap
    source .venv/bin/activate && \
    cmake  -DCMAKE_TOOLCHAIN_FILE=./misc/cmake/musl-toolchain.cmake -B{{buildDir_rel}} -DCMAKE_BUILD_TYPE={{buildTrgt_rel}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_rel}} -j 

# Test release 
test_rel: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir_rel}} && \
    ctest -C {{buildTrgt_rel}} --output-on-failure

##################################################################################################
####### Debug   ##################################################################################
##################################################################################################
buildTrgt_dbg := "Debug"
buildDir_dbg := "./.build/Debug"

# Clean the debug build dir
clean_dbg: bootstrap
    if test -e {{buildDir_dbg}}; then \
        rip {{buildDir_dbg}}; \
    fi

# Build for debug 
build_dbg : bootstrap
    source .venv/bin/activate && \
    cmake -DCMAKE_TOOLCHAIN_FILE=./misc/cmake/musl-toolchain.cmake -B{{buildDir_dbg}} -DCMAKE_BUILD_TYPE={{buildTrgt_dbg}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_dbg}} -j 

# Test debug 
test_dbg: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir_dbg}} && \
    ctest -C {{buildTrgt_dbg}}

##################################################################################################
####### Build All ################################################################################
##################################################################################################

# Build all versions
build_all: build_dbg build_rel build_win
    @echo "🚀 Build everything"
    exit 0

# Run testing for all versions
test_all: test_rel test_dbg 
    @echo "🚀 tested everything"
    exit 0

##################################################################################################
## mkdocs     ####################################################################################
##################################################################################################

# Build docs 
html: bootstrap
    source .venv/bin/activate && \
    mkdocs build -d ./.build/docs

# Luanch live docs 
live: bootstrap
    @echo "🚀 Check port 8000"
    source .venv/bin/activate && \
    mkdocs serve --livereload --dev-addr 0.0.0.0:8000


##################################################################################################
## formatting  ###################################################################################
##################################################################################################

##################################################################################################
####### Doxygen Style ############################################################################
##################################################################################################


# Generate warnings from doxygen 
warning-doxygen:
    -doxygen misc/doxy/.doxyconfig | python ./misc/doxy/make_doxywarnhtml.py 

# Cyclically Generate warnings from doxygen 
c-warning-doxygen:
    -watch -n 3 just warning-doxygen

# Server cppcheck results
[working-directory: '.build/doxygen/warnings']
serve-doxygen: bootstrap warning-doxygen 
    @echo "🚀 Check port 1315"
    source ../../../.venv/bin/activate && \
    python -m reloadserver 1315

# Run cmake-format
check-doxygen:
    mkdir -p .build/doxygen
    rip .build/doxygen
    doxygen misc/doxy/.doxyconfig

##################################################################################################
####### cmake format #############################################################################
##################################################################################################

# Run cmake-format
do-cmakeformat:
    find ./source/ -name 'CMakeLists.txt' -exec cmake-format -i {} \;
    find ./wrappers/ -name 'CMakeLists.txt' -exec cmake-format -i {} \;
    cmake-format -i ./libraries/CMakeLists.txt
    cmake-format -i CMakeLists.txt


##################################################################################################
####### cppcheck sytle ###########################################################################
##################################################################################################

# Clear cppcheck results
clear-cppcheck: build_rel
    mkdir -p ./.build/cppcheck

# Build cppckeck html 
report-cppcheck:
    mkdir -p ./.build/cppcheck
    cppcheck --project=./.build/Release/compile_commands.json -q -ilibraries  --enable=all --std=c99 --inline-suppr --suppressions-list=cppcheck.supp --suppress=*:./libraries/json/lib/single_include/nlohmann/json.hpp --xml 2> ./.build/cppcheck/err.xml
    cppcheck-htmlreport --file=./.build/cppcheck/err.xml --report-dir=./.build/cppcheck --source-dir=. 

# Server cppcheck results
[working-directory: '.build/cppcheck']
serve-cppcheck: build_rel clear-cppcheck report-cppcheck
    @echo "🚀 Check port 1314"
    source ../../.venv/bin/activate && \
    python -m reloadserver 1314

# check cppcheck fail on warning
check-cppcheck: build_rel
    cppcheck --project=./.build/Release/compile_commands.json -q -ilibraries  --enable=all  --std=c99     --inline-suppr      --error-exitcode=1       --suppressions-list=cppcheck.supp --suppress=*:./libraries/json/lib/single_include/nlohmann/json.hpp


##################################################################################################
####### uncrustify format ########################################################################
##################################################################################################

# Run uncrustify 
do-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;

##################################################################################################
####### rumdl format ##########################################################################
##################################################################################################
    
# Run rumdl 
do-rumdl:
    rumdl fmt --fix docs
    rumdl fmt --fix source


##################################################################################################
####### check everything #########################################################################
##################################################################################################

# Check all style and formatting. Fail on warning.  
check: 
    prek run --all-files
    @echo "🚀 Checked the files"
    exit 0

##################################################################################################
####### all format ###############################################################################
##################################################################################################

# Run all formatting.  
format: do-rumdl do-cmakeformat do-uncrustify
    @echo "🚀 Formated the files"
    exit 0
