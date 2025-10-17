add_library(comp_rlitt_positivity STATIC src/comp_rlitt_positivity.c)

target_include_directories(comp_rlitt_positivity PUBLIC src)
target_link_libraries(comp_rlitt_positivity
        tang_defs
        storage_defs
        notation_wptt
        computation_defs)


add_lizard_target(
  comp_rlitt_positivity_lizard
  ALL
  ARGUMENTS
    --warnings_only
)

set_target_properties(comp_rlitt_positivity PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)