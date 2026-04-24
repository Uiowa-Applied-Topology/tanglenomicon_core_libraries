/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_wptt_vertex_parity.h"
#include "unity.h"
#include "../../utils/utils.h"

static void test_compute_config_write();
static void test_compute_config_nowrite();

/**
 * \brief Positive computation test cases
 */
void test_compute_positive(void)
{
    RUN_TEST(test_compute_config_write);
    RUN_TEST(test_compute_config_nowrite);
}

static void test_compute_config_write()
{
    for (test_holder_t *test = compute_valid_set; test->wptt_string; test++)
    {
        uint8_t ret_val = comp_wptt_vertex_parity_config(&test->cfg);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
        ret_val = comp_wptt_vertex_parity_compute();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(test->parity,
                                         test_stub_read_success_msg(test->wptt_string,
                                                                    "parity"),
                                         "Error in output");
        char local_str[10] = { '\0' };
        sprintf(local_str, "%u", test->count);
        TEST_ASSERT_EQUAL_STRING_MESSAGE(local_str,
                                         test_stub_read_success_msg(test->wptt_string,
                                                                    "parity_components"),
                                         "Error in output");
    }
}

static void test_compute_config_nowrite()
{
    for (test_holder_t *test = compute_valid_set; test->wptt_string; test++)
    {
        comp_wptt_vertex_parity_config_t cfg = { NULL, test->cfg.wptt, test->cfg.vertex };
        uint8_t ret_val = comp_wptt_vertex_parity_config(&cfg);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
        ret_val = comp_wptt_vertex_parity_compute();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");
    }
}
