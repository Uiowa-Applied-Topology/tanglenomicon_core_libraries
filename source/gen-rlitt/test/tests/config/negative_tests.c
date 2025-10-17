/* */
/* Created by joe on 6/23/25. */
/* */
#include "generator_rlitt.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_config_negative_null_config(void);
static void test_config_negative_null_param(void);
static void test_config_negative_null_param_rootstocklist(void);
static void test_config_negative_null_param_rootstocklen(void);
static void test_config_negative_null_param_scionlist(void);
static void test_config_negative_null_param_scionlen(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_null_param_rootstocklist);
    RUN_TEST(test_config_negative_null_param_rootstocklen);
    RUN_TEST(test_config_negative_null_param_scionlist);
    RUN_TEST(test_config_negative_null_param_scionlen);
}

static void test_config_negative_null_param_rootstocklist(void)
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
        NULL,
        4,
        list,
        4,
    };

    uint8_t ret_val = gen_rlitt_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(
        GEN_STATUS_BLDR(GEN_DEFS_CONFIG_FAIL, GEN_RLITT_CONFIG_ROOTSTOCKS_ERROR),
        ret_val);
}

static void test_config_negative_null_param_rootstocklen(void)
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
        0,
        list,
        4,
    };

    uint8_t ret_val = gen_rlitt_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(
        GEN_STATUS_BLDR(GEN_DEFS_CONFIG_FAIL, GEN_RLITT_CONFIG_ROOTSTOCKS_ERROR),
        ret_val);
}

static void test_config_negative_null_param_scionlist(void)
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
        NULL,
        4,
    };

    uint8_t ret_val = gen_rlitt_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(
        GEN_STATUS_BLDR(GEN_DEFS_CONFIG_FAIL, GEN_RLITT_CONFIG_SCIONS_ERROR),
        ret_val);
}

static void test_config_negative_null_param_scionlen(void)
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
        0,
    };

    uint8_t ret_val = gen_rlitt_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(
        GEN_STATUS_BLDR(GEN_DEFS_CONFIG_FAIL, GEN_RLITT_CONFIG_SCIONS_ERROR),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = gen_rlitt_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        GEN_STATUS_BLDR(GEN_DEFS_CONFIG_FAIL, GEN_RLITT_CONFIG_IS_NULL),
        ret_val);
}
