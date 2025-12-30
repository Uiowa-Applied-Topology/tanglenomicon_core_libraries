#include "comp_rlitt_pure_vignette.h"
#include "notation_wptt.h"
#include "tests/compute/positive_tests.h"
#include "tests/compute/negative_tests.h"
#include "tests/config/positive_tests.h"
#include "tests/config/negative_tests.h"
#include "tests/results/positive_tests.h"
#include "tests/results/negative_tests.h"
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
    test_stub_storage_clear_buffers();
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_config_positive);
    RUN_TEST(test_config_negative);
    RUN_TEST(test_compute_positive);
    RUN_TEST(test_compute_negative);
    RUN_TEST(test_results_positive);
    RUN_TEST(test_results_negative);

    return UNITY_END();
}
