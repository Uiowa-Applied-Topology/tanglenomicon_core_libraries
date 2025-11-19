add_library(mut_wptt_f_moves STATIC src/mut_wptt_f_moves.c)

target_include_directories(mut_wptt_f_moves PUBLIC src)
target_link_libraries(mut_wptt_f_moves tang_defs mutator_defs notation_wptt)

add_lizard_target(mut_wptt_f_moves_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(mut_wptt_f_moves
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
