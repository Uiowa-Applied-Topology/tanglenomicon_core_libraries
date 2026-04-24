/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_vertex_parity.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "stdbool.h"
#include "unity.h"
#include "../../utils/utils.h"

void test_results_positive(void)
{
    for (test_holder_t *test = compute_valid_set; test->wptt_string; test++)
    {
        uint8_t ret_val = comp_wptt_vertex_parity_config(&test->cfg);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
        ret_val = comp_wptt_vertex_parity_compute();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");

        const comp_wptt_vertex_parity_result_t *rest = comp_wptt_vertex_parity_result();
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                        "Error in computation.");
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(test->count, rest->component_count, "Error in count.");
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(test->par_e, rest->parity, "Error in parity.");
    }
}
