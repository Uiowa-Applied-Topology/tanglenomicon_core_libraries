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
/************************** Private Function Declarations *********************/
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
int gen_rational_permute(uint8_t length);

/*!
 * @brief
 *
 * @param A
 * @param length
 * @return int
 */
int gen_rational_heaps(uint8_t *A, uint8_t length);

/*!
 * @brief
 *
 * @param ptr1
 * @param ptr2
 * @return int
 */
int gen_rational_swap_ptr(uint8_t *ptr1, uint8_t *ptr2);

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
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation at Declaration
 */
int gen_rational_accel_asc()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t l = 0;
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
                if ((k + 2) % 2 == 1)
                {
                    gen_rational_permute(k + 2);
                }
                x += 1;
                y -= 1;
            }
            a[k] = x + y;
            y = x + y - 1;
            if ((k + 2) % 2 == 1)
            {
                gen_rational_permute(k + 2);
            }
        }
    }

    return ret_val;
}

/*
 *  Documentation at Declaration
 */
int gen_rational_permute(uint8_t length)
{
    uint8_t i;
    uint8_t *p2tv = config->tv_buff->twist_vector;
    uint8_t num_ele_to_permute = length;
    uint8_t *elements_to_permute[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    for (i = 0u; i < length; i++)
    {
        if (p2tv[i] == 1)
        {
            num_ele_to_permute--;
        }
        else
        {
            num_ele_to_permute++;
            break;
        }
    }

    if (num_ele_to_permute < length)
    {
        uint8_t perms = 0;
        uint8_t j = 0;
        for (i = length-1; i > num_ele_to_permute; i--)
        {
            elements_to_permute[j] = &(p2tv[i]);
            j++;
        }
        while ((num_ele_to_permute + perms) < length)
        {
            gen_rational_heaps(elements_to_permute, num_ele_to_permute);
            perms++;
            if (perms % 2 == 0)
            {
                elements_to_permute[0] = &(p2tv[num_ele_to_permute - perms]);
            }
            else
            {
                elements_to_permute[num_ele_to_permute] =
                    &(p2tv[num_ele_to_permute + perms]);
            }
        }
    }
    else
    {

        for (i = 0u; i < length; i++)
        {
            elements_to_permute[num_ele_to_permute] = &(p2tv[i]);
        }
        gen_rational_heaps(elements_to_permute, length);
    }
    return 0;
}

/*
 *  Documentation at Declaration
 */
int gen_rational_heaps(uint8_t *A, uint8_t length)
{

    uint8_t i;
    uint8_t elements_to_permute;
    uint8_t c[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {[0] = 0};
    char *str;

    // i acts similarly to a stack pointer
    i = 1;
    while (i < length)
    {

        if (c[i] < i)
        {

            if (i % 2 == 0)
            {
                gen_rational_swap_ptr(&A[0], &A[i]);
            }
            else
            {
                gen_rational_swap_ptr(&A[c[i]], &A[i]);
            }

            note_tv_decode(*(config->tv_buff), str);
            config->storage_write("key", str, str);

            // Swap has occurred ending the for-loop. Simulate the increment
            // of the for-loop counter
            c[i]++;
            // Simulate recursive call reaching the base case by bringing
            // the pointer to the base case analog in the array
            i = 1;
        }
        else
        {
            // Calling generate(i+1, A) has ended as the for-loop
            // terminated. Reset the state and simulate popping the stack by
            // incrementing the pointer.
            c[i] = 0;
            i++;
        }
    }
    return 0;
}

/*
 *  Documentation at Declaration
 */
int gen_rational_swap_ptr(uint8_t *ptr1, uint8_t *ptr2)
{
    uint8_t *temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}
