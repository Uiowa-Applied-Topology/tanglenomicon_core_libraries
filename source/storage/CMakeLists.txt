add_library(storage STATIC storage.cpp)

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(JSON)
