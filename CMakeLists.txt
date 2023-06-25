# CMakeList.txt : CMake project for tanglenomicon, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(
  tanglenomicon
  LANGUAGES C CXX
  VERSION 0.0.1)

option(BUILD_DOC "Build documentation")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
find_package(
  Python
  COMPONENTS Interpreter
  REQUIRED)
find_package(Doxygen)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()
include(CTest)

add_subdirectory(libraries)
add_subdirectory(source)
add_subdirectory(tests)

################################################################################
# Start Compiler Defines
################################################################################

add_compile_definitions(UTIL_TANG_DEFS_MAX_CROSSINGNUM=20u)

################################################################################
# End Compiler Defines
################################################################################

if(BUILD_DOC)
  if(DOXYGEN_FOUND)
    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)

    message("Doxygen build started")

    add_custom_target(
      doc_doxygen ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM)
  else(DOXYGEN_FOUND)
    message(
      "Doxygen need to be installed to generate the doxygen documentation")
  endif(DOXYGEN_FOUND)
endif(BUILD_DOC)
