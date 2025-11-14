/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_ringshift.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "comp_rlitt_ringshift.h"
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
    comp_rlitt_ringshift_config_t cfg1 = { &test_stub_write_success, NULL };

    uint8_t ret_val = comp_rlitt_ringshift_config(&cfg1);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(
            COMP_DEFS_CONFIG_FAIL, COMP_RLITT_RINGSHIFT_CONFIG_WPTT),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_rlitt_ringshift_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(
            COMP_DEFS_CONFIG_FAIL, COMP_RLITT_RINGSHIFT_CONFIG_IS_NULL),
        ret_val);
}
