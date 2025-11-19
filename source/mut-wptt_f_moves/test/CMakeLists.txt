add_executable(
  test_mut_wptt_f_moves_app
  test_mut_wptt_f_moves.c utils/utils.c tests/config/positive_tests.c
  tests/config/negative_tests.c tests/mutate/positive_tests.c
  tests/mutate/negative_tests.c)
target_link_libraries(
  test_mut_wptt_f_moves_app
  mutator_defs
  tang_defs
  mut_wptt_f_moves
  storage_defs
  test_stub_storage_stub
  Unity
  Cmock)

add_test(NAME test_mut_wptt_f_moves COMMAND test_mut_wptt_f_moves_app)
