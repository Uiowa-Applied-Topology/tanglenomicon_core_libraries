/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "generator_rlitt.h"
#include "unity.h"
#include "../../utils/utils.h"


/**************************************    Parts    **********************************************/

static note_wptt_node_t ib2b = { {
                                     NULL
                                 },
                                 {
                                     2
                                 },
                                 0,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib0b = { {
                                     NULL
                                 },
                                 {
                                     0
                                 },
                                 0,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ibm2b = { {
                                      NULL
                                  },
                                  {
                                      -2
                                  },
                                  0,
                                  0,
                                  NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib2_0b = { {
                                       &ib2b
                                   },
                                   {
                                       0
                                   },
                                   1,
                                   0,
                                   NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ibm2_0b = { {
                                        &ibm2b
                                    },
                                    {
                                        0
                                    },
                                    1,
                                    0,
                                    NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ipb2bb2bp = { {
                                          &ib2b,
                                          &ib2b
                                      },
                                      {
                                          0
                                      },
                                      2,
                                      0,
                                      NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ippb2bb2bpp = { {
                                            &ipb2bb2bp
                                        },
                                        {
                                            0
                                        },
                                        1,
                                        0,
                                        NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ipbm2bm2bm1p = { {
                                             &ibm2b,
                                             &ibm2b
                                         },
                                         {
                                             0,
                                             0,
                                             -1
                                         },
                                         2,
                                         0,
                                         NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ipb2b2b1p = { {
                                          &ib2b,
                                          &ib2b
                                      },
                                      {
                                          0,
                                          0,
                                          1
                                      },
                                      2,
                                      0,
                                      NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib8b = { {
                                 },
                                 {
                                     8
                                 },
                                 0,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };

static note_wptt_node_t ipb8bb8bb8b9p = { {
                                              &ib8b,
                                              &ib8b,
                                              &ib8b
                                          },
                                          {
                                              0,
                                              0,
                                              0,
                                              9
                                          },
                                          3,
                                          0,
                                          NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ippb8bb8bb8b9p2p = { {
                                                 &ipb8bb8bb8b9p
                                             },
                                             {
                                                 0,
                                                 2
                                             },
                                             1,
                                             0,
                                             NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ippb8bb8bb8b9pm2p = { {
                                                  &ipb8bb8bb8b9p
                                              },
                                              {
                                                  0,
                                                  -2
                                              },
                                              1,
                                              0,
                                              NOTE_WPTT_ORDER_FORWARD };


static note_wptt_node_t ibm99b_root = { {
                                            NULL
                                        },
                                        {
                                            -99
                                        },
                                        0,
                                        0,
                                        NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib99_88b_root = { {
                                              &ibm99b_root
                                          },
                                          {
                                              0, 88
                                          },
                                          1,
                                          0,
                                          NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib99_88_77b_root = { {
                                                 &ib99_88b_root
                                             },
                                             {
                                                 0, 77
                                             },
                                             1,
                                             0,
                                             NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ipbm99bbm99bbm99bbm99bp_root = { {
                                                             &ibm99b_root,
                                                             &ibm99b_root,
                                                             &ibm99b_root,
                                                             &ibm99b_root,
                                                         },
                                                         {
                                                             0
                                                         },
                                                         4,
                                                         0,
                                                         NOTE_WPTT_ORDER_FORWARD };

/**************************************    Trees    **********************************************/
static note_wptt_node_t root_with_positve_ringsubtree = { {
                                                              &ib8b,
                                                              &ipb2b2b1p,
                                                          },
                                                          {
                                                              0,
                                                              0,
                                                              3
                                                          },
                                                          2,
                                                          0,
                                                          NOTE_WPTT_ORDER_FORWARD };

static note_wptt_t      tree_with_positve_ringsubtree = { &root_with_positve_ringsubtree,
                                                          NULL,
                                                          NOTE_WPTT_V4_LABEL_I, };
static note_wptt_node_t root_with_positive_internal_subtree = { {
                                                                    &ib8b,
                                                                    &ippb8bb8bb8b9p2p
                                                                },
                                                                {
                                                                    0,
                                                                    0,
                                                                    3
                                                                },
                                                                2,
                                                                0,
                                                                NOTE_WPTT_ORDER_FORWARD };
static note_wptt_t      tree_with_positive_internal_subtree =
{ &root_with_positive_internal_subtree,
  NULL,
  NOTE_WPTT_V4_LABEL_I, };
static note_wptt_t tree_is_a_positive_leaf = { &ib2b,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };

static note_wptt_node_t root_with_negative_ringsubtree = { {
                                                               &ipbm2bm2bm1p,
                                                               &ib8b,
                                                           },
                                                           {
                                                               0,
                                                               0,
                                                               3
                                                           },
                                                           2,
                                                           0,
                                                           NOTE_WPTT_ORDER_FORWARD };

static note_wptt_t      tree_with_negative_ringsubtree = { &root_with_negative_ringsubtree,
                                                           NULL,
                                                           NOTE_WPTT_V4_LABEL_I, };
static note_wptt_node_t root_with_negative_internal_subtree = { {
                                                                    &ib8b,
                                                                    &ippb8bb8bb8b9pm2p
                                                                },
                                                                {
                                                                    0,
                                                                    0,
                                                                    3
                                                                },
                                                                2,
                                                                0,
                                                                NOTE_WPTT_ORDER_FORWARD };
static note_wptt_t      tree_with_negative_internal_subtree =
{ &root_with_negative_internal_subtree,
  NULL,
  NOTE_WPTT_V4_LABEL_I, };
static note_wptt_t tree_is_a_negative_leaf = { &ibm2b,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };


static note_wptt_t tree_is_a_neutral_leaf = { &ibm99b_root,
                                              NULL,
                                              NOTE_WPTT_V4_LABEL_I, };
static note_wptt_t tree_is_a_neutral_leaf2 = { &ib8b,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };
static note_wptt_t tree_is_a_neutral_stellar = { &ipbm99bbm99bbm99bbm99bp_root,
                                                 NULL,
                                                 NOTE_WPTT_V4_LABEL_I, };

static note_wptt_t tree_is_a_neutral_stick = { &ib99_88_77b_root,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };
/**************************************************************************************************/

static void test_generate_write_pn(void);
static void test_generate_write_np(void);
static void test_generate_write_mn(void);
static void test_generate_write_nm(void);
static void test_generate_write_nn(void);
static void test_generate_write_22(void);
static void test_generate_write_222(void);
static void test_generate_write_212(void);
static void test_generate_write_211(void);
static void test_generate_write_210_2(void);
static void test_generate_write_221_0(void);

void test_generate_positive(void)
{
    RUN_TEST(test_generate_write_pn);
    RUN_TEST(test_generate_write_np);
    RUN_TEST(test_generate_write_mn);
    RUN_TEST(test_generate_write_nm);
    RUN_TEST(test_generate_write_nn);
    RUN_TEST(test_generate_write_22);
    RUN_TEST(test_generate_write_222);
    RUN_TEST(test_generate_write_212);
    RUN_TEST(test_generate_write_211);
    RUN_TEST(test_generate_write_210_2);
    RUN_TEST(test_generate_write_221_0);
}

static void test_generate_write_pn(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_with_positive_internal_subtree,
        [1] = &tree_is_a_positive_leaf,
        [2] = &tree_with_positve_ringsubtree
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_leaf,
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        rlist,
        3,
        slist,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i([8]([2][2]1)3)",
                             test_stub_read_success("i([8][-99]([2][2]1)3)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[-99]", test_stub_read_success("i([8][-99]([2][2]1)3)", "scion"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i([8][-99]([2][2]1)3)", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[2]", test_stub_read_success("i[99 2]", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[-99]", test_stub_read_success("i[99 2]", "scion"));
    TEST_ASSERT_EQUAL_STRING("neutral", test_stub_read_success("i[99 2]", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i([8](([8][8][8]9)2)3)",
                             test_stub_read_success("i([8](([8][8][8]9)2)[-99]3)",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i([8](([8][8][8]9)2)[-99]3)",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i([8](([8][8][8]9)2)[-99]3)",
                                                    "positivity"));
}

static void test_generate_write_np(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_with_positive_internal_subtree,
        [1] = &tree_is_a_positive_leaf,
        [2] = &tree_with_positve_ringsubtree
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_leaf
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        slist,
        1,
        rlist,
        3,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i([8]([2][2]1)3)",
                             test_stub_read_success("i(([8]([2][2]1)3)-99)", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i(([8]([2][2]1)3)-99)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i(([8]([2][2]1)3)-99)", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[2]", test_stub_read_success("i[-2 -99]", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]", test_stub_read_success("i[-2 -99]", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("neutral", test_stub_read_success("i[-2 -99]", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i([8](([8][8][8]9)2)3)",
                             test_stub_read_success("i(([8](([8][8][8]9)2)3)-99)",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i(([8](([8][8][8]9)2)3)-99)",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i(([8](([8][8][8]9)2)3)-99)",
                                                    "positivity"));
}

static void test_generate_write_mn(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_with_negative_internal_subtree,
        [1] = &tree_is_a_negative_leaf,
        [2] = &tree_with_negative_ringsubtree
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_leaf2,
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        rlist,
        3,
        slist,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i(([-2][-2]-1)[8]3)",
                             test_stub_read_success("i([8][8]([-2][-2]-1)3)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[8]", test_stub_read_success("i([8][8]([-2][-2]-1)3)", "scion"));
    TEST_ASSERT_EQUAL_STRING("negative",
                             test_stub_read_success("i([8][8]([-2][-2]-1)3)", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[-2]", test_stub_read_success("i[-8 -2]", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[8]", test_stub_read_success("i[-8 -2]", "scion"));
    TEST_ASSERT_EQUAL_STRING("neutral", test_stub_read_success("i[-8 -2]", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i([8](([8][8][8]9)-2)3)",
                             test_stub_read_success("i([8](([8][8][8]9)-2)[8]3)",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING("i[8]",
                             test_stub_read_success("i([8](([8][8][8]9)-2)[8]3)",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING("negative",
                             test_stub_read_success("i([8](([8][8][8]9)-2)[8]3)",
                                                    "positivity"));
}

static void test_generate_write_nm(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_with_negative_internal_subtree,
        [1] = &tree_is_a_neutral_leaf2,
        [2] = &tree_with_negative_ringsubtree
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_leaf
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        slist,
        1,
        rlist,
        3,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i(([-2][-2]-1)[8]3)",
                             test_stub_read_success("i(([8]([-2][-2]-1)3)-99)", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i(([8]([-2][-2]-1)3)-99)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("negative",
                             test_stub_read_success("i(([8]([-2][-2]-1)3)-99)", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[8]", test_stub_read_success("i[-8 -99]", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]", test_stub_read_success("i[-8 -99]", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("neutral", test_stub_read_success("i[-8 -99]", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i([8](([8][8][8]9)-2)3)",
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)-99)",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)-99)",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING("negative",
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)-99)",
                                                    "positivity"));

    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)99)",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)99)",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([8](([8][8][8]9)-2)3)99)",
                                                    "positivity"));
}

static void test_generate_write_nn(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_is_a_neutral_leaf2,
        [1] = &tree_is_a_neutral_stick,
        [2] = &tree_is_a_neutral_stellar,
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_leaf
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        rlist,
        3,
        slist,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i[99 8]", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[8]",
                             test_stub_read_success("i[99 8]", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("neutral",
                             test_stub_read_success("i[99 8]", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[-99]", test_stub_read_success("i([99 88][-99]77)", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-99 -88 77]",
                             test_stub_read_success("i([99 88][-99]77)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("neutral", test_stub_read_success("i([99 88][-99]77)", "positivity"));

    TEST_ASSERT_EQUAL_STRING("i[-99]",
                             test_stub_read_success("i([-99][-99][-99][-99][-99])",
                                                    "scion"));
    TEST_ASSERT_EQUAL_STRING("i([-99][-99][-99][-99])",
                             test_stub_read_success("i([-99][-99][-99][-99][-99])",
                                                    "rootstock"));
    TEST_ASSERT_EQUAL_STRING("neutral",
                             test_stub_read_success("i([-99][-99][-99][-99][-99])",
                                                    "positivity"));
}

static void test_generate_write_22(void)
{
    static note_wptt_t tree_is2 = { &ib2_0b,
                                    NULL,
                                    NOTE_WPTT_V4_LABEL_I, };
    static note_wptt_t tree_ism2 = { &ibm2_0b,
                                     NULL,
                                     NOTE_WPTT_V4_LABEL_I, };
    static note_wptt_t tree_2 = { &ib2b,
                                  NULL,
                                  NOTE_WPTT_V4_LABEL_I, };
    static note_wptt_t tree_m2 = { &ibm2b,
                                   NULL,
                                   NOTE_WPTT_V4_LABEL_I, };
    const note_wptt_t *rlist[] = {
        [0] = &tree_is2,
        [1] = &tree_ism2
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_2,
        [1] = &tree_m2
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        rlist,
        2,
        slist,
        2,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i[2]",
                             test_stub_read_success("i([2][2])", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-2 0]",
                             test_stub_read_success("i([2][2])", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i([2][2])", "positivity"));
    TEST_ASSERT_EQUAL_STRING("true",
                             test_stub_read_success("i([2][2])", "is_good"));

    TEST_ASSERT_EQUAL_STRING("i[-2]",
                             test_stub_read_success("i([-2][-2])", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[2 0]",
                             test_stub_read_success("i([-2][-2])", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("negative",
                             test_stub_read_success("i([-2][-2])", "positivity"));
    TEST_ASSERT_EQUAL_STRING("true",
                             test_stub_read_success("i([-2][-2])", "is_good"));
}

static void test_generate_write_222(void)
{
    static note_wptt_t tree_is2 = { &ipb2bb2bp,
                                    NULL,
                                    NOTE_WPTT_V4_LABEL_I, };
    static note_wptt_t tree_0 = { &ib0b,
                                  NULL,
                                  NOTE_WPTT_V4_LABEL_I, };
    const note_wptt_t *rlist[] = {
        [0] = &tree_0
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is2
    };

    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        rlist,
        1,
        slist,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i([2][2])",
                             test_stub_read_success("i(([2][2]))", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[0]",
                             test_stub_read_success("i(([2][2]))", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i(([2][2]))", "positivity"));
    TEST_ASSERT_EQUAL_STRING("false",
                             test_stub_read_success("i(([2][2]))", "is_good"));
}

static void test_generate_write_212(void)
{
    size_t       stick_n_count = 1;
    char *       stick_n[]     = { "i[2]" };
    note_wptt_t *stick_n_note[1];

    load_note(stick_n_note, stick_n, stick_n_count);

    size_t       integral_n_count = 1;
    char *       integral_n[]     = { "i[-3 -2 -1]" };
    note_wptt_t *integral_n_note[1];
    load_note(integral_n_note, integral_n, integral_n_count);


    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        (const note_wptt_t **)integral_n_note,
        1,
        (const note_wptt_t **)stick_n_note,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING("i[2]",
                             test_stub_read_success("i([3 2][2]-1)", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-3 -2 -1]",
                             test_stub_read_success("i([3 2][2]-1)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i([3 2][2]-1)", "positivity"));
    TEST_ASSERT_EQUAL_STRING("true",
                             test_stub_read_success("i([3 2][2]-1)", "is_good"));

    TEST_ASSERT_EQUAL_STRING("i[2]",
                             test_stub_read_success("i([3 2][2]1)", "scion"));
    TEST_ASSERT_EQUAL_STRING("i[-3 -2 -1]",
                             test_stub_read_success("i([3 2][2]1)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING("positive",
                             test_stub_read_success("i([3 2][2]1)", "positivity"));
    TEST_ASSERT_EQUAL_STRING("true",
                             test_stub_read_success("i([3 2][2]1)", "is_good"));
}

static void test_generate_write_211(void)
{
    size_t       stick_n_count = 1;
    char *       stick_n[]     = { "i(([2][2])-1)" };
    note_wptt_t *stick_n_note[1];

    load_note(stick_n_note, stick_n, stick_n_count);

    size_t       integral_n_count = 1;
    char *       integral_n[]     = { "i[1]" };
    note_wptt_t *integral_n_note[1];
    load_note(integral_n_note, integral_n, integral_n_count);


    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        (const note_wptt_t **)integral_n_note,
        1,
        (const note_wptt_t **)stick_n_note,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "scion"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "positivity"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "is_good"));

    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "scion"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "rootstock"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "positivity"));
    TEST_ASSERT_EQUAL_STRING(NULL,
                             test_stub_read_success("i(([2][2]-1)1)", "is_good"));
}

static void test_generate_write_210_2(void)
{
    size_t       integral_n_count = 1;
    char *       integral_n[]     = { "i[2 1 0]" };
    note_wptt_t *integral_n_note[1];

    load_note(integral_n_note, integral_n, integral_n_count);

    size_t       stick_n_count = 1;
    char *       stick_n[]     = { "i[-2]" };
    note_wptt_t *stick_n_note[1];
    load_note(stick_n_note, stick_n, stick_n_count);


    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        (const note_wptt_t **)integral_n_note,
        1,
        (const note_wptt_t **)stick_n_note,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i([-2 -1][-2])", "scion"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i([-2 -1][-2])", "rootstock"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i([-2 -1][-2])", "positivity"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i([-2 -1][-2])", "is_good"));
}

static void test_generate_write_221_0(void)
{
    size_t       rootstock_n_count = 1;
    char *       rootstock_n[]     = { "i[0]" };
    note_wptt_t *rootstock_n_note[1];

    load_note(rootstock_n_note, rootstock_n, rootstock_n_count);

    size_t       scion_n_count = 1;
    char *       scion_n[]     = { "i(([-2][-2])1)" };
    note_wptt_t *scion_n_note[1];
    load_note(scion_n_note, scion_n, scion_n_count);


    gen_rlitt_config_t cfg = {
        &test_stub_write_success,
        (const note_wptt_t **)rootstock_n_note,
        1,
        (const note_wptt_t **)scion_n_note,
        1,
    };
    uint8_t            ret_val = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i(([-2][-2]1))", "scion"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i(([-2][-2]1))", "rootstock"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i(([-2][-2]1))", "positivity"));
    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i(([-2][-2]1))", "is_good"));
}
