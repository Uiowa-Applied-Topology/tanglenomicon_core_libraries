/*!
 *  @file comp_rlitt_positivity.c
 *
 *  @brief  A rlitt_positivity module
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_rlitt_positivity.h"
#include "bits/stdint-uintn.h"
#include "computation_defs.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

#define COMP_RLITT_POSITIVITY_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the RLITT positivity computation module.
 *
 */
static comp_rlitt_positivity_config_t *comp_rlitt_positivity_localcfg = NULL;

/*!
 * @brief The local result of the RLITT positivity computation module.
 *
 */
static comp_rlitt_positivity_result_t comp_rlitt_positivity_localrestult = {};

/*!
 * @brief The local computation status of the RLITT positivity computation module.
 *
 */
static bool comp_rlitt_positivity_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE_UINT8 comp_rlitt_positivity_walk_tree(const note_wptt_t *tree);

STATIC_INLINE void comp_rlitt_positivity_proc_leaf(int8_t weight);

STATIC_INLINE void comp_rlitt_positivity_proc_internal(size_t stick_length,
                                                       bool stick_has_p2,
                                                       bool stick_has_m2);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_positivity_config(comp_rlitt_positivity_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_rlitt_positivity_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_RLITT_POSITIVITY_CONFIG_IS_NULL;
    } /*Ensure the tv is not empty.*/
    else if (config_arg->wptt == NULL)
    {
        ret_val |= COMP_RLITT_POSITIVITY_CONFIG_NULLTREE;
    }
    else
    {
        /* Set the config. */
        comp_rlitt_positivity_localcfg = config_arg;

        /* Clear the return value*/
        comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_UNINIT;

        /*clear the executed status*/
        comp_rlitt_positivity_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_positivity_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_rlitt_positivity_localcfg == NULL)
    {
        ret_val |= COMP_RLITT_POSITIVITY_COMPUTE_CFG_ERROR;
    } /*Ensure not previously executed.*/
    else if (comp_rlitt_positivity_executed != false)
    {
        ret_val |= COMP_RLITT_POSITIVITY_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        ret_val  = COMP_DEFS_COMPUTE_SUCCESS;
        ret_val |= comp_rlitt_positivity_walk_tree(comp_rlitt_positivity_localcfg->wptt);
        comp_rlitt_positivity_executed = true;

        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (comp_rlitt_positivity_localcfg->storage_write != NULL))
        {
            uint8_t write_retval = NOTE_DEFS_ENCODE_SUCCESS;
            char    result_str[NOTE_WPTT_MAX_STR_LEN] = "";
            write_retval |= note_wptt_encode(*comp_rlitt_positivity_localcfg->wptt,
                                             result_str,
                                             NOTE_WPTT_MAX_STR_LEN);

            if (write_retval == NOTE_DEFS_ENCODE_SUCCESS)
            {
                switch (comp_rlitt_positivity_localrestult.positivity)
                {
                case COMP_RLITT_POSITIVITY_FLVR_UND:
                    comp_rlitt_positivity_localcfg->storage_write(result_str,
                                                                  "rlitt_positivity",
                                                                  "undefined");
                    break;

                case COMP_RLITT_POSITIVITY_FLVR_POS:
                    comp_rlitt_positivity_localcfg->storage_write(result_str,
                                                                  "rlitt_positivity",
                                                                  "positive");
                    break;

                case COMP_RLITT_POSITIVITY_FLVR_NEG:
                    comp_rlitt_positivity_localcfg->storage_write(result_str,
                                                                  "rlitt_positivity",
                                                                  "negative");
                    break;

                case COMP_RLITT_POSITIVITY_FLVR_NEU:
                    comp_rlitt_positivity_localcfg->storage_write(result_str,
                                                                  "rlitt_positivity",
                                                                  "neutral");
                    break;

                default:
                    ret_val |= COMP_DEFS_COMPUTE_FAIL;
                }
            }
            else
            {
                ret_val |= COMP_DEFS_COMPUTE_FAIL;
            }
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_rlitt_positivity_result_t *comp_rlitt_positivity_result()
{
    const comp_rlitt_positivity_result_t *ret_val = NULL;

    if (comp_rlitt_positivity_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_rlitt_positivity_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_rlitt_positivity_result_t *)&comp_rlitt_positivity_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/


/*!
 * @brief Processes an internal vertex (has parent and children) to determine its positivity.
 *
 * @param stick_length The current length of the stick being traversed
 * @param stick_has_p2 Indicates if the stick being traversed contains a weight of +2.
 * @param stick_has_m2 Indicates if the stick being traversed contains a weight of -2.
 */
STATIC_INLINE void comp_rlitt_positivity_proc_internal(size_t stick_length,
                                                       bool stick_has_p2,
                                                       bool stick_has_m2)
{
    if (1 == stick_length)
    {
        if (true == stick_has_p2)
        {
            if (COMP_RLITT_POSITIVITY_FLVR_NEG != comp_rlitt_positivity_localrestult.positivity)
            {
                comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_POS;
            }
            else
            {
                comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_UND;
            }
        }
        else if (true == stick_has_m2)
        {
            if (COMP_RLITT_POSITIVITY_FLVR_POS != comp_rlitt_positivity_localrestult.positivity)
            {
                comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_NEG;
            }
            else
            {
                comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_UND;
            }
        }
    }
}

/*!
 * @brief Processes a leaf vertex (has parent and no children) to determine its positivity.
 *
 * @param weight The weight of the leaf vertex.
 */
STATIC_INLINE void comp_rlitt_positivity_proc_leaf(int8_t weight)
{
    if (2 == weight)
    {
        if (COMP_RLITT_POSITIVITY_FLVR_NEG != comp_rlitt_positivity_localrestult.positivity)
        {
            comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_POS;
        }
        else
        {
            comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_UND;
        }
    }
    else if (-2 == weight)
    {
        if (COMP_RLITT_POSITIVITY_FLVR_POS != comp_rlitt_positivity_localrestult.positivity)
        {
            comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_NEG;
        }
        else
        {
            comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_UND;
        }
    }
}

/*!
 * @brief Walk the input tree and determine positivity of each vertex.
 *
 * @param tree The tree to walk.
 * @return A status indicator for the function.
 */
STATIC_INLINE_UINT8 comp_rlitt_positivity_walk_tree(const note_wptt_t *tree)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;

    comp_rlitt_positivity_localrestult.positivity = COMP_RLITT_POSITIVITY_FLVR_NEU;

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
        note_wptt_node_t *stack[COMP_RLITT_POSITIVITY_STACK_SIZE]          = { NULL };
        size_t            childidx_stack[COMP_RLITT_POSITIVITY_STACK_SIZE] = { 0 };

        stack[stack_count - 1] = tree->root;

        while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
               (COMP_RLITT_POSITIVITY_FLVR_UND != comp_rlitt_positivity_localrestult.positivity) &&
               (stack_count != 0))
        {
            note_wptt_node_t *active_vertex = stack[stack_count - 1];
            /* Active vertex is a leaf vertex*/
            if ((0 == active_vertex->number_of_children) && (0 == stick_length))
            {
                comp_rlitt_positivity_proc_leaf(active_vertex->weights[0]);
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
                comp_rlitt_positivity_proc_internal(stick_length,
                                                    stick_has_p2,
                                                    stick_has_m2);
                stick_length = 0;
                stick_has_p2 = false;
                stick_has_m2 = false;
            }


            if ((active_vertex->number_of_children <= childidx_stack[stack_count - 1]) &&
                (COMP_RLITT_POSITIVITY_FLVR_UND != comp_rlitt_positivity_localrestult.positivity))
            {
                /*Pop stack*/
                stack_count--;
            }
            else
            {
                size_t child_idx = childidx_stack[stack_count - 1];
                /*Push child to stack*/
                childidx_stack[stack_count - 1]++;
                if (stack_count < COMP_RLITT_POSITIVITY_STACK_SIZE)
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
