
add_library(storage STATIC src/storage.cpp)

target_include_directories(storage PUBLIC src)
target_link_libraries(storage tang_defs storage_defs)

