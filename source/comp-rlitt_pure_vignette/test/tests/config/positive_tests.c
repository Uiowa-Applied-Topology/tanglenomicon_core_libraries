/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_rlitt_pure_vignette.h"
#include "positive_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"
#include "../../utils/data.h"

extern uint8_t stub_write_success();

void test_config_positive(void)
{
    note_wptt_t tree = {
        &b3b,
        NULL,
        NOTE_WPTT_V4_LABEL_I,
    };

    comp_rlitt_pure_vignette_config_t cfg = {
        &test_stub_write_success,
        &tree,
    };

    uint8_t ret_val = comp_rlitt_pure_vignette_config(&cfg);

    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
    comp_rlitt_pure_vignette_config_t cfg2 = { NULL, &tree };

    ret_val = comp_rlitt_pure_vignette_config(&cfg2);
    TEST_ASSERT_EQUAL_UINT8(ret_val, COMP_DEFS_CONFIG_SUCCESS);
}
