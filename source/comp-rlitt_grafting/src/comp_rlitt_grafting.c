/*!
 *  @file comp_rlitt_grafting.c
 *
 *  @brief  A rlitt_grafting module
 *
 *
 *  @author    Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_rlitt_grafting.h"
#include "bits/stdint-intn.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief The maximum size of the stack used for walking the trees.
 *
 */
#define COMP_RLITT_GRAFTING_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE_UINT8 comp_rlitt_grafting_copy_tree(const note_wptt_t *tree);
STATIC_INLINE void comp_rlitt_grafting_copy_nodevals(const note_wptt_node_t *src,
                                                     note_wptt_node_t *dest);
STATIC_INLINE_UINT8 comp_rlitt_grafting_graft(note_wptt_node_t *scion);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the rlitt grafting module.
 *
 */
static note_wptt_node_t *comp_rlitt_grafting_localnodes;

/*!
 * @brief The local configuration of the rlitt grafting module.
 *
 */
static size_t comp_rlitt_grafting_nodes_idx = 0;

/*!
 * @brief The local configuration of the rlitt grafting module.
 *
 */
static size_t comp_rlitt_grafting_nodes_count = 0;

/*!
 * @brief The local configuration of the rlitt grafting module.
 *
 */
static comp_rlitt_grafting_config_t *comp_rlitt_grafting_localcfg = NULL;

/*!
 * @brief The local result of the rlitt grafting module.
 *
 */
static comp_rlitt_grafting_result_t comp_rlitt_grafting_localrestult = { NULL };

/*!
 * @brief The local computation status of the rlitt grafting module.
 *
 */
