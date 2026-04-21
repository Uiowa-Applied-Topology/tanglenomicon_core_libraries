add_executable(
  test_comp_itt_to_path
  test_comp_itt_to_path.c
  tests/config/positive_tests.c
  tests/config/negative_tests.c
  tests/compute/positive_tests.c
  tests/compute/negative_tests.c
  tests/results/positive_tests.c
  tests/results/negative_tests.c
  utils/utils.c)

target_link_libraries(
  test_comp_itt_to_path
  computation_defs
  tang_defs
  storage_defs
  test_stub_storage_stub
  comp_itt_to_path
  Unity
  Cmock)

add_test(NAME test_comp_itt_to_path COMMAND test_comp_itt_to_path)
