

add_test(
  NAME rational_tang_gen
  COMMAND
    ${Python_EXECUTABLE} -m pytest
    --html=${TEST_RESULTS_PATH}/rational_tang_verification.html
    --self-contained-html ${CMAKE_CURRENT_SOURCE_DIR})
add_test(
  NAME rational_tang_data_comp
  COMMAND
    ${Python_EXECUTABLE} -m pytest
    --html=${TEST_RESULTS_PATH}/rational_tang_data_verification.html
    --self-contained-html ${CMAKE_CURRENT_SOURCE_DIR})
