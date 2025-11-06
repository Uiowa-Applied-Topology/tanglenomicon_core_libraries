/*!
 *  @file comp_wptt_canonicity.c
 *
 *  @brief  A wptt_canonicity module
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_wptt_canonicity.h"
#include "comp_wptt_vertex_canonicity.h"
#include "computation_defs.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

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
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree();

STATIC_INLINE comp_wptt_vert_canon_positivity_e comp_wptt_vert_canon_convert_pos(
    comp_wptt_cononicity_positivity_e pos);

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
        comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANONICITY_CAN_UNINIT;

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
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;
        comp_wptt_canonicity_walk_tree();
        /*@@@TODO: Implement the computation*/
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

STATIC_INLINE comp_wptt_vert_canon_positivity_e comp_wptt_vert_canon_convert_pos(
    comp_wptt_cononicity_positivity_e pos)
{
    switch (pos)
    {
    case COMP_WPTT_CANON_POS_POS: {
        return COMP_WPTT_VERT_CANON_POS_POS;
    }

    case COMP_WPTT_CANON_POS_NEG: {
        return COMP_WPTT_VERT_CANON_POS_POS;
    }

    default: {
        return COMP_WPTT_VERT_CANON_POS_UNINIT;
    }
    }
    return COMP_WPTT_VERT_CANON_POS_UNINIT;
}

/*!
 * @brief Walk the input tree and determine positivity of each vertex.
 *
 * @param tree The tree to walk.
 * @return A status indicator for the function.
 */
STATIC_INLINE_UINT8 comp_wptt_canonicity_walk_tree()
{
    const note_wptt_t *tree    = comp_wptt_canonicity_localcfg->wptt;
    uint8_t            ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    comp_wptt_vert_canon_positivity_e positivity =
        comp_wptt_vert_canon_convert_pos(comp_wptt_canonicity_localcfg->positivity);

    comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANONICITY_CAN_UNINIT;


    comp_wptt_vert_canon_config_t vrt_cfg = { NULL,
                                              NULL,
                                              tree->root,
                                              NULL,
                                              false,
                                              positivity };

    ret_val |= comp_wptt_vert_canon_config(&vrt_cfg);
    if (COMP_DEFS_CONFIG_SUCCESS == ret_val)
    {
        ret_val |= comp_wptt_vert_canon_compute();

        if (COMP_DEFS_COMPUTE_SUCCESS == ret_val)
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
                    note_wptt_node_t *stack[COMP_WPTT_CANONICITY_STACK_SIZE]          = { NULL };
                    size_t            childidx_stack[COMP_WPTT_CANONICITY_STACK_SIZE] = { 0 };

                    stack[stack_count - 1] = tree->root;
                    stack_count++;
                    stack[stack_count - 1]          = tree->root->children[0];
                    childidx_stack[stack_count - 1] = 0;

                    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
                           (COMP_WPTT_CANONICITY_IS_CANONICAL ==
                            comp_wptt_canonicity_localrestult.is_canonical) &&
                           (stack_count != 0))
                    {
                        note_wptt_node_t *active_vertex = stack[stack_count - 1];

                        vrt_cfg.vertex = active_vertex;
                        vrt_cfg.parent = stack[stack_count - 2];
                        if (2 == stack_count)
                        {
                            vrt_cfg.parent_is_root = true;
                        }
                        else
                        {
                            vrt_cfg.parent_is_root = false;
                        }

                        ret_val |= comp_wptt_vert_canon_config(&vrt_cfg);
                        if (COMP_DEFS_CONFIG_SUCCESS == ret_val)
                        {
                            ret_val |= comp_wptt_vert_canon_compute();

                            if (COMP_DEFS_COMPUTE_SUCCESS == ret_val)
                            {
                                vrt_result = comp_wptt_vert_canon_result();
                                if (COMP_WPTT_VERT_CANON_IS_NONCANONICAL ==
                                    vrt_result->is_canonical)
                                {
                                    comp_wptt_canonicity_localrestult.is_canonical =
                                        COMP_WPTT_CANONICITY_IS_NONCANONICAL;
                                    return COMP_DEFS_COMPUTE_SUCCESS;
                                }
                            }
                        }

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
                            if (stack_count < COMP_WPTT_CANONICITY_STACK_SIZE)
                            {
                                stack_count++;
                                stack[stack_count -
                                      1] = active_vertex->children[child_idx];
                                childidx_stack[stack_count - 1] = 0;
                            }
                            else
                            {
                                ret_val = COMP_DEFS_COMPUTE_FAIL;/*@@@TODO: Add special handling*/
                            }
                        }
                    }
                }
            }
            else
            {
                comp_wptt_canonicity_localrestult.is_canonical =
                    COMP_WPTT_CANONICITY_IS_NONCANONICAL;
                return COMP_DEFS_COMPUTE_SUCCESS;
            }
        }
    }

    comp_wptt_canonicity_localrestult.is_canonical = COMP_WPTT_CANONICITY_IS_CANONICAL;
    return COMP_DEFS_COMPUTE_SUCCESS;
}
