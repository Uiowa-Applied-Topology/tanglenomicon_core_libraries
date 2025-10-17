/* */
/* Created by joe on 6/29/25. */
/* */
/* cppcheck-suppress-begin [unreadVariable, unusedVariable] */
#include "bits/stdint-uintn.h"
#include "notation_wptt.h"
#include "generator_rlitt.h"
#include "test_low_crossing.h"
#include "stdlib.h"
#include "string.h"
#include "test_storage_stubs.h"
#include "../utils/utils.h"
#include "unity.h"
#include <stdbool.h>
static struct note_wptt_node_t note_wptt_nodes[20 * UTIL_TANG_DEFS_MAX_CROSSINGNUM];
static note_wptt_node_buffer_t buffer = { (note_wptt_node_t *)&note_wptt_nodes,
                                          20 * UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                          0 };
size_t number_of_tangles = 0;
STATIC_INLINE_UINT8 stub_write_success(const char *key,
                                       const char *index,
                                       const char *value)
{
    if ((0 == strcmp(index, "positivity")) && (false == test_stub_read_exists(key, index)))
    {
        number_of_tangles++;
        return test_stub_write_success(key, index, value);;
    }
    return STORE_DEFS_WRITE_SUCCESS;
}

void test_low_crossing(void)
{
    size_t i;
    char * zero[] = { "i[0]" };
    gen_rlitt_positivity_e zero_p[] = { GEN_RLITT_NEU };

    char *one[] = { "i[1]", "i[-1]" };
    gen_rlitt_positivity_e one_p[] = { GEN_RLITT_NEU, GEN_RLITT_NEU };
    note_wptt_t *          one_n[2];

    load_note(one_n, one, 2);

    char *two_good[] = { "i[2]", "i[-2]" };
    gen_rlitt_positivity_e two_good_p[] = { GEN_RLITT_NEU, GEN_RLITT_NEU };
    note_wptt_t *          two_good_n[2];
    load_note(two_good_n, two_good, 2);

    char *       two_not_good[] = { "i[2 0]", "i[-2 0]" };
    note_wptt_t *two_not_good_n[2];
    load_note(two_not_good_n, two_not_good, 2);

    char *       three_good[] = { "i[3]", "i[-3]", "i[2 1]", "i[-2 -1]" };
    note_wptt_t *three_good_n[4];
    load_note(three_good_n, three_good, 4);


    char *       three_not_good[] = { "i[3 0]", "i[-3 0]", "i[2 1 0]", "i[-2 -1 0]" };
    note_wptt_t *three_not_good_n[4];
    load_note(three_not_good_n, three_not_good, 4);

    char *four_good_neu[] = { "i[4]",
                              "i[-4]",
                              "i[3 1]",
                              "i[2 1 1]",
                              "i[-3 -1]",
                              "i[-2 -1 -1]",
                              "i[2 2]",
                              "i[-2 -2]" };

    note_wptt_t *four_good_neu_n[8];
    load_note(four_good_neu_n, four_good_neu, 8);

    char *four_good_neg[] = { "i([-2][-2])" };
    gen_rlitt_positivity_e four_good_neg_p[] = { GEN_RLITT_NEG };
    note_wptt_t *          four_good_neg_n[1];
    load_note(four_good_neg_n, four_good_neg, 1);

    char *four_good_pos[] = { "i([2][2])" };
    gen_rlitt_positivity_e four_good_pos_p[] = { GEN_RLITT_POS };
    note_wptt_t *          four_good_pos_n[1];
    load_note(four_good_pos_n, four_good_pos, 1);

    char *       four_not_good_neu[] = { "i[4 0]",
                                         "i[-4 0]",
                                         "i[3 1 0]",
                                         "i[2 1 1 0]",
                                         "i[-3 -1 0]",
                                         "i[-2 -1 -1 0]",
                                         "i[2 2 0]",
                                         "i[-2 -2 0]" };
    note_wptt_t *four_not_good_neu_n[8];
    load_note(four_not_good_neu_n, four_not_good_neu, 8);

    char *       four_not_good_neg[] = { "i(([-2][-2]))" };
    note_wptt_t *four_not_good_neg_n[1];
    load_note(four_not_good_neg_n, four_not_good_neg, 1);

    char *       four_not_good_pos[] = { "i(([2][2]))" };
    note_wptt_t *four_not_good_pos_n[1];
    load_note(four_not_good_pos_n, four_not_good_pos, 1);

    const char *five[] = { "i(([2][2])1)",
                           "i(([2][2])-1)",
                           "i(([-2][-2])1)",
                           "i(([-2][-2])-1)",
                           "i[3 2]",
                           "i[4 1]",
                           "i[3 1 1]",
                           "i[2 1 2]",
                           "i[2 1 1 1]",
                           "i[-3 -2]",
                           "i[2 2 1]",
                           "i[-2 -1 -2]",
                           "i[-4 -1]",
                           "i[-3 -1 -1]",
                           "i([-2][3])",
                           "i[-2 -1 -1 -1]",
                           "i[-2 -2 -1]",
                           "i([-2][-3])",
                           "i([2][3])",
                           "i([2][-3])",
                           "i[2 3]",
                           "i[-2 -3]",
                           "i([-3][2])",
                           "i([-3][-2])",
                           "i([3][2])",
                           "i([3][-2])",
                           "i([-2][-2]1)",
                           "i([-2][-2]-1)",
                           "i([2][2]-1)",
                           "i([2][2]1)", };

    gen_rlitt_config_t cfg;
    cfg.storage_write = &stub_write_success;
    uint8_t ret_val = 0;
/************************************************************************************************/
/* 0 5 skip*/
/************************************************************************************************/
/* 1 4 */
    cfg.rootstocks     = (const note_wptt_t **)one_n;
    cfg.rootstocks_len = 2;
    cfg.scions         = (const note_wptt_t **)four_good_neu_n;
    cfg.scions_len     = 8;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.rootstocks     = (const note_wptt_t **)one_n;
    cfg.rootstocks_len = 2;
    cfg.scions         = (const note_wptt_t **)four_good_pos_n;
    cfg.scions_len     = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.rootstocks     = (const note_wptt_t **)one_n;
    cfg.rootstocks_len = 2;
    cfg.scions         = (const note_wptt_t **)four_good_neg_n;
    cfg.scions_len     = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);
