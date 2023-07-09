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
 * @brief An impliementation of an integer partitioning algorithm info at:
 * Kelleher, J., & O'Sullivan, B. (2009). Generating All Partitions: A
 * Comparison Of Two Encodings (Version 2). arXiv.
 * https://doi.org/10.48550/ARXIV.0909.2331
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_accel_asc(gen_rational_config_t *cfg);

/*!
 * @brief This function handles the permuting of a twist vector found in cfg.
 * The function calls all configured permutation algorithms.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_permute(gen_rational_config_t *cfg);

/*!
 * @brief An impliementation of an permutation algorithm info at: Heap,
 * B. R. (1963). Permutations by Interchanges. In The Computer Journal (Vol. 6,
 * Issue 3, pp. 293-298). Oxford University Press (OUP).
 * https://doi.org/10.1093/comjnl/6.3.293
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_heaps(gen_rational_config_t *cfg);

/*!
 * @brief A function to swap the contents of two pointers.
 *
 * @param left_p The left side pointer.
 * @param right_p The right side pointer.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_swap_in_tv(uint8_t *left_p,
                                              uint8_t *right_p);

/*!
 * @brief A function to write the twist vector in cfg to the storage device in
 * cfg.
 *
 * @param cfg Configuration to work on.
 * @return uint8_t Success/Fail flag.
 */
static inline uint8_t gen_rational_write(gen_rational_config_t *cfg);

/*!
 * @brief A permutation function that checks if the twist vector in cfg is only
 * one value. This hapens for the largest odd partition, which is only "1"s.
 *
 * @param cfg Configuration to work on.
 * @return true
 * @return false
 */
static bool gen_rational_perm_all_matching(gen_rational_config_t *cfg);

/*!
 * @brief The default permutation function. Simply finds all permutations for
 * the twist vector found in cfg.
 *
 * @param cfg Configuration to work on.
 * @return true
 * @return false
 */
static bool gen_rational_perm_default(gen_rational_config_t *cfg);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the rational gen module.
 *
 */
static gen_rational_config_t *gen_rational_localcfg = NULL;

/*!
 * @brief The list of permuation function pointers.
 *
 */
static gen_rational_perm_t gen_rational_perm_funs[] = {
    &gen_rational_perm_all_matching, /*****************************************/
    &gen_rational_perm_default};

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
        (void)gen_rational_accel_asc(gen_rational_localcfg);
        ret_val = GEN_DEFS_GENERATION_SUCCESS;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_accel_asc(gen_rational_config_t *cfg)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    /* Set function inputs to match the cfg data*/
    uint8_t *tv = cfg->tv_n->twist_vector;
    size_t *len = &(cfg->tv_n->tv_length);
    uint8_t n = cfg->crossingNumber;

    uint8_t a[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};
    uint8_t l = 0;
    uint8_t k = 1;
    uint8_t y = n - 1;
    uint8_t x = 0;

    while (k != 0)
    {
        x = a[k - 1] + 1;
        k -= 1;
        while ((2 * x) <= y)
        {
            a[k] = x;
            y -= x;
            k += 1;
        }
        l = k + 1;
        while (x <= y)
        {
            a[k] = x;
            a[l] = y;

            /* Check if the current partition is odd then permute. */
            if (k % 2 == 1)
            {
                size_t i = 0;
                /* Initialize the tv in cfg with the partition.*/
                *len = k + 2;
                for (i = 0; i < k + 2; i++)
                {
                    tv[i] = a[i];
                }
                (void)gen_rational_permute(cfg);
            }

            x += 1;
            y -= 1;
        }
        a[k] = x + y;
        y = x + y - 1;

        /* Check if the current partition is odd then permute. */
        if (k % 2 == 0)
        {
            size_t i = 0;
            /* Initialize the tv in cfg with the partition.*/
            *len = k + 1;
            for (i = 0; i < k + 1; i++)
            {
                tv[i] = a[i];
            }
            (void)gen_rational_permute(cfg);
        }
    }
    return ret_val;
}

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_permute(gen_rational_config_t *cfg)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    /*@@@TODO: we need to add heuristics here to cut down on compares.*/
    size_t i = 0;
    /* Iterate over the function pointers for heuristic permutation functions.
     * This emulates the functionality of a switch case statement, but with
     * arbitrary functionality in each case. */
    for (i = 0; i < GEN_RATIONAL_PERM_FUNS_LEN; i++)
    {
        if (gen_rational_perm_funs[i](cfg) == true)
        {
            /* Break loop if we 'used' a heuristic. */
            break;
        }
    }

    return ret_val;
}

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_heaps(gen_rational_config_t *cfg)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    /* Set function inputs to match the cfg data*/
    uint8_t *a = cfg->tv_n->twist_vector;
    size_t length = cfg->tv_n->tv_length;

    uint8_t c[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};

    size_t i = 0;

    while (i < length)
    {
        if (i == 0)
        {
            (void)gen_rational_write(cfg);
        }
        if (c[i] < i)
        {
            if (i % 2 == 0)
            {
                (void)gen_rational_swap_in_tv(a, a + i);
            }
            else
            {
                (void)gen_rational_swap_in_tv(a + i, a + c[i]);
            }
            c[i]++;
            i = 0;
        }
        else
        {
            c[i] = 0;
            i++;
        }
    }
    return ret_val;
}

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_swap_in_tv(uint8_t *left_p, uint8_t *right_p)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t placeholder;

    /*Swap the int at left_p with the one at right_p*/
    placeholder = *left_p;
    *left_p = *right_p;
    *right_p = placeholder;

    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t gen_rational_write(gen_rational_config_t *cfg)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    note_tv_decode(*(cfg->tv_n), cfg->tv_str_buff);

    char *value = "twist_vector";
    /* Write the data to the storage device. */
    /*@@@TODO: we need to add the correct document values.*/
    cfg->storage_write(cfg->tv_str_buff, value, cfg->tv_str_buff);

    value = "crossing_num";
    /* Decode to get the string representation for the tv and store.*/
    sprintf(local_str, "%u", cfg->crossingNumber);
    cfg->storage_write(cfg->tv_str_buff, value, local_str);

    return ret_val;
}

/*
 *  Documentation at declaration
 */
bool gen_rational_perm_all_matching(gen_rational_config_t *cfg)
{
    bool ret_val = true;

    /* Set local redirects for cfg data. */
    uint8_t *tv = cfg->tv_n->twist_vector;
    uint8_t length = cfg->tv_n->tv_length;

    uint8_t i = 0;
    /* Iterate over tv backwards. We go backwards since the high values are the
     * non-1 values. While iterating check if successave values match. */
    for (i = length - 1; i > 0; i--)
    {
        if (tv[i - 1] != tv[i])
        {
            ret_val = false;
            break;
        }
    }

    /* If all idx match we can write and move on to the next parition. */
    if (ret_val == true)
    {
        (void)gen_rational_write(cfg);
    }

    return ret_val;
}

/*
 *  Documentation at declaration
 */
bool gen_rational_perm_default(gen_rational_config_t *cfg)
{
    /* Take all permutations of the tv. */
    (void)gen_rational_heaps(cfg);

    /* Default case return true. */
    return true;
}