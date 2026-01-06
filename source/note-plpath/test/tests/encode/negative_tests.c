/* */
/* Created by joe on 4/25/25. */
/* */
#include "negative_tests.h"
#include "notation_plpath.h"
#include "unity.h"
#include "notation_defs.h"
#include "../../utils/utils.h"

void test_encode_negative(void)
{
    uint8_t       retval;
    note_plpath_t good_path    = { { &p00, &p10, &p20 }, 3, NULL };
    char          output[1000] = { '\0' };

    retval = note_plpath_encode(good_path, NULL, 1000);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_ENCODE_FAIL, NOTE_PLPATH_ENCODE_STR_BUF), retval);
    retval = note_plpath_encode(good_path, &output[0], 0);
    TEST_ASSERT_EQUAL(NOTE_STATUS_BLDR(NOTE_DEFS_ENCODE_FAIL, NOTE_PLPATH_ENCODE_OVRUNDR_ERROR),
                      retval);
}
