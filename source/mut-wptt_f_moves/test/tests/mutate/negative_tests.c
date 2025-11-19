/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_wptt_f_moves.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "unity_internals.h"

static void test_mutate_negative_no_config(void);
static void test_mutate_negative_executed(void);
static void test_mutate_negative_idx(void);

void test_mutate_negative(void)
{
    RUN_TEST(test_mutate_negative_no_config);
    RUN_TEST(test_mutate_negative_executed);
    RUN_TEST(test_mutate_negative_idx);
}

static void test_mutate_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                      MUT_WPTT_F_MOVES_MUTATE_CFG_ERROR),
                      retval);
}

static void test_mutate_negative_executed(void)
{
    int retval = 0;
    mut_wptt_f_moves_config_t cfg;
    size_t       idx       = 0;
    char *       trees_s[] = { "i([3]([5]([6][7])4)9)",
                               "z([3]([5]([6][7])4)9)" };
    note_wptt_t *trees_n[2];

    load_note(trees_n, trees_s, 2);

/***********************************************************************************************/
    trees_n[idx + 1]->root->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F1;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_FWD;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F1 test 1");
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                      MUT_WPTT_F_MOVES_MUTATE_ALREADY_COMPUTED),
                      retval);
}

static void test_mutate_negative_idx(void)
{
    int retval = 0;
    mut_wptt_f_moves_config_t cfg;
    size_t       idx       = 0;
    char *       trees_s[] = { "i([3]1([5]([6][7])4)9)",
                               "i([3]10([5]([6][7])4))", };
    note_wptt_t *trees_n[2];

    load_note(trees_n, trees_s, 2);

/***********************************************************************************************/
    /* "i([3]1([5]([6][7])4)9)"*/
    /* "i([3]10(4([6][7])[5]))"*/
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 3;
    cfg.direction  = MUT_F_MOVES_DIR_BK;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                      MUT_WPTT_F_MOVES_MUTATE_MOVE_F3_ERROR),
                      retval);
}
