/*!
 *  @file comp_rational_data.c
 *
 *  @brief  A module for compute rational tangle data: fraction, algebraic
 * equivlance, and parity.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_rational_data.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 * @param p
 * @param q
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_alg_eq(uint16_t p, uint16_t q);

/*!
 * @brief
 *
 * @param num_eq
 * @param den_eq
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_write_alg_eq(uint16_t num_eq,
                                                      uint16_t den_eq);

/*!
 * @brief
 *
 * @param p
 * @param q
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_parity(uint16_t p, uint16_t q);

/*!
 * @brief
 *
 * @param parity
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_write_parity(char *parity);

/*!
 * @brief
 *
 * @param p
 * @param q
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_rat_num(uint16_t *p, uint16_t *q);

/*!
 * @brief
 *
 * @param p
 * @param q
 * @return uint8_t
 */
static inline uint8_t comp_rational_data_write_rat_num(uint16_t p, uint16_t q);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the rational comp module.
 *
 */
static comp_rational_data_config_t *comp_rational_data_localcfg = NULL;

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_rational_data_config(comp_rational_data_config_t *config_arg)
{

    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;
    if (config_arg == NULL)
    {
        ret_val |= COMP_RATIONAL_DAT_CONFIG_IS_NULL;
    }
    else if (config_arg->tv_n == NULL)
    {
        ret_val |= COMP_RATIONAL_DAT_CONFIG_BUFFER;
    }  /* Ensure the string buffer exists and has a length. */
    else if ((config_arg->tv_str_buff == NULL) ||
             (config_arg->tv_str_buff_len <= 0))
    {
        ret_val |= COMP_RATIONAL_DAT_CONFIG_STR_BUFFER;
    }
    else
    {
        /* Set the config. */
        comp_rational_data_localcfg = config_arg;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_rational_data_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    uint16_t p;
    uint16_t q;

    note_tv_decode(*(comp_rational_data_localcfg->tv_n),
                   comp_rational_data_localcfg->tv_str_buff);

    /*@@@TODO: Add error handling.*/
    ret_val |= comp_rational_data_rat_num(&p, &q);
    ret_val |= comp_rational_data_write_rat_num(p, q);
    ret_val |= comp_rational_data_alg_eq(p, q);
    ret_val |= comp_rational_data_parity(p, q);
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_alg_eq(uint16_t p, uint16_t q)
{
    return comp_rational_data_write_alg_eq(p % q, q % p);
}

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_write_alg_eq(uint16_t num_eq, uint16_t den_eq)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    char *value = COMP_RATIONAL_DAT_STORAGE_UKEY;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    value = "numerator_eq";
    /* Decode to get the string representation for the numerator equivalence
     * class and store.*/
    sprintf(local_str, "%u", num_eq);
    comp_rational_data_localcfg->storage_write(
        comp_rational_data_localcfg->tv_str_buff, value, local_str);

    value = "numerator_eq";
    /* Decode to get the string representation for the denominator equivalence
     * class and store.*/
    sprintf(local_str, "%u", den_eq);
    comp_rational_data_localcfg->storage_write(
        comp_rational_data_localcfg->tv_str_buff, value, local_str);
    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_parity(uint16_t p, uint16_t q)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;
    char *parity = "";
    if (!((p % 2 == 0) && (q % 2 == 0)))
    {
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;
        if (p % 2 == 1)
        {
            if (q % 2 == 1)
            {
                parity = UTIL_TANG_DEFS_ONE_TANG_STR;
            }
            else
            {
                parity = UTIL_TANG_DEFS_INF_TANG_STR;
            }
        }
        else
        {
            parity = UTIL_TANG_DEFS_ZERO_TANG_STR;
        }
        (void)comp_rational_data_write_parity(parity);
    }
    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_write_parity(char *parity)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    char *value = COMP_RATIONAL_DAT_STORAGE_UKEY;

    value = "parity";
    /* Decode to get the string representation for the numerator and store.*/
    comp_rational_data_localcfg->storage_write(
        comp_rational_data_localcfg->tv_str_buff, value, parity);
    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_rat_num(uint16_t *p, uint16_t *q)
{

    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    uint16_t pimo = 0;
    uint16_t pi = 1;
    uint16_t qimo = 1;
    uint16_t qi = 0;
    size_t i = 0;

    for (i = 0; i < comp_rational_data_localcfg->tv_n->tv_length; i++)
    {
        uint16_t tmp_p = pi;
        uint16_t tmp_q = qi;

        pi = comp_rational_data_localcfg->tv_n->twist_vector[i] * pi + pimo;
        qi = comp_rational_data_localcfg->tv_n->twist_vector[i] * qi + qimo;

        pimo = tmp_p;
        qimo = tmp_q;
    }

    *p = pi;
    *q = qi;

    return ret_val;
}

/*
 *  Documentation at declaration
 */
uint8_t comp_rational_data_write_rat_num(uint16_t p, uint16_t q)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    char *value = COMP_RATIONAL_DAT_STORAGE_UKEY;

    value = "numerator";
    /* Decode to get the string representation for the numerator and store.*/
    sprintf(local_str, "%u", p);
    comp_rational_data_localcfg->storage_write(
        comp_rational_data_localcfg->tv_str_buff, value, local_str);

    value = "denominator";
    /* Decode to get the string representation for the denominator and store.*/
    sprintf(local_str, "%u", q);
    comp_rational_data_localcfg->storage_write(
        comp_rational_data_localcfg->tv_str_buff, value, local_str);

    return ret_val;
}