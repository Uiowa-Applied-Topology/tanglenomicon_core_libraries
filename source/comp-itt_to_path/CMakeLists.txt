add_library(comp_itt_to_path STATIC src/comp_itt_to_path.c)

target_include_directories(comp_itt_to_path PUBLIC src)
target_link_libraries(
  comp_itt_to_path
  tang_defs
  storage_defs
  notation_wptt
  comp_sum_parity
  notation_plpath
  computation_defs)

add_lizard_target(comp_itt_to_path_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(comp_itt_to_path
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
