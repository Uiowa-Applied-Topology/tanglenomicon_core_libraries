add_executable(rational_tangle_benchmark rational_tangle_benchmark.cpp)

target_link_libraries(rational_tangle_benchmark generator_rational storage_json cxxopts
                      generator_defs tang_defs)

target_include_directories(rational_tangle_benchmark PUBLIC ${CMAKE_CURRENT_LIST_DIR})
