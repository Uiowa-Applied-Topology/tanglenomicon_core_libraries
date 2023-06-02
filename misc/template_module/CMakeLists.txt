add_library(template STATIC generator_rational.c)

target_include_directories(template PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(template
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
