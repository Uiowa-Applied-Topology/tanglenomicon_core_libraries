/* */
/* Created by joe on 6/23/25. */
/* */
#include "positive_tests.h"
#include "notation_wptt.h"
#include "stdlib.h"
#include "tang_defs.h"
#include "test_storage_stubs.h"
#include "mut_wptt_f_moves.h"
#include "unity.h"
#include "../../utils/utils.h"

STATIC_INLINE void test_mutate_positive_F3(void);
STATIC_INLINE void test_mutate_positive_F2(void);
STATIC_INLINE void test_mutate_positive_F1(void);

void test_mutate_positive(void)
{
    RUN_TEST(test_mutate_positive_F3);
    RUN_TEST(test_mutate_positive_F2);
    RUN_TEST(test_mutate_positive_F1);
}

STATIC_INLINE void test_mutate_positive_F1(void)
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
    cfg.weight_idx = 0;
    cfg.direction  = MUT_F_MOVES_DIR_UNINIT;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F1 test 1");
}

STATIC_INLINE void test_mutate_positive_F2(void)
{
    int retval = 0;
    mut_wptt_f_moves_config_t cfg;
    size_t       idx       = 0;
    char *       trees_s[] = { "i([3]([5]([6][7])4)9)",
                               "x([3]([5]([6][7])4)9)",
/***********************************************************************************************/
                               "i([3]([5]([6][7])4)9)",
                               "y([3]([5]([6][7])4)9)" };
    note_wptt_t *trees_n[4];

    load_note(trees_n, trees_s, 4);

/***********************************************************************************************/
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F2;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_FWD;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_CHILD;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F2 test 1");
    idx += 2;
/***********************************************************************************************/
    trees_n[idx + 1]->root->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F2;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_FWD;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_SELF;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F2 test 2");
}

STATIC_INLINE void test_mutate_positive_F3(void)
{
    int retval = 0;
    mut_wptt_f_moves_config_t cfg;
    size_t       idx       = 0;
    char *       trees_s[] = { "i([3]1([5]([6][7])4)9)",
                               "i([3]10([5]([6][7])4))",
/***********************************************************************************************/
                               "i([3]([5]([6][7])4)9)",
                               "i(9[3]([5]([6][7])4))",
/***********************************************************************************************/
                               "i([3]1([5]([6][7])4)8)",
                               "i([3]9([5]([6][7])4))",
/***********************************************************************************************/
                               "i([3]([5]([6][7])4)8)",
                               "i(8[3]([5]([6][7])4))",
/***********************************************************************************************/
                               "i(9[3]([5]([6][7])4)1)",
                               "i([3]([5]([6][7])4)10)",
/***********************************************************************************************/
                               "i(8[3]([5]([6][7])4))",
                               "i([3]([5]([6][7])4)8)", };
    note_wptt_t *trees_n[12];

    load_note(trees_n, trees_s, 12);

/***********************************************************************************************/
    /* "i([3]1([5]([6][7])4)9)"*/
    /* "i([3]10(4([6][7])[5]))"*/
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_BK;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 1");
    idx += 2;
/***********************************************************************************************/
    /* "i([3]1([5]([6][7])4)9)"*/
    /* "i(9[3](4([6][7])[5]))"*/
    trees_n[idx + 1]->root->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_FWD;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 2");
    idx += 2;
/***********************************************************************************************/
    /* "i([3]1([5]([6][7])4)8)"*/
    /* "i([3]9([5]([6][7])4))"*/

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_BK;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 3");
    idx += 2;
/***********************************************************************************************/
    /* "i([3]([5]([6][7])4)8)"*/
    /* "i(8[3]([5]([6][7])4))"*/

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 2;
    cfg.direction  = MUT_F_MOVES_DIR_FWD;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 4");
    idx += 2;
/***********************************************************************************************/
    /* "i(9[3]([5]([6][7])4)1)"*/
    /* "i([3](4([6][7])[5])10)"*/
    trees_n[idx + 1]->root->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[0]->order = NOTE_WPTT_ORDER_REVERSE;
    trees_n[idx + 1]->root->children[1]->children[1]->children[1]->order = NOTE_WPTT_ORDER_REVERSE;

    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 0;
    cfg.direction  = MUT_F_MOVES_DIR_BK;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 5");
    idx += 2;
/***********************************************************************************************/

    /* "i(8[3]([5]([6][7])4))"*/
    /* "i([3]([5]([6][7])4)8)"*/
    cfg.vertex     = trees_n[idx]->root;
    cfg.V4_label   = &(trees_n[idx]->label);
    cfg.move       = MUT_F_MOVE_F3;
    cfg.weight_idx = 0;
    cfg.direction  = MUT_F_MOVES_DIR_BK;
    cfg.eqclass    = MUT_F_MOVES_EQCLASS_UNINIT;

    retval = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    retval = mut_wptt_f_moves_mutate();
    TEST_ASSERT_EQUAL(MUT_DEFS_MUTATE_SUCCESS, retval);
    TEST_ASSERT_EQUAL_MESSAGE(true, test_util_trees_equal(trees_n[idx], trees_n[idx + 1]),
                              "Failed F3 test 6");
}
