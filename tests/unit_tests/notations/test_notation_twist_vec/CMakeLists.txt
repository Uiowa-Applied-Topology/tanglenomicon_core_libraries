add_executable(test_notation_twist_vec_app
test_notation_twist_vec.c
)

target_link_libraries(test_notation_twist_vec_app
    notation_defs
    notation_tv
    Unity
    Cmock
)

add_test(NAME test_notation_twist_vec COMMAND test_notation_twist_vec_app)
