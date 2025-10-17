add_library(comp_rlitt_grafting STATIC src/comp_rlitt_grafting.c)

target_include_directories(comp_rlitt_grafting PUBLIC src)
target_link_libraries(comp_rlitt_grafting
        tang_defs
        computation_defs
        storage_defs
        notation_wptt)


add_lizard_target(
  comp_rlitt_grafting_lizard
  ALL
  ARGUMENTS
    --warnings_only
)

set_target_properties(comp_rlitt_grafting
        PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)