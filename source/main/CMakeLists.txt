
add_executable(cli
    main.cpp
)
target_link_libraries(cli
generator_rational
cxxopts
)

get_target_property(CXXOPTS_INCLUDES cxxopts INCLUDE_DIRECTORIES)

foreach(dir ${CXXOPTS_INCLUDES})
    string(APPEND INCLUDE_COMPILER_STRING "/I${dir} ")
endforeach()

target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${INCLUDE_COMPILER_STRING}
)