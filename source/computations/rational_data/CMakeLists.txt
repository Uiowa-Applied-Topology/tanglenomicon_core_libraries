add_library(comp_rational_data STATIC comp_rational_data.c)

target_include_directories(comp_rational_data PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(comp_rational_data tang_defs computation_defs notation_tv)

set_target_properties(comp_rational_data
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
