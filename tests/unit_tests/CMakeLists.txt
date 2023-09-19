add_library(Unity STATIC framework/unity.c)
add_library(Cmock STATIC framework/cmock.c)

target_include_directories(Unity PUBLIC framework)

target_include_directories(Cmock PUBLIC framework)

add_subdirectory(computations)
add_subdirectory(generators)
add_subdirectory(notations)
add_subdirectory(storage)
add_subdirectory(translators)