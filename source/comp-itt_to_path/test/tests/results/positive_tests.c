/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_itt_to_path.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "stdbool.h"
#include "unity.h"
#include "../../utils/utils.h"

static test_holder_t *active_test = NULL;

static void test_result_valid(void);


void test_results_positive(void)
{
    for (test_holder_t **test = compute_valid_set; NULL != *test; test++)
    {
        active_test = *test;
        RUN_TEST(test_result_valid);
    }
}

static void test_result_valid(void)
{
    uint8_t ret_val = comp_itt_to_path_config(&active_test->cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_itt_to_path_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    const comp_itt_to_path_result_t *res = comp_itt_to_path_result();
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_TRUE_MESSAGE(plpath_match(res->path, &active_test->path), active_test->itt_string);
}
