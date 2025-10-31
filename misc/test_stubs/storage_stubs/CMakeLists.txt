add_library(test_stub_storage_stub STATIC src/test_storage_stubs.c)

target_include_directories(test_stub_storage_stub PUBLIC src)
target_link_libraries(test_stub_storage_stub storage_defs)

set_target_properties(test_stub_storage_stub
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
