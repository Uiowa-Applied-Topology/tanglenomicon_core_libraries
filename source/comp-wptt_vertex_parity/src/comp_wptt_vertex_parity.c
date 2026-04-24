/**
 *  \file comp_wptt_vertex_parity.c
 *
 *  \brief A module for computing the parity of a vertex in a WPTT.
 *
 *
 *  \author Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "notation_wptt.h"
#include "tang_defs.h"
#include "comp_wptt_vertex_parity.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "comp_sum_parity.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/**
 * \brief The stack size of the parity computation.
 *
 */
#define COMP_WPTT_VERT_PARITY_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/**
 * \brief The local configuration of the WPTT vertex parity.
 *
 */
static comp_wptt_vertex_parity_config_t *comp_wptt_vertex_parity_localcfg = NULL;

/**
 * \brief The local result of the WPTT vertex parity.
 *
 */
static comp_wptt_vertex_parity_result_t comp_wptt_vertex_parity_localresult = {
    .parity          = COMP_SUM_PARITY_PAR_UNINIT,
    .component_count = 0
};

/**
 * \brief The local computation status of the WPTT vertex parity module.
 *
 */
static bool comp_wptt_vertex_parity_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_weight(int16_t weight);
STATIC_INLINE_UINT8 comp_wptt_parity_walk_tree(void);
STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_rotate(
    comp_sum_parity_parity_e parity);
STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_sum(
    comp_sum_parity_parity_e parity_a,
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
uint8_t comp_wptt_vertex_parity_config(comp_wptt_vertex_parity_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_wptt_vertex_parity_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (NULL == config_arg)
    {
        ret_val |= COMP_WPTT_VERT_PARITY_CONFIG_IS_NULL;
    } /*Ensure the wptt is not empty.*/
    else if (NULL == config_arg->vertex)
    {
        ret_val |= COMP_WPTT_VERT_PARITY_CONFIG_PARAM;
    }
    else
    {
        /* Set the config. */
        comp_wptt_vertex_parity_localcfg = config_arg;

        /* Clear the return value*/
        comp_wptt_vertex_parity_localresult.parity          = COMP_SUM_PARITY_PAR_UNINIT;
        comp_wptt_vertex_parity_localresult.component_count = 0u;

        /*clear the executed status*/
        comp_wptt_vertex_parity_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_wptt_vertex_parity_compute(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_wptt_vertex_parity_localcfg == NULL)
    {
        ret_val |= COMP_WPTT_VERT_PARITY_COMPUTE_CFG_ERROR;
    }
    /*Ensure not previously executed.*/
    else if (comp_wptt_vertex_parity_executed != false)
    {
        ret_val |= COMP_WPTT_VERT_PARITY_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        /* Recursively identify parity of a the tree */
        ret_val = comp_wptt_parity_walk_tree();
        comp_wptt_vertex_parity_executed = true;

        /* Print results if requested. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (NULL != comp_wptt_vertex_parity_localcfg->storage_write))
        {
            char local_str[10] = { '\0' };
            char result_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };

            if (NULL != comp_wptt_vertex_parity_localcfg->wptt)
            {
                (void)note_wptt_encode(*comp_wptt_vertex_parity_localcfg->wptt,
                                       result_str,
                                       NOTE_WPTT_MAX_STR_LEN);
            }

            sprintf(local_str, "%u", comp_wptt_vertex_parity_localresult.component_count);

            comp_wptt_vertex_parity_localcfg->storage_write(result_str,
                                                            "parity_components",
                                                            local_str);
            switch (comp_wptt_vertex_parity_localresult.parity)
            {
            case COMP_SUM_PARITY_PAR_CHI: {
                comp_wptt_vertex_parity_localcfg->storage_write(result_str,
                                                                "parity",
                                                                "X");
                break;
            }

            case COMP_SUM_PARITY_PAR_ZERO: {
                comp_wptt_vertex_parity_localcfg->storage_write(result_str,
                                                                "parity",
                                                                "0");
                break;
            }

            case COMP_SUM_PARITY_PAR_INF: {
                comp_wptt_vertex_parity_localcfg->storage_write(result_str,
                                                                "parity",
                                                                "Inf");
                break;
            }

            default: {
                comp_wptt_vertex_parity_localcfg->storage_write(result_str,
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
const comp_wptt_vertex_parity_result_t *comp_wptt_vertex_parity_result(void)
{
    const comp_wptt_vertex_parity_result_t *ret_val = NULL;

    if (comp_wptt_vertex_parity_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_wptt_vertex_parity_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_wptt_vertex_parity_result_t *)&comp_wptt_vertex_parity_localresult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/**
 * \brief Compute the parity of a given weight.
 *
 * Bin integer weights into parity based on even/odd class.
 *
 * \param weight An input weight.
 * \return The parity of the integral tangle of weight crossings.
 */
STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_weight(int16_t weight)
{
    comp_sum_parity_parity_e retval = COMP_SUM_PARITY_PAR_UNINIT;

    if (0 == weight % 2)
    {
        retval = COMP_SUM_PARITY_PAR_ZERO;
    }
    else
    {
        retval = COMP_SUM_PARITY_PAR_CHI;
    }
    return retval;
}

/**
 * \brief Walk the tree and compute parity.
 *
 * For each vertex compute its parity. Recuse down children and repeat. Rotate children before
 *summing with running value.
 *
 * \return A success value.
 */
STATIC_INLINE_UINT8 comp_wptt_parity_walk_tree(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    size_t stack_count = 1;
    const note_wptt_node_t *stack[COMP_WPTT_VERT_PARITY_STACK_SIZE]         = { NULL };
    size_t childidx_stack[COMP_WPTT_VERT_PARITY_STACK_SIZE]                 = { 0 };
    comp_sum_parity_parity_e parity_stack[COMP_WPTT_VERT_PARITY_STACK_SIZE] =
    { COMP_SUM_PARITY_PAR_ZERO };

    stack[stack_count - 1] = comp_wptt_vertex_parity_localcfg->vertex;

    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) && (stack_count != 0))
    {
        const note_wptt_node_t *active_vertex = stack[stack_count - 1];

        /* Add the left most unprocessed weight to the running sum. */
        parity_stack[stack_count - 1] = comp_wptt_vertex_parity_sum(
            parity_stack[stack_count - 1],
            comp_wptt_vertex_parity_weight(active_vertex->weights[
                                               childidx_stack[stack_count - 1]]));

        if (active_vertex->number_of_children <= childidx_stack[stack_count - 1])
        {
            /*Pop stack*/
            stack_count--;

            /* When the stack is not empty add the result of the last child to the running sum. */
            if (0 < stack_count)
            {
                parity_stack[stack_count - 1] =
                    comp_wptt_vertex_parity_sum(parity_stack[stack_count - 1],
                                                comp_wptt_vertex_parity_rotate(
                                                    parity_stack[stack_count]));
            }
        }
        else
        {
            size_t child_idx = childidx_stack[stack_count - 1];
            /*Push child to stack*/
            childidx_stack[stack_count - 1]++;
            if (stack_count < COMP_WPTT_VERT_PARITY_STACK_SIZE)
            {
                stack_count++;
                stack[stack_count - 1]          = active_vertex->children[child_idx];
                childidx_stack[stack_count - 1] = 0;
                /* Set the parity of the next sub-tangle to 0. */
                parity_stack[stack_count - 1] = COMP_SUM_PARITY_PAR_ZERO;
            }
            else
            {
                ret_val = COMP_DEFS_COMPUTE_FAIL;    /*@@@TODO: Add special handling*/
            }
        }
    }
    /* Set the computed parity to the result. */
    comp_wptt_vertex_parity_localresult.parity = parity_stack[0];
    return ret_val;
}

STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_sum(
    comp_sum_parity_parity_e parity_a,
    comp_sum_parity_parity_e parity_b)
{
    comp_sum_parity_parity_e ret_val = COMP_SUM_PARITY_PAR_UNINIT;
    comp_sum_parity_config_t psg     = { .storage_write = NULL,
                                         .write_key     = NULL,
                                         .tangleA       = parity_a,
                                         .tangleB       = parity_b,
                                         .op            = COMP_SUM_PARITY_OP_PLUS };
    uint8_t ps_ret = comp_sum_parity_config(&psg);

    if (COMP_DEFS_CONFIG_SUCCESS == ps_ret)
    {
        ps_ret = comp_sum_parity_compute();
        if (COMP_DEFS_COMPUTE_SUCCESS == ps_ret)
        {
            const comp_sum_parity_result_t *res = comp_sum_parity_result();
            if (NULL != res)
            {
                ret_val = res->parity;
                comp_wptt_vertex_parity_localresult.component_count += res->component_count;
            }
        }
    }
    return ret_val;
}

/**
 * \brief Apply a 90deg rotation to the input parity.
 *
 *
 * \param parity An input parity
 * \return The translated parity
 */
STATIC_INLINE comp_sum_parity_parity_e comp_wptt_vertex_parity_rotate(
    comp_sum_parity_parity_e parity)
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
