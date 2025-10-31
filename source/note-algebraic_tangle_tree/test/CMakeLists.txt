add_executable(test_notation_att_app test_notation_att.c)

target_link_libraries(test_notation_att_app notation_defs notation_tv
                      notation_att Unity Cmock)

add_test(NAME test_notation_att COMMAND test_notation_att_app)
