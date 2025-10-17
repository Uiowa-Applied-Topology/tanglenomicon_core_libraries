add_library(notation_template STATIC src/notation_template.c)

target_include_directories(notation_template PUBLIC src)
target_link_libraries(notation_template notation_tv tang_defs notation_defs)

set_target_properties(notation_template
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
