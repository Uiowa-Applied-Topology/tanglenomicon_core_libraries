################################################################################
# Add definitions directory
################################################################################
add_subdirectory(defs)

################################################################################
# Add Computation Components
################################################################################
add_subdirectory(comp-rational_data)
add_subdirectory(comp-rlitt_grafting)
add_subdirectory(comp-rlitt_ringshift)

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
add_subdirectory(note-wptt)

################################################################################
# Add Storage Components
################################################################################
add_subdirectory(store-json)
add_subdirectory(store-cpp_storage_interface)