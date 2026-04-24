/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_i2pp_buf_size.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_compute_config_write(void);
static void test_compute_config_nowrite(void);

static test_holder_t *active_test = NULL;

/**
 * \brief Positive computation test cases
 */
void test_compute_positive(void)
{
    for (test_holder_t *test = compute_valid_set; test->wptt_string; test++)
    {
        active_test = test;
        RUN_TEST(test_compute_config_write);
        RUN_TEST(test_compute_config_nowrite);
    }
}

static void test_compute_config_write(void)
{
    uint8_t ret_val = comp_i2pp_buf_size_config(&active_test->cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_i2pp_buf_size_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    char local_str[30] = { '\0' };
    sprintf(local_str, "%llu", (long long unsigned int)active_test->size);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(local_str,
                                     test_stub_read_success_msg(active_test->wptt_string,
                                                                "buffer_size"),
                                     active_test->wptt_string);
}

static void test_compute_config_nowrite(void)
{
    comp_i2pp_buf_size_config_t cfg = { NULL, active_test->cfg.itt };
    uint8_t ret_val = comp_i2pp_buf_size_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_i2pp_buf_size_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
}
