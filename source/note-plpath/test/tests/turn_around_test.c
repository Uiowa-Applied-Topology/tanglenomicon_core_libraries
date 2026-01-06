/* */
/* Created by joe on 4/27/25. */
/* */
#include "turn_around_test.h"
#include "notation_plpath.h"
#include "notation_defs.h"
#include "unity.h"
#include "../utils/utils.h"

static void test_turn_around_test_ede(void);
static void test_turn_around_test_ded(void);

/*!
 * @brief
 * @param
 */
void test_turn_around(void)
{
    RUN_TEST(test_turn_around_test_ede);
    RUN_TEST(test_turn_around_test_ded);
}

static char *paths_e =
    "0.000000,0.000000,0.000000\n0.000000,1.000000,1.000000\n0.000000,2.000000,2.000000\n0.000000,3.000000,3.000000\n\n1.000000,0.000000,0.000000\n1.000000,1.000000,1.000000\n1.000000,2.000000,2.000000\n\n2.000000,0.000000,0.000000";
static char *paths_d =
    "0,0,0\n0,1,1\n0,2,2\n0,3,3\n\n// a comment\n1,0,0\n1,1,1\n1,2,2\n\n2,0,0";
static note_plpath_t good_path = { { &p00, &p10, &p20 }, 3, NULL };
/************************************************************************************************/

static void test_turn_around_test_ede(void)
{
    uint8_t                    retval;
    char                       output[1000]      = { '\0' };
    char                       output_post[1000] = { '\0' };
    note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t              path = { { NULL }, 0, &buffer };

    retval = note_plpath_encode(good_path, &output[0], 1000);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(paths_e, output);
    retval = note_plpath_decode(output, &path);
    TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
    retval = note_plpath_encode(path, &output_post[0], 1000);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(paths_e, output_post);
    TEST_ASSERT_EQUAL_STRING(output_post, output);
}

/************************************************************************************************/
static void test_turn_around_test_ded(void)
{
    {
        uint8_t                    retval;
        char                       output[1000] = { '\0' };
        note_plpath_point_t        points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
        note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                              UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                              0 };
        note_plpath_t              path = { { NULL }, 0, &buffer };

        note_plpath_point_t        points_post[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
        note_plpath_point_buffer_t buffer_post = { (note_plpath_point_t *)&points_post,
                                                   UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                                   0 };
        note_plpath_t path_post = { { NULL }, 0, &buffer_post };

        retval = note_plpath_decode(paths_d, &path);
        TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
        TEST_ASSERT_EQUAL(true, test_util_path_equal(&path, &good_path));
        retval = note_plpath_encode(good_path, &output[0], 1000);
        TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
        TEST_ASSERT_EQUAL_STRING(paths_e, output);
        retval = note_plpath_decode(output, &path_post);
        TEST_ASSERT_EQUAL(NOTE_DEFS_DECODE_SUCCESS, retval);
        TEST_ASSERT_EQUAL(true, test_util_path_equal(&path_post, &good_path));
        TEST_ASSERT_EQUAL(true, test_util_path_equal(&path_post, &path));
    }
}
