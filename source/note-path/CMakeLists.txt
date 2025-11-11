add_library(notation_path STATIC src/notation_wptt.c)

target_include_directories(notation_path PUBLIC src)
target_link_libraries(notation_path tang_defs notation_defs)

add_lizard_target(notation_path_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(notation_path PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                               "C")
add_subdirectory(test)