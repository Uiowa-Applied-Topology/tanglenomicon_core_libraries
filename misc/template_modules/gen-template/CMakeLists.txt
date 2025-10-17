add_library(comp_template STATIC src/comp_template.c)

target_include_directories(comp_template PUBLIC src)
target_link_libraries(comp_template tang_defs computation_defs notation_tv)

set_target_properties(comp_template PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                               "C")
add_subdirectory(test)
