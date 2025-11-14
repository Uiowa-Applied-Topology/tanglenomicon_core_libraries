/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_rlitt_ringshift.h"
#include "unity.h"
#include "../../utils/utils.h"
static void test_compute_write(void);
static void test_compute_no_write(void);

void test_compute_positive(void)
{
    RUN_TEST(test_compute_write);
    RUN_TEST(test_compute_no_write);
}

/*!
 * @brief
 * @param
 */
static void test_compute_write(void)
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
    comp_rlitt_ringshift_config_t cfg = {
        &test_stub_write_success, &wptt
    };
    retval = comp_rlitt_ringshift_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    retval = comp_rlitt_ringshift_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING("i([8](([2][2]1)5)[8][8][8][8]([2][2]1)([2][2]1)([2][2]1)([2][2]1))",
                             test_stub_read_success(
                                 "i([8](([2][2]1)5)[8][8][8][8]([2][2]1)([2][2]1)([2][2]1)([2][2]1))",
                                 "ringshifted"));
}

/*!
 * @brief
 * @param
 */
static void test_compute_no_write(void)
{
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
    comp_rlitt_ringshift_config_t cfg = {
        NULL, &wptt
    };
    uint8_t retval = comp_rlitt_ringshift_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    retval = comp_rlitt_ringshift_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
}
