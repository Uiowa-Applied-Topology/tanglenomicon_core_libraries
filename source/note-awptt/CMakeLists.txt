add_library(notation_awptt STATIC src/notation_awptt.c)

target_include_directories(notation_awptt PUBLIC src)
target_link_libraries(notation_awptt notation_tv tang_defs notation_defs)


set_target_properties(notation_awptt
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)