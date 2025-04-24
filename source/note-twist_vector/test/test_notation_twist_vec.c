#include "notation_tv.h"
#include "unity.h"

/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
/* clang-format off */
note_tv_t tv_t = {
    {
        [0] = 145,
        [1] = 2,
        [2] = 3,
        [3] = 4,
        [4] = 5,
        [5] = 6,
        [6] = 7
    },
    7};
char tv_string[] = "[7 6 5 4 3 2 145]";

#define STR_TERMINAL_CHAR (0x7Fu)

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
STATIC_INLINE void test_encode(void)
{
    note_tv_t test_tv;
    uint8_t retval = note_tv_decode(tv_string, &test_tv);
    TEST_ASSERT_EQUAL_UINT8(retval, NOTE_DEFS_DECODE_SUCCESS);
    TEST_ASSERT_EQUAL_UINT8(test_tv.tv_length, tv_t.tv_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(
        test_tv.twist_vector, tv_t.twist_vector, tv_t.tv_length);
}
/*!
 * @brief
 * @param
 */
STATIC_INLINE void test_decode(void)
{
    char test_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u] = {
        [0] = STR_TERMINAL_CHAR};
    uint8_t retval = note_tv_encode(
        tv_t, test_str, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u);
    TEST_ASSERT_EQUAL_UINT8(retval, NOTE_DEFS_ENCODE_SUCCESS);
    TEST_ASSERT_EQUAL_STRING(tv_string, test_str);
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_encode);
    RUN_TEST(test_decode);

    return UNITY_END();
}
