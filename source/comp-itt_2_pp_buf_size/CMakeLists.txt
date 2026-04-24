add_library(comp_i2pp_buf_size STATIC src/comp_i2pp_buf_size.c)

target_include_directories(comp_i2pp_buf_size PUBLIC src)
target_link_libraries(comp_i2pp_buf_size tang_defs storage_defs notation_wptt
                      computation_defs)

add_lizard_target(comp_i2pp_buf_size_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(comp_i2pp_buf_size
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
