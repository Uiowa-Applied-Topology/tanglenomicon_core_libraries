#include "positive_tests.h"
#include "notation_plpath.h"
#include "unity.h"

static void test_decode_positive_knot_1(void);

/*!
 * @brief
 * @param
 */
void test_decode_positive(void)
{
    RUN_TEST(test_decode_positive_knot_1);
}

/****************************** Test 1 Data ***********************************/

/*
 * - A tree with an essential vertex.
 * - A tree with a vertex that has ring number.
 * - A tree with a vertex with more than one weight.
 */

static void test_decode_positive_knot_1(void)
{
    char *paths =
        "1.5,-1.5,0.2\n5,-1,2\n1.5,-1.5,0.2\n1.5,-1.5,0.2\n1.5,-1.5,0.2\n\n// a comment\n1.5,-1.5,0.2\n5,-1,2\n1.5,-1.5,0.2\n\n1.5,-1.5,0.2";
    struct note_plpath_point_t points[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = { 0, 0, 0, NULL };
    note_plpath_point_buffer_t buffer = { (note_plpath_point_t *)&points,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
    note_plpath_t path;

    path.buffer         = &buffer;
    path.segement_count = 0;

    note_plpath_decode(paths, &path);
}
