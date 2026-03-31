/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_sum_parity.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"

static void test_config_positive_nowrite(void);
static void test_config_positive_write(void);

void test_config_positive(void)
{
    RUN_TEST(test_config_positive_nowrite);
    RUN_TEST(test_config_positive_write);
}

static void test_config_positive_nowrite(void)
{
    comp_sum_parity_config_t cfg = { .storage_write = NULL,
                                     .write_key     = NULL,
                                     .tangleA       = COMP_SUM_PARITY_PAR_ZERO,
                                     .tangleB       = COMP_SUM_PARITY_PAR_ZERO,
                                     .op            = COMP_SUM_PARITY_OP_PLUS };

    uint8_t ret_val = comp_sum_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
}

static void test_config_positive_write(void)
{
    comp_sum_parity_config_t cfg = { .storage_write = test_stub_write_success,
                                     .write_key     = "key",
                                     .tangleA       = COMP_SUM_PARITY_PAR_ZERO,
                                     .tangleB       = COMP_SUM_PARITY_PAR_ZERO,
                                     .op            = COMP_SUM_PARITY_OP_PLUS };

    uint8_t ret_val = comp_sum_parity_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
}
