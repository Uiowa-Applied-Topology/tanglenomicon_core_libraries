/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_canonicity.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/data.h"
static void test_compute_negative_no_config(void);
static void test_compute_negative_executed(void);

void test_compute_negative(void)
{
    RUN_TEST(test_compute_negative_no_config);
    RUN_TEST(test_compute_negative_executed);
}

static void test_compute_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = comp_wptt_canonicity_compute();
    TEST_ASSERT_EQUAL(COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                       COMP_WPTT_CANON_COMPUTE_CFG_ERROR), retval);
}

static void test_compute_negative_executed(void)
{
    uint8_t retval = 0;

    comp_wptt_canonicity_config_t cfg = { NULL,
                                          &ib3b,
                                          COMP_WPTT_CANON_POS_NEG };
    uint8_t ret_val = comp_wptt_canonicity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_canonicity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    retval = comp_wptt_canonicity_compute();
    TEST_ASSERT_EQUAL(COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                       COMP_WPTT_CANON_COMPUTE_ALREADY_COMPUTED), retval);
}
