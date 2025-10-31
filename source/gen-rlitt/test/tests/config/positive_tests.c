/* */
/* Created by joe on 6/23/25. */
/* */
#include "generator_rlitt.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "notation_wptt.h"
#include "unity.h"
#include "../../utils/utils.h"
extern uint8_t stub_write_success();

void test_config_positive(void)
{
    /* clang-format off */
    note_wptt_node_t rootstock_node_1 = {
            {NULL},
            {1},
            0,
            1,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_2 = {
            {NULL},
            {2},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_3 = {
            {NULL},
            {3},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_5 = {
            {NULL},
            {5},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_4 = {
            {&rootstock_node_5},
            {1, 3},
            1,
            4,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root= {
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4},
        {9, 1, 2, 3, 4},
        4,
        6,
        NOTE_WPTT_ORDER_REVERSE};
    note_wptt_t rootstock = {
        &rootstock_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    const note_wptt_t *list[] = {&rootstock, &rootstock, &rootstock, &rootstock };
    /* clang-format on */
    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        list,
        4,
        list,
        4,
    };

    uint8_t ret_val = gen_rlitt_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);

    gen_rlitt_config_t cfg2 = {
        NULL,
        list,
        4,
        list,
        4,
    };

    ret_val = gen_rlitt_config(&cfg2);
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
}
