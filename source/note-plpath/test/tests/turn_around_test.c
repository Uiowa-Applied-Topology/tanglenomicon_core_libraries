/* */
/* Created by joe on 4/27/25. */
/* */
#include "turn_around_test.h"
#include "notation_plpath.h"
#include "unity.h"

extern bool test_util_trees_equal(const note_plpath_t *tree1, const note_plpath_t *tree2);
static void test_turn_around_test_1(void);

/*!
 * @brief
 * @param
 */
void test_turn_around(void)
{
    RUN_TEST(test_turn_around_test_1);
}

/****************************** Test 1 Data ***********************************/

/*
 * - A tree with an essential vertex.
 * - A tree with a vertex that has ring number.
 * - A tree with a vertex with more than one weight.
 */

/*!
 * @brief
 * @param
 */
static void test_turn_around_test_1(void)
{
}