static bool comp_rlitt_grafting_executed = false;
/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_grafting_config(comp_rlitt_grafting_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_rlitt_grafting_localcfg   = NULL;
    comp_rlitt_grafting_localnodes = NULL;
    comp_rlitt_grafting_localrestult.grafted_wptt = NULL;
    comp_rlitt_grafting_nodes_idx   = 0;
    comp_rlitt_grafting_nodes_count = 0;

    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_RLITT_GRAFTING_CONFIG_IS_NULL;
    }
    /*Ensure the rootstock is not empty.*/
    else if (config_arg->rootstock == NULL)
    {
        ret_val |= COMP_RLITT_GRAFTING_CONFIG_ROOTSTOCK;
    }
    /*Ensure the scion is not empty.*/
    else if (config_arg->scion == NULL)
    {
        ret_val |= COMP_RLITT_GRAFTING_CONFIG_SCION;
    }
    /*Ensure the output buffer is not empty.*/
    else if ((config_arg->output_wptt == NULL) ||
             (config_arg->output_wptt->node_buffer->buffer == NULL) ||
             (config_arg->output_wptt->node_buffer->size == 0))
    {
        ret_val |= COMP_RLITT_GRAFTING_CONFIG_BUFFER;
    }
    else
    {
        /* Set the config. */
        comp_rlitt_grafting_localcfg = config_arg;

        /* Set the return value*/
        comp_rlitt_grafting_localnodes =
            comp_rlitt_grafting_localcfg->output_wptt->node_buffer->buffer;
        comp_rlitt_grafting_nodes_idx =
            comp_rlitt_grafting_localcfg->output_wptt->node_buffer->idx;
        comp_rlitt_grafting_nodes_count =
            comp_rlitt_grafting_localcfg->output_wptt->node_buffer->size;
        comp_rlitt_grafting_localrestult.grafted_wptt =
            comp_rlitt_grafting_localcfg->output_wptt;

        /*clear the executed status*/
        comp_rlitt_grafting_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_grafting_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_rlitt_grafting_localcfg == NULL)
    {
        ret_val |= COMP_RLITT_GRAFTING_COMPUTE_CFG_ERROR;
    } /*Ensure not executed.*/
    else if (comp_rlitt_grafting_executed != false)
    {
        ret_val |= COMP_RLITT_GRAFTING_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        comp_rlitt_grafting_executed = true;
        note_wptt_node_t *scion_root = NULL;

        ret_val = COMP_DEFS_COMPUTE_SUCCESS;

        /* Set output data. */
        comp_rlitt_grafting_localrestult.grafted_wptt->root =
            &comp_rlitt_grafting_localnodes[comp_rlitt_grafting_nodes_idx];
        comp_rlitt_grafting_localrestult.grafted_wptt->label =
            comp_rlitt_grafting_localcfg->rootstock->label;
        comp_rlitt_grafting_nodes_idx++;

        /* Copy rootstock into output buffer */
        ret_val |= comp_rlitt_grafting_copy_tree(comp_rlitt_grafting_localcfg->rootstock);

        /* If we have room left in the buffer after our copy we copy the scion. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (comp_rlitt_grafting_localcfg->rlitt_grafting_idx < comp_rlitt_grafting_nodes_idx))
        {
            scion_root = &comp_rlitt_grafting_localnodes[comp_rlitt_grafting_nodes_idx];
            comp_rlitt_grafting_nodes_idx++;

            ret_val |= comp_rlitt_grafting_copy_tree(comp_rlitt_grafting_localcfg->scion);
            ret_val |= comp_rlitt_grafting_graft(scion_root);


            /* write to storage interface */
            if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
                (comp_rlitt_grafting_localcfg->storage_write != NULL))
            {
                uint8_t write_retval = NOTE_DEFS_ENCODE_SUCCESS;
                char    rootstock_str[NOTE_WPTT_MAX_STR_LEN] = "";
                char    scion_str[NOTE_WPTT_MAX_STR_LEN]     = "";
                char    result_str[NOTE_WPTT_MAX_STR_LEN]    = "";
                write_retval |= note_wptt_encode(*comp_rlitt_grafting_localcfg->rootstock,
                                                 rootstock_str,
                                                 NOTE_WPTT_MAX_STR_LEN);
                write_retval |= note_wptt_encode(*comp_rlitt_grafting_localcfg->scion,
                                                 scion_str,
                                                 NOTE_WPTT_MAX_STR_LEN);
                write_retval |= note_wptt_encode(*comp_rlitt_grafting_localrestult.grafted_wptt,
                                                 result_str,
                                                 NOTE_WPTT_MAX_STR_LEN);
                if (write_retval == NOTE_DEFS_ENCODE_SUCCESS)
                {
                    comp_rlitt_grafting_localcfg->storage_write(result_str,
                                                                "rootstock",
                                                                rootstock_str);
                    comp_rlitt_grafting_localcfg->storage_write(result_str,
                                                                "scion",
                                                                scion_str);
                }
                else
                {
                    ret_val |= COMP_DEFS_COMPUTE_FAIL;
                }
            }
        }
        else
        {
            ret_val |= COMP_DEFS_COMPUTE_FAIL;
        }
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_rlitt_grafting_result_t *comp_rlitt_grafting_result()
{
    const comp_rlitt_grafting_result_t *ret_val = NULL;

    if (comp_rlitt_grafting_localcfg == NULL)
    {
        ret_val = NULL;
    }
    /*Ensure previously executed.*/
    else if (comp_rlitt_grafting_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_rlitt_grafting_result_t *)&comp_rlitt_grafting_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Copies a given tree into the output buffer.
 *
 * @param tree The tree to copy into the output buffer.
 * @return A flag indicating success of the copy.
 */
STATIC_INLINE_UINT8 comp_rlitt_grafting_copy_tree(const note_wptt_t *tree)
{
    uint8_t           ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    note_wptt_node_t *old_stack[COMP_RLITT_GRAFTING_STACK_SIZE]      = { NULL };
    note_wptt_node_t *new_stack[COMP_RLITT_GRAFTING_STACK_SIZE]      = { NULL };
    size_t            childidx_stack[COMP_RLITT_GRAFTING_STACK_SIZE] = { 0 };

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    size_t stack_count = 1;

    old_stack[stack_count - 1] = tree->root;
    new_stack[stack_count - 1] = &comp_rlitt_grafting_localnodes[comp_rlitt_grafting_nodes_idx - 1];
    comp_rlitt_grafting_copy_nodevals(old_stack[stack_count - 1], new_stack[stack_count - 1]);

    /* While stack is not empty. */
    while (stack_count != 0)
    {
        note_wptt_node_t *active_node_p = old_stack[stack_count - 1];

        /* Have all the children of the active vertex been exhausted?*/
        if (active_node_p->number_of_children <= childidx_stack[stack_count - 1])
        {
            /*Pop stack*/
            stack_count--;
        }
        else
        {
            note_wptt_node_t *newchild_p = NULL;
            size_t            child_idx  = childidx_stack[stack_count - 1];

            comp_rlitt_grafting_nodes_idx++;
            newchild_p =
                &comp_rlitt_grafting_localnodes[comp_rlitt_grafting_nodes_idx - 1];
            new_stack[stack_count - 1]->children[child_idx] = newchild_p;

            /* Push child onto stack. */
            childidx_stack[stack_count - 1]++;
            if (stack_count < COMP_RLITT_GRAFTING_STACK_SIZE)
            {
                stack_count++;
                old_stack[stack_count - 1] = active_node_p->children[child_idx];
                new_stack[stack_count - 1] = newchild_p;
                comp_rlitt_grafting_copy_nodevals(old_stack[stack_count - 1],
                                                  new_stack[stack_count - 1]);
                childidx_stack[stack_count - 1] = 0;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_RLITT_GRAFTING_COMPUTE_COPYERROR);
                break;
            }
        }
    }

    return ret_val;
}

