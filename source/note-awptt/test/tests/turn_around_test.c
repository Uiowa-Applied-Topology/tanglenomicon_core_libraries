//
// Created by joe on 4/27/25.
//
#include "turn_around_test.h"
#include "notation_awptt.h"
#include "unity.h"

extern bool trees_equal(const note_awptt_t *tree1, const note_awptt_t *tree2);
static void test_turn_around_test_1(void);

/*!
 * @brief
 * @param
 */
void test_turn_around(void) { RUN_TEST(test_turn_around_test_1); }

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
    struct note_awptt_node_t  note_awptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    note_awptt_node_buffer_t buffer = {(note_awptt_node_t*)&note_awptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_awptt_t note_awptt = {
                                NULL,
                                buffer,
                                NOTE_AWPTT_V4_LABEL_UNINIT};
    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];

    retval = note_awptt_decode(string, &note_awptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);

    retval = note_awptt_encode(
        note_awptt, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}
