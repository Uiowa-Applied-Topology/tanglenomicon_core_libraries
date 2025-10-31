add_library(notation_att STATIC src/notation_att.c)

target_include_directories(notation_att PUBLIC src)
target_link_libraries(notation_att notation_tv tang_defs notation_defs)

add_lizard_target(notation_att_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(notation_att PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                              "C")
add_subdirectory(test)
