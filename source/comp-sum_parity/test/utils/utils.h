/* */
/* Created by joe on 6/23/25. */
/* */

#ifndef TEST_COMP_SUM_PARITY_UTILS_H
#define TEST_COMP_SUM_PARITY_UTILS_H

#include "comp_sum_parity.h"
#include <stdint.h>

/************************************************************************************************/
/*  Base */
/************************************************************************************************/

typedef struct {
    char *                   parity;
    uint16_t                 count;
    comp_sum_parity_parity_e par_e;
    comp_sum_parity_config_t cfg;
}test_holder_t;



extern test_holder_t compute_valid_set[];

#endif /* TEST_COMP_SUM_PARITY_UTILS_H */
