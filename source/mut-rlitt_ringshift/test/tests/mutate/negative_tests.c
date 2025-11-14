/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_rlitt_ringshift.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"

static void test_mutate_negative_no_config(void);

void test_mutate_negative(void)
{
    RUN_TEST(test_mutate_negative_no_config);
}

static void test_mutate_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = mut_rlitt_ringshift_mutate();
    TEST_ASSERT_EQUAL(MUT_STATUS_BLDR(MUT_DEFS_COMPUTE_FAIL,
                                      MUT_RLITT_RINGSHIFT_COMPUTE_CFG_ERROR),
                      retval);
}
