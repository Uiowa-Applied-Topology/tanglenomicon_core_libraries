add_executable(
  test_comp_rlitt_pure_vignette_app
  test_comp_rlitt_pure_vignette.c
  utils/data.c
  tests/config/positive_tests.c
  tests/config/negative_tests.c
  tests/compute/positive_tests.c
  tests/compute/negative_tests.c
  tests/results/positive_tests.c
  tests/results/negative_tests.c)

target_link_libraries(
  test_comp_rlitt_pure_vignette_app
  computation_defs
  tang_defs
  storage_defs
  test_stub_storage_stub
  comp_rlitt_pure_vignette
  Unity
  Cmock)

add_test(NAME test_comp_rlitt_pure_vignette
         COMMAND test_comp_rlitt_pure_vignette_app)