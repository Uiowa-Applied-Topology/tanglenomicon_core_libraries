/* */
/* Created by joe starr on 12/29/25. */
/* */
#include "comp_rlitt_pure_vignette.h"
#include "positive_tests.h"
#include "tang_defs.h"
#include "../../utils/data.h"
#include "test_storage_stubs.h"
#include "unity.h"

void test_results_positive(void)
{
    const comp_rlitt_pure_vignette_result_t *results;
    note_wptt_t tree = {
        &pppb3bm3p3pm3p,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    comp_rlitt_pure_vignette_config_t cfg = { &test_stub_write_success, &tree };
    uint8_t ret_val = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL_STRING("i((([])))", results->result);

    tree.root = &pppb3bb3bpm3p3p;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL_STRING("i((([][])))", results->result);

    tree.root = &pb3bb3b3p;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL_STRING("i([][])", results->result);

    tree.root = &ppb3bb3b3ppb3bb3b3ppb3bb3b3pp;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL_STRING("i(([][])([][])([][]))", results->result);

    tree.root = &b3b;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    results = comp_rlitt_pure_vignette_result();
    TEST_ASSERT_NOT_NULL(results);
    TEST_ASSERT_EQUAL_STRING("i[]", results->result);
}
