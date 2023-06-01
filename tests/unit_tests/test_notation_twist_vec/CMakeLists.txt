add_executable(test_notation_twist_vec_app
    test_storage_JSON.cpp
)

target_link_libraries(test_notation_twist_vec_app
    notation_twist_vector
    notation_defs
    Unity
    Cmock
)

add_test(NAME test_notation_twist_vec COMMAND test_notation_twist_vec_app)
