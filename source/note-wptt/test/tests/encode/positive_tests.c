#include "positive_tests.h"
#include "notation_wptt.h"
#include "unity.h"

static void test_encode_positive_knot_1(void);
static void test_encode_positive_knot_2(void);
static void test_encode_positive_tangle_1(void);
static void test_encode_positive_tangle_2(void);
static void test_encode_positive_tangle_3(void);
static void test_encode_positive_tangle_4(void);

/*!
 * @brief
 * @param
 */
void test_encode_positive(void)
{
    RUN_TEST(test_encode_positive_knot_1);
    RUN_TEST(test_encode_positive_knot_2);
    RUN_TEST(test_encode_positive_tangle_1);
    RUN_TEST(test_encode_positive_tangle_2);
    RUN_TEST(test_encode_positive_tangle_3);
    RUN_TEST(test_encode_positive_tangle_4);
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
static void test_encode_positive_knot_1(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "<1 13<2(3(4(5[7 8 9 10])12(11)6))>>";

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

    note_wptt_t note_wptt_valid = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_NONE,
                            };
    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}

/****************************** Test 2 Data ***********************************/

/*
 * - A valid string representing a knot.
 */

/*!
 * @brief
 * @param
 */
static void test_encode_positive_knot_2(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "[7 8 9 10]";


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

    note_wptt_t note_wptt_valid = {
                            &S_10,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_NONE,
                            };
    /* clang-format on */

    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = "";
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}

/****************************** Test 1 Data ***********************************/

/*
 * - A tree with an essential vertex.
 * - A tree with a vertex that has ring number.
 * - A tree with a vertex with more than one weight.
 * - A valid wptt representing a tangle with each label:
 *     - i
 */

/*!
 * @brief
 * @param
 */
static void test_encode_positive_tangle_1(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "i<1 13<2(3(4(5[7 8 9 10])12(11)6))>>";

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

    note_wptt_t note_wptt_valid = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_I,
                            };
    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = "";
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}

/****************************** Test 2 Data ***********************************/

/*
 * - A valid string representing a knot.
 * - A valid wptt representing a tangle with each label:
 *     - x
 */

/*!
 * @brief
 * @param
 */
static void test_encode_positive_tangle_2(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "x[7 8 9 10]";


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

    note_wptt_t note_wptt_valid = {
                            &S_10,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_X,
                            };
    /* clang-format on */

    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}

/****************************** Test 3 Data ***********************************/

/*
 * - A tree with an essential vertex.
 * - A tree with a vertex that has ring number.
 * - A tree with a vertex with more than one weight.
 * - A valid wptt representing a tangle with each label:
 *     - y
 */

/*!
 * @brief
 * @param
 */
static void test_encode_positive_tangle_3(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "y<1 13<2(3(4(5[7 8 9 10])12(11)6))>>";

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

    note_wptt_t note_wptt_valid = {
                            &P_1,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_Y,
                            };
    /* clang-format on */
    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}

/****************************** Test 4 Data ***********************************/

/*
 * - A valid string representing a knot.
 *
 * - A valid wptt representing a tangle with each label:
 *     - z
 */

/*!
 * @brief
 * @param
 */
static void test_encode_positive_tangle_4(void)
{
    uint8_t retval = -1;

    /* clang-format off */
    char string[UTIL_TANG_DEFS_MAX_CROSSINGNUM] =
    "z[7 8 9 10]";


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

    note_wptt_t note_wptt_valid = {
                            &S_10,
                            {NULL,0,0},
                            NOTE_wptt_V4_LABEL_Z,
                            };
    /* clang-format on */

    char test_string[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];
    retval = note_wptt_encode(
        note_wptt_valid, test_string, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(string, test_string);
}
