/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_grafting.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "unity.h"

void test_results_positive(void)
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
        {5},
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

    note_wptt_node_t rootstock_node_5_grafted = {
        {&scion_root},
        {0,5},
        1,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_4_grafted = {
        {&rootstock_node_5_grafted},
        {0, 4},
        1,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root_grafted= {
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4_grafted
            },
        {0, 0, 0, 0,6},
        4,
        0,
        NOTE_WPTT_ORDER_FORWARD};
    note_wptt_t rootstock_grafted = {
        &rootstock_root_grafted,
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
    const comp_rlitt_grafting_result_t *result = comp_rlitt_grafting_result();
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(
        true, test_util_trees_equal(result->grafted_wptt, &rootstock_grafted));
}
