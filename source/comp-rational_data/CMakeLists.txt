add_library(comp_rational_data STATIC src/comp_rational_data.c)

target_include_directories(comp_rational_data PUBLIC src)
target_link_libraries(comp_rational_data tang_defs computation_defs storage_defs notation_tv)

set_target_properties(comp_rational_data
        PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)