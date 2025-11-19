/**
 * @file
 * @brief
 */

/*!
 *  @file mut_wptt_f_moves.c
 *
 *  @brief Mutates a tree by one of the $F_i$ moves.
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "mut_wptt_f_moves.h"
#include "mutator_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/**
 * @brief The maximum stack size for the walk function.
 */
#define MUT_WPTT_F_MOVES_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/*!
 * @brief The function pointer type for walk reverse checker callback functions.
 */
typedef bool (*should_reverse_funptr_t)(size_t depth);

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE note_wptt_V4_label_e mut_wptt_f_moves_V4_mult(note_wptt_V4_label_e x,
                                                            note_wptt_V4_label_e y);
STATIC_INLINE_UINT8 mut_wptt_f_moves_F1();
STATIC_INLINE_UINT8 mut_wptt_f_moves_F2();
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3();
STATIC_INLINE_UINT8 mut_wptt_f_moves_walk(note_wptt_node_t *vertex,
                                          should_reverse_funptr_t reverse_checker);
STATIC_INLINE bool mut_wptt_f_moves_revall(size_t depth);
STATIC_INLINE bool mut_wptt_f_moves_revodd(size_t depth);
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3_wrap(size_t target_idx);
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3_nowrap();

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/**
 * @brief Variable indicating if the configuration has been executed against.
 */
static uint8_t was_executed = 0;

/**
 * @brief Variable to store the local configuration to execute against.
 */
