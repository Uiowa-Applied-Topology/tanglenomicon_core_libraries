/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_itt_to_path.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/utils.h"

extern uint8_t stub_write_success(void);

void test_config_positive(void)
{
    uint8_t ret_val = comp_itt_to_path_config(&compute_valid_set[0]->cfg);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(ret_val, COMP_DEFS_CONFIG_SUCCESS, "Error in config.");
}
