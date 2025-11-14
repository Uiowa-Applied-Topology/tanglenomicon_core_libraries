/*!
 *  @file mut_rlitt_ringshift.c
 *
 *  @brief  A rlitt_ringshift module
 *
 *
 *  @author    Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "mut_rlitt_ringshift.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief Maximum size of the stacks used for tree traversal
 *
 */
#define MUT_RLITT_RINGSHIFT_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE bool mut_rlitt_ringshift_is_ringsubtree(const note_wptt_node_t *node);
STATIC_INLINE int mut_rlitt_ringshift_ringsubtreecmp(const void *node1,
                                                     const void *node2);
STATIC_INLINE void mut_rlitt_ringshift_move_ringsubtrees(note_wptt_node_t *node);
STATIC_INLINE_UINT8 mut_rlitt_ringshift_ringshift_tree(note_wptt_t *tree);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the RLITT ring shift computation module.
 *
 */
static note_wptt_node_t *mut_rlitt_ringshift_localnodes;

/*!
 * @brief The local configuration of the RLITT ring shift computation module.
 *
 */
static size_t mut_rlitt_ringshift_nodes_idx = 0;

/*!
 * @brief The local configuration of the RLITT ring shift computation module.
 *
 */
static size_t mut_rlitt_ringshift_nodes_count = 0;

/*!
 * @brief The local configuration of the RLITT ring shift computation module.
 *
 */
static mut_rlitt_ringshift_config_t *mut_rlitt_ringshift_localcfg = NULL;

/*!
 * @brief The local computation status of the RLITT ring shift computation module.
 *
 */
