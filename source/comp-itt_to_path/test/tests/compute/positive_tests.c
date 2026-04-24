/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "computation_defs.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_itt_to_path.h"
#include "unity.h"
#include <time.h>
#include "../../utils/utils.h"

static void test_compute_config_write(void);
static void test_compute_config_nowrite(void);


#define UTIL_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM * 1000u)
static test_holder_t *active_test = NULL;

/**
 * \brief Positive computation test cases
 */
void test_compute_positive(void)
{
    for (test_holder_t **test = compute_valid_set; NULL != *test; test++)
    {
        active_test = *test;
        RUN_TEST(test_compute_config_write);
        RUN_TEST(test_compute_config_nowrite);
    }
}

static void test_compute_config_write(void)
{
    uint8_t ret_val = comp_itt_to_path_config(&active_test->cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_itt_to_path_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(active_test->pl_path_string,
                                     test_stub_read_success_msg(active_test->itt_string,
                                                                "pl_path"),
                                     active_test->itt_string);
}

static void test_compute_config_nowrite(void)
{
    comp_itt_to_path_config_t cfg = { NULL,
                                      active_test->cfg.itt,
                                      active_test->cfg.out_path };
    uint8_t ret_val = comp_itt_to_path_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_itt_to_path_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
}
