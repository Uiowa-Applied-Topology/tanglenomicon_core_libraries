/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "comp_wptt_vertex_canonicity.h"
#include "unity.h"

static void test_compute_config_write();
static void test_compute_config_nowrite();

static void test_compute_stick_alternating();
static void test_compute_stick_one_end();
static void test_compute_stick_non_zero();
static void test_compute_positivity();
static void test_compute_weight();

/* clang-format off */
static note_wptt_node_t leaf3 = {{NULL},{3},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pb3bb3bp= {{&leaf3,&leaf3},{0,0,0},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppb3bb3bpm2p= {{&pb3bb3bp},{0,-2},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppb3bb3bpm2p1p= {{&ppb3bb3bpm2p},{0,1},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t primary_canon_wptt = {&pppb3bb3bpm2p1p,NULL,NOTE_WPTT_V4_LABEL_I};
/* i((([3][3])-2)1) */

static note_wptt_node_t leafm3 = {{NULL},{-3},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pbm3bbm3bp= {{&leafm3,&leafm3},{0,0,0},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppbm3bbm3bp2p= {{&pbm3bbm3bp},{0,2},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppbm3bbm3bp2pm1p= {{&ppbm3bbm3bp2p},{0,-1},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t primary_canon_mwptt = {&pppbm3bbm3bp2pm1p,NULL,NOTE_WPTT_V4_LABEL_I};

/************************************************************************************************/
/****** Weight Condition ************************************************************************/
/************************************************************************************************/
/****** Canon ***********************************************************************************/
/************************************************************************************************/
/* primary_canon_wptt */
/************************************************************************************************/
/****** Non-Canon *******************************************************************************/
/************************************************************************************************/
static note_wptt_node_t p1b3bb3b1p = {{&leaf3,&leaf3},{1,0,1},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t weight_double_weight_root = {&p1b3bb3b1p,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_node_t pp1b3bb3b1p3p = {{&p1b3bb3b1p},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t weight_double_weight_nonroot = {&pp1b3bb3b1p3p,NULL,NOTE_WPTT_V4_LABEL_I};



/************************************************************************************************/
/****** Stick Condition *************************************************************************/
/************************************************************************************************/
/*********** Zero *******************************************************************************/
/************************************************************************************************/
/****************** Canon ***********************************************************************/
/************************************************************************************************/
/* primary_canon_wptt */

static note_wptt_node_t b0b = {{NULL},{0,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pb3bb0bp= {{&leaf3,&b0b},{0,0,0},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pb0bp = {{&b0b},{0,0},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t inf_tangle = {&pb0bp,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_t zero_tangle = {&b0b,NULL,NOTE_WPTT_V4_LABEL_I};

/************************************************************************************************/
/****************** Non-Canon *******************************************************************/
/************************************************************************************************/
static note_wptt_node_t pb0b3p = {{&b0b},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t stick_zero_leaf = {&pb0b3p,NULL,NOTE_WPTT_V4_LABEL_I};

static note_wptt_node_t pb3bb0_3bp = {{&leaf3,&pb0b3p },{0,0},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppb3bb3bpp = {{&pb3bb3bp},{0,0},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppb3bb0bpp = {{&pb3bb0bp},{0,0},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppb3bb3bpp3p = {{&ppb3bb3bpp },{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_t stick_zero_internal = {&pppb3bb3bpp3p,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_t stick_zero_leaf2 = {&pb3bb0bp,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_t stick_zero_leaf3 = {&pb3bb0_3bp ,NULL,NOTE_WPTT_V4_LABEL_I};

/*********** One  *******************************************************************************/
/************************************************************************************************/
/****************** Canon ***********************************************************************/
/************************************************************************************************/
/* primary_canon_wptt */
/************************************************************************************************/
/****************** Non-Canon *******************************************************************/
/************************************************************************************************/

static note_wptt_node_t b3b = {{NULL},{3,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t bm3b = {{NULL},{-3,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t bm1b = {{NULL},{-1,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t b1b = {{NULL},{1,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pb3bm3p = {{&b3b},{0,-3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pbm3b3p = {{&bm3b},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t ppb3bm3p1p = {{&pb3bm3p},{0,1},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppbm3b3pm1p = {{&pbm3b3p},{0,-1},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pppb3bm3p1pb3bp = {{&ppb3bm3p1p,&b3b},{0,0,3},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppbm3b3pm1pb3bp = {{&ppbm3b3pm1p,&b3b},{0,0,3},2,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pb1bm3p = {{&b1b},{0,-3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pbm1b3p = {{&bm1b},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t ppb3bb3bp1p = {{&pb3bb3bp},{0,1},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppb3bb3bpm1p = {{&pb3bb3bp},{0,-1},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pppb3bb3bp1pm3p = {{&ppb3bb3bp1p},{0,-3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppb3bb3bpm1p3p = {{&ppb3bb3bpm1p},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};


/*i[3 1]*/
static note_wptt_t stick_one_leaf_1 = {&pb1bm3p,NULL,NOTE_WPTT_V4_LABEL_I};
/*i([-1]3)*/
static note_wptt_t stick_one_leaf_m1 = {&pbm1b3p,NULL,NOTE_WPTT_V4_LABEL_I};

/*i((([3]-3)1)[3])*/
static note_wptt_t stick_one_internal_up_1 = {&pppb3bm3p1pb3bp,NULL,NOTE_WPTT_V4_LABEL_I};
/*i((([3]3)-1)[-3])*/
static note_wptt_t stick_one_internal_up_m1 = {&pppbm3b3pm1pb3bp,NULL,NOTE_WPTT_V4_LABEL_I};

/*i([1]3)*/
static note_wptt_t stick_one_internal_down_1 = {&pppb3bb3bp1pm3p,NULL,NOTE_WPTT_V4_LABEL_I};
/*i([1]3)*/
static note_wptt_t stick_one_internal_down_m1 = {&pppb3bb3bpm1p3p,NULL,NOTE_WPTT_V4_LABEL_I};



/*********** Alternating ************************************************************************/
/************************************************************************************************/
/****************** Canon ***********************************************************************/
/************************************************************************************************/
/* primary_canon_wptt */
/************************************************************************************************/
/****************** Non-Canon *******************************************************************/
/************************************************************************************************/


static note_wptt_node_t pb3b3p = {{&b3b},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pbm3bm3p = {{&bm3b},{0,-3},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t ppb3b3p3p = {{&pb3b3p},{0,3},1,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t ppbm3bm3pm3p = {{&pbm3bm3p},{0,-3},1,0,NOTE_WPTT_ORDER_FORWARD};

/* i(([3]3)3)*/
static note_wptt_t stick_alt_plus = {&ppb3b3p3p,NULL,NOTE_WPTT_V4_LABEL_I};
/* i(([-3]-3)-3)*/
static note_wptt_t stick_alt_minus = {&ppbm3bm3pm3p,NULL,NOTE_WPTT_V4_LABEL_I};

/************************************************************************************************/
/****** Positivity Condition ********************************************************************/
/************************************************************************************************/

static note_wptt_node_t b2b = {{NULL},{2,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t bm2b = {{NULL},{-2,0,0},0,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pb2bb3bp  = {{&b2b,&b3b},{0,0,0},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pbm2bb3bp  = {{&bm2b,&b3b},{0,0,0},2,0,NOTE_WPTT_ORDER_FORWARD};


static note_wptt_node_t ppb3bb3bp2p  = {{&pb3bb3bp},{0,2},1,0,NOTE_WPTT_ORDER_FORWARD};

static note_wptt_node_t pppb3bb3bp2pb3bp  = {{&ppb3bb3bp2p,&b3b},{0,0,3},2,0,NOTE_WPTT_ORDER_FORWARD};
static note_wptt_node_t pppb3bb3bpm2pb3bp  = {{&ppb3bb3bpm2p,&b3b},{0,0,3},2,0,NOTE_WPTT_ORDER_FORWARD};


/************************************************************************************************/
/*********** Plus *******************************************************************************/
/************************************************************************************************/
/****************** Canon ***********************************************************************/
/************************************************************************************************/
/* primary_canon_wptt */

static note_wptt_t pos_plus_canon_leaf = {&pb2bb3bp,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_t pos_plus_canon_internal = {&pppb3bb3bp2pb3bp,NULL,NOTE_WPTT_V4_LABEL_I};

/************************************************************************************************/
/****************** Non-Canon *******************************************************************/
/************************************************************************************************/

static note_wptt_t pos_plus_noncanon_leaf = {&pbm2bb3bp,NULL,NOTE_WPTT_V4_LABEL_I};
static note_wptt_t pos_plus_noncanon_internal = {&pppb3bb3bpm2pb3bp,NULL,NOTE_WPTT_V4_LABEL_I};

/* clang-format on */


/*!
 * @brief Positive computation test cases
 */
void test_compute_positive(void)
{
    RUN_TEST(test_compute_config_write);
    RUN_TEST(test_compute_config_nowrite);
    RUN_TEST(test_compute_stick_alternating);
    RUN_TEST(test_compute_stick_non_zero);
    RUN_TEST(test_compute_positivity);
    RUN_TEST(test_compute_stick_one_end);
    RUN_TEST(test_compute_weight);
}

static void test_compute_config_write()
{
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &primary_canon_wptt,
                                          primary_canon_wptt.root,
                                          NULL,
                                          false,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([3][3])-2)1)",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.parent     = &pppb3bb3bpm2p1p;
    cfg.vertex     = &ppb3bb3bpm2p;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([3][3])-2)1)",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt       = &primary_canon_mwptt;
    cfg.parent     = &pppbm3bbm3bp2pm1p;
    cfg.vertex     = &ppbm3bbm3bp2p;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([-3][-3])2)-1)",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.parent     = NULL;
    cfg.vertex     = primary_canon_mwptt.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([-3][-3])2)-1)",
                                                                "is_canon_vertex"),
                                     "Error in output");
}

static void test_compute_config_nowrite()
{
    comp_wptt_vert_canon_config_t cfg = { NULL,
                                          NULL,
                                          &ppb3bb3bpm2p,
                                          primary_canon_wptt.root,
                                          true,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_COMPUTE_SUCCESS);
}

static void test_compute_stick_alternating()
{
/*******************************************************************/
/* Near the root*/
/*******************************************************************/
/*  ++*/
/*******************************************************************/
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &stick_alt_plus,
                                          &pb3b3p,
                                          stick_alt_plus.root,
                                          true,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[3 -3 3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*  --*/
/*******************************************************************/

    cfg.wptt       = &stick_alt_minus;
    cfg.vertex     = &pbm3bm3p;
    cfg.parent     = stick_alt_minus.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[-3 3 -3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*Away from the root*/
/*******************************************************************/
/*  ++*/
/*******************************************************************/

    cfg.wptt           = &stick_alt_plus;
    cfg.vertex         = &b3b;
    cfg.parent         = &pb3b3p;
    cfg.parent_is_root = false;
    cfg.positivity     = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[3 -3 3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*  --*/
/*******************************************************************/

    cfg.wptt       = &stick_alt_minus;
    cfg.vertex     = &bm3b;
    cfg.parent     = &pbm3bm3p;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[-3 3 -3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
}

static void test_compute_stick_one_end()
{
/*******************************************************************/
/* Leaf*/
/*******************************************************************/
/*  + */
/*******************************************************************/
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &stick_one_leaf_1,
                                          &b1b,
                                          stick_one_leaf_1.root,
                                          false,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[-1 -3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*  - */
/*******************************************************************/

    cfg.wptt       = &stick_one_leaf_m1;
    cfg.vertex     = &bm1b;
    cfg.parent     = stick_one_leaf_m1.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[1 3]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*Internal*/
/*******************************************************************/
/*  up */
/*******************************************************************/
/*     + */
/*******************************************************************/

    cfg.wptt       = &stick_one_internal_up_1;
    cfg.vertex     = &ppb3bm3p1p;
    cfg.parent     = stick_one_internal_up_1.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([3 3 1][3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

/*******************************************************************/
/*      - */
/*******************************************************************/

    cfg.wptt       = &stick_one_internal_up_m1;
    cfg.vertex     = &ppbm3b3pm1p;
    cfg.parent     = stick_one_internal_up_m1.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([-3 -3 -1][3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

/*******************************************************************/
/*  down */
/*******************************************************************/
/*     + */
/*******************************************************************/

    cfg.wptt       = &stick_one_internal_down_1;
    cfg.vertex     = &ppb3bb3bp1p;
    cfg.parent     = stick_one_internal_down_1.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((([3][3])1)-3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

/*******************************************************************/
/*      - */
/*******************************************************************/

    cfg.wptt       = &stick_one_internal_down_m1;
    cfg.vertex     = &ppb3bb3bpm1p;
    cfg.parent     = stick_one_internal_down_m1.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((([3][3])-1)3)",
                                                                "is_canon_vertex"),
                                     "Error in output");
}

static void test_compute_stick_non_zero()
{
/*******************************************************************/
/* Infinity Tangle */
/*******************************************************************/
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &inf_tangle,
                                          &b0b,
                                          inf_tangle.root,
                                          true,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i[0 0]",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.vertex         = inf_tangle.root;
    cfg.parent         = NULL;
    cfg.parent_is_root = false;
    cfg.positivity     = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val            = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i[0 0]",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt           = &zero_tangle;
    cfg.vertex         = &b0b;
    cfg.parent         = NULL;
    cfg.parent_is_root = false;
    cfg.positivity     = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val            = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i[0]",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/* leaf*/
/*******************************************************************/

    cfg.wptt       = &stick_zero_leaf;
    cfg.vertex     = &b0b;
    cfg.parent     = &pb0b3p;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val        = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i[0 3]",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt           = &stick_zero_leaf3;
    cfg.vertex         = &b0b;
    cfg.parent         = &pb0b3p;
    cfg.parent_is_root = false;
    cfg.positivity     = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val            = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([3][0 3])",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt           = &stick_zero_leaf2;
    cfg.vertex         = &b0b;
    cfg.parent         = &pb3bb0bp;
    cfg.parent_is_root = true;
    cfg.positivity     = COMP_WPTT_VERT_CANON_POS_POS;
    ret_val            = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([3][0])",
                                                                "is_canon_vertex"),
                                     "Error in output");
/*******************************************************************/
/*Internal*/
/*******************************************************************/

    cfg.wptt       = &stick_zero_internal;
    cfg.vertex     = &ppb3bb3bpp;
    cfg.parent     = stick_zero_internal.root;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((([3][3]))3)",
                                                                "is_canon_vertex"),
                                     "Error in output");
}

static void test_compute_positivity()
{
/************************************************************************************************/
/* Plus */
/************************************************************************************************/
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &pos_plus_canon_leaf,
                                          &b2b,
                                          &pb2bb3bp,
                                          true,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i([2][3])",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.positivity = COMP_WPTT_VERT_CANON_POS_NEG;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([2][3])",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt       = &pos_plus_canon_internal;
    cfg.vertex     = &ppb3bb3bp2p;
    cfg.parent     = &pppb3bb3bp2pb3bp;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([3][3])2)[3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.positivity = COMP_WPTT_VERT_CANON_POS_NEG;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((([3][3])2)[3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

/************************************************************************************************/
/* Negative */
/************************************************************************************************/
    cfg.wptt       = &pos_plus_noncanon_leaf;
    cfg.vertex     = &bm2b;
    cfg.parent     = &pbm2bb3bp;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_NEG;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i([-2][3])",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i([-2][3])",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.wptt       = &pos_plus_noncanon_internal;
    cfg.vertex     = &ppb3bb3bpm2p;
    cfg.parent     = &pppb3bb3bpm2pb3bp;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_NEG;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("true",
                                     test_stub_read_success_msg("i((([3][3])-2)[3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");

    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((([3][3])-2)[3]3)",
                                                                "is_canon_vertex"),
                                     "Error in output");
}

static void test_compute_weight()
{
/************************************************************************************************/
/* At the root */
/************************************************************************************************/
    comp_wptt_vert_canon_config_t cfg = { &test_stub_write_success,
                                          &weight_double_weight_root,
                                          weight_double_weight_root.root,
                                          NULL,
                                          false,
                                          COMP_WPTT_VERT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i(1[3][3]1)",
                                                                "is_canon_vertex"),
                                     "Error in output");
/************************************************************************************************/
/* Away from the root */
/************************************************************************************************/
    cfg.wptt       = &weight_double_weight_nonroot;
    cfg.vertex     = &p1b3bb3b1p;
    cfg.parent     = &pp1b3bb3b1p3p;
    cfg.positivity = COMP_WPTT_VERT_CANON_POS_POS;

    ret_val = comp_wptt_vert_canon_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("false",
                                     test_stub_read_success_msg("i((1[3][3]1)3)",
                                                                "is_canon_vertex"),
                                     "Error in output");
}
