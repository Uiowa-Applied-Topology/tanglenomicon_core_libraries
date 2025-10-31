add_executable(
  test_generator_rlitt_app
  test_generator_rlitt.c
  utils/utils.c
  tests/config/positive_tests.c
  tests/config/negative_tests.c
  tests/generate/positive_tests.c
  tests/generate/negative_tests.c
  tests/test_low_crossing.c)

target_link_libraries(
  test_generator_rlitt_app
  computation_defs
  tang_defs
  generator_rlitt
  storage_defs
  test_stub_storage_stub
  Unity
  Cmock)

add_test(NAME test_generator_rlitt COMMAND test_generator_rlitt_app)
