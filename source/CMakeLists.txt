################################################################################
# Add definitions directory
################################################################################
add_subdirectory(defs)

################################################################################
# Add Computation Components
################################################################################
add_subdirectory(comp-rational_data)

################################################################################
# Add Generation Components
################################################################################
add_subdirectory(gen-rational)
add_subdirectory(gen-montesinos)

################################################################################
# Add Notation Components
################################################################################
add_subdirectory(note-twist_vector)
add_subdirectory(note-algebraic_tangle_tree)
add_subdirectory(note-awptt)

################################################################################
# Add Storage Components
################################################################################
add_subdirectory(store-json)
add_subdirectory(store-cpp_storage_interface)
