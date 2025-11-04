add_executable(test_computation_wptt_canoncity_app
               test_computation_wptt_canoncity.c)

target_link_libraries(
  test_computation_wptt_canoncity_app
  computation_defs
  tang_defs
  notation_wptt
  comp_wptt_canoncity
  Unity
  Cmock)

add_test(NAME test_computation_wptt_canoncity
         COMMAND test_computation_wptt_canoncity_app)
