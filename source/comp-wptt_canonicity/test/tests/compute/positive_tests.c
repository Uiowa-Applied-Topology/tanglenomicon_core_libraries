/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "stdlib.h"
#include "test_storage_stubs.h"
#include "comp_wptt_canonicity.h"
#include "unity.h"
#include "../../utils/data.h"

static void test_compute_config_write();
static void test_compute_config_nowrite();

static void test_compute_stick_alternating();
static void test_compute_stick_one_end();
static void test_compute_stick_non_zero();
static void test_compute_positivity();
static void test_compute_weight();

static storage_write_funptr_t write_g;
static note_wptt_t *          notes_g;
static char *strs_g;
static comp_wptt_cononicity_positivity_e pos_g;
static char *res_g;

static void test_func_compute()
{
    char buffer[1024] = { '\0' };
    comp_wptt_canonicity_config_t cfg = { write_g,
                                          notes_g,
                                          pos_g };
    uint8_t ret_val = comp_wptt_canonicity_config(&cfg);

    snprintf(buffer, sizeof(buffer), "Error in test: %s", strs_g);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_canonicity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS,
                                    "Error in computation.");
    if (NULL != write_g)
    {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(res_g,
                                         test_stub_read_success_msg(strs_g,
                                                                    "is_canon"),
                                         buffer);
    }
}

/*!
 * @brief Positive computation test cases
 */
void test_compute_positive(void)
{
    test_compute_config_write();
    test_compute_config_nowrite();
    test_compute_stick_alternating();
    test_compute_stick_non_zero();
    test_compute_positivity();
    test_compute_stick_one_end();
    test_compute_weight();
}

