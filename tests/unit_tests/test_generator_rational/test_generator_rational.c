#include "tang_defs.h"
#include "generator_rational.h"
#include "string.h"
#include "unity.h"

/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/******************************* Stubs ****************************************/
/******************************************************************************/

#define STR_TERMINAL_CHAR (0x7Fu)

#define STORE_WRITE_FAIL (0x1u)
#define STORE_WRITE_SUCCESS (0x0u)

char key_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u] = {[0] = STR_TERMINAL_CHAR};
char index_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u] = {[0] =
                                                            STR_TERMINAL_CHAR};
char value_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u] = {[0] =
                                                            STR_TERMINAL_CHAR};

int stub_write_success(char *key, char *index, char *value)
{
    strcpy(key_buff, key);
    strcpy(index_buff, index);
    strcpy(value_buff, value);
    return STORE_WRITE_SUCCESS;
}

int stub_write_fail(char *key, char *index, char *value)
{
    strcpy(key_buff, key);
    strcpy(index_buff, index);
    strcpy(value_buff, value);
    return STORE_WRITE_FAIL;
}

const char *stub_read(char *key, char *index) { return value_buff; }

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
note_tv_t tv;
gen_rational_config_t tc_write_success = {8, &stub_write_success, &stub_read,
                                          false, &tv};
gen_rational_config_t tc_write_fail = {8, &stub_write_fail, &stub_read, false,
                                       &tv};
gen_rational_config_t tc_null_buff = {8, &stub_write_fail, &stub_read, false,
                                      NULL};

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
}
/*!
 * @brief
 * @param
 */
void test_generate(void) {}
/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config);
    RUN_TEST(test_generate);

    return UNITY_END();
}
