add_library(generator_montesinos STATIC generator_montesinos.c)

target_include_directories(generator_montesinos
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(generator_montesinos tang_defs generator_defs
                      notation_att storage_defs)

set_target_properties(generator_montesinos
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