static void test_compute_config_write()
{
    note_wptt_t *notes[] = { &ib3_3b,
                             &ib3_0b,
                             &xpb3_3b3b3_3bp,
                             &xppb3_3b3b3_3bpp,
                             &ipppb3_3b3b3_3bp3pm3p,
                             &ib3b,
                             &ib0b,
                             &ib0_0b,
                             &ib2b,
                             &ibm2b,
                             &ib1b,
                             &ibm1b };
    char *       notes_str[] = { "i[3 3]",
                                 "i[3 0]",
                                 "x([3 3]3[3 3])",
                                 "x(([3 3]3[3 3]))",
                                 "i((([3 3]3[3 3])3)-3)",
                                 "i[-3]",
                                 "i[0]",
                                 "i[0 0]",
                                 "i[2]",
                                 "i[-2]",
                                 "i[1]",
                                 "i[-1]" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };

    size_t i;

    for (i = 0; i < 12; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "true";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_config_nowrite()
{
    note_wptt_t *notes[] = { &ib3_3b,
                             &ib3_0b,
                             &xpb3_3b3b3_3bp,
                             &xppb3_3b3b3_3bpp,
                             &ipppb3_3b3b3_3bp3pm3p,
                             &ib3b,
                             &ib0b,
                             &ib0_0b,
                             &ib2b,
                             &ibm2b,
                             &ib1b,
                             &ibm1b };
    char *       notes_str[] = { "i[3 3]",
                                 "i[3 0]",
                                 "x([3 3]3[3 3])",
                                 "x(([3 3]3[3 3]))",
                                 "i((([3 3]3[3 3])3)-3)",
                                 "i[3]",
                                 "i[0]",
                                 "i[0 0]",
                                 "i[2]",
                                 "i[-2]",
                                 "i[1]",
                                 "i[-1]" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };

    size_t i;

    for (i = 0; i < 12; i++)
    {
        write_g = NULL;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "true";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_stick_alternating()
{
    note_wptt_t *notes[] = { &ib3_m3b,
                             &ipppb3_m3b3b3_3bp3pm3p,
                             &ipppb3_3b3b3_3bp3p3p,
                             &ippb3_3b3b3_3bp3pppb3_3b3b3_3bp3p3pp };
    char *       notes_str[] = { "i[3 -3]",
                                 "i((([3 -3]3[3 3])3)-3)",
                                 "i((([3 3]3[3 3])3)3)",
                                 "i(([3 3]3[3 3])3((([3 3]3[3 3])3)3))" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };

    size_t i;

    for (i = 0; i < 4; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "false";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_stick_one_end()
{
    note_wptt_t *notes[] = { &ib1_3b,
                             &ibm1_m3b,
                             &ipb3_3bb3_3bppb3_3b3b3_3bp1pp,
                             &ipb3_3bb3_3bppb3_3b3b3_3bpm1pp,
                             &ipb3_3bb3_3bb1bp,
                             &ipb3_3bb3_3bbm1bp,
                             &ippppb3_3b3b3_3bp1pm3pb3_3bp,
                             &ippppb3_3b3b3_3bpm1p3pb3_3bp,
                             &ippppb3_3b3b3_3bp3pm1pb3_3bp,
                             &ippppb3_3b3b3_3bpm3p1pb3_3bp };
    char *       notes_str[] = { "i[-1 -3]",
                                 "i[1 3]",
                                 "i([3 3][3 3](([3 3]3[3 3])1))",
                                 "i([3 3][3 3](([3 3]3[3 3])-1))",
                                 "i([3 3][3 3][1])",
                                 "i([3 3][3 3][-1])",
                                 "i(((([3 3]3[3 3])1)-3)[3 3])",
                                 "i(((([3 3]3[3 3])-1)3)[3 3])",
                                 "i(((([3 3]3[3 3])3)-1)[3 3])",
                                 "i(((([3 3]3[3 3])-3)1)[3 3])" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };

    size_t i;

    for (i = 0; i < 10; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "false";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_stick_non_zero()
{
    note_wptt_t *notes[] = { &ib3_0_3b,
                             &ipb3_3bb3_3bb0bp,
                             &ipppb3_3b3b3_3bp0pb3_3bp,
                             &ippppb3_3b3b3_3bp3p0p3p,
                             &ippppb3_3b3b3_3bp0p3p3p };
    char *       notes_str[] = { "i[-3 0 3]",
                                 "i([3 3][3 3][0])",
                                 "i((([3 3]3[3 3]))[3 3])",
                                 "i(((([3 3]3[3 3])3))3)",
                                 "i(((([3 3]3[3 3]))3)3)" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };
    size_t i;

    for (i = 0; i < 5; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "false";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_positivity()
{
    note_wptt_t *notes[] = { &ipbm2bb3bp,
                             &ipb3_3bppb3_3b3b3_3bpm2pp,
                             &ipb2bb3bp,
                             &ipb3_3bppb3_3b3b3_3bp2pp };
    char *       notes_str[] = { "i([-2][3])",
                                 "i([3 3](([3 3]3[3 3])-2))",
                                 "i([2][3])",
                                 "i([3 3](([3 3]3[3 3])2))" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_NEG,
                                                COMP_WPTT_CANON_POS_NEG, };
    size_t i;

    for (i = 0; i < 4; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "false";

        RUN_TEST(test_func_compute);
    }
}

static void test_compute_weight()
{
    note_wptt_t *notes[] = { &ip3b3b3p,
                             &ipb3bp3b3b3pp,
                             &ip3b3b3b3bp };
    char *       notes_str[] = { "i(3[-3]3)",
                                 "i([-3](3[-3]3))",
                                 "i(3[-3]3[-3])" };
    comp_wptt_cononicity_positivity_e pos[] = { COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS,
                                                COMP_WPTT_CANON_POS_POS, };
    size_t i;

    for (i = 0; i < 3; i++)
    {
        write_g = &test_stub_write_success;
        notes_g = notes[i];
        strs_g  = notes_str[i];
        pos_g   = pos[i];
        res_g   = "false";

        RUN_TEST(test_func_compute);
    }
}
