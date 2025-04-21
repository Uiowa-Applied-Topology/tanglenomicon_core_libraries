#include "notation_att.h"
#include "notation_tv.h"
#include "unity.h"

/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
/* clang-format off */

note_tv_t tv_buffer_de = {
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
note_att_node_t node_buffer_de[] = {
    [0]={
        (void *)&(node_buffer_de[1]),
        (void *)&(tv_buffer_de),
        NOTE_ATT_FLVR(NOTE_ATT_OP_PLUS,NOTE_ATT_TYPE_L_OP,NOTE_ATT_TYPE_R_TANG)
    },
    [1]={
        (void *)&(tv_buffer_de),
        (void *)&(node_buffer_de[2]),
        NOTE_ATT_FLVR(NOTE_ATT_OP_VEE,NOTE_ATT_TYPE_L_TANG,NOTE_ATT_TYPE_R_OP)},
    [2]={
        (void *)&(tv_buffer_de),
        (void *)&(tv_buffer_de),
        NOTE_ATT_FLVR(NOTE_ATT_OP_PLUS,NOTE_ATT_TYPE_L_TANG,NOTE_ATT_TYPE_R_TANG)}
};
note_att_t att_de = {
        &node_buffer_de[0],
        NULL,
        0,
        NULL,
        0
    };


char att_string[] = "+v[7 6 5 4 3 2 145]+[7 6 5 4 3 2 145][7 6 5 4 3 2 145][7 6 5 4 3 2 145]";
/*
                            +
                    v              [7 6 5 4 3 2 145]
[7 6 5 4 3 2 145]       +
    [7 6 5 4 3 2 145]       [7 6 5 4 3 2 145]
*/

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
    note_att_t test_att;
    note_att_node_t node_buffer[100];
    note_tv_t tv_buffer[100];
    test_att.node_buffer = node_buffer;
    test_att.node_buffer_len = 100;
    test_att.tv_buffer = tv_buffer;
    test_att.tv_buffer_len = 100;
    char test_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = {
        [0] = STR_TERMINAL_CHAR};

    uint8_t retval = note_att_decode(att_string, &test_att);
    TEST_ASSERT_EQUAL_UINT8(retval, NOTE_DEFS_DECODE_SUCCESS);
    retval = note_att_encode(test_att, test_str);
    TEST_ASSERT_EQUAL_UINT8(retval, NOTE_DEFS_ENCODE_SUCCESS);
    TEST_ASSERT_EQUAL_STRING(att_string, test_str);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(tv_buffer_de.twist_vector,
                                  tv_buffer[0].twist_vector,
                                  tv_buffer_de.tv_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(tv_buffer_de.twist_vector,
                                  tv_buffer[1].twist_vector,
                                  tv_buffer_de.tv_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(tv_buffer_de.twist_vector,
                                  tv_buffer[2].twist_vector,
                                  tv_buffer_de.tv_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(tv_buffer_de.twist_vector,
                                  tv_buffer[3].twist_vector,
                                  tv_buffer_de.tv_length);
}
/*!
 * @brief
 * @param
 */
STATIC_INLINE void test_decode(void)
{
    char test_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u] = {
        [0] = STR_TERMINAL_CHAR};
    uint8_t retval = note_att_encode(att_de, test_str);
    TEST_ASSERT_EQUAL_UINT8(retval, NOTE_DEFS_ENCODE_SUCCESS);
    TEST_ASSERT_EQUAL_STRING(att_string, test_str);
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_decode);
    RUN_TEST(test_encode);

    return UNITY_END();
}
