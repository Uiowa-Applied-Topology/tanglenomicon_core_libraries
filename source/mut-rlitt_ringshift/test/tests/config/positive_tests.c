/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_rlitt_ringshift.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"
extern uint8_t stub_write_success();

void test_config_positive(void)
{
    /* clang-format off */
    note_wptt_node_t wptt_node_1 = {
        {NULL},
        {1},
        0,
        1,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_node_2 = {
        {NULL},
        {2},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_node_3 = {
        {NULL},
        {3},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_node_5 = {
        {NULL},
        {5},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_node_4 = {
        {&wptt_node_5},
        {1, 3},
        1,
        4,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t wptt_root= {
        {
            &wptt_node_1,
            &wptt_node_2,
            &wptt_node_3,
            &wptt_node_4},
        {9, 1, 2, 3, 4},
        4,
        6,
        NOTE_WPTT_ORDER_REVERSE};
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

    uint8_t ret_val = mut_rlitt_ringshift_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, MUT_DEFS_CONFIG_SUCCESS);
}
