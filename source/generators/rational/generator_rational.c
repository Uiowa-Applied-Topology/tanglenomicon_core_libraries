/*!
 *  @file generator_rational.c
 *
 *  @brief  A pattern for generator modules
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

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief
 *
 */
static gen_rational_config_t *config = NULL;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 * @return uint8_t
 */
static uint8_t gen_rational_accel_asc();

/*!
 * @brief
 *
 *
 * @return uint8_t
 */
static uint8_t gen_rational_permute();

/*!
 * @brief
 *
 * @param A
 * @param length
 * @return uint8_t
 */
static uint8_t gen_rational_heaps();

/*!
 * @brief
 *
 * @param i
 * @param j
 * @return uint8_t
 */
static uint8_t gen_rational_swap_in_tv(uint8_t *left_p, uint8_t *right_p);

/*!
 * @brief
 *
 * @return uint8_t
 */
static uint8_t gen_rational_tvrev();

/*!
 * @brief
 *
 *
 * @return
 */
static uint8_t gen_rational_write();

/******************************************************************************/
/************************** Public Function Definitions
 ***********************/
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
    else if ((config_arg->tv_str_buff == NULL) ||
             (config_arg->tv_str_buff_len <= 0))
    {
        ret_val |= GEN_RATIONAL_CONFIG_STR_BUFFER;
    }
    else
    {
        config = config_arg;

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
    if (config == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_IS_NULL;
    }
    else
    {
        (void)gen_rational_accel_asc();
    }
    return ret_val;
}
/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_accel_asc()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t *a = config->tv_n->twist_vector;
    size_t *len = &(config->tv_n->tv_length);

    uint8_t l = 0;
    uint8_t n = config->crossingNumber;
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
            if (k % 2 == 1)
            {
                *len = k + 2;
                gen_rational_permute();
            }
            x += 1;
            y -= 1;
        }
        a[k] = x + y;
        y = x + y - 1;
        if (k % 2 == 1)
        {
            *len = k + 2;
            gen_rational_permute();
        }
    }
    *len = 1;
    a[0] = config->crossingNumber;
    (void)gen_rational_write();
    return ret_val;
}

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_permute()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    //@@@TODO: we need to add heuristics here to cut down on compares.
    (void)gen_rational_heaps();
    (void)gen_rational_tvrev();

    return ret_val;
}

/*
 *  Documentation at Declaration
 */
uint8_t gen_rational_heaps()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    uint8_t c[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};

    uint8_t *a = config->tv_n->twist_vector;
    size_t length = config->tv_n->tv_length;

    size_t i = 0;

    while (i < length)
    {
        if (i == 0)
        {
            (void)gen_rational_write();
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
    /*Swap the int at left_p with the one at right_p*/
    uint8_t placeholder;
    placeholder = *left_p;
    *left_p = *right_p;
    *right_p = placeholder;
    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t gen_rational_write()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    note_tv_decode(*(config->tv_n), config->tv_str_buff);
    config->storage_write("key", config->tv_str_buff, config->tv_str_buff);
    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t gen_rational_tvrev()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;

    uint8_t *tv = config->tv_n->twist_vector;
    uint8_t length = config->tv_n->tv_length;

    uint8_t *left_p, *right_p;

    left_p = tv;
    right_p = tv + length - 1;

    /* While the address for the right_p is bigger then the address on the
     * left_p.*/
    while (right_p > left_p)
    {

        /*Move the left_p right by one*/
        left_p++;
        /*Move the right_p left by one*/
        right_p--;
    }

    return ret_val;
}