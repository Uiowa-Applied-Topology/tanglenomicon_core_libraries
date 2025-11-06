#include "string.h"
#include "unity.h"
#include "comp_wptt_canonicity.h"
/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/******************************* Stubs ****************************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/


/* clang-format off */

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
static void test_config(void)
{
}

static note_wptt_node_t b0b             = { { NULL }, { 0, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
static note_wptt_node_t pb0b3p          = { { &b0b }, { 0, 3 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
static note_wptt_t      stick_zero_leaf = { &pb0b3p, NULL, NOTE_WPTT_V4_LABEL_I };

/*!
 * @brief
 * @param
 */
static void test_compute(void)
{
    comp_wptt_canonicity_config_t cfg = { NULL,
                                          &stick_zero_leaf,
                                          COMP_WPTT_CANON_POS_POS };

    uint8_t ret_val = comp_wptt_canonicity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
    ret_val = comp_wptt_canonicity_compute();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
    const comp_wptt_canonicity_result_t *result = comp_wptt_canonicity_result();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_COMPUTE_SUCCESS, "Error in computation.");
}

/*!
 * @brief
 * @param
 */
void test_results(void)
{
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config);
    RUN_TEST(test_compute);

    return UNITY_END();
}
