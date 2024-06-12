#include "generator_montesinos.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "unity.h"


/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/******************************* Stubs ****************************************/
/******************************************************************************/

#define STR_TERMINAL_CHAR (0x7Fu)

char key_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u]
             [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
char index_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u]
               [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
char value_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u]
               [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
size_t key_idx = 0;
size_t index_idx = 0;
size_t value_idx = 0;

uint8_t stub_write_dedup_success(char *key, char *index, char *value)
{
    size_t i = 0;
    for (i = 0; i < key_idx; i++)
    {
        if (strcmp(key_buff[i], key) == 0)
        {
            return STORE_DEFS_WRITE_SUCCESS;
        }
    }
    strcpy(key_buff[key_idx], key);
    strcpy(index_buff[index_idx], index);
    strcpy(value_buff[value_idx], value);
    key_idx++;
    index_idx++;
    value_idx++;
    return STORE_DEFS_WRITE_SUCCESS;
}

uint8_t stub_write_success(char *key, char *index, char *value)
{
    strcpy(key_buff[key_idx], key);
    strcpy(index_buff[index_idx], index);
    strcpy(value_buff[value_idx], value);
    key_idx++;
    index_idx++;
    value_idx++;
    return STORE_DEFS_WRITE_SUCCESS;
}

uint8_t stub_write_fail(char *key, char *index, char *value)
{
    return STORE_DEFS_WRITE_FAIL;
}

const char *stub_read(char *key, char *index) { return value_buff[value_idx]; }

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
char str_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];

/* clang-format off */
note_att_node_t nodes[UTIL_TANG_DEFS_MAX_CROSSINGNUM *2];
note_att_t att_n = {
        NULL,
        nodes,
        UTIL_TANG_DEFS_MAX_CROSSINGNUM *2,
        NULL,
        0
};
note_tv_t tv_set_1[]={
        [0]={
                {
                    [0] = 0,
                    [1] = 1,
                    [2] = 1
                },
                3
            },
        [1]={
                {
                    [0] = 0,
                    [1] = 2,
                    [2] = 2
                },
                3
            },
        [2]={
                {
                    [0] = 0,
                    [1] = 3,
                    [2] = 3
                },
                3
            },
    };

note_tv_t tv_set_2[]={
        [0]={
                {
                    [0] = 1,
                    [1] = 1,
                    [2] = 1
                },
                3
            },
        [1]={
                {
                    [0] = 1,
                    [1] = 2,
                    [2] = 2
                },
                3
            }
    };

note_tv_t tv_set_3[]={
        [0]={
                {
                    [0] = 2,
                    [1] = 1,
                    [2] = 1
                },
                3
            },
        [1]={
                {
                    [0] = 2,
                    [1] = 2,
                    [2] = 2
                },
                3
            },
        [2]={
                {
                    [0] = 2,
                    [1] = 3,
                    [2] = 3
                },
                3
            },
        [3]={
                {
                    [0] = 2,
                    [1] = 4,
                    [2] = 4
                },
                3
            },
    };
note_tv_t *tv_sets[]={
    [0]=&tv_set_1,
    [1]=&tv_set_2,
    [2]=&tv_set_3
};
size_t tv_set_lens[]={3,2,4};
gen_montesinos_config_t tc_write_success = {
                                            &stub_write_success,
                                            &stub_read,
                                            &att_n,
                                            tv_sets,
                                            tv_set_lens,
                                            3,
                                            str_buff,
                                            UTIL_TANG_DEFS_MAX_CROSSINGNUM *2
                                            };

gen_montesinos_config_t tc_write_fail = {
                                            &stub_write_fail,
                                            &stub_read,
                                            &att_n,
                                            tv_sets,
                                            tv_set_lens,
                                            3,
                                            str_buff,
                                            UTIL_TANG_DEFS_MAX_CROSSINGNUM *2
                                            };