/************************************************************************************************/
/* 2 3 */
    cfg.rootstocks     = (const note_wptt_t **)two_good_n;
    cfg.rootstocks_len = 2;
    cfg.scions         = (const note_wptt_t **)three_good_n;
    cfg.scions_len     = 4;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.rootstocks     = (const note_wptt_t **)two_not_good_n;
    cfg.rootstocks_len = 2;
    cfg.scions         = (const note_wptt_t **)three_good_n;
    cfg.scions_len     = 4;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

/************************************************************************************************/
/* 3 2 */

    cfg.scions         = (const note_wptt_t **)two_good_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)three_good_n;
    cfg.rootstocks_len = 4;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)two_good_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)three_not_good_n;
    cfg.rootstocks_len = 4;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

/************************************************************************************************/
/* 4 1 */
    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_not_good_neu_n;
    cfg.rootstocks_len = 8;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_not_good_pos_n;
    cfg.rootstocks_len = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_not_good_neg_n;
    cfg.rootstocks_len = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_good_neu_n;
    cfg.rootstocks_len = 8;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_good_pos_n;
    cfg.rootstocks_len = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

    cfg.scions         = (const note_wptt_t **)one_n;
    cfg.scions_len     = 2;
    cfg.rootstocks     = (const note_wptt_t **)four_good_neg_n;
    cfg.rootstocks_len = 1;
    ret_val            = gen_rlitt_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rlitt_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);

/************************************************************************************************/
/* 5 0 skip */
/************************************************************************************************/
    /* TEST_ASSERT_EQUAL_UINT8(number_of_tangles, 32); */
    for (i = 0; i < 30; i++)
    {
        char msg_buffer[1024] = { '\0' };
        snprintf(msg_buffer, sizeof(msg_buffer), "Couldn't find %s", five[i]);

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(true,
                                        test_stub_read_exists((const char *)five[i], "positivity"),
                                        msg_buffer);
    }
}

/* cppcheck-suppress-end [unreadVariable, unusedVariable] */
