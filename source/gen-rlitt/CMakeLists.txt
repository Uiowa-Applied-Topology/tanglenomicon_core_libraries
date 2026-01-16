add_library(generator_rlitt STATIC src/generator_rlitt.c)

target_include_directories(generator_rlitt PUBLIC src)
target_link_libraries(
  generator_rlitt
  notation_wptt
  comp_rlitt_grafting
  mut_rlitt_ringshift
  comp_rlitt_positivity
  comp_wptt_vertex_canonicity
  tang_defs
  generator_defs
  storage_defs
  notation_defs)

add_lizard_target(generator_rlitt_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(generator_rlitt
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
