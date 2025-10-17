add_library(notation_wptt STATIC src/notation_wptt.c)

target_include_directories(notation_wptt PUBLIC src)
target_link_libraries(notation_wptt tang_defs notation_defs)

add_lizard_target(
  notation_wptt_lizard
  ALL
  ARGUMENTS
    --warnings_only
)

set_target_properties(notation_wptt
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)