

if (DEFINED EMSCRIPTEN)
else ()

add_test(
  NAME rational_tang_gen
  COMMAND
    ${Python3_EXECUTABLE} -m pytest
    --html=${TEST_RESULTS_PATH}/rational_tang_verification.html
    --self-contained-html ${CMAKE_CURRENT_SOURCE_DIR})
add_test(
  NAME rational_tang_data_comp
  COMMAND
    ${Python3_EXECUTABLE} -m pytest
    --html=${TEST_RESULTS_PATH}/rational_tang_data_verification.html
    --self-contained-html ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TEST rational_tang_gen PROPERTY ENVIRONMENT "BUILD_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(TEST rational_tang_data_comp PROPERTY ENVIRONMENT "BUILD_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif ()