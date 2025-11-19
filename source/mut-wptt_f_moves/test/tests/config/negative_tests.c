/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_wptt_f_moves.h"
#include "negative_tests.h"
#include "mutator_defs.h"
#include "notation_wptt.h"
#include "test_storage_stubs.h"
#include "../../utils/utils.h"
#include "unity.h"

static void test_config_negative_null_config(void);
static void test_config_negative_param_error(void);

void test_config_negative(void)
{
    RUN_TEST(test_config_negative_null_config);
    RUN_TEST(test_config_negative_param_error);
}

static void test_config_negative_param_error(void)
{
    char *       trees_s[] = { "i([3]([5]([6][7])4))",
                               "i([3](4([6][7])[5]))" };
    note_wptt_t *trees_n[2];

    load_note(trees_n, trees_s, 2);

    mut_wptt_f_moves_config_t cfg = {
        NULL,
        &(trees_n[0]->label),
        MUT_F_MOVE_F1,
        0,
        MUT_F_MOVES_DIR_UNINIT,
        MUT_F_MOVES_EQCLASS_UNINIT
    };

    uint8_t ret_val = mut_wptt_f_moves_config(&cfg);
/************************************************************************************************/
    /* F1 NULL vertex */
    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_VERTEX),
        ret_val);

/************************************************************************************************/
    /* move uniint */
    cfg.vertex = trees_n[0]->root;
    cfg.move   = MUT_F_MOVE_UNINIT;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_MOVE),
        ret_val);

/************************************************************************************************/
    /* F1 NULL label */
    cfg.vertex   = trees_n[0]->root;
    cfg.move     = MUT_F_MOVE_F1;
    cfg.V4_label = NULL;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F1),
        ret_val);

/************************************************************************************************/
    /* F1 label unint */
    trees_n[0]->label = NOTE_WPTT_V4_LABEL_UNINIT;
    cfg.V4_label      = &(trees_n[0]->label);
    cfg.vertex        = trees_n[0]->root;
    cfg.move          = MUT_F_MOVE_F1;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F1),
        ret_val);

/************************************************************************************************/
    /* F2 NULL label */
    cfg.vertex   = trees_n[0]->root;
    cfg.move     = MUT_F_MOVE_F2;
    cfg.V4_label = NULL;
    cfg.eqclass  = MUT_F_MOVES_EQCLASS_CHILD;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F2),
        ret_val);

/************************************************************************************************/
    /* F2 unint label */
    trees_n[0]->label = NOTE_WPTT_V4_LABEL_UNINIT;
    cfg.V4_label      = &(trees_n[0]->label);
    cfg.vertex        = trees_n[0]->root;
    cfg.move          = MUT_F_MOVE_F2;
    cfg.eqclass       = MUT_F_MOVES_EQCLASS_CHILD;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F2),
        ret_val);

/************************************************************************************************/
    /* F2 eqclass uninit */
    trees_n[0]->label = NOTE_WPTT_V4_LABEL_I;
    cfg.V4_label      = &(trees_n[0]->label);
    cfg.vertex        = trees_n[0]->root;
    cfg.move          = MUT_F_MOVE_F2;
    cfg.eqclass       = MUT_F_MOVES_EQCLASS_UNINIT;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F2),
        ret_val);
/************************************************************************************************/
    /* F3 uninit direction*/

    cfg.vertex    = trees_n[0]->root;
    cfg.move      = MUT_F_MOVE_F3;
    cfg.direction = MUT_F_MOVES_DIR_UNINIT;

    ret_val = mut_wptt_f_moves_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_F3),
        ret_val);
}

static void test_config_negative_null_config(void)
{
    uint8_t ret_val = mut_wptt_f_moves_config(NULL);

    TEST_ASSERT_EQUAL_UINT8(
        MUT_STATUS_BLDR(
            MUT_DEFS_CONFIG_FAIL, MUT_WPTT_F_MOVES_CONFIG_IS_NULL),
        ret_val);
}
