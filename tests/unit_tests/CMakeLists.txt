add_library(Unity STATIC framework/unity.c)
add_library(Cmock STATIC framework/cmock.c)

target_include_directories(Unity PUBLIC framework)

target_include_directories(Cmock PUBLIC framework)

add_subdirectory(test_storage_JSON)
add_subdirectory(test_notation_twist_vec)