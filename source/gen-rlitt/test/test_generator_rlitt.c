#include "generator_rlitt.h"
#include "notation_wptt.h"
#include "utils/utils.h"
#include "tests/generate/positive_tests.h"
#include "tests/generate/negative_tests.h"
#include "tests/config/positive_tests.h"
#include "tests/config/negative_tests.h"
#include "tests/test_low_crossing.h"
#include "test_storage_stubs.h"
#include "unity.h"

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
    test_stub_storage_clear_buffers();
}

void tearDown(void)
{
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config_positive);
    RUN_TEST(test_config_negative);
    RUN_TEST(test_generate_positive);
    RUN_TEST(test_generate_negative);
    RUN_TEST(test_low_crossing);

    return UNITY_END();
}
