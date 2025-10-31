/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_vertex_canonicity.h"
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
    note_wptt_node_t vert;
    comp_wptt_vert_canon_config_t cfg = { NULL,
                                          NULL,
                                          &vert,
                                          NULL,
                                          COMP_WPTT_VERT_CANON_POS_UNINIT };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_CANON_CONFIG_PARAM),
        ret_val);

    cfg.vertex     = NULL;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_CANON_CONFIG_PARAM),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_wptt_vert_canon_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL, COMP_WPTT_VERT_CANON_CONFIG_IS_NULL),
        ret_val);
}
