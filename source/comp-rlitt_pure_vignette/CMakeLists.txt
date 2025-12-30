add_library(comp_rlitt_pure_vignette STATIC src/comp_rlitt_pure_vignette.c)

target_include_directories(comp_rlitt_pure_vignette PUBLIC src)
target_link_libraries(comp_rlitt_pure_vignette tang_defs storage_defs
                      notation_wptt computation_defs)

add_lizard_target(comp_rlitt_pure_vignette_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(comp_rlitt_pure_vignette
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
