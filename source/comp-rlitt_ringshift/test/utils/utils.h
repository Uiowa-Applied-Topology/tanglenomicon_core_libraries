/* */
/* Created by joe on 4/25/25. */
/* */
#ifndef TEST_COMP_RLITT_RINGSHIFT_CONFIG_UTILS_H
#define TEST_COMP_RLITT_RINGSHIFT_CONFIG_UTILS_H
#include "notation_wptt.h"
#include "storage_defs.h"

bool test_util_trees_equal(const note_wptt_t *tree1, const note_wptt_t *tree2);
void test_util_clear_buffer(void);
note_wptt_node_buffer_t *test_util_get_buffer(void);

#endif /* TEST_COMP_RLITT_RINGSHIFT_CONFIG_UTILS_H */
