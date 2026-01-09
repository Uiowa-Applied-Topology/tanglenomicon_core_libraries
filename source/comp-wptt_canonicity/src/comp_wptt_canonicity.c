/*!
 *  @file comp_wptt_canonicity.c
 *
 *  @brief  A module for computing the canonicity of a WPTT
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_wptt_canonicity.h"
#include "bits/stdint-uintn.h"
#include "comp_wptt_vertex_canonicity.h"
#include "computation_defs.h"
#include "notation_defs.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

#define COMP_WPTT_CANON_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree();

STATIC_INLINE comp_wptt_vert_canon_positivity_e comp_wptt_vert_canon_convert_pos(
    comp_wptt_cononicity_positivity_e pos);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/**
 * @brief File scoped variable for storing result of the previous computation.
 */
static comp_wptt_canonicity_result_t comp_wptt_canonicity_localrestult;

/**
 * @brief File scoped variable for storing the execution state of the module.
 */
static bool comp_wptt_canonicity_executed = true;

/**
 * @brief File scoped variable for storing the configuration of the next run.
 */
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
    if (NULL == config_arg)
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_CONFIG_IS_NULL);
    }
    else if (COMP_WPTT_CANON_POS_UNINIT == config_arg->positivity)
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_CONFIG_POS_ERROR);
    }
    else if (NULL == config_arg->wptt)
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_CONFIG_TREE_ERROR);
    }
    else
    {
        /* Set the config. */
        comp_wptt_canonicity_localcfg = config_arg;

        /* Clear the return value*/
        comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANON_CAN_UNINIT;

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
    if (NULL == comp_wptt_canonicity_localcfg)
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_COMPUTE_CFG_ERROR);
    }
    /*Ensure not previously executed.*/
    else if (false != comp_wptt_canonicity_executed)
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_COMPUTE_ALREADY_COMPUTED);
    }
    else
    {
        comp_wptt_canonicity_executed = true;
        ret_val  = COMP_DEFS_COMPUTE_SUCCESS;
        ret_val |= comp_wptt_canonicity_walk_tree();
        if (COMP_DEFS_COMPUTE_SUCCESS == ret_val)
        {
            if (NULL != comp_wptt_canonicity_localcfg->storage_write)
            {
                uint8_t encode_res;
                char    result_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };
                encode_res = note_wptt_encode(*comp_wptt_canonicity_localcfg->wptt,
                                              result_str,
                                              NOTE_WPTT_MAX_STR_LEN);
                if (encode_res == NOTE_DEFS_ENCODE_SUCCESS)
                {
                    if (COMP_WPTT_CANON_IS_CANONICAL ==
                        comp_wptt_canonicity_localrestult.is_canonical)
                    {
                        comp_wptt_canonicity_localcfg->storage_write(result_str,
                                                                     "is_canon",
                                                                     "true");
                    }
                    else if (COMP_WPTT_CANON_IS_NONCANONICAL ==
                             comp_wptt_canonicity_localrestult.is_canonical)
                    {
                        comp_wptt_canonicity_localcfg->storage_write(result_str,
                                                                     "is_canon",
                                                                     "false");
                    }
                }
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

    if (NULL == comp_wptt_canonicity_localcfg)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (false == comp_wptt_canonicity_executed)
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

/**
 * @brief Convert the enum from the global version to the local vertex version
 *
 * @param pos The positivity condition to check for the whole tree
 * @return The vertex enum representation for the positivity condition.
 */
STATIC_INLINE comp_wptt_vert_canon_positivity_e comp_wptt_vert_canon_convert_pos(
    comp_wptt_cononicity_positivity_e pos)
{
    switch (pos)
    {
    case COMP_WPTT_CANON_POS_POS: {
        return COMP_WPTT_VERT_CANON_POS_POS;
    }

    case COMP_WPTT_CANON_POS_NEG: {
        return COMP_WPTT_VERT_CANON_POS_NEG;
    }

    default: {
        return COMP_WPTT_VERT_CANON_POS_UNINIT;
    }
    }
    return COMP_WPTT_VERT_CANON_POS_UNINIT;
}

/*!
 * @brief Walk the input tree and determine the canonicity of each vertex.
 *
 * @param tree The tree to walk.
 * @return A status indicator for the function.
 */
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree()
{
    const note_wptt_t *tree     = comp_wptt_canonicity_localcfg->wptt;
    uint8_t            ret_val  = COMP_DEFS_COMPUTE_SUCCESS;
    uint8_t            vert_ret = COMP_DEFS_CONFIG_SUCCESS;
    comp_wptt_vert_canon_positivity_e positivity =
        comp_wptt_vert_canon_convert_pos(comp_wptt_canonicity_localcfg->positivity);

    comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANON_IS_CANONICAL;


    comp_wptt_vert_canon_config_t vrt_cfg = { NULL,
                                              NULL,
                                              tree->root,
                                              NULL,
                                              false,
                                              positivity };

    vert_ret |= comp_wptt_vert_canon_config(&vrt_cfg);
    if (COMP_DEFS_CONFIG_SUCCESS == vert_ret)
    {
        vert_ret  = COMP_DEFS_COMPUTE_SUCCESS;
        vert_ret |= comp_wptt_vert_canon_compute();

        if (COMP_DEFS_COMPUTE_SUCCESS == vert_ret)
        {
            const comp_wptt_vert_canon_result_t *vrt_result = comp_wptt_vert_canon_result();
            if (COMP_WPTT_VERT_CANON_IS_CANONICAL == vrt_result->is_canonical)
            {
                if (0 != tree->root->number_of_children)
                {
                    /* We are going to use count instead of index. This helps with intuiting the
                     * state of the stack. The count starts at 1 since the root is going to be added
                     * to the stack before the main loop.
                     */
                    size_t            stack_count = 1;
                    note_wptt_node_t *stack[COMP_WPTT_CANON_STACK_SIZE]          = { NULL };
                    size_t            childidx_stack[COMP_WPTT_CANON_STACK_SIZE] = { 0 };

                    /* Init the stack with the root and first child */
                    stack[stack_count - 1] = tree->root;
                    stack_count++;
                    stack[stack_count - 1]          = tree->root->children[0];
                    childidx_stack[stack_count - 1] = 0;

                    /* While:
                     * - The computation hasn't failed
                     * - The determination isn't noncanonical (this should never happen but it's
                     *safer to add the condition)
                     * - The stack is not empty
                     */
                    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
                           (COMP_WPTT_CANON_IS_NONCANONICAL !=
                            comp_wptt_canonicity_localrestult.is_canonical) &&
                           (0 != stack_count))
                    {
                        note_wptt_node_t *active_vertex = stack[stack_count - 1];
                        /* Ignoring the root vertex which we already checked.*/
                        if (2 <= stack_count)
                        {
                            vrt_cfg.vertex = active_vertex;
                            vrt_cfg.parent = stack[stack_count - 2];

                            /* If we are the child of the root */
                            if (2 == stack_count)
                            {
                                vrt_cfg.parent_is_root = true;
                            }
                            else
                            {
                                vrt_cfg.parent_is_root = false;
                            }

                            /* Complete the computation of the vertex canonicity for the current
                             * stack state.
                             */
                            vert_ret  = COMP_DEFS_CONFIG_SUCCESS;
                            vert_ret |= comp_wptt_vert_canon_config(&vrt_cfg);
                            if (COMP_DEFS_CONFIG_SUCCESS == vert_ret)
                            {
                                vert_ret  = COMP_DEFS_COMPUTE_SUCCESS;
                                vert_ret |= comp_wptt_vert_canon_compute();

                                if (COMP_DEFS_COMPUTE_SUCCESS == vert_ret)
                                {
                                    vrt_result = comp_wptt_vert_canon_result();
                                    if (COMP_WPTT_VERT_CANON_IS_NONCANONICAL ==
                                        vrt_result->is_canonical)
                                    {
                                        comp_wptt_canonicity_localrestult.is_canonical =
                                            COMP_WPTT_CANON_IS_NONCANONICAL;
                                        break;
                                    }
                                }
                                else
                                {
                                    ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                                                COMP_WPTT_CANON_COMPUTE_VERTCOMP_ERROR);
                                }
                            }
                            else
                            {
                                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                                            COMP_WPTT_CANON_COMPUTE_VERTCOMP_ERROR);
                            }
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
                            if (stack_count < COMP_WPTT_CANON_STACK_SIZE)
                            {
                                stack_count++;
                                stack[stack_count - 1] =
                                    active_vertex->children[child_idx];
                                childidx_stack[stack_count - 1] = 0;
                            }
                            else
                            {
                                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                                            COMP_WPTT_CANON_COMPUTE_STACK_ERROR);
                            }
                        }
                    }
                }
            }
            else
            {
                comp_wptt_canonicity_localrestult.is_canonical =
                    COMP_WPTT_CANON_IS_NONCANONICAL;
            }
        }
        else
        {
            ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                        COMP_WPTT_CANON_COMPUTE_VERTCOMP_ERROR);
        }
    }
    else
    {
        ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                    COMP_WPTT_CANON_COMPUTE_VERTCOMP_ERROR);
    }


    return ret_val;
}
