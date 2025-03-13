add_executable(test_generator_rational_app
        test_generator_rational.c
)

target_link_libraries(test_generator_rational_app
    generator_defs
    storage_defs
    tang_defs
    generator_rational
    Unity
    Cmock
)

add_test(NAME test_generator_rational COMMAND test_generator_rational_app)
