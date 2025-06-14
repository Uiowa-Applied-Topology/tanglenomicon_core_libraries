//
// Created by joe on 4/25/25.
//
#include "negative_tests.h"
#include "notation_wptt.h"
#include "unity.h"

extern bool trees_equal(const note_wptt_t *tree1, const note_wptt_t *tree2);
static void test_encode_negative_1(void);
static void test_encode_negative_2(void);
static void test_encode_negative_3(void);
static void test_encode_negative_4(void);

/*!
 * @brief
 * @param
 */
void test_encode_negative(void)
{
    RUN_TEST(test_encode_negative_1);
    RUN_TEST(test_encode_negative_2);
    RUN_TEST(test_encode_negative_3);
    RUN_TEST(test_encode_negative_4);
}

/****************************** Test 1 Data ***********************************/
/*
 *
 * - An UNINIT label is present
 */
void test_encode_negative_1()
{

    uint8_t retval = -1;
    /* clang-format off */

    note_wptt_node_t S_7 = {
                            {NULL},
                            {7},
                            0,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_8 = {
                            {&S_7},
                            {0, 8},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_9 = {
                            {&S_8},
                            {0, 9},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_10 = {
                            {&S_9},
                            {0, 10},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_5 = {
                            {&S_10},
                            {5},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_12 = {
                            {NULL},
                            {11},
                            0,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_46 = {
                            {&S_5, &P_12},
                            {4, 12, 6},
                            2,
                            0,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_node_t P_3 = {
                            {&P_46},
                            {3},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_node_t P_2 = {
                            {&P_3},
                            {0},
                            1,
                            2,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_1 = {
                            {&P_2},
                            {13},
                            1,
                            1,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_t note_wptt = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_UNINIT,
                            };

    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = "";
    retval = note_wptt_encode(
        note_wptt, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_FAIL, 0x01u & retval);
}
/****************************** Test 2 Data ***********************************/
/*
 *
 * - A NULL root is present
 */
void test_encode_negative_2()
{

    uint8_t retval = -1;
    /* clang-format off */


    note_wptt_t note_wptt = {
                            NULL,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_X,
                            };

    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = "";
    retval = note_wptt_encode(
        note_wptt, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_FAIL, 0x01u & retval);
}

/****************************** Test 3 Data ***********************************/
/*
 *
 * - A NULL child is present
 */
void test_encode_negative_3()
{

    uint8_t retval = -1;
    /* clang-format off */

    note_wptt_node_t P_1 = {
                            {NULL},
                            {13},
                            1,
                            1,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_t note_wptt = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_UNINIT,
                            };

    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = "";
    retval = note_wptt_encode(
        note_wptt, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_FAIL, 0x01u & retval);
}

/****************************** Test 4 Data ***********************************/
/*
 *
 * - A NULL pointer buffer is passed to the function
 */
void test_encode_negative_4()
{

    uint8_t retval = -1;
    /* clang-format off */

    note_wptt_node_t S_7 = {
                            {NULL},
                            {7},
                            0,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_8 = {
                            {&S_7},
                            {0, 8},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_9 = {
                            {&S_8},
                            {0, 9},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_10 = {
                            {&S_9},
                            {0, 10},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t S_5 = {
                            {&S_10},
                            {5},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_12 = {
                            {NULL},
                            {11},
                            0,
                            0,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_46 = {
                            {&S_5, &P_12},
                            {4, 12, 6},
                            2,
                            0,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_node_t P_3 = {
                            {&P_46},
                            {3},
                            1,
                            0,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_node_t P_2 = {
                            {&P_3},
                            {0},
                            1,
                            2,
                            NOTE_wptt_ORDER_FORWARD};
    note_wptt_node_t P_1 = {
                            {&P_2},
                            {13},
                            1,
                            1,
                            NOTE_wptt_ORDER_FORWARD};

    note_wptt_t note_wptt = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_NONE,
                            };

    /* clang-format on */
    retval = note_wptt_encode(
        note_wptt, NULL, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_FAIL, 0x01u & retval);
}