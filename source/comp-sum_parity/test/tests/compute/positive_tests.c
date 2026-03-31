/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "comp_sum_parity.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_compute_config_write(void);
static void test_compute_config_nowrite(void);

/**
 * \brief Positive computation test cases
 */
void test_compute_positive(void)
{
    RUN_TEST(test_compute_config_write);
    RUN_TEST(test_compute_config_nowrite);
}

static void test_compute_config_write(void)
{
    for (test_holder_t *test = compute_valid_set; test->parity; test++)
    {
        uint8_t ret_val = comp_sum_parity_config(&test->cfg);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
        ret_val = comp_sum_parity_compute();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(test->parity,
                                         test_stub_read_success_msg(test->cfg.write_key,
                                                                    "sum parity"),
                                         test->cfg.write_key);
        char local_str[10] = { '\0' };
        sprintf(local_str, "%u", test->count);
        TEST_ASSERT_EQUAL_STRING_MESSAGE(local_str,
                                         test_stub_read_success_msg(test->cfg.write_key,
                                                                    "sum parity components"),
                                         test->cfg.write_key);
    }
}

static void test_compute_config_nowrite(void)
{
    for (test_holder_t *test = compute_valid_set; test->parity; test++)
    {
        comp_sum_parity_config_t cfg = { .storage_write = NULL,
                                         .write_key     = NULL,
                                         .tangleA       = test->cfg.tangleA,
                                         .tangleB       = test->cfg.tangleB,
                                         .op            = test->cfg.op };
        uint8_t ret_val = comp_sum_parity_config(&cfg);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
        ret_val = comp_sum_parity_compute();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");
    }
}
