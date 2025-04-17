add_executable(test_notation_awptt_app
        test_notation_awptt.c
)

target_link_libraries(test_notation_awptt_app
    notation_defs
    notation_awptt
    Unity
    Cmock
)

add_test(NAME test_notation_awptt COMMAND test_notation_awptt_app)