/*!
 * @brief Copies values of a vertex to a new vertex.
 *
 * @param src The source vertex.
 * @param dest The destination vertex.
 */
STATIC_INLINE void comp_rlitt_grafting_copy_nodevals(const note_wptt_node_t *src,
                                                     note_wptt_node_t *dest)
{
    size_t i = 0;

    for (i = 0; i < src->number_of_children; i++)
    {
        dest->weights[i] = src->weights[i];
    }
    dest->weights[i] = src->weights[i];

    dest->number_of_children = src->number_of_children;
    dest->number_of_rings    = src->number_of_rings;
    dest->order = src->order;
}

/*!
 * @brief Graft a scion onto the idx element of the rootstock.
 *
 * We copied the rootstock into a new buffer so that buffer is in index order. We can directly
 *access the ith element for grafting.
 *
 * @param scion The scion for processing.
 * @return A status indicator for the operation
 */
STATIC_INLINE_UINT8 comp_rlitt_grafting_graft(note_wptt_node_t *scion)
{
    uint8_t retval = COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                      COMP_RLITT_GRAFTING_COMPUTE_GRAFTING_RLITT);
    size_t            idx            = comp_rlitt_grafting_localcfg->rlitt_grafting_idx;
    note_wptt_node_t *rootstock_node = &comp_rlitt_grafting_localnodes[idx];

    /* If there is room for a new child */
    if (rootstock_node->number_of_children < NOTE_WPTT_DECODE_MAX_CHILDREN - 1)
    {
        /* Start shifting the weights */
        int8_t weight_to_move = rootstock_node->weights[rootstock_node->number_of_children];
        rootstock_node->weights[rootstock_node->number_of_children] = 0;

        /* Add the child */
        rootstock_node->children[rootstock_node->number_of_children] = scion;
        rootstock_node->number_of_children++;

        /* Finish shifting the weights */
        rootstock_node->weights[rootstock_node->number_of_children] = weight_to_move;
        retval = COMP_DEFS_COMPUTE_SUCCESS;
    }
    return retval;
}
