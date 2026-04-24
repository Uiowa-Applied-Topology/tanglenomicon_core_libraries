/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_sum_parity.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"

static void test_config_negative_null_config(void);
static void test_config_negative_bad_param_OP(void);
static void test_config_negative_bad_param_A(void);
static void test_config_negative_bad_param_B(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_bad_param_OP);
    RUN_TEST(test_config_negative_bad_param_A);
    RUN_TEST(test_config_negative_bad_param_B);
}

static void test_config_negative_bad_param_A(void)
{
    comp_sum_parity_config_t cfg = { .storage_write = NULL,
                                     .write_key     = NULL,
                                     .tangleA       = COMP_SUM_PARITY_PAR_UNINIT,
                                     .tangleB       = COMP_SUM_PARITY_PAR_ZERO,
                                     .op            = COMP_SUM_PARITY_OP_VEE };

    uint8_t ret_val = comp_sum_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_SUM_PARITY_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_bad_param_B(void)
{
    comp_sum_parity_config_t cfg = { .storage_write = NULL,
                                     .write_key     = NULL,
                                     .tangleA       = COMP_SUM_PARITY_PAR_ZERO,
                                     .tangleB       = COMP_SUM_PARITY_PAR_UNINIT,
                                     .op            = COMP_SUM_PARITY_OP_VEE };

    uint8_t ret_val = comp_sum_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_SUM_PARITY_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_bad_param_OP(void)
{
    comp_sum_parity_config_t cfg = { .storage_write = NULL,
                                     .write_key     = NULL,
                                     .tangleA       = COMP_SUM_PARITY_PAR_ZERO,
                                     .tangleB       = COMP_SUM_PARITY_PAR_ZERO,
                                     .op            = COMP_SUM_PARITY_OP_UNINIT };

    uint8_t ret_val = comp_sum_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_SUM_PARITY_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_sum_parity_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_SUM_PARITY_CONFIG_IS_NULL),
        ret_val);
}
