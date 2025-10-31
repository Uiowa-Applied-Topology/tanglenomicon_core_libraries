/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_ringshift.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "comp_rlitt_ringshift.h"
#include "unity.h"

static void test_compute_negative_no_config(void);

void test_compute_negative(void)
{
    RUN_TEST(test_compute_negative_no_config);
}

static void test_compute_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = comp_rlitt_ringshift_compute();
    TEST_ASSERT_EQUAL(COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                       COMP_RLITT_RINGSHIFT_COMPUTE_CFG_ERROR),
                      retval);
}
