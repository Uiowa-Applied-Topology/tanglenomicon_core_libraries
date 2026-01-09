/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_canonicity.h"
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
    note_wptt_t vert;
    comp_wptt_canonicity_config_t cfg = { NULL,
                                          NULL,
                                          COMP_WPTT_CANON_POS_UNINIT };

    uint8_t ret_val = comp_wptt_canonicity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_CANON_CONFIG_POS_ERROR),
        ret_val);

    cfg.positivity = COMP_WPTT_CANON_POS_POS;
    ret_val        = comp_wptt_canonicity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_CANON_CONFIG_TREE_ERROR),
        ret_val);

    cfg.wptt       = &vert;
    cfg.positivity = COMP_WPTT_CANON_POS_UNINIT;
    ret_val        = comp_wptt_canonicity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_CANON_CONFIG_POS_ERROR),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_wptt_canonicity_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_CANON_CONFIG_IS_NULL),
        ret_val);
}
