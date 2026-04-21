/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_i2pp_buf_size.h"
#include "negative_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
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
    comp_i2pp_buf_size_config_t cfg = { .storage_write = NULL,
                                        .itt           = NULL };

    uint8_t ret_val = comp_i2pp_buf_size_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_W2PP_BUF_SIZE_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_i2pp_buf_size_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_W2PP_BUF_SIZE_CONFIG_IS_NULL),
        ret_val);
}
