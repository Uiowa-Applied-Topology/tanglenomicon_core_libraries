add_library(notation_tv STATIC src/notation_tv.c)

target_include_directories(notation_tv PUBLIC src)
target_link_libraries(notation_tv tang_defs notation_defs)

add_lizard_target(notation_tv_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(notation_tv PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                             "C")
add_subdirectory(test)
