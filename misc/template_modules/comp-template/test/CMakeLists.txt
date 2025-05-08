add_executable(test_computation_template_app test_computation_template.c)

target_link_libraries(test_computation_template_app computation_defs
                      tang_defs comp_template Unity Cmock)

add_test(NAME test_computation_template
         COMMAND test_computation_template_app)
