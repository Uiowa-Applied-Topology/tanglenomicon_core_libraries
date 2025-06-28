/* */
/* Created by joe on 4/27/25. */
/* */
#include "turn_around_test.h"
#include "notation_wptt.h"
#include "unity.h"

extern bool trees_equal(const note_wptt_t *tree1, const note_wptt_t *tree2);
static void test_turn_around_test_1(void);

/*!
 * @brief
 * @param
 */
void test_turn_around(void)
{
    RUN_TEST(test_turn_around_test_1);
}

/****************************** Test 1 Data ***********************************/

/*
 * - A tree with an essential vertex.
 * - A tree with a vertex that has ring number.
 * - A tree with a vertex with more than one weight.
 */

/*!
 * @brief
 * @param
 */
static void test_turn_around_test_1(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "x<1 13<2(3(4(5[7 8 -9 10])12(-11)6))>>";
    struct note_wptt_node_t  note_wptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    note_wptt_node_buffer_t buffer = {(note_wptt_node_t*)&note_wptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_wptt_t note_wptt = {
                                NULL,
                                buffer,
                                NOTE_wptt_V4_LABEL_UNINIT};
    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];

    retval = note_wptt_decode(string, &note_wptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);

    retval = note_wptt_encode(
        note_wptt, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}
