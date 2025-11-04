add_library(comp_wptt_canonicity STATIC src/comp_wptt_canonicity.c)

target_include_directories(comp_wptt_canonicity PUBLIC src)
target_link_libraries(comp_wptt_canonicity tang_defs computation_defs
                      notation_wptt)

set_target_properties(comp_wptt_canonicity
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
