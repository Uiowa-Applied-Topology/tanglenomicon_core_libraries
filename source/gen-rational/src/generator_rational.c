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
#define GEN_RATIONAL_PERM_FUNS_LEN    (2u)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief A function to process a template describing the ' ', and '+' for a twist vector. A template is a bitfield where 1 is $+$ and 0 is ' '. Example: 0101 -> [1 1+1 1+1] -> [1 2 2]
 *
 * @param template Template to work on.
 * @return uint8_t Success/Fail flag.
 */
STATIC_INLINE_UINT8 gen_rational_proc_template(uint8_t template);

/*!
 * @brief A function to write the twist vector in cfg to the store-storage_interface device in cfg.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
STATIC_INLINE_UINT8 gen_rational_write();

/*!
 * @brief The canonical form for twist vector is given as odd length. When we get something in the even class of twist vectors we can 'oddify' it by prepending a 0. This function handles prepending the zero and then writing to the cfg store-storage_interface device.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
STATIC_INLINE_UINT8 gen_rational_evenperm_shift_write();

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
    else if (config_arg->tv_str_buff == NULL)
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
        size_t i = 0u;
        /* A left shift multiplies the value of an integer by 2. */
        size_t count_lim = 0x01u << (gen_rational_localcfg->crossingNumber - 1);
        for (i = 0u; i < count_lim; i++)
        {
            ret_val = gen_rational_proc_template(i);
            if (ret_val == GEN_DEFS_GENERATION_FAIL)
            {
                break;
            }
        }
        /* Find all partitions for the local config. */
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation in declaration
 */
static uint8_t gen_rational_proc_template(uint8_t template)
{
    uint8_t  ret_val = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t  counter = gen_rational_localcfg->crossingNumber;
    size_t * tv_len  = &(gen_rational_localcfg->tv_n->tv_length);
    uint8_t *tv      = gen_rational_localcfg->tv_n->twist_vector;
    size_t   i       = 0u;

    for (i = 0u; i < UTIL_TANG_DEFS_MAX_CROSSINGNUM; i++)
    {
        tv[i] = 1;
    }
    *tv_len = 0;
    while (counter > 0u)
    {
        counter--;
        if ((template & 0x01u) == 0)
        {
            (*tv_len)++;
        }
        else
        {
            (tv[(*tv_len)])++;
        }
        template = template >> 0x01u;
    }
    if ((*tv_len) % 2 == 0)
    {
        ret_val = gen_rational_evenperm_shift_write();
    }
    else
    {
        /* Twist vector already odd length. */
        ret_val = gen_rational_write();
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
    uint8_t *tv  = gen_rational_localcfg->tv_n->twist_vector;
    size_t * len = &(gen_rational_localcfg->tv_n->tv_length);

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

    ret_val = gen_rational_write();

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
    uint8_t ret_val      = GEN_DEFS_GENERATION_FAIL;
    uint8_t write_status = STORE_DEFS_WRITE_FAIL;

    note_tv_encode(*(gen_rational_localcfg->tv_n),
                   gen_rational_localcfg->tv_str_buff,
                   gen_rational_localcfg->tv_str_buff_len);

    char *value = "note-twist_vector";
    /* Write the data to the store-storage_interface device. */
    /*@@@TODO: we need to add the correct document values.*/
    write_status = gen_rational_localcfg->storage_write(
        gen_rational_localcfg->tv_str_buff,
        value,
        gen_rational_localcfg->tv_str_buff);
    if (write_status == STORE_DEFS_WRITE_SUCCESS)
    {
        char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
        value = "crossing_num";
        /* Decode to get the string representation for the tv and store.*/
        sprintf(local_str, "%u", gen_rational_localcfg->crossingNumber);
        write_status = gen_rational_localcfg->storage_write(
            gen_rational_localcfg->tv_str_buff, value, local_str);
    }

    if (write_status == STORE_DEFS_WRITE_SUCCESS)
    {
        ret_val = GEN_DEFS_GENERATION_SUCCESS;
    }
    return ret_val;
}
