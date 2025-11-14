add_executable(
  test_mut_rlitt_ringshift_app
  test_mut_rlitt_ringshift.c utils/utils.c tests/config/positive_tests.c
  tests/config/negative_tests.c tests/mutate/positive_tests.c
  tests/mutate/negative_tests.c)

target_link_libraries(
  test_mut_rlitt_ringshift_app
  computation_defs
  tang_defs
  storage_defs
  test_stub_storage_stub
  mut_rlitt_ringshift
  Unity
  Cmock)

add_test(NAME test_mut_rlitt_ringshift COMMAND test_mut_rlitt_ringshift_app)
