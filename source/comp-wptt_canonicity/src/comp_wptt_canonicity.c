/*!
 *  @file comp_wptt_canonicity.c
 *
 *  @brief  A wptt_canonicity module
 *
 *
 *  @author    wptt_canonicity
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_wptt_canonicity.h"
#include "computation_defs.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

#define COMP_WPTT_CANONICITY_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree(const note_wptt_t *tree);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/
static comp_wptt_canonicity_result_t comp_wptt_canonicity_localrestult;
static uint8_t comp_wptt_canonicity_executed = 0;
static comp_wptt_canonicity_config_t *comp_wptt_canonicity_localcfg = NULL;
/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_wptt_canonicity_config(comp_wptt_canonicity_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_wptt_canonicity_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_DEFS_CONFIG_FAIL; /*@@@TODO: Add specific failure*/
    } /*Ensure the wptt is not empty.*/
    else
    {
        /* Set the config. */
        comp_wptt_canonicity_localcfg = config_arg;

        /* Clear the return value*/
        comp_wptt_canonicity_localrestult.is_canon = COMP_WPTT_CANONICITY_CAN_UNINIT;

        /*clear the executed status*/
        comp_wptt_canonicity_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_wptt_canonicity_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_wptt_canonicity_localcfg == NULL)
    {
        ret_val |= COMP_DEFS_COMPUTE_FAIL; /*@@@TODO: Add specific failure*/
    }
    /*Ensure not previously executed.*/
    else if (comp_wptt_canonicity_executed != false)
    {
        ret_val |= COMP_DEFS_COMPUTE_FAIL; /*@@@TODO: Add specific failure*/
    }
    else
    {
        if (NULL != comp_wptt_canonicity_localcfg->storage_write)
        {
            char result_str[NOTE_WPTT_MAX_STR_LEN] = "is_canon";
            if (NULL != comp_wptt_canonicity_localcfg->wptt)
            {
                (void)note_wptt_encode(*comp_wptt_canonicity_localcfg->wptt,
                                       result_str,
                                       NOTE_WPTT_MAX_STR_LEN);
            }

            if (comp_wptt_canonicity_localrestult.is_canonical ==
                COMP_WPTT_CANONICITY_IS_CANONICAL)
            {
                comp_wptt_canonicity_localcfg->storage_write(result_str,
                                                             "is_canon",
                                                             "true");
            }
            else if (comp_wptt_canonicity_localrestult.is_canonical ==
                     COMP_WPTT_CANONICITY_IS_NONCANONICAL
                     )
            {
                comp_wptt_canonicity_localcfg->storage_write(result_str,
                                                             "is_canon",
                                                             "false");
            }
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_wptt_canonicity_result_t *comp_wptt_canonicity_result()
{
    const comp_wptt_canonicity_result_t *ret_val = NULL;

    if (comp_wptt_canonicity_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_wptt_canonicity_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_wptt_canonicity_result_t *)&comp_wptt_canonicity_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Walk the input tree and determine positivity of each vertex.
 *
 * @param tree The tree to walk.
 * @return A status indicator for the function.
 */
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree(const note_wptt_t *tree)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;

    comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANONICITY_CAN_UNINIT;

    if (0 != tree->root->number_of_children)
    {
        /* We are going to use count instead of index. This helps with intuiting the state of the
         * stack. The count starts at 1 since the root is going to be added to the stack before the
         * main loop.
         */
        size_t            stack_count  = 1;
        uint8_t           stick_length = 0u;
        bool              stick_has_p2 = false;
        bool              stick_has_m2 = false;
        note_wptt_node_t *stack[COMP_WPTT_CANONICITY_STACK_SIZE]          = { NULL };
        size_t            childidx_stack[COMP_WPTT_CANONICITY_STACK_SIZE] = { 0 };

        stack[stack_count - 1] = tree->root;

        while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
               (COMP_WPTT_CANONICITY_FLVR_UND != comp_rlitt_positivity_localrestult.positivity) &&
               (stack_count != 0))
        {
            note_wptt_node_t *active_vertex = stack[stack_count - 1];
            /* Active vertex is a leaf vertex*/
            if ((0 == active_vertex->number_of_children) && (0 == stick_length))
            {
                comp_wptt_canonicity_proc_leaf(active_vertex->weights[0]);
            }/* Active vertex is on a stick */
            else if (1 == active_vertex->number_of_children)
            {
                stick_length++;
                if (1 < stack_count)
                {
                    if (2 == active_vertex->weights[1])
                    {
                        stick_has_p2 = true;
                    }
                    else if (-2 == active_vertex->weights[1])
                    {
                        stick_has_m2 = true;
                    }
                }
            }
            else if (1 < active_vertex->number_of_children) /* Otherwise, we are not on a stick */
            {
                comp_wptt_canonicity_proc_internal(stick_length,
                                                   stick_has_p2,
                                                   stick_has_m2);
                stick_length = 0;
                stick_has_p2 = false;
                stick_has_m2 = false;
            }


            if ((active_vertex->number_of_children <= childidx_stack[stack_count - 1]) &&
                (COMP_wptt_canonicity_FLVR_UND != comp_rlitt_positivity_localrestult.positivity))
            {
                /*Pop stack*/
                stack_count--;
            }
            else
            {
                size_t child_idx = childidx_stack[stack_count - 1];
                /*Push child to stack*/
                childidx_stack[stack_count - 1]++;
                if (stack_count < COMP_WPTT_CANONICITY_STACK_SIZE)
                {
                    stack_count++;
                    stack[stack_count - 1]          = active_vertex->children[child_idx];
                    childidx_stack[stack_count - 1] = 0;
                }
                else
                {
                    ret_val = COMP_DEFS_COMPUTE_FAIL;/*@@@TODO: Add special handling*/
                }
            }
        }
    }
    return ret_val;
}
