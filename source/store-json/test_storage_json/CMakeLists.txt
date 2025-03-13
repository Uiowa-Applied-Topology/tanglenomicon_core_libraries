add_executable(test_storage_JSON_app
        test_storage_JSON.cpp
)

target_link_libraries(test_storage_JSON_app
    storage
    storage_JSON
    Unity
    Cmock
)

add_test(NAME test_storage_JSON COMMAND test_storage_JSON_app)
