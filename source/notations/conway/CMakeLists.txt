
add_library(notation_conway STATIC
notation_conway.c
)

target_include_directories(notation_conway PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(notation_conway PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES "C"
)


