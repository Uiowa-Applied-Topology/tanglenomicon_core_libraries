/* */
/* Created by joe on 4/25/25. */
/* */
#include "negative_tests.h"
#include "notation_plpath.h"
#include "unity.h"
#include "notation_defs.h"

static void test_decode_negative_badchar(void);
static void test_decode_negative_badpoint(void);
static void test_decode_negative_null(void);


void test_decode_negative(void)
{
    RUN_TEST(test_decode_negative_badchar);
    RUN_TEST(test_decode_negative_badpoint);
    RUN_TEST(test_decode_negative_null);
}

/************************************************************************************************/
static void test_decode_negative_null(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n1,0,\n1,1,1\n1,2,2\n\n2,0,0";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;



    path.buffer = &buffer;

    path.segment_count = 0;


    retval = note_plpath_decode(NULL, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_EMPTY_STR),
                      retval);
    retval = note_plpath_decode(paths, NULL);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_NULL_DEST),
                      retval);
}

/************************************************************************************************/

/*
 *  - A string with a bad char in the input string.
 */
static void test_decode_negative_badpoint(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n1,0,\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths2 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n1,,0\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths3 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths4 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n,,\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths_e =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n1,0,";
    char *paths_e2 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n1,,0";
    char *paths_e3 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n,0,0";
    char *paths_e4 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a% comment\n,,";
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;



    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths2, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths3, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    retval             = note_plpath_decode(paths4, &path);
    path.segment_count = 0;
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);

    retval = note_plpath_decode(paths_e, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths_e2, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths_e3, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    retval             = note_plpath_decode(paths_e4, &path);
    path.segment_count = 0;
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
}

/************************************************************************************************/

/*
 *  - A string with a bad char in the input string.
 */
static void test_decode_negative_badchar(void)
{
    uint8_t retval;
    char *  paths =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n// a% comment\n1,0,0%\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths2 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n// a% comment\n%1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths3 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n// a% comment\n%1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
    char *paths4 =
        "0,0,0\n0,1,1\n0,2,2\n0,3,3\n// a% comment\n1,0,0%";
    note_plpath_point_t        points[10u * UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;



    path.buffer = &buffer;

    path.segment_count = 0;

    retval = note_plpath_decode(paths, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths2, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths3, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
    path.segment_count = 0;
    retval             = note_plpath_decode(paths4, &path);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR), retval);
}