static bool mut_rlitt_ringshift_executed = false;
/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t mut_rlitt_ringshift_config(mut_rlitt_ringshift_config_t *config_arg)
{
    uint8_t ret_val = MUT_DEFS_CONFIG_FAIL;

    mut_rlitt_ringshift_localcfg    = NULL;
    mut_rlitt_ringshift_localcfg    = NULL;
    mut_rlitt_ringshift_localnodes  = NULL;
    mut_rlitt_ringshift_nodes_idx   = 0;
    mut_rlitt_ringshift_nodes_count = 0;

    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= MUT_RLITT_RINGSHIFT_CONFIG_IS_NULL;
    } /*Ensure the wptt is not empty.*/
    else if (config_arg->wptt == NULL)
    {
        ret_val |= MUT_RLITT_RINGSHIFT_CONFIG_WPTT;
    }
    else
    {
        /* Set the config. */
        mut_rlitt_ringshift_localcfg = config_arg;


        /*clear the executed status*/
        mut_rlitt_ringshift_executed = false;

        ret_val = MUT_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t mut_rlitt_ringshift_mutate()
{
    uint8_t ret_val = MUT_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (mut_rlitt_ringshift_localcfg == NULL)
    {
        ret_val |= MUT_RLITT_RINGSHIFT_COMPUTE_CFG_ERROR;
    } /*Ensure not previously executed.*/
    else if (mut_rlitt_ringshift_executed != false)
    {
        ret_val |= MUT_RLITT_RINGSHIFT_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        ret_val = MUT_DEFS_COMPUTE_SUCCESS;
        mut_rlitt_ringshift_executed = true;
        ret_val |= mut_rlitt_ringshift_ringshift_tree(mut_rlitt_ringshift_localcfg->wptt);
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Walk the input tree.
 *
 * @param tree The input tree.
 * @return
 */
STATIC_INLINE_UINT8 mut_rlitt_ringshift_ringshift_tree(note_wptt_t *tree)
{
    uint8_t           ret_val = MUT_DEFS_COMPUTE_SUCCESS;
    note_wptt_node_t *stack[MUT_RLITT_RINGSHIFT_STACK_SIZE]          = { NULL };
    size_t            childidx_stack[MUT_RLITT_RINGSHIFT_STACK_SIZE] = { 0 };

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    size_t stack_count = 1;

    /* try to shift the root */
    mut_rlitt_ringshift_move_ringsubtrees(tree->root);

    stack[stack_count - 1] = tree->root;
    while (stack_count != 0)
    {
        note_wptt_node_t *active_node_p = stack[stack_count - 1];
        if (active_node_p->number_of_children <= childidx_stack[stack_count - 1])
        {
            /* shift the active vertex. */
            mut_rlitt_ringshift_move_ringsubtrees(active_node_p);
            stack_count--;
        }
        else
        {
            size_t child_idx = childidx_stack[stack_count - 1];
            /*Push child to stack*/
            childidx_stack[stack_count - 1]++;
            stack_count++;
            stack[stack_count - 1]          = active_node_p->children[child_idx];
            childidx_stack[stack_count - 1] = 0;
        }
    }

    return ret_val;
}

/*!
 * @brief Normalize the vertex order to forward.
 *
 * @param node The vertex to reverse.
 */
STATIC_INLINE void mut_rlitt_ringshift_reverse_node(note_wptt_node_t *node)
{
    size_t i = 0;

    for (i = 0; 2 * i < node->number_of_children; i++)
    {
        size_t            back_child_pos  = (node->number_of_children - 1) - i;
        size_t            back_weight_pos = node->number_of_children - i;
        note_wptt_node_t *child           = node->children[i];
        uint8_t           weight          = node->weights[i];

        node->children[i] = node->children[back_child_pos];
        node->children[back_child_pos] = child;

        node->weights[i] = node->weights[back_weight_pos];
        node->weights[back_weight_pos] = weight;
    }
    if (node->order == NOTE_WPTT_ORDER_REVERSE)
    {
        node->order = NOTE_WPTT_ORDER_FORWARD;
    }
    else
    {
        node->order = NOTE_WPTT_ORDER_REVERSE;
    }
}

/*!
 * @brief Identify if the vertex is the root of a $\pm$-ring subtree.
 *
 * @param node the vertex to examine.
 * @return
 */
STATIC_INLINE bool mut_rlitt_ringshift_is_ringsubtree(const note_wptt_node_t *node)
{
    bool ret_val = false;

    if (node->number_of_children == 2)
    {
        if ((node->weights[node->number_of_children] == 1) &&
            (node->children[0]->number_of_children == 0) &&
            (node->children[0]->weights[0] == 2) &&
            (node->children[1]->number_of_children == 0) &&
            (node->children[1]->weights[0] == 2))
        {
            ret_val = true;
        }
        if ((node->weights[node->number_of_children] == -1) &&
            (node->children[0]->number_of_children == 0) &&
            (node->children[0]->weights[0] == -2) &&
            (node->children[1]->number_of_children == 0) &&
            (node->children[1]->weights[0] == -2))
        {
            ret_val = true;
        }
    }
    return ret_val;
}

/*!
 * @brief Compares two vertices and orders them.
 *
 *  The function takes two vertices as input. The two are placed in the following order:
 *
 *  - node1 < node2: When node2 has a ring and node1 does not
 *  - node2 < node1: When node1 has a ring and node2 does not
 *  - node1 = node2: When node1 and node2 both have a ring
 *
 * @param node1 The first node.
 * @param node2 The second vertex.
 * @return An integer -1,0,1 indicating the result of the compare.
 */
STATIC_INLINE int mut_rlitt_ringshift_ringsubtreecmp(const void *node1, const void *node2)
{
    bool node1_ring = mut_rlitt_ringshift_is_ringsubtree(
        *(const note_wptt_node_t **)node1);
    bool node2_ring = mut_rlitt_ringshift_is_ringsubtree(
        *(const note_wptt_node_t **)node2);

    if (node1_ring != node2_ring)
    {
        if (true == node1_ring)
        {
            return 1;
        }
        return -1;
    }
    return 0;
}

/*!
 * @brief Sort the children of a vertex so ring subtrees are at the highest indices.
 *
 * @param node The vertex to sort the children of.
 */
STATIC_INLINE void mut_rlitt_ringshift_move_ringsubtrees(note_wptt_node_t *node)
{
    if (node->number_of_children != 0)
    {
        /* Sort the children of the input vertex. The qsort function swaps in place based on the
         * given compare function. */
        qsort(node->children,
              node->number_of_children,
              sizeof(note_wptt_node_t *),
              mut_rlitt_ringshift_ringsubtreecmp);
    }
}
