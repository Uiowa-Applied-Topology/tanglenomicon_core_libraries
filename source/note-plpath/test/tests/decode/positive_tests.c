#include "positive_tests.h"
#include "bits/stdint-uintn.h"
#include "notation_plpath.h"
#include "notation_defs.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_decode_positive_multiple_segments(void);
static void test_decode_positive_single_segment(void);
static void test_decode_positive_no_comment(void);
static void test_decode_positive_with_comment(void);
static void test_decode_positive_nlnlnl(void);
static void test_decode_positive_term_nl(void);
static void test_decode_positive_no_segments(void);


/*!
 * @brief
 * @param
 */
void test_decode_positive(void)
{
    RUN_TEST(test_decode_positive_multiple_segments);
    RUN_TEST(test_decode_positive_single_segment);
    RUN_TEST(test_decode_positive_no_comment);
    RUN_TEST(test_decode_positive_with_comment);
    RUN_TEST(test_decode_positive_nlnlnl);
    RUN_TEST(test_decode_positive_term_nl);
    RUN_TEST(test_decode_positive_no_segments);
}

/************************************************************************************************/

/*
 *  - A string with multiple segments
 */

static void test_decode_positive_multiple_segments(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a comment\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with a single segment
 */

static void test_decode_positive_single_segment(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00 }, 1, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with no comments
 */

static void test_decode_positive_no_comment(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with comments
 */

static void test_decode_positive_with_comment(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a comment\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with `\n\n\n`
 */

static void test_decode_positive_nlnlnl(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n\n// a comment\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0\n\n\n";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with terminal `\n`
 */

static void test_decode_positive_term_nl(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n\n// a comment\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0\n";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}

/************************************************************************************************/

/*
 *  - A string with no segments.
 */
static void test_decode_positive_no_segments(void)
{
    uint8_t retval;
    char *  paths = "";

    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;


    note_plpath_t good_path = { { NULL }, 0, NULL };


    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
}
