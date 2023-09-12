add_executable(test_computation_rational_data_app
test_generator_rational.c
)

target_link_libraries(test_computation_rational_data_app
    generator_defs
    tang_defs
    generator_rational
    Unity
    Cmock
)

add_test(NAME test_generator_rational COMMAND test_computation_rational_data_app)
