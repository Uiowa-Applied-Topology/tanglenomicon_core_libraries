/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_itt_to_path.h"
#include "negative_tests.h"
#include "computation_defs.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_config_negative_null_config(void);
static void test_config_negative_null_param(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_null_param);
}

static void test_config_negative_null_param(void)
{
    comp_itt_to_path_config_t cfg = {
        .storage_write = &test_stub_write_success,
        .itt           = compute_valid_set[0]->cfg.itt,
        .out_path      = compute_valid_set[0]->cfg.out_path
    };

    cfg.itt = NULL;
    uint8_t ret_val = comp_itt_to_path_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val,
                                    COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL,
                                                     COMP_ITT_TO_PATH_CONFIG_PARAM),
                                    "Error in config.");

    cfg.itt      = compute_valid_set[0]->cfg.itt;
    cfg.out_path = NULL;
    ret_val      = comp_itt_to_path_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val,
                                    COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL,
                                                     COMP_ITT_TO_PATH_CONFIG_PARAM),
                                    "Error in config.");
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = comp_itt_to_path_config(NULL);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val,
                                    COMP_STATUS_BLDR(COMP_DEFS_CONFIG_FAIL,
                                                     COMP_ITT_TO_PATH_CONFIG_IS_NULL),
                                    "Error in config.");
}
