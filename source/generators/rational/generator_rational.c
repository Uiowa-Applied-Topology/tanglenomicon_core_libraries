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
 * @brief Number of combination functions used by the module.
 *
 */
#define GEN_RATIONAL_PERM_FUNS_LEN (2u)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Iteratively generates all possible combination of integer partitions
 * of the cfg.crossingNumber without.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_combinations();

/*!
 * @brief A function to write the twist vector in cfg to the storage device in
 * cfg.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_write();

/*!
 * @brief The canonical form for twist vector is given as odd length. When we
 * get something in the even class of twist vectors we can 'oddify' it by
 * prepending a 0. This function handles prepending the zero and then writing to
 * the cfg storage device.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_evenperm_shift_write();

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

    if (gen_rational_localcfg == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_IS_NULL;
    }
    else
    {
        /* Find all partitions for the local config. */
        ret_val = gen_rational_combinations();
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation in declaration
 */
static uint8_t gen_rational_combinations()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    /* Set function inputs to match the cfg data*/
    uint8_t *tv = gen_rational_localcfg->tv_n->twist_vector;
    uint8_t crossing_num = (gen_rational_localcfg->crossingNumber);
    size_t *len = &(gen_rational_localcfg->tv_n->tv_length);

    /* Variables to emulate recursive calling.*/
    size_t stack_i[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};
    size_t tv_idx = 0;
    size_t available_crossings = crossing_num;

    /* Set the outermost for loop iterator to 1.*/
    stack_i[0] = 1;

    /* This while loop emulates for loops executing recursively. The outermost
     * for loop as the termination condition. */
    while (stack_i[0] <= crossing_num)
    {
        /* Set the tv to the value of the tv_idx-th for loop counter. */
        tv[tv_idx] = stack_i[tv_idx];

        /* Check if the inner most (tv_idx-th) for loop has exhausted availble
         * crossings. */
        if ((available_crossings - stack_i[tv_idx]) == 0)
        {
            /*Set twist vector length*/
            *len = tv_idx + 1;

            if ((*len) % 2 == 0)
            {
                (void)gen_rational_evenperm_shift_write();
            }
            else
            {
                /* Twist vector already odd length. */
                (void)gen_rational_write();
            }

            /* Emulate an escape from the tv_idx-th for loop.*/

            /* Make sure we don't underflow then decrament.*/
            if (tv_idx != 0)
            {
                tv_idx--;
            }

            /* Restore available crossings */
            available_crossings += stack_i[tv_idx];
        }
        else
        {
            /* Emulate a recursive call into the tv_idx+1-th for loop.*/

            /* Remove available crossings */
            available_crossings -= stack_i[tv_idx];
            tv_idx++;
            /* We want the initial state of the tv_idx+1-th loop iterator to be
             * 1, we set 0 here and increment on the next instruction.*/
            stack_i[tv_idx] = 0;
        }
        /* Increment the tv_idx-th for loop iterator.*/
        stack_i[tv_idx]++;
    }

    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t gen_rational_evenperm_shift_write()
{

    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    /* Set function inputs to match the cfg data*/
    uint8_t *tv = gen_rational_localcfg->tv_n->twist_vector;
    uint8_t crossing_num = (gen_rational_localcfg->crossingNumber);
    size_t *len = &(gen_rational_localcfg->tv_n->tv_length);

    /* Increase tv_length by 1 to account for leading 0.*/
    (*len)++;

    /* right shift the twist vector */
    size_t i;
    for (i = *len - 1; i > 0; i--)
    {
        tv[i] = tv[i - 1];
    }

    /* Add leading 0 */
    tv[0] = 0;

    (void)gen_rational_write();

    /* left shift the twist vector */
    for (i = 0; i < *len; i++)
    {
        tv[i] = tv[i + 1];
    }
    return ret_val;
}
/*
 *  Documentation at declaration
 */
uint8_t gen_rational_write()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    note_tv_decode(*(gen_rational_localcfg->tv_n),
                   gen_rational_localcfg->tv_str_buff);

    char *value = "twist_vector";
    /* Write the data to the storage device. */
    /*@@@TODO: we need to add the correct document values.*/
    gen_rational_localcfg->storage_write(gen_rational_localcfg->tv_str_buff,
                                         value,
                                         gen_rational_localcfg->tv_str_buff);

    value = "crossing_num";
    /* Decode to get the string representation for the tv and store.*/
    sprintf(local_str, "%u", gen_rational_localcfg->crossingNumber);
    gen_rational_localcfg->storage_write(gen_rational_localcfg->tv_str_buff,
                                         value, local_str);

    return ret_val;
}
