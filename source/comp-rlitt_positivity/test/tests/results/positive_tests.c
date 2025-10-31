/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_positivity.h"
#include "positive_tests.h"
#include "tang_defs.h"
#include "../../utils/data.h"
#include "test_storage_stubs.h"
#include "unity.h"

void test_results_positive(void)
{
    const note_wptt_t plus    = { &pb2bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t minus   = { &pbm2bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t undef   = { &pb2bbm2bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t neutral = { &pb3bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };

    const comp_rlitt_positivity_result_t *results = NULL;

    comp_rlitt_positivity_config_t cfg = { &test_stub_write_success, &plus };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_positivity_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL(COMP_RLITT_POSITIVITY_FLVR_POS, results->positivity);

    cfg.wptt = &minus;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_positivity_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL(COMP_RLITT_POSITIVITY_FLVR_NEG, results->positivity);

    cfg.wptt = &undef;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_positivity_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL(COMP_RLITT_POSITIVITY_FLVR_UND, results->positivity);

    cfg.wptt = &neutral;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_positivity_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL(COMP_RLITT_POSITIVITY_FLVR_NEU, results->positivity);
}
