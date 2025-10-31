/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_grafting.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"
extern uint8_t stub_write_success();
static void test_config_positive_nowrite(void);
static void test_config_positive_write(void);

void test_config_positive(void)
{
    RUN_TEST(test_config_positive_nowrite);
    RUN_TEST(test_config_positive_write);
}

static void test_config_positive_write(void)
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

    note_wptt_node_t scion_root = {
        {NULL},
        {1},
        0,
        1,
        NOTE_WPTT_ORDER_FORWARD};

    note_wptt_t scion = {
        &scion_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };
    /* clang-format on */
    test_util_clear_buffer();
    note_wptt_t output_wptt = {
        NULL, test_util_get_buffer(), NOTE_WPTT_V4_LABEL_UNINIT
    };
    comp_rlitt_grafting_config_t cfg = {
        &test_stub_write_success, &rootstock, &scion, 5, &output_wptt
    };

    uint8_t ret_val = comp_rlitt_grafting_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
}

static void test_config_positive_nowrite(void)
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

    note_wptt_node_t scion_root = {
        {NULL},
        {1},
        0,
        1,
        NOTE_WPTT_ORDER_FORWARD};

    note_wptt_t scion = {
        &scion_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };
    /* clang-format on */
    test_util_clear_buffer();
    note_wptt_t output_wptt = {
        NULL, test_util_get_buffer(), NOTE_WPTT_V4_LABEL_UNINIT
    };
    comp_rlitt_grafting_config_t cfg = { NULL, &rootstock, &scion, 5, &output_wptt };

    uint8_t ret_val = comp_rlitt_grafting_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
}
