add_library(comp_wptt_canoncity STATIC src/comp_wptt_canoncity.c)

target_include_directories(comp_wptt_canoncity PUBLIC src)
target_link_libraries(comp_wptt_canoncity tang_defs computation_defs
                      notation_wptt)

set_target_properties(comp_wptt_canoncity
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
