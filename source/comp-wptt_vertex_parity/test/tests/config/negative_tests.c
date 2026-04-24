/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_vertex_parity.h"
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
    comp_wptt_vertex_parity_config_t cfg = { NULL,
                                             NULL,
                                             NULL, };

    uint8_t ret_val = comp_wptt_vertex_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_PARITY_CONFIG_PARAM),
        ret_val);

    cfg.vertex = NULL;
    ret_val    = comp_wptt_vertex_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_PARITY_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_wptt_vertex_parity_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_PARITY_CONFIG_IS_NULL),
        ret_val);
}
