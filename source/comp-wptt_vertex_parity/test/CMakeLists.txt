add_executable(
  test_comp_wptt_vertex_parity
  test_comp_wptt_vertex_parity.c
  utils/utils.c
  tests/config/positive_tests.c
  tests/config/negative_tests.c
  tests/compute/positive_tests.c
  tests/compute/negative_tests.c
  tests/results/positive_tests.c
  tests/results/negative_tests.c)

target_link_libraries(
  test_comp_wptt_vertex_parity
  computation_defs
  tang_defs
  storage_defs
  test_stub_storage_stub
  comp_wptt_vertex_parity
  Unity
  Cmock)

add_test(NAME test_comp_wptt_vertex_parity COMMAND test_comp_wptt_vertex_parity)
