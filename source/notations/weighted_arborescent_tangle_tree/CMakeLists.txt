add_library(notation_watt STATIC notation_watt.c)

target_include_directories(notation_watt PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(notation_watt notation_tv tang_defs notation_defs)


set_target_properties(notation_watt
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
