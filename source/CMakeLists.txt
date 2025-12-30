# ##############################################################################
# Add definitions directory
# ##############################################################################
add_subdirectory(defs)

# ##############################################################################
# Add Computation Components
# ##############################################################################
add_subdirectory(comp-rational_data)
add_subdirectory(comp-rlitt_grafting)
add_subdirectory(comp-wptt_vertex_canonicity)
add_subdirectory(comp-rlitt_positivity)
add_subdirectory(comp-rlitt_pure_vignette)

# ##############################################################################
# Add Generation Components
# ##############################################################################
add_subdirectory(gen-rational)
add_subdirectory(gen-montesinos)
add_subdirectory(gen-rlitt)

# ##############################################################################
# Add Mutator Components
# ##############################################################################
add_subdirectory(mut-rlitt_ringshift)
add_subdirectory(mut-wptt_f_moves)

# ##############################################################################
# Add Notation Components
# ##############################################################################
add_subdirectory(note-twist_vector)
add_subdirectory(note-algebraic_tangle_tree)
add_subdirectory(note-wptt)

# ##############################################################################
# Add Storage Components
# ##############################################################################
add_subdirectory(store-json)
add_subdirectory(store-cpp_storage_interface)
