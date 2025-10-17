add_library(generator_rational STATIC src/generator_rational.c)

target_include_directories(generator_rational PUBLIC src)
target_link_libraries(generator_rational tang_defs generator_defs notation_tv
                      storage_defs)

add_lizard_target(generator_rational_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(generator_rational
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
