block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)
add_library(storage_json STATIC src/storage_json.cpp)

target_include_directories(storage_json PUBLIC src)
target_link_libraries(storage_json json storage storage_defs)

endblock()
