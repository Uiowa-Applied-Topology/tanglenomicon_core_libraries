#include "comp_rational_data.h"
#include "string.h"
#include "unity.h"

/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/******************************* Stubs ****************************************/
/******************************************************************************/

char   key_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u][UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
char   index_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u][UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
char   value_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u][UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
size_t key_idx   = 0;
size_t index_idx = 0;
size_t value_idx = 0;

STATIC_INLINE_UINT8 stub_write_success(const char *key,
                                       const char *index,
                                       const char *value)
{
    strcpy(key_buff[key_idx], key);
    strcpy(index_buff[index_idx], index);
    strcpy(value_buff[value_idx], value);
    key_idx++;
    index_idx++;
    value_idx++;
    return STORE_DEFS_WRITE_SUCCESS;
}

STATIC_INLINE_UINT8 stub_write_fail(const char *key,
                                    const char *index,
                                    const char *value)
{
    strcpy(key_buff[key_idx], key);
    strcpy(index_buff[index_idx], index);
    strcpy(value_buff[value_idx], value);
    key_idx++;
    index_idx++;
    value_idx++;
    return STORE_DEFS_WRITE_SUCCESS;
}

STATIC_INLINE const char *stub_read(const char *key, const char *index)
{
    return value_buff[value_idx];
}

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
note_tv_t tv;
char      tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];

/* this is tv: 1 3 2*/
note_tv_t tv_oe = { { 2, 3, 1 },
                    3 };
char      output_oe[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 5][UTIL_TANG_DEFS_MAX_CROSSINGNUM *
                                                        2u] = { "9",
                                                                "4",
                                                                "1",
                                                                "4",
                                                                UTIL_TANG_DEFS_INF_TANG_STR };

/* this is tv: 2 3 1*/
note_tv_t tv_oo = { { 1, 3, 2 },
                    3 };
char      output_oo[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 5][UTIL_TANG_DEFS_MAX_CROSSINGNUM *
                                                        2u] = { "9",
                                                                "7",
                                                                "2",
                                                                "7",
                                                                UTIL_TANG_DEFS_ONE_TANG_STR };

/* this is tv: 3 2 1*/
note_tv_t tv_eo = { { 1, 2, 3 },
                    3 };
char      output_eo[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 5][UTIL_TANG_DEFS_MAX_CROSSINGNUM *
                                                        2u] = { "10",
                                                                "7",
                                                                "3",
                                                                "7",
                                                                UTIL_TANG_DEFS_ZERO_TANG_STR };

size_t output_len = 5;
/* clang-format off */

comp_rational_data_config_t tc_write_success = {
                                          &stub_write_success,
                                          &tv,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
comp_rational_data_config_t tc_write_fail = {
                                          &stub_write_fail,
                                          &tv,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
comp_rational_data_config_t tc_null_buff = {
                                          &stub_write_fail,
                                          NULL,
                                          tv_str,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};
comp_rational_data_config_t tc_null_str_buff = {
                                          &stub_write_fail,
                                          &tv,
                                          NULL,
                                          UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u,};

/* clang-format on */

/******************************************************************************/
/*******************************Test prep**************************************/
/******************************************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

/******************************************************************************/
/*******************************Test cases*************************************/
/******************************************************************************/

/*!
 * @brief
 * @param
 */
STATIC_INLINE void test_config(void)
{
    uint8_t ret_val = comp_rational_data_config(&tc_write_success);

    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_rational_data_config(NULL);
    TEST_ASSERT_EQUAL_UINT8(
        ret_val, COMP_RATIONAL_DAT_CONFIG_IS_NULL | COMP_DEFS_CONFIG_FAIL);
    ret_val = comp_rational_data_config(&tc_null_buff);
    TEST_ASSERT_EQUAL_UINT8(
        ret_val, COMP_RATIONAL_DAT_CONFIG_BUFFER | COMP_DEFS_CONFIG_FAIL);
    ret_val = comp_rational_data_config(&tc_null_str_buff);
    TEST_ASSERT_EQUAL_UINT8(
        ret_val, COMP_RATIONAL_DAT_CONFIG_STR_BUFFER | COMP_DEFS_CONFIG_FAIL);
}

/*!
 * @brief
 * @param
 */
STATIC_INLINE void test_result(void)
{
    uint8_t ret_val = comp_rational_data_config(&tc_write_success);
    const comp_rational_data_result_t *result;

    /* Odd/Even*/
    tc_write_success.tv_n = &tv_oe;
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_rational_data_compute();
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_COMPUTE_SUCCESS);
    result = comp_rational_data_result();
    TEST_ASSERT_EQUAL_STRING(result->parity, UTIL_TANG_DEFS_INF_TANG_STR);
    TEST_ASSERT_EQUAL_UINT8(result->numerator, 9);
    TEST_ASSERT_EQUAL_UINT8(result->denominator, 4);
    TEST_ASSERT_EQUAL_UINT8(result->num_algebraic_equ, 1);
    TEST_ASSERT_EQUAL_UINT8(result->den_algebraic_equ, 4);
}

/*!
 * @brief
 * @param
 */
STATIC_INLINE void test_compute(void)
{
    uint8_t ret_val;
    size_t  i;

    /* Odd/Even*/
    tc_write_success.tv_n = &tv_oe;
    ret_val = comp_rational_data_config(&tc_write_success);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_rational_data_compute();
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_COMPUTE_SUCCESS);
    for (i = 0; i < output_len; i++)
    {
        TEST_ASSERT_EQUAL_STRING(output_oe[i], value_buff[i]);
    }
    key_idx   = 0;
    index_idx = 0;
    value_idx = 0;
    /* Even/Odd*/
    tc_write_success.tv_n = &tv_oo;
    ret_val = comp_rational_data_config(&tc_write_success);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_rational_data_compute();
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_COMPUTE_SUCCESS);
    for (i = 0; i < output_len; i++)
    {
        TEST_ASSERT_EQUAL_STRING(output_oo[i], value_buff[i]);
    }
    key_idx   = 0;
    index_idx = 0;
    value_idx = 0;
    /* Odd/Odd*/
    tc_write_success.tv_n = &tv_eo;
    ret_val = comp_rational_data_config(&tc_write_success);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    ret_val = comp_rational_data_compute();
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_COMPUTE_SUCCESS);
    for (i = 0; i < output_len; i++)
    {
        TEST_ASSERT_EQUAL_STRING(output_eo[i], value_buff[i]);
    }
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config);
    RUN_TEST(test_compute);
    RUN_TEST(test_result);

    return UNITY_END();
}
