/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_itt_to_path.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_results_negative_result(void);

void test_results_negative(void)
{
    RUN_TEST(test_results_negative_result);
}

static void test_results_negative_result(void)
{
    comp_itt_to_path_config_t test = compute_valid_set[0]->cfg;
    uint8_t ret_val = comp_itt_to_path_config(&test);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");

    const comp_itt_to_path_result_t *rest = comp_itt_to_path_result();
    TEST_ASSERT_NULL(rest);
}
