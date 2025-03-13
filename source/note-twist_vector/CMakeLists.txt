add_library(notation_tv STATIC notation_tv.c)

target_include_directories(notation_tv PUBLIC .)
target_link_libraries(notation_tv tang_defs notation_defs)


set_target_properties(notation_tv
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test_notation_twist_vec)