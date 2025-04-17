block(SCOPE_FOR VARIABLES)
    unset(CMAKE_CXX_CPPCHECK)
    unset(CMAKE_C_CPPCHECK)
    if (DEFINED EMSCRIPTEN)
    else ()
        add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/py_gen_montesinos.c
                DEPENDS py_gen_montesinos.pyx
                VERBATIM
                COMMAND "${CYTHON}" "${CMAKE_CURRENT_SOURCE_DIR}/py_gen_montesinos.pyx" --output-file
                "${CMAKE_CURRENT_BINARY_DIR}/py_gen_montesinos.c")


        python_add_library(py_gen_montesinos MODULE "${CMAKE_CURRENT_BINARY_DIR}/py_gen_montesinos.c"
                WITH_SOABI)
        target_link_libraries(py_gen_montesinos PRIVATE generator_montesinos tang_defs generator_defs
                notation_att storage_defs)
        set_property(TARGET py_gen_montesinos PROPERTY C_STANDARD 99)
    endif ()
endblock()