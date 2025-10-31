/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_rlitt_grafting.h"
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
    note_wptt_node_t rootstock_node_1 = {
        {NULL},
        {1},
        0,
        0,
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
        {-5},
        0,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_4 = {
        {&rootstock_node_5},
        {0, 4},
        1,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root= {
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4},
        {0, 0, 0, 0, 6},
        4,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_t rootstock = {
        &rootstock_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    note_wptt_node_t scion_root = {
        {NULL},
        {99},
        0,
        0,
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

    retval = comp_rlitt_grafting_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_CONFIG_SUCCESS, retval);
    retval = comp_rlitt_grafting_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);

    TEST_ASSERT_EQUAL_STRING("i([1][2][3][5 4]6)",
                             test_stub_read_success("i([1][2][3][99 5 4]6)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[99]", test_stub_read_success("i([1][2][3][99 5 4]6)", "scion"));
}

/*!
 * @brief
 * @param
 */
static void test_compute_no_write(void)
{
    /* clang-format off */
    note_wptt_node_t rootstock_node_1 = {
            {NULL},
            {1},
            0,
            0,
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
            {0, 3},
            1,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root= {
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4},
        {0, 0, 0, 0, 4},
        4,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_t rootstock = {
        &rootstock_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    note_wptt_node_t scion_root = {
        {NULL},
        {99},
        0,
        0,
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
        NULL, &rootstock, &scion, 5, &output_wptt
    };
    uint8_t retval = comp_rlitt_grafting_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_CONFIG_SUCCESS, retval);
    retval = comp_rlitt_grafting_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
}
