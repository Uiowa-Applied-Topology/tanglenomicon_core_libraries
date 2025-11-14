/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_rlitt_ringshift.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "mut_rlitt_ringshift.h"
#include "unity.h"

static void test_config_negative_null_config(void);
static void test_config_negative_null_param(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_null_param);
}

static void test_config_negative_null_param(void)
{
    mut_rlitt_ringshift_config_t cfg1 = { NULL };

    uint8_t ret_val = mut_rlitt_ringshift_config(&cfg1);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_RLITT_RINGSHIFT_CONFIG_WPTT),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = mut_rlitt_ringshift_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_RLITT_RINGSHIFT_CONFIG_IS_NULL),
        ret_val);
}
