# CMakeList.txt : CMake project for tanglenomicon, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.12)

project(
        tanglenomicon
        LANGUAGES C CXX
        VERSION 0.0.1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(Doxygen)

set(CMAKE_C_STANDARD 90)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(TEST_RESULTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tests/results/)

if (DEFINED EMSCRIPTEN)
    add_compile_options("-fPIC")
    add_compile_definitions(ENABLE_EMSCRIPTEN)
else ()
    set(Python_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin)
    set(Python3_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin/python)
    set(Python3_FIND_VIRTUALENV "ONLY")
    SET(ENV{VIRTUAL_ENV} "${CMAKE_CURRENT_SOURCE_DIR}/.venv")

    find_package(
            Python
            COMPONENTS Interpreter Development.Module
            REQUIRED)
    find_program(CYTHON "cython")


    if (DOXYGEN_FOUND)
        set(DOXY_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs/build/doxygen)
        set(SPHINX_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs/build/sphinx)
        set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
        set(SPHINX_EXE ${Python_ROOT_DIR}/sphinx-build)

        message("Doxygen build started")
        set(DOXYGEN_INDEX_FILE ${DOXY_BUILD_DIR}/xml/index.xml)
        set(SPHINX_INDEX_FILE ${SPHINX_BUILD_DIR}/index.html)
        add_custom_target(dox ALL
                COMMAND rm -r ${SPHINX_BUILD_DIR} && mkdir -p ${SPHINX_BUILD_DIR} && ${Python_ROOT_DIR}/sphinx-build -M html docs ${SPHINX_BUILD_DIR} && ${Python_ROOT_DIR}/sphinx-build -M xml docs ${SPHINX_BUILD_DIR}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating documentation with Sphinx"
                DEPENDS ${SPHINX_EXE} ${DOXYGEN_INDEX_FILE})
        add_custom_command(
                OUTPUT ${DOXYGEN_INDEX_FILE}
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating API documentation with Doxygen")
        add_custom_command(
                OUTPUT ${SPHINX_EXE}
                COMMAND ${Python3_EXECUTABLE} -m pip install --upgrade pip wheel pip-tools && ${Python3_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Updating pip from requirements.txt")

    else (DOXYGEN_FOUND)
        message(
                "Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)


endif ()
################################################################################
# Start Compiler Defines
################################################################################

add_compile_definitions(UTIL_TANG_DEFS_MAX_CROSSINGNUM=40)

################################################################################
# Start Includes
################################################################################

enable_testing()
include(CTest)

add_subdirectory(libraries)
add_subdirectory(source)
add_subdirectory(misc)
add_subdirectory(tests)


################################################################################
# End Compiler Defines
################################################################################

################################################################################
# Start Extra Build Defines
################################################################################


################################################################################
# Start Extra Build Defines
################################################################################