add_library(mut_template STATIC src/mut_template.c)

target_include_directories(mut_template PUBLIC src)
target_link_libraries(mut_template tang_defs mutator_defs)

set_target_properties(mut_template PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                              "C")
add_subdirectory(test)
