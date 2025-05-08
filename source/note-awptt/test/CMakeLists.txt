add_executable(test_notation_awptt_app
        test_notation_awptt.c
        tests/decode/positive_tests.c
        tests/decode/negative_tests.c
        tests/encode/positive_tests.c
        tests/encode/negative_tests.c
        utils/utils.c
        tests/turn_around_test.c
)

target_link_libraries(test_notation_awptt_app
    notation_defs
    notation_awptt
    Unity
    Cmock
)

add_test(NAME test_notation_awptt COMMAND test_notation_awptt_app)
