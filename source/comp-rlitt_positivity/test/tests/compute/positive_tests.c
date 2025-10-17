/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_positivity.h"
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "../../utils/data.h"
#include "unity.h"

static void test_compute_at_root(void);
static void test_compute_as_leaf(void);
static void test_compute_internal(void);
static void test_compute_config_write(void);
static void test_compute_config_nowrite(void);


const static note_wptt_t root_neut_3 = { &b3b, NULL, NOTE_WPTT_V4_LABEL_I };

void test_compute_positive(void)
{
    RUN_TEST(test_compute_config_write);
    RUN_TEST(test_compute_config_nowrite);
    RUN_TEST(test_compute_at_root);
    RUN_TEST(test_compute_as_leaf);
    RUN_TEST(test_compute_internal);
}

static void test_compute_config_write()
{
    comp_rlitt_positivity_config_t cfg = { &test_stub_write_success, &root_neut_3 };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i[3]",
                                                                "rlitt_positivity"),
                                     "Error in output");
}

static void test_compute_config_nowrite()
{
    comp_rlitt_positivity_config_t cfg = { NULL, &root_neut_3 };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
}

static void test_compute_at_root(void)
{
    const note_wptt_t root_neut_2  = { &b2b, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t root_neut_m2 = { &bm2b, NULL, NOTE_WPTT_V4_LABEL_I };

    comp_rlitt_positivity_config_t cfg = { &test_stub_write_success, &root_neut_3 };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i[3]",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &root_neut_2;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i[2]",
                                                                "rlitt_positivity"),
                                     "Error in output");
    cfg.wptt = &root_neut_m2;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i[-2]",
                                                                "rlitt_positivity"),
                                     "Error in output");
}

static void test_compute_as_leaf(void)
{
    const note_wptt_t plus           = { &pb2bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t minus          = { &pbm2bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t undef          = { &pb2bbm2bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t neutral_1      = { &pb3bb3bp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t neutral_2      = { &ppb2bm3p3p, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t stick_mixedpm2 = { &pb2bb22bp, NULL, NOTE_WPTT_V4_LABEL_I };

    comp_rlitt_positivity_config_t cfg = { &test_stub_write_success, &plus };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("positive",
                                     test_stub_read_success_msg("i([2][3])",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &minus;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("negative",
                                     test_stub_read_success_msg("i([-2][3])",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &undef;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("undefined",
                                     test_stub_read_success_msg("i([2][-2])",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &neutral_1;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i([3][3])",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &neutral_2;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i[2 3 3]",
                                                                "rlitt_positivity"),
                                     "Error in output");
    cfg.wptt = &stick_mixedpm2;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("positive",
                                     test_stub_read_success_msg("i([2][-2 -2])",
                                                                "rlitt_positivity"),
                                     "Error in output");
}

static void test_compute_internal(void)
{
    const note_wptt_t plus    = { &pb3bppb3bb3bp2pp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t minus   = { &pb3bppb3bb3bpm2pp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t undef   = { &pppb3bb3bp2pppb3bb3bpm2pp, NULL, NOTE_WPTT_V4_LABEL_I };
    const note_wptt_t neutral = { &pb3bppb3bb3bp3pp, NULL, NOTE_WPTT_V4_LABEL_I };

    comp_rlitt_positivity_config_t cfg = { &test_stub_write_success, &plus };
    uint8_t ret_val = comp_rlitt_positivity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("positive",
                                     test_stub_read_success_msg("i([3](([3][3])2))",
                                                                "rlitt_positivity"),
                                     "Error in output");

    cfg.wptt = &minus;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("negative",
                                     test_stub_read_success_msg("i([3](([3][3])-2))",
                                                                "rlitt_positivity"),
                                     "Error in output");
    cfg.wptt = &undef;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("undefined",
                                     test_stub_read_success_msg("i((([3][3])2)(([3][3])-2))",
                                                                "rlitt_positivity"),
                                     "Error in output");
    cfg.wptt = &neutral;

    ret_val = comp_rlitt_positivity_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_rlitt_positivity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("neutral",
                                     test_stub_read_success_msg("i([3](([3][3])3))",
                                                                "rlitt_positivity"),
                                     "Error in output");
}
