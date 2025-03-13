add_executable(cli main.cpp)

target_link_libraries(cli generator_rational comp_rational_data storage_JSON cxxopts
                      generator_defs tang_defs computation_defs)

target_include_directories(cli PUBLIC .)
