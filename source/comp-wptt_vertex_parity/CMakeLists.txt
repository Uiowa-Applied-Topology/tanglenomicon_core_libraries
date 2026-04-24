add_library(comp_wptt_vertex_parity STATIC src/comp_wptt_vertex_parity.c)

target_include_directories(comp_wptt_vertex_parity PUBLIC src)
target_link_libraries(comp_wptt_vertex_parity tang_defs storage_defs
                      notation_wptt computation_defs comp_sum_parity)

add_lizard_target(comp_wptt_vertex_parity_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(comp_wptt_vertex_parity
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
