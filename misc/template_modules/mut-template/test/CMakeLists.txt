add_executable(test_mut_template_app test_mut_template.c)

target_link_libraries(test_mut_template_app mut_defs tang_defs mut_template
                      Unity Cmock)

add_test(NAME test_mut_template COMMAND test_mut_template_app)
