/*!
 *  @file generator_rational.c
 *
 *  @brief  A module for generating rational tangles.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "generator_rational.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief Number of permutation functions used by the module.
 *
 */
#define GEN_RATIONAL_PERM_FUNS_LEN (2u)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/*!
 * @brief The type for permutation functions used by the module.
 *
 */
typedef bool (*gen_rational_perm_t)(gen_rational_config_t *);

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 * @param cfg
 * @return uint8_t
 */
static uint8_t gen_rational_partions(size_t n, size_t i,
                                     gen_rational_config_t *cfg);

/*!
 * @brief A function to write the twist vector in cfg to the storage device in
 * cfg.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_write(gen_rational_config_t *cfg);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the rational gen module.
 *
 */
static gen_rational_config_t *gen_rational_localcfg = NULL;

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t gen_rational_config(gen_rational_config_t *config_arg)
{
    uint8_t ret_val = GEN_DEFS_CONFIG_FAIL;
    if (config_arg == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_IS_NULL;
    }
    else if (config_arg->tv_n == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_BUFFER;
    }
    /* Ensure the string buffer exists and has a length. */
    else if ((config_arg->tv_str_buff == NULL) ||
             (config_arg->tv_str_buff_len <= 0))
    {
        ret_val |= GEN_RATIONAL_CONFIG_STR_BUFFER;
    }
    else
    {
        /* Set the config. */
        gen_rational_localcfg = config_arg;

        ret_val = GEN_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t gen_rational_generate()
{

    uint8_t ret_val = GEN_DEFS_GENERATION_FAIL;
    uint8_t cn = gen_rational_localcfg->crossingNumber;

    if (gen_rational_localcfg == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_IS_NULL;
    }
    else
    {
        /* Find all partitions for the local config. */
        (void)gen_rational_partions(cn, 0, gen_rational_localcfg);
        ret_val = GEN_DEFS_GENERATION_SUCCESS;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
static uint8_t gen_rational_partions(size_t n, size_t i,
                                     gen_rational_config_t *cfg)
{
    /* Set function inputs to match the cfg data*/
    uint8_t *tv = cfg->tv_n->twist_vector;
    uint8_t cn = (cfg->crossingNumber) + 1;
    size_t *len = &(cfg->tv_n->tv_length);
    size_t k;
    if (n == 0)
    {
        if (i % 2 == 1)
        {
            *len = i;
            (void)gen_rational_write(cfg);
        }
    }
    else
    {
        for (k = 1; k <= cn; k++)
        {
            tv[i] = k;
            (void)gen_rational_partions(n - k, i + 1, cfg);
            if ((n - k) == 0)
            {
                break;
            }
        }
    }
}

/*
 *  Documentation at declaration
 */
uint8_t gen_rational_write(gen_rational_config_t *cfg)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    note_tv_decode(*(cfg->tv_n), cfg->tv_str_buff);

    /* Write the data to the storage device. */
    /*@@@TODO: we need to add the correct document values.*/
    cfg->storage_write(cfg->tv_str_buff, "twist_vector", cfg->tv_str_buff);

    /* Decode to get the string representation for the tv and store.*/
    sprintf(local_str, "%u", cfg->crossingNumber);
    cfg->storage_write(cfg->tv_str_buff, "crossing_num", local_str);

    return ret_val;
}
