add_executable(test_computation_wptt_canonicity_app
               test_computation_wptt_canonicity.c)

target_link_libraries(
  test_computation_wptt_canonicity_app
  computation_defs
  tang_defs
  notation_wptt
  comp_wptt_canonicity
  comp-wptt_vertex_canonicity
  Unity
  Cmock)

add_test(NAME test_computation_wptt_canonicity
         COMMAND test_computation_wptt_canonicity_app)
