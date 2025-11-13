add_library(notation_plpath STATIC src/notation_plpath.c)

target_include_directories(notation_plpath PUBLIC src)
target_link_libraries(notation_plpath tang_defs notation_defs)

add_lizard_target(notation_plpath_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(notation_plpath
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
set_property(TARGET notation_plpath PROPERTY C_STANDARD 99)
