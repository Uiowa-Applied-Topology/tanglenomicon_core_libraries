/**
 *  \file comp_i2pp_buf_size.c
 *
 *  \brief A component to compute the buffer seize needed to turn a ITT into a PL path.
 *
 *
 *  \author Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_i2pp_buf_size.h"
#include "computation_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/**
 * \brief The maximum stack size for walking the tree.
 *
 */
#define COMP_W2PP_BUF_SIZE_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/**
 * \brief The local configuration of the component.
 *
 */
static comp_i2pp_buf_size_config_t *comp_i2pp_buf_size_localcfg = NULL;

/**
 * \brief The local result of the component.
 *
 */
static comp_i2pp_buf_size_result_t comp_i2pp_buf_size_localrestult;

/**
 * \brief The local computation status of the component.
 *
 */
static bool comp_i2pp_buf_size_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

STATIC_INLINE_UINT8 comp_i2pp_buf_size_walk_tree(void);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_i2pp_buf_size_config(comp_i2pp_buf_size_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_i2pp_buf_size_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_W2PP_BUF_SIZE_CONFIG_IS_NULL;
    } /*Ensure the ITT is not NULL.*/
    else if (config_arg->itt == NULL)
    {
        ret_val |= COMP_W2PP_BUF_SIZE_CONFIG_PARAM;
    }
    else
    {
        /* Set the config. */
        comp_i2pp_buf_size_localcfg = config_arg;

        /* Clear the return value*/
        comp_i2pp_buf_size_localrestult.buff_size = 0x0u;

        /*clear the executed status*/
        comp_i2pp_buf_size_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_i2pp_buf_size_compute(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_i2pp_buf_size_localcfg == NULL)
    {
        ret_val |= COMP_W2PP_BUF_SIZE_COMPUTE_CFG_ERROR;
    }
    /*Ensure not previously executed.*/
    else if (comp_i2pp_buf_size_executed != false)
    {
        ret_val |= COMP_W2PP_BUF_SIZE_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        /* Recursively identify parity of a the tree */
        ret_val = comp_i2pp_buf_size_walk_tree();
        comp_i2pp_buf_size_executed = true;

        /* Print results if requested. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (NULL != comp_i2pp_buf_size_localcfg->storage_write))
        {
            char local_str[30] = { '\0' };
            char result_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };

            (void)note_wptt_encode(*comp_i2pp_buf_size_localcfg->itt,
                                   result_str,
                                   NOTE_WPTT_MAX_STR_LEN);

            sprintf(local_str, "%llu",
                    (long long unsigned int)comp_i2pp_buf_size_localrestult.buff_size);

            comp_i2pp_buf_size_localcfg->storage_write(result_str,
                                                       "buffer_size",
                                                       local_str);
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_i2pp_buf_size_result_t *comp_i2pp_buf_size_result(void)
{
    const comp_i2pp_buf_size_result_t *ret_val = NULL;

    if (comp_i2pp_buf_size_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_i2pp_buf_size_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_i2pp_buf_size_result_t *)&comp_i2pp_buf_size_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/**
 * \brief Walk the tree and compute buffer requirements.
 *
 * For each vertex compute accumulate vertex count and sum of weights. Recuse down children and
 *
 * \return A success value.
 */
STATIC_INLINE_UINT8 comp_i2pp_buf_size_walk_tree(void)
{
    const note_wptt_t *tree    = comp_i2pp_buf_size_localcfg->itt;
    uint8_t            ret_val = COMP_DEFS_COMPUTE_SUCCESS;

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    note_wptt_node_t *stack[COMP_W2PP_BUF_SIZE_STACK_SIZE];
    size_t            childidx_stack[COMP_W2PP_BUF_SIZE_STACK_SIZE];
    size_t            stack_count  = 1;
    uint64_t          vertex_count = 1;
    uint64_t          weight_sum   = 0;

    memset(childidx_stack, 0, COMP_W2PP_BUF_SIZE_STACK_SIZE * sizeof(size_t));
    for (size_t i = 0; i < COMP_W2PP_BUF_SIZE_STACK_SIZE; i++)
    {
        stack[i] = NULL;
    }

    /* Clear the buffer. */
    comp_i2pp_buf_size_localrestult.buff_size = 0;



    /* Init the stack with the root and first child */
    stack[stack_count - 1] = tree->root;

    /* While:
     * - The computation hasn't failed
     * - The stack is not empty
     */
    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) && (0 != stack_count))
    {
        note_wptt_node_t *active_vertex = stack[stack_count - 1];

        if (0u == active_vertex->weights[childidx_stack[stack_count - 1]])
        {
            if (0u == active_vertex->number_of_children)
            {
                /*If the current weight is zero add one to the sum.*/
                weight_sum += 1u;
            }
        }
        else
        {
            /*If the current weight is NOT zero add the weight to the sum.*/
            weight_sum += abs(active_vertex->weights[childidx_stack[stack_count - 1]]);
        }

        /* Iterative tree walk logic */
        if (active_vertex->number_of_children <=
            childidx_stack[stack_count - 1])
        {
            /*Pop stack*/
            stack_count--;
        }
        else
        {
            size_t child_idx = childidx_stack[stack_count - 1];
            /*Push child to stack*/
            childidx_stack[stack_count - 1]++;
            if (stack_count < COMP_W2PP_BUF_SIZE_STACK_SIZE)
            {
                /*Add a new vertex to the count*/
                vertex_count++;
                stack_count++;
                stack[stack_count - 1] =
                    active_vertex->children[child_idx];
                childidx_stack[stack_count - 1] = 0;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_W2PP_BUF_SIZE_COMPUTE_STACK_ERROR);
            }
        }
    }

    /* Combine the vertex count and weight count into a buffer size. */
    comp_i2pp_buf_size_localrestult.buff_size = (10 * vertex_count) + (4 * weight_sum) - 4;

    return ret_val;
}
