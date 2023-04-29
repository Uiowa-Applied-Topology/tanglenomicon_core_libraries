
add_library(generator_rational STATIC
generator_rational.c
)

target_include_directories(generator_rational PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(generator_rational PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES "C"
)


