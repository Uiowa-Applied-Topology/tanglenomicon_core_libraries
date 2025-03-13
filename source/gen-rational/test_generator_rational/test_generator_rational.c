#include "generator_rational.h"
#include "string.h"
#include "unity.h"
#include "storage_defs.h"

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
note_tv_t tv;
char tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];

/* clang-format off */

gen_rational_config_t tc_write_success = {5,
                                          &stub_write_dedup_success,
                                          &stub_read,
                                          &tv,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
gen_rational_config_t tc_write_fail    = {5,
                                          &stub_write_fail,
                                          &stub_read,
                                          &tv,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
gen_rational_config_t tc_null_buff     = {5,
                                          &stub_write_fail,
                                          &stub_read,
                                          NULL,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
gen_rational_config_t tc_null_str_buff = {5,
                                          &stub_write_fail,
                                          &stub_read,
                                          &tv,
                                          NULL,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};

char cross_num_five_rattang[UTIL_TANG_DEFS_MAX_CROSSINGNUM*5][UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u]={
/* 5 */
"[1 1 1 1 1]",
/* 4 */
"[2 1 1 1 0]",
"[1 2 1 1 0]",
"[1 1 2 1 0]",
"[1 1 1 2 0]",
/* 3 */
"[3 1 1]",
"[1 3 1]",
"[1 1 3]",
"[2 2 1]",
"[2 1 2]",
"[1 2 2]",
/* 2 */
"[3 2 0]",
"[2 3 0]",
"[4 1 0]",
"[1 4 0]",
/* 1 */
"[5]",
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
    uint8_t ret_val = gen_rational_config(&tc_write_success);
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rational_config(NULL);
    TEST_ASSERT_EQUAL_UINT8(ret_val,
                            GEN_RATIONAL_CONFIG_IS_NULL | GEN_DEFS_CONFIG_FAIL);
    ret_val = gen_rational_config(&tc_null_buff);
    TEST_ASSERT_EQUAL_UINT8(ret_val,
                            GEN_RATIONAL_CONFIG_BUFFER | GEN_DEFS_CONFIG_FAIL);
    ret_val = gen_rational_config(&tc_null_str_buff);
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_RATIONAL_CONFIG_STR_BUFFER |
                                         GEN_DEFS_CONFIG_FAIL);
}
/*!
 * @brief
 * @param
 */
void test_generate_fail(void)
{

    uint8_t ret_val = gen_rational_config(&tc_write_fail);
    ret_val = gen_rational_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_FAIL);
}
/*!
 * @brief
 * @param
 */
void test_generate(void)
{
    uint8_t ret_val = gen_rational_config(&tc_write_success);
    size_t j, i;

    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_CONFIG_SUCCESS);
    ret_val = gen_rational_generate();
    TEST_ASSERT_EQUAL_UINT8(ret_val, GEN_DEFS_GENERATION_SUCCESS);
    //@@@TODO check the buffers

    TEST_ASSERT_EQUAL_UINT8(16, key_idx);
    for (i = 0; i < 16; i++)
    {
        TEST_MESSAGE("Checking against:");
        TEST_MESSAGE(key_buff[i]);

        bool fail = true;
        for (j = 0; j < key_idx; j++)
        {
            TEST_MESSAGE("Looking for generated:");
            TEST_MESSAGE(cross_num_five_rattang[j]);
            if (strcmp(key_buff[j], cross_num_five_rattang[i]) == 0)
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
