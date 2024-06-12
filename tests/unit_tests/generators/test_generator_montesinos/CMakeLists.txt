add_executable(test_generator_montesinos_app
test_generator_montesinos.c
)

target_link_libraries(test_generator_montesinos_app
    generator_defs
    tang_defs
    generator_montesinos
    Unity
    Cmock
)

add_test(NAME test_generator_montesinos COMMAND test_generator_montesinos_app)
