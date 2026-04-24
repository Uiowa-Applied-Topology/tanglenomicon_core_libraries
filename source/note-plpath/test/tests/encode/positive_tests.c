#include "positive_tests.h"
#include "notation_plpath.h"
#include "notation_defs.h"
#include "unity.h"
#include "../../utils/utils.h"
#include <string.h>

static void test_encode_positive_multiple_segments(void);
static void test_encode_positive_single_segment(void);
static void test_encode_positive_no_segments(void);


/**
 * \brief
 * \param
 */
void test_encode_positive(void)
{
    RUN_TEST(test_encode_positive_multiple_segments);
    RUN_TEST(test_encode_positive_single_segment);
    RUN_TEST(test_encode_positive_no_segments);
}

/************************************************************************************************/

/*
 *  - A string with multiple segments
 */

static void test_encode_positive_multiple_segments(void)
{
    uint8_t retval;
    char *  paths =
        "0.000000,0.000000,0.000000\n0.000000,1.000000,1.000000\n0.000000,2.000000,2.000000\n0.000000,3.000000,3.000000\n\n1.000000,0.000000,0.000000\n1.000000,1.000000,1.000000\n1.000000,2.000000,2.000000\n\n2.000000,0.000000,0.000000";



    note_plpath_t good_path = { &sp00, NULL, NULL };

    char output[1000] = { '\0' };

    retval = note_plpath_encode(good_path, output, 1000);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(paths, output);
}

/************************************************************************************************/

/*
 *  - A string with a single segment
 */

static void test_encode_positive_single_segment(void)
{
    uint8_t retval;
    char *  paths =
        "0.000000,0.000000,0.000000\n0.000000,1.000000,1.000000\n0.000000,2.000000,2.000000\n0.000000,3.000000,3.000000";

    note_plpath_t good_path    = { &sp00ss, NULL, NULL };
    char          output[1000] = { '\0' };

    retval = note_plpath_encode(good_path, output, 1000);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(paths, output);
}

/************************************************************************************************/

/*
 *  - A string with no segments.
 */
static void test_encode_positive_no_segments(void)
{
    uint8_t retval;
    char *  paths = "";

    note_plpath_t good_path    = { NULL, NULL, NULL };
    char          output[1000] = { '\0' };

    retval = note_plpath_encode(good_path, output, 1000);
    TEST_ASSERT_EQUAL(NOTE_DEFS_ENCODE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING(paths, output);
}
