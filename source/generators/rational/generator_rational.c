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

gen_rational_config_t *config;

/******************************************************************************/
/************************** Private Function Declerations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 * @return int
 */
int gen_rational_accel_asc(int n);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
int gen_rational_config(gen_rational_config_t *config_arg)
{
    int ret_val = GEN_DEFS_CONFIG_FAIL;
    if (config != NULL)
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

    int ret_val = GEN_DEFS_CONFIG_FAIL;

    return ret_val;
}
/******************************************************************************/
/************************** Private Function Declerations *********************/
/******************************************************************************/

/*
 *  Documentation at decleration
 */
int gen_rational_accel_asc(uint8_t n)
{
    int a[n];
    // k = 1
    // y = n - 1
    // while k != 0:
    //     x = a[k - 1] + 1
    //     k -= 1
    //     while 2 * x <= y:
    //         a[k] = x
    //         y -= x
    //         k += 1
    //     l = k + 1
    //     while x <= y:
    //         a[k] = x
    //         a[l] = y
    //         yield a[:k + 2]
    //         x += 1
    //         y -= 1
    //     a[k] = x + y
    //     y = x + y - 1
    //     yield a[:k + 1]
    return 0;
}