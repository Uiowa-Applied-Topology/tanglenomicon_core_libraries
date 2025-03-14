add_subdirectory(computation_defs)
add_subdirectory(generator_defs)
add_subdirectory(storage_defs)
add_subdirectory(notation_defs)
add_library(tang_defs INTERFACE)

target_include_directories(tang_defs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
