/* */
/* Created by joe on 6/23/25. */
/* */
#include "comp_wptt_vertex_canonicity.h"
#include "negative_tests.h"
#include "test_storage_stubs.h"
#include "unity.h"

static void test_compute_negative_no_config(void);

void test_compute_negative(void)
{
    RUN_TEST(test_compute_negative_no_config);
}

static void test_compute_negative_no_config(void)
{
    uint8_t retval = 0;

    retval = comp_wptt_vert_canon_compute();
    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_FAIL, retval & 0x1u);
}
