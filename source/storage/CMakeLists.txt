add_subdirectory(storage_defs)
add_subdirectory(JSON)

add_library(storage STATIC storage.cpp )

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(storage tang_defs storage_defs)

