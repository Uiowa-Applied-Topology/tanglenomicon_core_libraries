/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_grafting.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "comp_rlitt_grafting.h"
#include "unity.h"

static void test_config_negative_null_config(void);
static void test_config_negative_null_param(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_null_param);
}

static void test_config_negative_null_param(void)
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
        NULL, NULL, NOTE_WPTT_V4_LABEL_UNINIT
    };
    comp_rlitt_grafting_config_t cfg1 = {
        &test_stub_write_success, NULL, &scion, 5, &output_wptt
    };
    comp_rlitt_grafting_config_t cfg2 = {
        &test_stub_write_success, &rootstock, NULL, 5, &output_wptt
    };
    comp_rlitt_grafting_config_t cfg3 = {
        &test_stub_write_success, &rootstock, &scion, 5, NULL
    };

    uint8_t ret_val = comp_rlitt_grafting_config(&cfg1);
    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_RLITT_GRAFTING_CONFIG_ROOTSTOCK),
        ret_val);
    ret_val = comp_rlitt_grafting_config(&cfg2);
    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_RLITT_GRAFTING_CONFIG_SCION),
        ret_val);
    ret_val = comp_rlitt_grafting_config(&cfg3);
    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_RLITT_GRAFTING_CONFIG_BUFFER),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_rlitt_grafting_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_RLITT_GRAFTING_COMPUTE_CFG_ERROR),
        ret_val);
}
