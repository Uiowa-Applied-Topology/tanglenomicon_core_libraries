add_library(generator_rational STATIC src/generator_rational.c)

target_include_directories(generator_rational PUBLIC .)
target_link_libraries(generator_rational tang_defs generator_defs notation_tv
                      storage_defs)

set_target_properties(generator_rational
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
