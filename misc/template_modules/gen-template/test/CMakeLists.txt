add_executable(test_generation_template_app test_generation_template.c)

target_link_libraries(test_generation_template_app generation_defs
                      tang_defs comp_template Unity Cmock)

add_test(NAME test_generation_template
         COMMAND test_generation_template_app)