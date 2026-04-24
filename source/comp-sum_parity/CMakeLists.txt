add_library(comp_sum_parity STATIC src/comp_sum_parity.c)

target_include_directories(comp_sum_parity PUBLIC src)
target_link_libraries(comp_sum_parity tang_defs storage_defs computation_defs)

add_lizard_target(comp_sum_parity_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(comp_sum_parity
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
