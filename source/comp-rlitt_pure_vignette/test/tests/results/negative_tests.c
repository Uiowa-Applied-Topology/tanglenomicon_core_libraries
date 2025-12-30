/* */
/* Created by joe on 6/23/25. */
/* */
#include "bits/stdint-uintn.h"
#include "comp_rlitt_pure_vignette.h"
#include "negative_tests.h"
#include "computation_defs.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/data.h"

static void test_results_negative_result(void);

void test_results_negative(void)
{
    RUN_TEST(test_results_negative_result);
}

static void test_results_negative_result(void)
{
    const note_wptt_t plus                = { &b3b, NULL, NOTE_WPTT_V4_LABEL_I };
    uint8_t           ret_val             = COMP_DEFS_CONFIG_FAIL;
    comp_rlitt_pure_vignette_config_t cfg = { &test_stub_write_success, &plus };

    ret_val = comp_rlitt_pure_vignette_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    const comp_rlitt_pure_vignette_result_t *results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_EQUAL(NULL, results);
}
