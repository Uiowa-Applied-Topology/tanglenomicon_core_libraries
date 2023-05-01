/*!
 *  @file generator_pattern.c
 *
 *  @brief  A pattern for generator modules
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "generator_rational.h"
#include <stddef.h>
gen_rational_config_t *config;

/*Docs in header*/
int gen_rational_config(gen_rational_config_t *config_arg)
{
    int ret_val = GEN_RATIONAL_CONFIG_FAIL;
    if (config != NULL)
    {
        config = config_arg;
        ret_val = GEN_RATIONAL_CONFIG_SUCCESS;
    }
    return ret_val;
}
