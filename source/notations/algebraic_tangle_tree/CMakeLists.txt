add_library(notation_att STATIC notation_att.c)

target_include_directories(notation_att PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(notation_att notation_tv tang_defs notation_defs)


set_target_properties(notation_att
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
