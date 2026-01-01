/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_pure_vignette.h"
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "../../utils/data.h"
#include "unity.h"



void test_compute_positive(void)
{
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
    TEST_ASSERT_EQUAL_STRING_MESSAGE("i((([])))",
                                     test_stub_read_success_msg("i[-3 -3 -3 -3]",
                                                                "pure_vignette"),
                                     "Error in output");

    tree.root = &pppb3bb3bpm3p3p;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("i((([][])))",
                                     test_stub_read_success_msg("i((([3][3])-3)3)",
                                                                "pure_vignette"),
                                     "Error in output");

    tree.root = &pb3bb3b3p;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("i([][])",
                                     test_stub_read_success_msg("i([3][3]3)",
                                                                "pure_vignette"),
                                     "Error in output");

    tree.root = &ppb3bb3b3ppb3bb3b3ppb3bb3b3pp;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("i(([][])([][])([][]))",
                                     test_stub_read_success_msg("i(([3][3]3)([3][3]3)([3][3]3))",
                                                                "pure_vignette"),
                                     "Error in output");
    tree.root = &b3b;
    cfg.wptt  = &tree;
    ret_val   = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_pure_vignette_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("i[]",
                                     test_stub_read_success_msg("i[3]",
                                                                "pure_vignette"),
                                     "Error in output");
}
