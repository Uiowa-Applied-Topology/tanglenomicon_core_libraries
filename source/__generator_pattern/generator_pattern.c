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


#include "generator_pattern.h"

generator_pattern_config_t *config;

void generator_pattern_config(generator_pattern_config_t *config_arg)
{
    config = config_arg;
}