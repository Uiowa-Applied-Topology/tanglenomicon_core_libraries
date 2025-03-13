add_library(Unity STATIC unity.c)
add_library(Cmock STATIC cmock.c)
target_include_directories(Unity PUBLIC .)
target_include_directories(Cmock PUBLIC .)
