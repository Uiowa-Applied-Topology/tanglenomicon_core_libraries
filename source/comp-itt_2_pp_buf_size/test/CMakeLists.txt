add_executable(
  test_comp_i2pp_buf_size
  test_comp_i2pp_buf_size.c
  tests/config/positive_tests.c
  tests/config/negative_tests.c
  tests/compute/positive_tests.c
  tests/compute/negative_tests.c
  tests/results/positive_tests.c
  tests/results/negative_tests.c
  utils/utils.c)

target_link_libraries(
  test_comp_i2pp_buf_size
  computation_defs
  tang_defs
  storage_defs
  test_stub_storage_stub
  comp_i2pp_buf_size
  Unity
  Cmock)

add_test(NAME test_comp_i2pp_buf_size COMMAND test_comp_i2pp_buf_size)
