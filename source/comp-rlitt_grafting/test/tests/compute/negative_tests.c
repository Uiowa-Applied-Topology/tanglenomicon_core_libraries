/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_grafting.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "comp_rlitt_grafting.h"
#include "unity.h"

static void test_compute_negative_no_config(void);

void test_compute_negative(void)
{
    RUN_TEST(test_compute_negative_no_config);
}

static void test_compute_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = comp_rlitt_grafting_compute();
    TEST_ASSERT_EQUAL(COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                       COMP_RLITT_GRAFTING_COMPUTE_CFG_ERROR),
                      retval);
}