static mut_wptt_f_moves_config_t *localcfg = NULL;
/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t mut_wptt_f_moves_config(mut_wptt_f_moves_config_t *config_arg)
{
    uint8_t ret_val = MUT_DEFS_CONFIG_FAIL;

    was_executed = false;
    localcfg     = NULL;

    /*Ensure the cfg is not empty.*/
    if (NULL == config_arg)
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_IS_NULL);
    } /*Ensure the vertex is not empty.*/
    else if (NULL == config_arg->vertex)
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_VERTEX);
    }/*Ensure a move is configured.*/
    else if (MUT_F_MOVE_UNINIT == config_arg->move)
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_MOVE);
    }/*When F_1 is configured ensure the label is configured.*/
    else if ((MUT_F_MOVE_F1 == config_arg->move) &&
             ((NULL == config_arg->V4_label) ||
              (NOTE_WPTT_V4_LABEL_UNINIT == *(config_arg->V4_label))))
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_F1);
    }/*When F_2 is configured ensure the label and eqclass are configured.*/
    else if ((MUT_F_MOVE_F2 == config_arg->move) &&
             ((NULL == config_arg->V4_label) ||
              (NOTE_WPTT_V4_LABEL_UNINIT == *(config_arg->V4_label) ||
               (MUT_F_MOVES_EQCLASS_UNINIT == config_arg->eqclass))))
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_F2);
    }/*When F_3 is configured ensure the direction is configured.*/
    else if ((MUT_F_MOVE_F3 == config_arg->move) &&
             (MUT_F_MOVES_DIR_UNINIT == config_arg->direction))
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_CONFIG_FAIL,
                                   MUT_WPTT_F_MOVES_CONFIG_F3);
    }
    else
    {
        /* Set the config. */
        localcfg = config_arg;

        ret_val = MUT_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t mut_wptt_f_moves_mutate()
{
    uint8_t ret_val = MUT_DEFS_MUTATE_FAIL;

    /*Ensure the local config is not empty.*/
    if (localcfg == NULL)
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_CFG_ERROR);
    } /*Ensure not previously executed.*/
    else if (was_executed != false)
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_ALREADY_COMPUTED);
    }
    else
    {
        ret_val      = MUT_DEFS_MUTATE_SUCCESS;
        was_executed = true;
        switch (localcfg->move)
        {
        case MUT_F_MOVE_F1: {
            ret_val |= mut_wptt_f_moves_F1();
            break;
        }

        case MUT_F_MOVE_F2: {
            ret_val |= mut_wptt_f_moves_F2();
            break;
        }

        case MUT_F_MOVE_F3: {
            ret_val |= mut_wptt_f_moves_F3();
            break;
        }

        default: {
            ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                       MUT_WPTT_F_MOVES_MUTATE_MOVE_CFG);
        }
        }
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/**
 * @brief Apply the $F_1$ move to a WPTT at the given vertex.
 *
 * If the object vertex is not the root the move is mathematically undefined.
 *
 * @return The success flag of the move.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_F1()
{
    uint8_t ret_val = MUT_DEFS_MUTATE_SUCCESS;

    *(localcfg->V4_label) = mut_wptt_f_moves_V4_mult(*(localcfg->V4_label),
                                                     NOTE_WPTT_V4_LABEL_Z);
    ret_val = mut_wptt_f_moves_walk(localcfg->vertex, &mut_wptt_f_moves_revall);
    if (NOTE_WPTT_V4_LABEL_UNINIT == *(localcfg->V4_label))
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_LABEL_ERROR);
    }
    return ret_val;
}

/**
 * @brief Apply the $F_2$ move to a WPTT at the given vertex.
 *
 * If the object vertex is not the root the move is mathematically undefined.
 *
 * @return The success flag of the move.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_F2()
{
    uint8_t ret_val = MUT_DEFS_MUTATE_SUCCESS;


    switch (localcfg->eqclass)
    {
    case MUT_F_MOVES_EQCLASS_SELF: {
        *(localcfg->V4_label) = mut_wptt_f_moves_V4_mult(*(localcfg->V4_label),
                                                         NOTE_WPTT_V4_LABEL_Y);
        ret_val |= mut_wptt_f_moves_walk(localcfg->vertex, &mut_wptt_f_moves_revodd);
        break;
    };

    case MUT_F_MOVES_EQCLASS_CHILD: {
        size_t i;
        *(localcfg->V4_label) = mut_wptt_f_moves_V4_mult(*(localcfg->V4_label),
                                                         NOTE_WPTT_V4_LABEL_X);
        for (i = 0; i < localcfg->vertex->number_of_children; i++)
        {
            ret_val |= mut_wptt_f_moves_walk(localcfg->vertex->children[i],
                                             &mut_wptt_f_moves_revodd);
        }
        break;
    };

    default: {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_MOVE_EQCLASS);
    }
    }

    if (NOTE_WPTT_V4_LABEL_UNINIT == *(localcfg->V4_label))
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_LABEL_ERROR);
    }

    return ret_val;
}

/**
 * @brief Apply the $F_3^\prime$ move to a WPTT at the given vertex.
 *
 * If the move would be applied "upwards" in the tree instead apply $F_3^\prime$ to all siblings in
 *the opposite direction.
 *
 * @return The success flag of the move.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3()
{
    uint8_t      ret_val            = MUT_DEFS_MUTATE_SUCCESS;
    const size_t idx                = localcfg->weight_idx;
    const size_t number_of_children = localcfg->vertex->number_of_children;

    if (idx <= number_of_children)
    {
        if ((0 == idx) &&
            (((MUT_F_MOVES_DIR_BK == localcfg->direction) &&
              (NOTE_WPTT_ORDER_FORWARD == localcfg->vertex->order)) ||
             ((MUT_F_MOVES_DIR_FWD == localcfg->direction) &&
              (NOTE_WPTT_ORDER_REVERSE == localcfg->vertex->order))))
        {
            ret_val |= mut_wptt_f_moves_F3_wrap(number_of_children);
        }
        else if ((number_of_children == idx) &&
                 (((MUT_F_MOVES_DIR_BK == localcfg->direction) &&
                   (NOTE_WPTT_ORDER_REVERSE == localcfg->vertex->order)) ||
                  ((MUT_F_MOVES_DIR_FWD == localcfg->direction) &&
                   (NOTE_WPTT_ORDER_FORWARD == localcfg->vertex->order))))
        {
            ret_val |= mut_wptt_f_moves_F3_wrap(0);
        }
        else
        {
            ret_val |= mut_wptt_f_moves_F3_nowrap();
        }
    }
    else
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_MOVE_F3_ERROR);
    }
    return ret_val;
}

/**
 * @brief Apply $F_3^\prime$ to the object vertex with no wrap around parent.
 *
 * @return Indicate the success of the operation.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3_nowrap()
{
    uint8_t      ret_val    = MUT_DEFS_MUTATE_SUCCESS;
    const size_t idx        = localcfg->weight_idx;
    size_t       target_idx = idx;
    int8_t       weight     = localcfg->vertex->weights[idx];

    if (MUT_F_MOVES_DIR_BK == localcfg->direction)
    {
        if (NOTE_WPTT_ORDER_FORWARD == localcfg->vertex->order)
        {
            target_idx--;
        }
        else
        {
            target_idx++;
        }
    }
    else if (MUT_F_MOVES_DIR_FWD == localcfg->direction)
    {
        if (NOTE_WPTT_ORDER_FORWARD == localcfg->vertex->order)
        {
            target_idx++;
        }
        else
        {
            target_idx--;
        }
    }
    else
    {
        ret_val |= MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                   MUT_WPTT_F_MOVES_MUTATE_MOVE_F3_ERROR);
    }
    localcfg->vertex->weights[target_idx] += weight;
    localcfg->vertex->weights[idx]         = 0;
    if (1 == abs(weight) % 2)
    {
        ret_val |= mut_wptt_f_moves_walk(localcfg->vertex->children[target_idx],
                                         &mut_wptt_f_moves_revodd);
    }
    return ret_val;
}

/**
 * @brief Apply $F_3^\prime$ to the object vertex with wrap around parent.
 *
 * @return Indicate the success of the operation.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_F3_wrap(size_t target_idx)
{
    uint8_t      ret_val            = MUT_DEFS_MUTATE_SUCCESS;
    const size_t idx                = localcfg->weight_idx;
    const size_t number_of_children = localcfg->vertex->number_of_children;
    int8_t       weight             = localcfg->vertex->weights[idx];

    localcfg->vertex->weights[target_idx] += weight;
    localcfg->vertex->weights[idx]         = 0;
    if (1 == abs(weight) % 2)
    {
        size_t i;
        for (i = 0; i < number_of_children; i++)
        {
            ret_val |= mut_wptt_f_moves_walk(localcfg->vertex->children[i],
                                             &mut_wptt_f_moves_revodd);
        }
    }
    return ret_val;
}

/**
 * @brief Walk the tree, reverse the order of the current vertex when reverse_checker() is true.
 *
 * @param vertex The vertex to start the walk at.
 * @param reverse_checker The function to determine if order should be reversed.
 *
 * @return The success flag of the move.
 */
