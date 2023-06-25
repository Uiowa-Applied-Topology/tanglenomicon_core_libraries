add_library(generator_rational STATIC generator_rational.c)

target_include_directories(generator_rational PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(generator_rational tang_defs generator_defs notation_tv)

set_target_properties(generator_rational
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
