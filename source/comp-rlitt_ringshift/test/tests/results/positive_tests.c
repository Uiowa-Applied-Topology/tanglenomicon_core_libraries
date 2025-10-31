/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_ringshift.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "unity.h"

void test_results_positive(void)
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

    note_wptt_node_t wptt_root_ringshiftd= {
        {
            &leaf,
            &wptt_internal,
            &leaf,
            &leaf,
            &leaf,
            &leaf,
            &ring_subtree,
            &ring_subtree,
            &ring_subtree,
            &ring_subtree},
        {0},
        10,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_t wptt_ringshiftd = {
        &wptt_root_ringshiftd,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };
    /* clang-format on */
    test_util_clear_buffer();
    comp_rlitt_ringshift_config_t cfg = {
        NULL, &wptt
    };
    retval = comp_rlitt_ringshift_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    retval = comp_rlitt_ringshift_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    const comp_rlitt_ringshift_result_t *result = comp_rlitt_ringshift_result();
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(
        true, test_util_trees_equal(result->ringshiftd_wptt, &wptt_ringshiftd));
}
