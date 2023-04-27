
add_executable(cli
    main.cpp
)

target_link_libraries(cli
generator_rational
cxxopts
)


target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)