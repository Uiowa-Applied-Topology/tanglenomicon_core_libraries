/* */
/* Created by joe on 6/23/25. */
/* */

#ifndef TEST_COMP_W2PP_BUF_SIZE_UTILS_H
#define TEST_COMP_W2PP_BUF_SIZE_UTILS_H

#include "comp_i2pp_buf_size.h"
#include "notation_wptt.h"
#include <stdint.h>

/************************************************************************************************/
/*  Base */
/************************************************************************************************/

typedef struct {
    char *                      wptt_string;
    uint64_t                    size;
    comp_i2pp_buf_size_config_t cfg;
}test_holder_t;



extern test_holder_t compute_valid_set[];

#endif /* TEST_COMP_W2PP_BUF_SIZE_UTILS_H */
