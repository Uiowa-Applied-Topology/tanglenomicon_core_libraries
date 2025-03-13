add_library(storage_JSON STATIC src/storage_json.cpp)

target_include_directories(storage_JSON PUBLIC .)
target_link_libraries(storage_JSON json storage storage_defs)
