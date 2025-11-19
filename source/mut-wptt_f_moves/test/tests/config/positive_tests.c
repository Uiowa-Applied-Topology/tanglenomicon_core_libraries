/* */
/* Created by joe on 6/23/25. */
/* */
#include "mut_wptt_f_moves.h"
#include "positive_tests.h"
#include "unity.h"
#include "../../utils/utils.h"

void test_config_positive(void)
{
    char *       trees_s[] = { "i([3]([5]([6][7])4))",
                               "i([3](4([6][7])[5]))" };
    note_wptt_t *trees_n[2];

    load_note(trees_n, trees_s, 2);

    mut_wptt_f_moves_config_t cfg = {
        trees_n[0]->root->children[1],
        &(trees_n[0]->label),
        MUT_F_MOVE_F1,
        0,
        MUT_F_MOVES_DIR_UNINIT,
        MUT_F_MOVES_EQCLASS_UNINIT
    };

    uint8_t ret_val = mut_wptt_f_moves_config(&cfg);
    TEST_ASSERT_EQUAL_UINT8(ret_val, MUT_DEFS_CONFIG_SUCCESS);
}