STATIC_INLINE_UINT8 mut_wptt_f_moves_walk(note_wptt_node_t *vertex,
                                          should_reverse_funptr_t reverse_checker)
{
    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    uint8_t           ret_val     = MUT_DEFS_MUTATE_SUCCESS;
    size_t            stack_count = 1;
    note_wptt_node_t *stack[MUT_WPTT_F_MOVES_STACK_SIZE]          = { NULL };
    size_t            childidx_stack[MUT_WPTT_F_MOVES_STACK_SIZE] = { 0 };

    stack[stack_count - 1] = vertex;

    while ((MUT_DEFS_MUTATE_SUCCESS == ret_val) &&
           (stack_count != 0))
    {
        note_wptt_node_t *active_vertex = stack[stack_count - 1];
        /* Active vertex is a leaf vertex*/
        if (true == reverse_checker(stack_count - 1))
        {
            if (NOTE_WPTT_ORDER_FORWARD == active_vertex->order)
            {
                active_vertex->order = NOTE_WPTT_ORDER_REVERSE;
            }
            else if (NOTE_WPTT_ORDER_REVERSE == active_vertex->order)
            {
                active_vertex->order = NOTE_WPTT_ORDER_FORWARD;
            }
            else
            {
                ret_val = MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                          MUT_WPTT_F_MOVES_MUTATE_MOVE_WALK_ERROR);
            }
        }


        if (active_vertex->number_of_children <= childidx_stack[stack_count - 1])
        {
            /*Pop stack*/
            stack_count--;
        }
        else
        {
            size_t child_idx = childidx_stack[stack_count - 1];
            /*Push child to stack*/
            childidx_stack[stack_count - 1]++;
            if ((NULL != active_vertex->children[child_idx]) &&
                (stack_count < MUT_WPTT_F_MOVES_STACK_SIZE))
            {
                stack_count++;
                stack[stack_count - 1]          = active_vertex->children[child_idx];
                childidx_stack[stack_count - 1] = 0;
            }
            else
            {
                ret_val = MUT_STATUS_BLDR(MUT_DEFS_MUTATE_FAIL,
                                          MUT_WPTT_F_MOVES_MUTATE_MOVE_WALK_ERROR);
            }
        }
    }

    return ret_val;
}

