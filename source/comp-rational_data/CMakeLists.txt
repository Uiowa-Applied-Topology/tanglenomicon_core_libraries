add_library(comp_rational_data STATIC src/comp_rational_data.c)

target_include_directories(comp_rational_data PUBLIC src)
target_link_libraries(comp_rational_data
        tang_defs
        computation_defs
        notation_tv
        storage_defs)


add_lizard_target(
  comp_rational_data_lizard
  ALL
  ARGUMENTS
    --warnings_only
)

set_target_properties(comp_rational_data
        PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)