
add_executable(mont_gen_wasm main.cpp)

target_link_libraries(mont_gen_wasm generator_montesinos tang_defs generator_defs notation_att storage_defs
        generator_defs tang_defs computation_defs)

target_include_directories(mont_gen_wasm PUBLIC ${CMAKE_CURRENT_LIST_DIR})
if (DEFINED EMSCRIPTEN)
    # set(CMAKE_EXECUTABLE_SUFFIX ".mjs")

    set_target_properties(mont_gen_wasm PROPERTIES COMPILE_FLAGS "-O3")
    set_target_properties(mont_gen_wasm PROPERTIES LINK_FLAGS    "-O3 -sALLOW_MEMORY_GROWTH  -s ENVIRONMENT=web --closure 1 -sINCOMING_MODULE_JS_API=print,printErr -s SINGLE_FILE=1 -s 'EXPORT_NAME=montgen' -s MODULARIZE --bind --pre-js ${CMAKE_CURRENT_LIST_DIR}/pre-js.js")
    # set_target_properties(mont_gen_wasm PROPERTIES COMPILE_FLAGS "-O0")
    # set_target_properties(mont_gen_wasm PROPERTIES LINK_FLAGS "-O0 -sALLOW_MEMORY_GROWTH -s ENVIRONMENT=web -sASSERTIONS  -sINCOMING_MODULE_JS_API=print,printErr -s SINGLE_FILE=1 -s 'EXPORT_NAME=montgen' -s MODULARIZE --bind --pre-js ${CMAKE_CURRENT_LIST_DIR}/pre-js.js")
    endif (DEFINED EMSCRIPTEN)