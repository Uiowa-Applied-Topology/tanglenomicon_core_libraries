
add_library(generator_pattern STATIC
generator_pattern.c
)

target_include_directories(generator_pattern PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
