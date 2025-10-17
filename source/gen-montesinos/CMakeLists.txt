add_library(generator_montesinos STATIC src/generator_montesinos.c)

target_include_directories(generator_montesinos
                           PUBLIC src)
target_link_libraries(generator_montesinos tang_defs generator_defs
                      notation_att storage_defs)

add_lizard_target(
  generator_montesinos_lizard
  ALL
  ARGUMENTS
    --warnings_only
)

set_target_properties(generator_montesinos
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")

add_subdirectory(test)