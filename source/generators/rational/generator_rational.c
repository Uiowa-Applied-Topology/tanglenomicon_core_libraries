/*!
 *  @file generator_rational.c
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
#include "stdbool.h"
#include "stdint.h"

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

static gen_rational_config_t *config = NULL;

/******************************************************************************/
/************************** Private Function Declerations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 * @return int
 */
int gen_rational_accel_asc();

/*!
 * @brief
 *
 *
 * @param ary
 * @param length
 * @return
 */
int gen_rational_permute(uint8_t *ary, uint8_t length);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
int gen_rational_config(gen_rational_config_t *config_arg)
{
    int ret_val = GEN_DEFS_CONFIG_FAIL;
    if (config_arg == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_IS_NULL;
    }
    else if (config_arg->tv_buff == NULL)
    {
        ret_val |= GEN_RATIONAL_CONFIG_BUFFER;
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
int gen_rational_generate()
{

    int ret_val = GEN_DEFS_GENERATION_FAIL;
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
/************************** Private Function Declerations *********************/
/******************************************************************************/

/*
 *  Documentation at decleration
 */
int gen_rational_accel_asc()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t l;
    uint8_t *a = config->tv_buff->twist_vector;
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
            l = k + 1;
            while (x <= y)
            {
                a[k] = x;
                a[l] = y;
                gen_rational_permute(a, k + 2);
                x += 1;
                y -= 1;
            }
            a[k] = x + y;
            y = x + y - 1;
            gen_rational_permute(a, k + 2);
        }
    }

    return ret_val;
}

/*
 *  Documentation at decleration
 */
int gen_rational_permute(uint8_t *ary, uint8_t length)
{
    (void)0;
    return 0;
}
