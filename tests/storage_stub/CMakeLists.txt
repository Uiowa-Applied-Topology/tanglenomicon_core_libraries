add_library(storage_test_stub STATIC storage_test_stub.cpp)


target_include_directories(storage_test_stub PUBLIC .)
target_link_libraries(storage_test_stub test_stub storage)