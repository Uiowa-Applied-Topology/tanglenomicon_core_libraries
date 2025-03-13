add_executable(test_computation_rational_data_app test_computation_rational_data.c)

target_link_libraries(test_computation_rational_data_app computation_defs
                      tang_defs comp_rational_data Unity Cmock)

add_test(NAME test_computation_rational_data
         COMMAND test_computation_rational_data_app)