/**
 * @brief Callback function for always true.
 *
 * @param depth The depth that has been achieved in the tree walk.
 * @return The determination of if to reverse the order of the vertex.
 */
STATIC_INLINE bool mut_wptt_f_moves_revall(size_t depth)
{
    return true;
}

/**
 * @brief Callback function that reverse order at even distance from the root of the walk.
 *
 * An odd depth indicates an even distance from the root the root is depth $0$.
 *
 * @param depth The count of edges away from the root of the tree.
 * @return The determination of if to reverse the order of the vertex.
 */
STATIC_INLINE bool mut_wptt_f_moves_revodd(size_t depth)
{
    if (0 == depth % 2)
    {
        return true;
    }
    return false;
}

/**
 * @brief Multiply two values of the Klein four group.
 *
 * @param x Left multiplicand.
 * @param y Right multiplicand.
 * @return Resultant element of $K_4$.
 */
STATIC_INLINE note_wptt_V4_label_e mut_wptt_f_moves_V4_mult(note_wptt_V4_label_e x,
                                                            note_wptt_V4_label_e y)
{
    if (x == y)
    {
        return NOTE_WPTT_V4_LABEL_I;
    }

    if (NOTE_WPTT_V4_LABEL_I == x)
    {
        return y;
    }
    if (NOTE_WPTT_V4_LABEL_I == y)
    {
        return x;
    }

    switch (x)
    {
    case NOTE_WPTT_V4_LABEL_X: {
        switch (y)
        {
        case NOTE_WPTT_V4_LABEL_Y: { return NOTE_WPTT_V4_LABEL_Z; }

        case NOTE_WPTT_V4_LABEL_Z: { return NOTE_WPTT_V4_LABEL_Y; }

        default: { return NOTE_WPTT_V4_LABEL_UNINIT; }
        }
    }

    case NOTE_WPTT_V4_LABEL_Y: {
        switch (y)
        {
        case NOTE_WPTT_V4_LABEL_X: { return NOTE_WPTT_V4_LABEL_Z; }

        case NOTE_WPTT_V4_LABEL_Z: { return NOTE_WPTT_V4_LABEL_X; }

        default: { return NOTE_WPTT_V4_LABEL_UNINIT; }
        }
    }

    case NOTE_WPTT_V4_LABEL_Z: {
        switch (y)
        {
        case NOTE_WPTT_V4_LABEL_X: { return NOTE_WPTT_V4_LABEL_Y; }

        case NOTE_WPTT_V4_LABEL_Y: { return NOTE_WPTT_V4_LABEL_X; }

        default: { return NOTE_WPTT_V4_LABEL_UNINIT; }
        }
    }

    default: { return NOTE_WPTT_V4_LABEL_UNINIT; }
    }

    return NOTE_WPTT_V4_LABEL_UNINIT;
}