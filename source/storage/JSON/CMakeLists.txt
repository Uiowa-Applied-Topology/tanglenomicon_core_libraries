
add_library(storage_JSON STATIC
storage_JSON.cpp
)

target_include_directories(storage_JSON PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(storage_JSON
json
storage
)