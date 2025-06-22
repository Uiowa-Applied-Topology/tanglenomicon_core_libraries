//
// Created by joe on 4/25/25.
//
#include "negative_tests.h"
#include "notation_wptt.h"
#include "unity.h"

extern bool trees_equal(const note_wptt_t *tree1, const note_wptt_t *tree2);
static void test_decode_negative_test_1(void);
static void test_decode_negative_test_2(void);
static void test_decode_negative_test_3(void);
static void test_decode_negative_test_4(void);

void test_decode_negative(void)
{
    RUN_TEST(test_decode_negative_test_1);
    RUN_TEST(test_decode_negative_test_2);
    RUN_TEST(test_decode_negative_test_3);
    RUN_TEST(test_decode_negative_test_4);
}

/****************************** Test 1 Data ***********************************/
/*
 *
 * - An empty string.
 */
void test_decode_negative_test_1()
{

    uint8_t retval = -1;
    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "";
    struct note_wptt_node_t  note_wptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {NULL};
    note_wptt_node_buffer_t buffer = {(note_wptt_node_t*)&note_wptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_wptt_t note_wptt = {
                                NULL,
                                buffer,
                                NOTE_wptt_V4_LABEL_UNINIT};

    retval = note_wptt_decode(string, &note_wptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_FAIL, 0x01u & retval);
}
/****************************** Test 1 Data ***********************************/
/*
 *
 * - A missing closing delimiter.
 */
void test_decode_negative_test_2()
{

    uint8_t retval = -1;
    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "(";
    struct note_wptt_node_t  note_wptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {NULL};
    note_wptt_node_buffer_t buffer = {(note_wptt_node_t*)&note_wptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_wptt_t note_wptt = {
                                NULL,
                                buffer,
                                NOTE_wptt_V4_LABEL_UNINIT};

    retval = note_wptt_decode(string, &note_wptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_FAIL, 0x01u & retval);
}
/****************************** Test 1 Data ***********************************/
/*
 *
 * - An unexpected character is in the string.
 */
void test_decode_negative_test_3()
{

    uint8_t retval = -1;
    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "x(4 *)";
    struct note_wptt_node_t  note_wptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {NULL};
    note_wptt_node_buffer_t buffer = {(note_wptt_node_t*)&note_wptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_wptt_t note_wptt = {
                                NULL,
                                buffer,
                                NOTE_wptt_V4_LABEL_UNINIT};

    retval = note_wptt_decode(string, &note_wptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_FAIL, 0x01u & retval);
}
/****************************** Test 1 Data ***********************************/
/*
 *
 * - The string has more weights than possible.
 */
void test_decode_negative_test_4()
{

    uint8_t retval = -1;
    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "x(4 4)";
    struct note_wptt_node_t  note_wptt_node[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {NULL};
    note_wptt_node_buffer_t buffer = {(note_wptt_node_t*)&note_wptt_node,
                                        UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                        0};
    note_wptt_t note_wptt = {
                                NULL,
                                buffer,
                                NOTE_wptt_V4_LABEL_UNINIT};

    retval = note_wptt_decode(string, &note_wptt);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_FAIL, 0x01u & retval);
}