// gen_montesinos_config_t tc_write_fail    = {
//                                             &stub_write_fail,
//                                             &stub_read,
//                                             };
// gen_montesinos_config_t tc_null_buff     = {
//                                             &stub_write_fail,
//                                             &stub_read,
//                                             };
// gen_montesinos_config_t tc_null_str_buff = {
//                                             &stub_write_fail,
//                                             &stub_read,
//                                             };


char mont_trees[UTIL_TANG_DEFS_MAX_CROSSINGNUM*5][UTIL_TANG_DEFS_MAX_CROSSINGNUM * 4u]={
"+[1 1 0]+[1 1 1][1 1 2]",
"+[1 1 0]+[1 1 1][2 2 2]",
"+[1 1 0]+[1 1 1][3 3 2]",
"+[1 1 0]+[1 1 1][4 4 2]",
"+[1 1 0]+[2 2 1][1 1 2]",
"+[1 1 0]+[2 2 1][2 2 2]",
"+[1 1 0]+[2 2 1][3 3 2]",
"+[1 1 0]+[2 2 1][4 4 2]",
"+[2 2 0]+[1 1 1][1 1 2]",
"+[2 2 0]+[1 1 1][2 2 2]",
"+[2 2 0]+[1 1 1][3 3 2]",
"+[2 2 0]+[1 1 1][4 4 2]",
"+[2 2 0]+[2 2 1][1 1 2]",
"+[2 2 0]+[2 2 1][2 2 2]",
"+[2 2 0]+[2 2 1][3 3 2]",
"+[2 2 0]+[2 2 1][4 4 2]",
"+[3 3 0]+[1 1 1][1 1 2]",
"+[3 3 0]+[1 1 1][2 2 2]",
"+[3 3 0]+[1 1 1][3 3 2]",
"+[3 3 0]+[1 1 1][4 4 2]",
"+[3 3 0]+[2 2 1][1 1 2]",
"+[3 3 0]+[2 2 1][2 2 2]",
"+[3 3 0]+[2 2 1][3 3 2]",
"+[3 3 0]+[2 2 1][4 4 2]",
};


/* clang-format on */

/******************************************************************************/
/*******************************Test prep**************************************/
/******************************************************************************/

void setUp(void) {}

void tearDown(void) {}

/******************************************************************************/
/*******************************Test cases*************************************/
/******************************************************************************/

/*!
 * @brief
 * @param
 */
void test_config(void)
{
    uint8_t ret_val = gen_montesinos_config(&tc_write_success);
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_montesinos_config(NULL);
    TEST_ASSERT_EQUAL_UINT8(ret_val,
                            GEN_MONTESINOS_CONFIG_IS_NULL | GEN_DEFS_CONFIG_FAIL);
}
/*!
 * @brief
 * @param
 */
void test_generate(void)
{
    uint8_t ret_val = gen_montesinos_config(&tc_write_success);
    size_t j, i;

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_montesinos_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);
    //@@@TODO check the buffers

    TEST_ASSERT_EQUAL_UINT8(24, key_idx);
    for (i = 0; i < 24; i++)
    {
        TEST_MESSAGE("Checking against:");
        TEST_MESSAGE(key_buff[i]);

        bool fail = true;
        for (j = 0; j < key_idx; j++)
        {
            TEST_MESSAGE("Looking for generated:");
            TEST_MESSAGE(mont_trees[j]);
            if (strcmp(key_buff[j], mont_trees[i]) == 0)
            {
                TEST_MESSAGE("Found!");
                fail = false;
                break;
            }
        }
        if (fail)
        {
            TEST_FAIL_MESSAGE("Couldn't find a tangle in the list.");
        }
    }

}

/*!
 * @brief
 * @param
 */
void test_generate_fail(void)
{

    uint8_t ret_val = gen_montesinos_config(&tc_write_fail);
    ret_val = gen_montesinos_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_FAIL);
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config);
    RUN_TEST(test_generate);
    RUN_TEST(test_generate_fail);

    return UNITY_END();
}
