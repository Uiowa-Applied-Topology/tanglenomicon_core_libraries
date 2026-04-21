/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_i2pp_buf_size.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "stdbool.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_results_runner(void);

static test_holder_t *active_test = NULL;

void test_results_positive(void)
{
    for (test_holder_t *test = compute_valid_set; test->wptt_string; test++)
    {
        active_test = test;
        RUN_TEST(test_results_runner);
    }
}

void test_results_runner(void)
{
    uint8_t ret_val = comp_i2pp_buf_size_config(&active_test->cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_i2pp_buf_size_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");

    const comp_i2pp_buf_size_result_t *rest = comp_i2pp_buf_size_result();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(active_test->size, rest->buff_size, "Error in count.");
}
