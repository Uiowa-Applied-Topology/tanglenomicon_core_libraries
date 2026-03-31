/**
 *  \file comp_sum_parity.c
 *
 *  \brief A computation module for computing the parity of a tangle sum
 *
 *
 *  \author Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "tang_defs.h"
#include "comp_sum_parity.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/**
 * \brief The local configuration of the parity computation.
 *
 */
static comp_sum_parity_config_t *comp_sum_parity_localcfg = NULL;

/**
 * \brief The local result of the parity computation.
 *
 */
static comp_sum_parity_result_t comp_sum_parity_localrestult = {
    .parity          = COMP_SUM_PARITY_PAR_UNINIT,
    .component_count = 0
};

/**
 * \brief The local computation status of the parity computation.
 *
 */
static bool comp_sum_parity_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

STATIC_INLINE comp_sum_parity_parity_e comp_sum_parity_rotate(comp_sum_parity_parity_e parity);
STATIC_INLINE comp_sum_parity_parity_e comp_sum_parity_sum(comp_sum_parity_parity_e parity_a,
                                                           comp_sum_parity_parity_e parity_b);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_sum_parity_config(comp_sum_parity_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_sum_parity_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (NULL == config_arg)
    {
        ret_val |= COMP_SUM_PARITY_CONFIG_IS_NULL;
    } /*Ensure the inputs are not empty.*/
    else if ((COMP_SUM_PARITY_PAR_UNINIT == config_arg->tangleA) ||
             (COMP_SUM_PARITY_PAR_UNINIT == config_arg->tangleB) ||
             (COMP_SUM_PARITY_OP_UNINIT == config_arg->op))
    {
        ret_val |= COMP_SUM_PARITY_CONFIG_PARAM;
    }
    else
    {
        /* Set the config. */
        comp_sum_parity_localcfg = config_arg;

        /* Clear the return value*/
        comp_sum_parity_localrestult.parity          = COMP_SUM_PARITY_PAR_UNINIT;
        comp_sum_parity_localrestult.component_count = 0u;

        /*clear the executed status*/
        comp_sum_parity_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_sum_parity_compute(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_sum_parity_localcfg == NULL)
    {
        ret_val |= COMP_SUM_PARITY_COMPUTE_CFG_ERROR;
    }
    /*Ensure not previously executed.*/
    else if (comp_sum_parity_executed != false)
    {
        ret_val |= COMP_SUM_PARITY_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        /* Recursively identify parity of a the tree */
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;
        comp_sum_parity_executed = true;
        comp_sum_parity_parity_e tangleA = comp_sum_parity_localcfg->tangleA;
        comp_sum_parity_parity_e tangleB = comp_sum_parity_localcfg->tangleB;

        /* If the operation is v we need to flip the tangles and then flip them back */
        if (COMP_SUM_PARITY_OP_VEE == comp_sum_parity_localcfg->op)
        {
            comp_sum_parity_localrestult.parity =
                comp_sum_parity_rotate(comp_sum_parity_sum(comp_sum_parity_rotate(tangleA),
                                                           comp_sum_parity_rotate(tangleB)));
        }
        else
        {
            comp_sum_parity_localrestult.parity =
                comp_sum_parity_sum(tangleA,
                                    tangleB);
        }

        /* Print results if requested. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (NULL != comp_sum_parity_localcfg->storage_write) &&
            (NULL != comp_sum_parity_localcfg->write_key))
        {
            char local_str[10] = { '\0' };

            sprintf(local_str, "%u", comp_sum_parity_localrestult.component_count);

            comp_sum_parity_localcfg->storage_write(comp_sum_parity_localcfg->write_key,
                                                    "sum parity components",
                                                    local_str);
            switch (comp_sum_parity_localrestult.parity)
            {
            case COMP_SUM_PARITY_PAR_CHI: {
                comp_sum_parity_localcfg->storage_write(comp_sum_parity_localcfg->write_key,
                                                        "sum parity",
                                                        "X");
                break;
            }

            case COMP_SUM_PARITY_PAR_ZERO: {
                comp_sum_parity_localcfg->storage_write(comp_sum_parity_localcfg->write_key,
                                                        "sum parity",
                                                        "0");
                break;
            }

            case COMP_SUM_PARITY_PAR_INF: {
                comp_sum_parity_localcfg->storage_write(comp_sum_parity_localcfg->write_key,
                                                        "sum parity",
                                                        "Inf");
                break;
            }

            default: {
                comp_sum_parity_localcfg->storage_write(comp_sum_parity_localcfg->write_key,
                                                        "parity",
                                                        "error");
            }
            }
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_sum_parity_result_t *comp_sum_parity_result(void)
{
    const comp_sum_parity_result_t *ret_val = NULL;

    if (comp_sum_parity_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_sum_parity_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_sum_parity_result_t *)&comp_sum_parity_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/**
 * \brief Apply a 90deg rotation to the input parity.
 *
 *
 * \param parity An input parity
 * \return The translated parity
 */
STATIC_INLINE comp_sum_parity_parity_e comp_sum_parity_rotate(comp_sum_parity_parity_e parity)
{
    switch (parity)
    {
    case COMP_SUM_PARITY_PAR_CHI: {
        return COMP_SUM_PARITY_PAR_CHI;
    }

    case COMP_SUM_PARITY_PAR_ZERO: {
        return COMP_SUM_PARITY_PAR_INF;
    }

    case COMP_SUM_PARITY_PAR_INF: {
        return COMP_SUM_PARITY_PAR_ZERO;
    }

    default: {
        break;
    }
    }
    return COMP_SUM_PARITY_PAR_UNINIT;
}

/**
 * \brief Sum (horizontal) two parities.
 *
 * Sum two parities with a tangle algebraic $+$.
 *
 * $$a+b$$
 *
 * Additionally, add to the component sum where needed.
 *
 * \param parity_a Left side parity.
 * \param parity_b Right side parity.
 * \return Resultant tangle.
 */
STATIC_INLINE comp_sum_parity_parity_e comp_sum_parity_sum(comp_sum_parity_parity_e parity_a,
                                                           comp_sum_parity_parity_e parity_b)
{
    switch (parity_a)
    {
    case COMP_SUM_PARITY_PAR_CHI: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            return COMP_SUM_PARITY_PAR_ZERO;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            return COMP_SUM_PARITY_PAR_CHI;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            return COMP_SUM_PARITY_PAR_INF;
        }

        default: {
            break;
        }
        }
        return COMP_SUM_PARITY_PAR_UNINIT;
    }

    case COMP_SUM_PARITY_PAR_ZERO: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            return COMP_SUM_PARITY_PAR_CHI;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            return COMP_SUM_PARITY_PAR_ZERO;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            return COMP_SUM_PARITY_PAR_INF;
        }

        default: {
            break;
        }
        }
        return COMP_SUM_PARITY_PAR_UNINIT;
    }

    case COMP_SUM_PARITY_PAR_INF: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            return COMP_SUM_PARITY_PAR_INF;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            return COMP_SUM_PARITY_PAR_INF;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            comp_sum_parity_localrestult.component_count++;
            return COMP_SUM_PARITY_PAR_INF;
        }

        default: {
            break;
        }
        }
        return COMP_SUM_PARITY_PAR_UNINIT;
    }

    default: {
        break;
    }
    }
    return COMP_SUM_PARITY_PAR_UNINIT;
}
