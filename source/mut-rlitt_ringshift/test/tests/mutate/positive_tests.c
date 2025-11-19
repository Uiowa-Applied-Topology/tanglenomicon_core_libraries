/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "mut_rlitt_ringshift.h"
#include "unity.h"
#include "../../utils/utils.h"

void test_mutate_positive(void)
{
    int retval = 0;

    /* clang-format off */
    note_wptt_node_t leaf = {
        {NULL},
        {8},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t ring_leaf = {
        {NULL},
        {2},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t ring_subtree = {
        {&ring_leaf,&ring_leaf},
        {0,0,1},
        2,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_internal = {
        {&ring_subtree},
        {0,5},
        1,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_root= {
        {
            &leaf,
            &wptt_internal,
            &leaf,
            &ring_subtree,
            &leaf,
            &ring_subtree,
            &leaf,
            &ring_subtree,
            &leaf,
            &ring_subtree},
        {0},
        10,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_t wptt = {
        &wptt_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };
    /* clang-format on */
    test_util_clear_buffer();
    mut_rlitt_ringshift_config_t cfg = {
        &wptt
    };
    retval = mut_rlitt_ringshift_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_rlitt_ringshift_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
}
