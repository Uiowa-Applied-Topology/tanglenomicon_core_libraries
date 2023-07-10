

add_test(
  NAME rational_tang_gen
  COMMAND
    ${Python_EXECUTABLE} -m pytest
    --html=${TEST_RESULTS_PATH}/rational_tang_verification.html
    --self-contained-html ${CMAKE_CURRENT_SOURCE_DIR})
