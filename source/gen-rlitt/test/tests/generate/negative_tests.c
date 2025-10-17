/* */
/* Created by joe on 6/23/25. */
/* */
#include "generator_rlitt.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"

static note_wptt_node_t ibm99b_root = { {
                                            NULL
                                        },
                                        {
                                            99
                                        },
                                        0,
                                        0,
                                        NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t ib99_88b_root = { {
                                              &ibm99b_root
                                          },
                                          {
                                              0, -88
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

static note_wptt_node_t ib2b = { {
                                     NULL
                                 },
                                 {
                                     2
                                 },
                                 0,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };

static note_wptt_t tree_is_a_neutral_stick = { &ib99_88_77b_root,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };
static note_wptt_t tree_is_a_positive_leaf = { &ib2b,
                                               NULL,
                                               NOTE_WPTT_V4_LABEL_I, };
static void test_generate_negative_no_config(void);
static void test_generate_negative_non_alternating(void);

void test_generate_negative(void)
{
    RUN_TEST(test_generate_negative_no_config);
    RUN_TEST(test_generate_negative_non_alternating);
}

static void test_generate_negative_no_config(void)
{
    uint8_t retval = gen_rlitt_generate();

    TEST_ASSERT_EQUAL(GEN_DEFS_GENERATION_FAIL, retval & 0x1u);
}

static void test_generate_negative_non_alternating(void)
{
    const note_wptt_t *rlist[] = {
        [0] = &tree_is_a_positive_leaf
    };
    const note_wptt_t *slist[] = {
        [0] = &tree_is_a_neutral_stick
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

    TEST_ASSERT_EQUAL_STRING(NULL, test_stub_read_success("i[-99 -88 -77 2]", "scion"));
}
