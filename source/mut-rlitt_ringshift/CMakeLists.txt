add_library(mut_rlitt_ringshift STATIC src/mut_rlitt_ringshift.c)

target_include_directories(mut_rlitt_ringshift PUBLIC src)
target_link_libraries(mut_rlitt_ringshift tang_defs computation_defs
                      storage_defs notation_wptt)

add_lizard_target(mut_rlitt_ringshift_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(mut_rlitt_ringshift
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)