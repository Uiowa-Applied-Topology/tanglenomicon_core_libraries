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

generator_rational_config_t *config;

void generator_pattern_config(generator_rational_config_t *config_arg)
{
    config = config_arg;
}