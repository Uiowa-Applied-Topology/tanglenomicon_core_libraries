/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_vertex_canonicity.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "stdbool.h"
#include "unity.h"

static void test_results_canon(void);
static void test_results_noncanon(void);

void test_results_positive(void)
{
    RUN_TEST(test_results_canon);
    RUN_TEST(test_results_noncanon);
}

static void test_results_canon(void)
{
    int retval = 0;

    /* clang-format off */

    note_wptt_node_t rootstock_node_1 = {//6
            {NULL},
            {1},
            0,
            1,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_2 = {//5
            {NULL},
            {8},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_3 = {//4
            {NULL},
            {3},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_6 = {//3
            {NULL},
            {99},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_5 = {//2
            {&rootstock_node_6},
            {0,5},
            1,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_4 = {//1
            {&rootstock_node_5},
            {0, 3},
            1,
            4,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root= {//0
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4},
        {0, 0, 0, 0, 4},
        4,
        6,
        NOTE_WPTT_ORDER_REVERSE};

    note_wptt_t rootstock = {
        &rootstock_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    /* clang-format on */
    comp_wptt_vert_canon_config_t cfg = { NULL,
                                          &rootstock,
                                          &rootstock_root,
                                          NULL,
                                          false,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    retval = comp_wptt_vert_canon_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_CONFIG_SUCCESS, retval);
    retval = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    const comp_wptt_vert_canon_result_t *result = comp_wptt_vert_canon_result();

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(COMP_WPTT_VERT_CANON_IS_CANONICAL, result->is_canonical);
}

static void test_results_noncanon(void)
{
    int retval = 0;

    /* clang-format off */

    note_wptt_node_t rootstock_node_1 = {//6
            {NULL},
            {1},
            0,
            1,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_2 = {//5
            {NULL},
            {8},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_3 = {//4
            {NULL},
            {3},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_6 = {//3
            {NULL},
            {99},
            0,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_5 = {//2
            {&rootstock_node_6},
            {0,5},
            1,
            0,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_node_4 = {//1
            {&rootstock_node_5},
            {0, 3},
            1,
            4,
            NOTE_WPTT_ORDER_FORWARD};
    note_wptt_node_t rootstock_root= {//0
        {
            &rootstock_node_1,
            &rootstock_node_2,
            &rootstock_node_3,
            &rootstock_node_4},
        {0, 3, 0, 0, 4},
        4,
        6,
        NOTE_WPTT_ORDER_REVERSE};

    note_wptt_t rootstock = {
        &rootstock_root,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    /* clang-format on */
    comp_wptt_vert_canon_config_t cfg = { NULL,
                                          &rootstock,
                                          rootstock.root,
                                          NULL,
                                          false,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    retval = comp_wptt_vert_canon_config(&cfg);
    TEST_ASSERT_EQUAL(COMP_DEFS_CONFIG_SUCCESS, retval);
    retval = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);
    const comp_wptt_vert_canon_result_t *result = comp_wptt_vert_canon_result();

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(COMP_WPTT_VERT_CANON_IS_NONCANONICAL, result->is_canonical);
}
