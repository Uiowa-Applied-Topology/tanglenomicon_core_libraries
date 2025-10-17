add_library(comp_wptt_vertex_canonicity STATIC
            src/comp_wptt_vertex_canonicity.c)

target_include_directories(comp_wptt_vertex_canonicity PUBLIC src)
target_link_libraries(comp_wptt_vertex_canonicity tang_defs storage_defs
                      notation_wptt computation_defs)

add_lizard_target(comp_wptt_vertex_canonicity_lizard ALL ARGUMENTS
                  --warnings_only)

set_target_properties(comp_wptt_vertex_canonicity
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
