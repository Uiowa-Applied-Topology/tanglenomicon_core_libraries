/**
 *  \file comp_itt_to_path.c
 *
 *  \brief A module for computing a PL path for a given ITT.
 *
 *
 *  \author Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_itt_to_path.h"
#include "comp_sum_parity.h"
#include "computation_defs.h"
#include "notation_wptt.h"
#include "notation_plpath.h"
#include "comp_sum_parity.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"
#include <math.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/**
 * \brief Size of the stack used for walking the ITT.
 *
 * This corresponds to the maximum depth of ITT the component supports. We configure the value as
 *ten times the max crossing number (nominally 400).
 *
 */
#define COMP_ITT_TO_PATH_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/**
 * \brief Type definition for a segment during build.
 *
 * We store both the head pointer and end pointer for the segment linked list. This lets us extend
 *the linked list easily without having to traverse it.
 *
 */
typedef struct {
    note_plpath_point_t *head; /**< A pointer to the head of linked list of points. */
    note_plpath_point_t *end;  /**< A pointer to the end of linked list of points. */
} seg_t;

/**
 * \brief The type definition for a set of segments which form a subtangle.
 *
 * Contains the collection of segments making up the subtangle. First a segment connected to the
 *"NW" corner of the tangle. Second, a second segment connected to the boundary at either "SW" or
 *"NE" corner. Third, a collection of closed loops internal to the tangle. Finally, for optimization
 *and simplicity we maintain the parity, bounding box (height and width) of the tangle.
 *
 */
typedef struct {
    seg_t *                  NW_seg;       /**< A pointer to segment connected to the NW corner. */
    seg_t *                  second_seg;   /**< A pointer to segment connected not to the NW corner.
                                            */
    note_plpath_segment_t *  knotted_segs; /**< A pointer to a linked list of segments of internally
                                            * knotted segments. . */
    comp_sum_parity_parity_e parity;       /**< The parity of the segment set. */
    double                   height;       /**< The height of the bounding box of the tangle. */
    double                   width;        /**< The width of the bounding box of the tangle. */
} segset_t;


/******************************************************************************/
/************************** private data **************************************/
/******************************************************************************/

/**
 * \brief The local configuration of the ITT to PL path computation.
 *
 */
static comp_itt_to_path_config_t *comp_itt_to_path_localcfg = NULL;

/**
 * \brief The local result of the ITT to PL path computation.
 *
 */
static comp_itt_to_path_result_t comp_itt_to_path_localrestult = { .path = NULL };

/**
 * \brief The local computation status of the ITT to PL path computation.
 *
 */
static bool comp_itt_to_path_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE void reverse_path(note_plpath_point_t *head);
STATIC_INLINE void reverse_segment(seg_t *seg);
STATIC_INLINE void translate_segset(segset_t *set, double x, double y, double z);
STATIC_INLINE void translate_point(note_plpath_point_t *point, double x, double y, double z);
STATIC_INLINE note_plpath_segment_t *proc_intern_knot(segset_t *tangleA, segset_t *tangleB);
STATIC_INLINE_UINT8 normalize_ends(segset_t *set);
STATIC_INLINE_UINT8 normalize_zero(segset_t *set);
STATIC_INLINE_UINT8 normalize_inf(segset_t *set);
STATIC_INLINE_UINT8 normalize_chi(segset_t *set);
STATIC_INLINE_UINT8 build_int_tang(segset_t *set, int64_t weight, comp_sum_parity_op_e op);
STATIC_INLINE_UINT8 basic_inf(segset_t *set);
STATIC_INLINE_UINT8 basic_zero(segset_t *set);
STATIC_INLINE_UINT8 build_nonzero_plus(segset_t *set, int64_t weight);
STATIC_INLINE_UINT8 build_nonzero_vee(segset_t *set, int64_t weight);
STATIC_INLINE_UINT8 do_sum(segset_t *tangleA, segset_t *tangleB, comp_sum_parity_op_e op);
STATIC_INLINE_UINT8 do_vee(segset_t *tangleA, segset_t *tangleB);
STATIC_INLINE_UINT8 do_plus(segset_t *tangleA, segset_t *tangleB);
STATIC_INLINE_UINT8 walk_tree(void);


/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_itt_to_path_config(comp_itt_to_path_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_itt_to_path_localcfg = NULL;

    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_ITT_TO_PATH_CONFIG_IS_NULL;
    } /*Ensure the ITT and output is not empty.*/
    else if ((config_arg->itt == NULL) ||
             (config_arg->itt->root == NULL) ||
             (config_arg->out_path == NULL) ||
             (config_arg->out_path->seg_buff == NULL) ||
             (config_arg->out_path->pnt_buff == NULL))
    {
        ret_val |= COMP_ITT_TO_PATH_CONFIG_PARAM;
    }
    else
    {
        /* Set the config. */
        comp_itt_to_path_localcfg = config_arg;

        /* Clear the return value*/
        comp_itt_to_path_localrestult.path = NULL;

        /*clear the executed status*/
        comp_itt_to_path_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_itt_to_path_compute(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_itt_to_path_localcfg == NULL)
    {
        ret_val |= COMP_ITT_TO_PATH_COMPUTE_CFG_ERROR;
    }
    /*Ensure not previously executed.*/
    else if (comp_itt_to_path_executed != false)
    {
        ret_val |= COMP_ITT_TO_PATH_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;
        comp_itt_to_path_executed = true;

        /* Process the tree*/
        ret_val |= walk_tree();

        comp_itt_to_path_localrestult.path = comp_itt_to_path_localcfg->out_path;

        /* Print results if requested. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (NULL != comp_itt_to_path_localcfg->storage_write))
        {
            char result_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };
            char path_str[NOTE_WPTT_MAX_STR_LEN]   = { '\0' };

            (void)note_wptt_encode(*comp_itt_to_path_localcfg->itt,
                                   result_str,
                                   NOTE_WPTT_MAX_STR_LEN);

            (void)note_plpath_encode(*comp_itt_to_path_localrestult.path,
                                     path_str,
                                     NOTE_WPTT_MAX_STR_LEN);


            comp_itt_to_path_localcfg->storage_write(result_str,
                                                     "pl_path",
                                                     path_str);
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_itt_to_path_result_t *comp_itt_to_path_result(void)
{
    const comp_itt_to_path_result_t *retval = NULL;

    if (comp_itt_to_path_localcfg == NULL)
    {
        retval = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_itt_to_path_executed == false)
    {
        retval = NULL;
    }
    else
    {
        retval = (const comp_itt_to_path_result_t *)&comp_itt_to_path_localrestult;
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/**
 * \brief Walk the configured ITT building a PL tangle as we go.
 *
 * Use a breadth first progression to walk the nodes and weights of an ITT. At each nonzero and leaf
 *weight produce a PL integer tangle. Combine those integral tangles with child subtrees.
 *
 *
 * \return A status flag indicating success or failure of the computation.
 */
STATIC_INLINE_UINT8 walk_tree(void)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    size_t stack_count = 1;
    const note_wptt_node_t *stack[COMP_ITT_TO_PATH_STACK_SIZE] = { NULL };
    size_t   childidx_stack[COMP_ITT_TO_PATH_STACK_SIZE]       = { 0 };
    seg_t    nw_stack[COMP_ITT_TO_PATH_STACK_SIZE];
    seg_t    scnd_stack[COMP_ITT_TO_PATH_STACK_SIZE];
    segset_t segset_stack[COMP_ITT_TO_PATH_STACK_SIZE];
    note_plpath_segment_buffer_t *seg_buff = comp_itt_to_path_localcfg->out_path->seg_buff;

    /* Clear the stack.*/
    for (size_t i = 0; i < COMP_ITT_TO_PATH_STACK_SIZE; i++)
    {
        stack[i]                     = NULL;
        childidx_stack[i]            = 0;
        nw_stack[i].head             = NULL;
        nw_stack[i].end              = NULL;
        scnd_stack[i].head           = NULL;
        scnd_stack[i].end            = NULL;
        segset_stack[i].NW_seg       = &nw_stack[i];
        segset_stack[i].second_seg   = &scnd_stack[i];
        segset_stack[i].parity       = COMP_SUM_PARITY_PAR_UNINIT;
        segset_stack[i].knotted_segs = NULL;
        segset_stack[i].width        = 0;
        segset_stack[i].height       = 0;
    }

    /* Push the root of the tree to the stack. */
    stack[stack_count - 1] = comp_itt_to_path_localcfg->itt->root;

    /* While the stack is not empty and the computation hasn't failed. */
    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) && (stack_count != 0))
    {
        const note_wptt_node_t *active_vertex = stack[stack_count - 1];
        segset_t *active_segset = &segset_stack[stack_count - 1];
        int64_t   cur_weight    = active_vertex->weights[childidx_stack[stack_count -
                                                                        1]];
        comp_sum_parity_op_e op = (1 == stack_count % 2)?
                                  COMP_SUM_PARITY_OP_PLUS :
                                  COMP_SUM_PARITY_OP_VEE;

        /* If the current weight is nonzero or a leaf build an integer tangle. */
        if ((0 != cur_weight) || (0 == active_vertex->number_of_children))
        {
            seg_t nw_temp   = { .head = NULL, .end = NULL };
            seg_t scnd_temp = { .head = NULL, .end = NULL };
            /* Segment set to hold the current weight */
            segset_t segset_int = { .NW_seg       = &nw_temp,
                                    .second_seg   = &scnd_temp,
                                    .knotted_segs = NULL,
                                    .parity       = COMP_SUM_PARITY_PAR_UNINIT,
                                    .width        =                          0,
                                    .height       = 0 };
            /*Make the weight integral tangle*/
            ret_val |= build_int_tang(&segset_int, cur_weight, op);
            /* Combine the current weight segment with the active segment*/
            ret_val |= do_sum(active_segset, &segset_int, op);
        }

        /* If the active_vertex has no remaining children */
        if (active_vertex->number_of_children <= childidx_stack[stack_count - 1])
        {
            /*Pop stack*/
            stack_count--;

            /* Combine the child segment (active) with the parent segment*/
            if (0 < stack_count)
            {
                segset_t *parent_set = &segset_stack[stack_count - 1];
                op = (1 == stack_count % 2)?
                     COMP_SUM_PARITY_OP_PLUS :
                     COMP_SUM_PARITY_OP_VEE;
                ret_val |= do_sum(parent_set, active_segset, op);
            }
            else
            {
                break;
            }
        }
        else
        {
            size_t child_idx = childidx_stack[stack_count - 1];

            /*Push child to stack*/
            childidx_stack[stack_count - 1]++;
            if (stack_count < COMP_ITT_TO_PATH_STACK_SIZE)
            {
                stack_count++;
                stack[stack_count - 1]          = active_vertex->children[child_idx];
                childidx_stack[stack_count - 1] = 0;

                nw_stack[stack_count - 1].head             = NULL;
                nw_stack[stack_count - 1].end              = NULL;
                scnd_stack[stack_count - 1].head           = NULL;
                scnd_stack[stack_count - 1].end            = NULL;
                segset_stack[stack_count - 1].knotted_segs = NULL;
                segset_stack[stack_count - 1].height       = 0;
                segset_stack[stack_count - 1].width        = 0;
                segset_stack[stack_count - 1].parity       = COMP_SUM_PARITY_PAR_UNINIT;
            }
            else
            {
                ret_val = COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                           COMP_ITT_TO_PATH_COMPUTE_STACK_ERROR);
                break;
            }
        }
    }

    /* At this point we have a single set of segments. This needs to be converted into PL Path
     * segments.*/
    if (COMP_DEFS_COMPUTE_SUCCESS == ret_val)
    {
        if (seg_buff->idx + 1 < seg_buff->size)
        {
            note_plpath_segment_t *ks_NW = NULL;
            ks_NW = &seg_buff->buffer[seg_buff->idx];
            seg_buff->idx++;

            ks_NW->next_seg = &seg_buff->buffer[seg_buff->idx];
            seg_buff->idx++;

            ks_NW->head               = segset_stack[0].NW_seg->head;
            ks_NW->next_seg->head     = segset_stack[0].second_seg->head;
            ks_NW->next_seg->next_seg = segset_stack[0].knotted_segs;

            comp_itt_to_path_localcfg->out_path->segments = ks_NW;
        }
        else
        {
            ret_val = COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                       COMP_ITT_TO_PATH_COMPUTE_SEG_BUFF_ERROR);
        }
    }

    return ret_val;
}

/**
 * \brief Build a vertical or horizontal integral tangle.
 *
 *  Create a segment set representing an integral tangle with `weight` crossings. Store the segments
 *in the `set` pointer. If the tangle is to be horizontal or vertical is determined by `op` \f$+\f$
 * for horizontal and \f$\vee\f$ for vertical.
 *
 * \param set The segement set to store the integral tangle.
 * \param weight The number of crossings to include in the integral tangle.
 * \param op The operation to use to build the tangle.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 build_int_tang(segset_t *set, int64_t weight, comp_sum_parity_op_e op)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;

    /* Set the parity of the tangle. */
    if (0 == weight % 2)
    {
        if (COMP_SUM_PARITY_OP_VEE == op)
        {
            set->parity = COMP_SUM_PARITY_PAR_INF;
        }
        else if (COMP_SUM_PARITY_OP_PLUS == op)
        {
            set->parity = COMP_SUM_PARITY_PAR_ZERO;
        }
    }
    else
    {
        set->parity = COMP_SUM_PARITY_PAR_CHI;
    }

    /* If the weight is zero build a zero or infinity tangle.*/
    if (0 == weight)
    {
        if (COMP_SUM_PARITY_OP_VEE == op)
        {
            retval |= basic_inf(set);
        }
        else if (COMP_SUM_PARITY_OP_PLUS == op)
        {
            retval |= basic_zero(set);
        }
    }
    /* Otherwise, build a horizontal or vertical tangle with weight crossings.*/
    else
    {
        if (COMP_SUM_PARITY_OP_PLUS == op)
        {
            retval |= build_nonzero_plus(set, weight);
        }
        else if (COMP_SUM_PARITY_OP_VEE == op)
        {
            retval |= build_nonzero_vee(set, weight);
        }
    }

    return retval;
}

/**
 * \brief Build a basic zero tangle.
 *
 * \param set The segment set to store the tangle in.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8  basic_zero(segset_t *set)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW    = set->NW_seg;
    seg_t *other = set->second_seg;

    set->width  = 2;
    set->height = 2;
    if (pt_buff->idx + 5 < pt_buff->size)
    {
        NW->head    = &pt_buff->buffer[pt_buff->idx];
        NW->head->x = 0;
        NW->head->y = 2;
        NW->head->z = 0;
        pt_buff->idx++;

        NW->head->next_point    = &pt_buff->buffer[pt_buff->idx];
        NW->head->next_point->x = 1;
        NW->head->next_point->y = 1.5;
        NW->head->next_point->z = 0;
        pt_buff->idx++;

        NW->head->next_point->next_point    = &pt_buff->buffer[pt_buff->idx];
        NW->head->next_point->next_point->x = 2;
        NW->head->next_point->next_point->y = 2;
        NW->head->next_point->next_point->z = 0;
        NW->end             = NW->head->next_point->next_point;
        NW->end->next_point = NULL;
        pt_buff->idx++;

        other->head    = &pt_buff->buffer[pt_buff->idx];
        other->head->x = 0;
        other->head->y = 0;
        other->head->z = 0;
        pt_buff->idx++;

        other->head->next_point    = &pt_buff->buffer[pt_buff->idx];
        other->head->next_point->x = 1;
        other->head->next_point->y = 0.5;
        other->head->next_point->z = 0;
        pt_buff->idx++;

        other->head->next_point->next_point    = &pt_buff->buffer[pt_buff->idx];
        other->head->next_point->next_point->x = 2;
        other->head->next_point->next_point->y = 0;
        other->head->next_point->next_point->z = 0;
        other->end             = other->head->next_point->next_point;
        other->end->next_point = NULL;
        pt_buff->idx++;
    }
    else
    {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }
    return retval;
}

/**
 * \brief Build a basic infinity tangle.
 *
 * \param set The segment set to store the tangle in.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8  basic_inf(segset_t *set)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW    = set->NW_seg;
    seg_t *other = set->second_seg;

    set->width  = 2;
    set->height = 2;
    if (pt_buff->idx + 5 < pt_buff->size)
    {
        NW->head    = &pt_buff->buffer[pt_buff->idx];
        NW->head->x = 0;
        NW->head->y = 2;
        NW->head->z = 0;
        pt_buff->idx++;

        NW->head->next_point    = &pt_buff->buffer[pt_buff->idx];
        NW->head->next_point->x = 0.5;
        NW->head->next_point->y = 1;
        NW->head->next_point->z = 0;
        pt_buff->idx++;

        NW->head->next_point->next_point    = &pt_buff->buffer[pt_buff->idx];
        NW->head->next_point->next_point->x = 0;
        NW->head->next_point->next_point->y = 0;
        NW->head->next_point->next_point->z = 0;
        NW->end             = NW->head->next_point->next_point;
        NW->end->next_point = NULL;
        pt_buff->idx++;

        other->head    = &pt_buff->buffer[pt_buff->idx];
        other->head->x = 2;
        other->head->y = 2;
        other->head->z = 0;
        pt_buff->idx++;

        other->head->next_point    = &pt_buff->buffer[pt_buff->idx];
        other->head->next_point->x = 1.5;
        other->head->next_point->y = 1;
        other->head->next_point->z = 0;
        pt_buff->idx++;

        other->head->next_point->next_point    = &pt_buff->buffer[pt_buff->idx];
        other->head->next_point->next_point->x = 2;
        other->head->next_point->next_point->y = 0;
        other->head->next_point->next_point->z = 0;
        other->end             = other->head->next_point->next_point;
        other->end->next_point = NULL;
        pt_buff->idx++;
    }
    else
    {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }
    return retval;
}

/**
 * \brief Build a nonzero horizontal integral tangle.
 *
 * Build a nonzero horizontal integral tangle with `weight` crossings each of sign matching the sign
 *of `weight`.
 *
 * \param set The segment set to store the tangle in.
 * \param weight The weight indicating the number of crossings.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8  build_nonzero_plus(segset_t *set, int64_t weight)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW  = set->NW_seg;
    seg_t *sec = set->second_seg;
    note_plpath_point_t *pt_NW  = NULL;
    note_plpath_point_t *pt_sec = NULL;
    int sign = 1;

    if (weight < 0)
    {
        sign = -1;
    }

    /* Set the bounding box */
    set->width  = 2 * llabs(weight);
    set->height = 2;

    /* Set the head points. */
    if (pt_buff->idx + 1 < pt_buff->size)
    {
        pt_NW             = &pt_buff->buffer[pt_buff->idx];
        pt_NW->x          = 0;
        pt_NW->y          = 2;
        pt_NW->z          = 0;
        pt_NW->next_point = NULL;
        pt_buff->idx++;

        pt_sec             = &pt_buff->buffer[pt_buff->idx];
        pt_sec->x          = 0;
        pt_sec->y          = 0;
        pt_sec->z          = 0;
        pt_sec->next_point = NULL;
        pt_buff->idx++;
    }
    else
    {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }

    NW->head  = pt_NW;
    sec->head = pt_sec;

    for (size_t i = 0u; i < llabs(weight); i++)
    {
        if (pt_buff->idx + 3 < pt_buff->size)
        {
            pt_NW->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_NW             = pt_NW->next_point;
            pt_NW->x          = (2u * i) + 1;
            pt_NW->y          = 1;
            pt_NW->z          = -1 * sign;
            pt_NW->next_point = NULL;
            pt_buff->idx++;

            pt_sec->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_sec             = pt_sec->next_point;
            pt_sec->x          = (2u * i) + 1;
            pt_sec->y          = 1;
            pt_sec->z          = sign;
            pt_sec->next_point = NULL;
            pt_buff->idx++;

            pt_NW->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_NW             = pt_NW->next_point;
            pt_NW->x          = (2u * i) + 2.f;
            pt_NW->y          = 0;
            pt_NW->z          = 0;
            pt_NW->next_point = NULL;
            pt_buff->idx++;

            pt_sec->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_sec             = pt_sec->next_point;
            pt_sec->x          = (2u * i) + 2.f;
            pt_sec->y          = 2;
            pt_sec->z          = 0;
            pt_sec->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            retval = COMP_DEFS_COMPUTE_FAIL;
            break;
        }

        note_plpath_point_t *tmp = pt_NW;
        pt_NW  = pt_sec;
        pt_sec = tmp;
    }

    if (0 == weight % 2)
    {
        NW->end  = pt_NW;
        sec->end = pt_sec;
    }
    else
    {
        NW->end  = pt_sec;
        sec->end = pt_NW;
    }

    return retval;
}

/**
 * \brief Build a nonzero vertical integral tangle.
 *
 * Build a nonzero vertical integral tangle with `weight` crossings each of sign opposite the sign
 *of `weight`.
 *
 *> [!note] Note
 *>
 *>
 *> The signs are opposite due to the rotation of the bands when descending the tree.
 *
 * \param set The segment set to store the tangle in.
 * \param weight The weight indicating the number of crossings.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8  build_nonzero_vee(segset_t *set, int64_t weight)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW  = set->NW_seg;
    seg_t *sec = set->second_seg;
    note_plpath_point_t *pt_NW  = NULL;
    note_plpath_point_t *pt_sec = NULL;
    int      sign   = 1;
    uint64_t offset = llabs(weight);

    if (weight < 0)
    {
        sign = -1;
    }

    /* Set the bounding box */
    set->width  = 2;
    set->height = 2 * offset;

    /* Set the head points. */
    if (pt_buff->idx + 1 < pt_buff->size)
    {
        pt_NW             = &pt_buff->buffer[pt_buff->idx];
        pt_NW->x          = 0;
        pt_NW->y          = 2 * offset;
        pt_NW->z          = 0;
        pt_NW->next_point = NULL;
        pt_buff->idx++;

        pt_sec             = &pt_buff->buffer[pt_buff->idx];
        pt_sec->x          = 2;
        pt_sec->y          = 2 * offset;
        pt_sec->z          = 0;
        pt_sec->next_point = NULL;
        pt_buff->idx++;
    }
    else
    {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }

    /* Set */
    NW->head  = pt_NW;
    sec->head = pt_sec;
    for (size_t i = offset; 0 < i; i--)
    {
        if (pt_buff->idx + 3 < pt_buff->size)
        {
            pt_NW->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_NW             = pt_NW->next_point;
            pt_NW->x          = 1;
            pt_NW->y          = (2 * (i - 1)) + 1;
            pt_NW->z          = sign;
            pt_NW->next_point = NULL;
            pt_buff->idx++;

            pt_sec->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_sec             = pt_sec->next_point;
            pt_sec->x          = 1;
            pt_sec->y          = (2 * (i - 1)) + 1;
            pt_sec->z          = -1 * sign;
            pt_sec->next_point = NULL;
            pt_buff->idx++;

            pt_NW->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_NW             = pt_NW->next_point;
            pt_NW->x          = 2;
            pt_NW->y          = (2 * i) - 2.f;
            pt_NW->z          = 0;
            pt_NW->next_point = NULL;
            pt_buff->idx++;

            pt_sec->next_point = &pt_buff->buffer[pt_buff->idx];
            pt_sec             = pt_sec->next_point;
            pt_sec->x          = 0;
            pt_sec->y          = (2 * i) - 2.f;
            pt_sec->z          = 0;
            pt_sec->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }

        note_plpath_point_t *tmp = pt_NW;
        pt_NW  = pt_sec;
        pt_sec = tmp;
    }

    if (COMP_DEFS_COMPUTE_SUCCESS == retval)
    {
        if (0 == weight % 2)
        {
            NW->end  = pt_NW;
            sec->end = pt_sec;
        }
        else
        {
            NW->end  = pt_sec;
            sec->end = pt_NW;
            reverse_segment(sec);
        }
    }

    return retval;
}

/**
 * \brief Sum two tangles with \f$+\f$ or \f$\vee\f$.
 *
 * Use either the \f$+\f$ or \f$\vee\f$ operation to sum two tangles A and B. The sum modifies the
 *tangle A with the content of tangle B.
 *
 * \param tangleA The left summand.
 * \param tangleB The right summand.
 * \param op The operation to apply
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 do_sum(segset_t *tangleA, segset_t *tangleB, comp_sum_parity_op_e op)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;

    /* Ensure the right summand is not empty */
    if ((NULL != tangleB->NW_seg->head) &&
        (NULL != tangleB->second_seg->head))
    {
        /* If the left summand is empty just copy the right summand into it. */
        if ((NULL == tangleA->NW_seg->head) && (NULL == tangleA->second_seg->head))
        {
            tangleA->NW_seg->head     = tangleB->NW_seg->head;
            tangleA->NW_seg->end      = tangleB->NW_seg->end;
            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            tangleA->knotted_segs     = tangleB->knotted_segs;
            tangleA->parity           = tangleB->parity;
            tangleA->height           = tangleB->height;
            tangleA->width            = tangleB->width;
        }
        else
        {
            /* Do the sum. */
            double offset_x = 0;
            double offset_y = 0;
            comp_sum_parity_parity_e parity_a    = tangleA->parity;
            comp_sum_parity_parity_e parity_b    = tangleB->parity;
            comp_sum_parity_config_t sum_par_cfg = { .tangleA       = parity_a,
                                                     .tangleB       = parity_b,
                                                     .op            = op,
                                                     .storage_write = NULL,
                                                     .write_key     = NULL };
            if (op == COMP_SUM_PARITY_OP_PLUS)
            {
                offset_x = tangleA->width + 2;
                offset_y = fabs((tangleA->height - tangleB->height) / 2.0);

                if (tangleA->height < tangleB->height)
                {
                    translate_segset(tangleA,
                                     0,
                                     offset_y,
                                     0);
                    tangleA->height = tangleB->height;
                }
                else if (tangleA->height > tangleB->height)
                {
                    translate_segset(tangleB,
                                     0,
                                     offset_y,
                                     0);
                }


                translate_segset(tangleB,
                                 offset_x,
                                 0,
                                 0);

                retval |= do_plus(tangleA, tangleB);

                tangleA->width = labs((int64_t)offset_x) + tangleB->width;
            }
            else
            {
                offset_y = tangleB->height + 2;
                offset_x = fabs((tangleA->width - tangleB->width) / 2.0);

                if (tangleA->width < tangleB->width)
                {
                    translate_segset(tangleA,
                                     offset_x,
                                     0,
                                     0);
                    tangleA->width = tangleB->width;
                }
                else if (tangleA->width > tangleB->width)
                {
                    translate_segset(tangleB,
                                     offset_x,
                                     0,
                                     0);
                }


                translate_segset(tangleA,
                                 0,
                                 offset_y,
                                 0);

                retval |= do_vee(tangleA, tangleB);

                tangleA->height = labs((int64_t)offset_y) + tangleA->height;
            }

            /* Compute the parity of the resulting tangle.*/
            retval |= comp_sum_parity_config(&sum_par_cfg);
            retval |= comp_sum_parity_compute();
            const comp_sum_parity_result_t *sum_par = comp_sum_parity_result();
            tangleA->parity = sum_par->parity;

            retval |= normalize_ends(tangleA);
        }
    }
    return retval;
}

/**
 * \brief Do a \f$\vee\f$ sum
 *
 *
 * \param tangleA The left summand.
 * \param tangleB The right summand.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 do_vee(segset_t *tangleA, segset_t *tangleB)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    comp_sum_parity_parity_e parity_a = tangleA->parity;
    comp_sum_parity_parity_e parity_b = tangleB->parity;

    switch (parity_a)
    {
    case COMP_SUM_PARITY_PAR_CHI: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            reverse_segment(tangleB->second_seg);
            tangleA->NW_seg->end->next_point = tangleB->second_seg->head;
            tangleA->NW_seg->end             = tangleB->second_seg->end;
            reverse_segment(tangleA->second_seg);
            tangleA->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->second_seg->end             = tangleB->NW_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            reverse_segment(tangleB->NW_seg);
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;
            tangleA->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleA->NW_seg->end             = tangleA->second_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            tangleA->NW_seg->end->next_point = tangleB->second_seg->head;
            tangleA->NW_seg->end             = tangleB->second_seg->end;
            reverse_segment(tangleA->second_seg);
            tangleA->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->second_seg->end             = tangleB->NW_seg->end;
            reverse_segment(tangleA->second_seg);
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }
        }
        break;
    }

    case COMP_SUM_PARITY_PAR_ZERO: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            reverse_segment(tangleA->second_seg);
            tangleB->second_seg->end->next_point = tangleA->second_seg->head;
            tangleB->second_seg->end             = tangleA->second_seg->end;
            tangleB->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleB->second_seg->end             = tangleB->NW_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            note_plpath_segment_t *ks = proc_intern_knot(tangleA, tangleB);
            if (NULL == tangleA->knotted_segs)
            {
                tangleA->knotted_segs = ks;
            }
            else
            {
                ks->next_seg          = tangleA->knotted_segs;
                tangleA->knotted_segs = ks;
            }
            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            reverse_segment(tangleB->NW_seg);
            tangleB->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleB->NW_seg->end             = tangleA->second_seg->end;
            tangleB->NW_seg->end->next_point = tangleB->second_seg->head;
            tangleB->NW_seg->end             = tangleB->second_seg->end;

            tangleA->second_seg->head = tangleB->NW_seg->head;
            tangleA->second_seg->end  = tangleB->NW_seg->end;
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }
        }
        break;
    }

    case COMP_SUM_PARITY_PAR_INF: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;

            reverse_segment(tangleA->second_seg);
            tangleB->second_seg->end->next_point = tangleA->second_seg->head;
            tangleB->second_seg->end             = tangleA->second_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;
            reverse_segment(tangleA->second_seg);
            tangleA->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleA->NW_seg->end             = tangleA->second_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            tangleA->NW_seg->end->next_point     = tangleB->NW_seg->head;
            tangleA->NW_seg->end                 = tangleB->NW_seg->end;
            tangleA->second_seg->end->next_point = tangleB->second_seg->head;
            tangleA->second_seg->end             = tangleB->second_seg->end;
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }
        }
        break;
    }

    default: {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }
    }

    return retval;
}

/**
 * \brief Do a \f$+\f$ sum
 *
 * \param tangleA The left summand.
 * \param tangleB The right summand.
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 do_plus(segset_t *tangleA, segset_t *tangleB)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    comp_sum_parity_parity_e parity_a = tangleA->parity;
    comp_sum_parity_parity_e parity_b = tangleB->parity;


    switch (parity_a)
    {
    case COMP_SUM_PARITY_PAR_CHI: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            tangleA->NW_seg->end->next_point     = tangleB->second_seg->head;
            tangleA->NW_seg->end                 = tangleB->second_seg->end;
            tangleA->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->second_seg->end             = tangleB->NW_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            tangleA->NW_seg->end->next_point     = tangleB->second_seg->head;
            tangleA->NW_seg->end                 = tangleB->second_seg->end;
            tangleA->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->second_seg->end             = tangleB->NW_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            reverse_segment(tangleB->NW_seg);
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;
            reverse_segment(tangleA->second_seg);
            tangleA->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleA->NW_seg->end             = tangleA->second_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
            break;
        }
        }
        break;
    }

    case COMP_SUM_PARITY_PAR_ZERO: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;

            tangleA->second_seg->end->next_point = tangleB->second_seg->head;
            tangleA->second_seg->end             = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;

            tangleA->second_seg->end->next_point = tangleB->second_seg->head;
            tangleA->second_seg->end             = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            tangleA->NW_seg->end->next_point = tangleB->NW_seg->head;
            tangleA->NW_seg->end             = tangleB->NW_seg->end;
            reverse_segment(tangleA->second_seg);
            tangleA->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleA->NW_seg->end             = tangleA->second_seg->end;

            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }
        }
        break;
    }

    case COMP_SUM_PARITY_PAR_INF: {
        switch (parity_b)
        {
        case COMP_SUM_PARITY_PAR_CHI: {
            reverse_segment(tangleB->second_seg);
            reverse_segment(tangleA->second_seg);
            tangleB->second_seg->end->next_point = tangleA->second_seg->head;
            tangleB->second_seg->end             = tangleA->second_seg->end;
            tangleB->second_seg->end->next_point = tangleB->NW_seg->head;
            tangleB->second_seg->end             = tangleB->NW_seg->end;
            tangleA->second_seg->head            = tangleB->second_seg->head;
            tangleA->second_seg->end             = tangleB->second_seg->end;
            break;
        }

        case COMP_SUM_PARITY_PAR_ZERO: {
            reverse_segment(tangleB->NW_seg);
            tangleB->NW_seg->end->next_point = tangleA->second_seg->head;
            tangleB->NW_seg->end             = tangleA->second_seg->end;

            tangleB->NW_seg->end->next_point = tangleB->second_seg->head;
            tangleB->NW_seg->end             = tangleB->second_seg->end;

            tangleA->second_seg->head = tangleB->NW_seg->head;
            tangleA->second_seg->end  = tangleB->NW_seg->end;

            break;
        }

        case COMP_SUM_PARITY_PAR_INF: {
            note_plpath_segment_t *ks = proc_intern_knot(tangleA, tangleB);
            if (NULL == tangleA->knotted_segs)
            {
                tangleA->knotted_segs = ks;
            }
            else
            {
                ks->next_seg          = tangleA->knotted_segs;
                tangleA->knotted_segs = ks;
            }
            tangleA->second_seg->head = tangleB->second_seg->head;
            tangleA->second_seg->end  = tangleB->second_seg->end;
            break;
        }

        default: {
            retval = COMP_DEFS_COMPUTE_FAIL;
        }
        }
        break;
    }

    default: {
        retval = COMP_DEFS_COMPUTE_FAIL;
    }
    }

    return retval;
}

/**
 * \brief Process an internally knotted segment.
 *
 * The sum results in an internally knotted component. Process that component into a notation PL
 *path segment.
 *
 * \param tangleA The left summand.
 * \param tangleB The right summand.
 * \return The internally knotted segment.
 */
STATIC_INLINE note_plpath_segment_t *proc_intern_knot(segset_t *tangleA, segset_t *tangleB)
{
    seg_t *sec_A = tangleA->second_seg;
    seg_t *NW_B  = tangleB->NW_seg;
    note_plpath_segment_buffer_t *seg_buff = comp_itt_to_path_localcfg->out_path->seg_buff;
    note_plpath_point_buffer_t *  pt_buff  = comp_itt_to_path_localcfg->out_path->pnt_buff;
    note_plpath_segment_t *       ks       = NULL;
    note_plpath_point_t *         pt       = NULL;

    reverse_segment(sec_A);

    NW_B->end->next_point = sec_A->head;
    NW_B->end             = sec_A->end;
    if (seg_buff->idx < seg_buff->size)
    {
        ks           = &seg_buff->buffer[seg_buff->idx];
        ks->head     = NULL;
        ks->next_seg = NULL;
        seg_buff->idx++;
    }
    else
    {
        return NULL;
    }

    if (pt_buff->idx < pt_buff->size)
    {
        pt = &pt_buff->buffer[pt_buff->idx];
        pt_buff->idx++;
    }
    else
    {
        return NULL;
    }
    pt->x          = NW_B->head->x;
    pt->y          = NW_B->head->y;
    pt->z          = NW_B->head->z;
    pt->next_point = NULL;

    NW_B->end->next_point = pt;
    NW_B->end             = pt;

    ks->head = NW_B->head;

    return ks;
}

/**
 * \brief Attach the fixed points of the tangle to the corners of it's bounding box.
 *
 * \param set The segment set for the tangle to normalize
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 normalize_ends(segset_t *set)
{
    uint8_t retval = COMP_DEFS_COMPUTE_SUCCESS;
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW_seg = set->NW_seg;

    if ((0 != NW_seg->head->x) || (set->height != NW_seg->head->y))
    {
        note_plpath_point_t *NW = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            NW             = &pt_buff->buffer[pt_buff->idx];
            NW->x          = 0;
            NW->y          = set->height;
            NW->z          = 0;
            NW->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        NW->next_point = NW_seg->head;
        NW_seg->head   = NW;
    }

    switch (set->parity)
    {
    case COMP_SUM_PARITY_PAR_CHI: {
        retval |= normalize_chi(set);
        break;
    }

    case COMP_SUM_PARITY_PAR_ZERO: {
        retval |= normalize_zero(set);
        break;
    }

    case COMP_SUM_PARITY_PAR_INF: {
        retval |= normalize_inf(set);
        break;
    }

    default: {
        retval = COMP_DEFS_COMPUTE_FAIL;
        break;
    }
    }

    return retval;
}

/**
 * \brief Attach the fixed points of the tangle with parity \f$\chi\f$ to the corners of it's
 *bounding box.
 *
 * \param set The segment set for the tangle to normalize
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 normalize_chi(segset_t *set)
{
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW_seg  = set->NW_seg;
    seg_t *sec_seg = set->second_seg;


    if ((0 != sec_seg->head->x) || (0 != sec_seg->head->y))
    {
        note_plpath_point_t *SW = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SW             = &pt_buff->buffer[pt_buff->idx];
            SW->x          = 0;
            SW->y          = 0;
            SW->z          = 0;
            SW->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        SW->next_point = sec_seg->head;
        sec_seg->head  = SW;
    }

    if ((set->width != sec_seg->end->x) || (set->height != sec_seg->end->y))
    {
        note_plpath_point_t *NE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            NE             = &pt_buff->buffer[pt_buff->idx];
            NE->x          = set->width;
            NE->y          = set->height;
            NE->z          = 0;
            NE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        sec_seg->end->next_point = NE;
        sec_seg->end             = NE;
    }

    if ((set->width != NW_seg->end->x) || (0 != NW_seg->end->y))
    {
        note_plpath_point_t *SE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SE             = &pt_buff->buffer[pt_buff->idx];
            SE->x          = set->width;
            SE->y          = 0;
            SE->z          = 0;
            SE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        NW_seg->end->next_point = SE;
        NW_seg->end             = SE;
    }
    return COMP_DEFS_COMPUTE_SUCCESS;
}

/**
 * \brief Attach the fixed points of the tangle with parity \f$\infty\f$ to the corners of it's
 *bounding box.
 *
 * \param set The segment set for the tangle to normalize
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 normalize_inf(segset_t *set)
{
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW_seg  = set->NW_seg;
    seg_t *sec_seg = set->second_seg;

    if ((0 != NW_seg->head->x) || (0 != NW_seg->head->y))
    {
        note_plpath_point_t *SW = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SW             = &pt_buff->buffer[pt_buff->idx];
            SW->x          = 0;
            SW->y          = 0;
            SW->z          = 0;
            SW->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        NW_seg->end->next_point = SW;
        NW_seg->end             = SW;
    }

    if ((set->width != sec_seg->head->x) || (set->height != sec_seg->head->y))
    {
        note_plpath_point_t *NE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            NE             = &pt_buff->buffer[pt_buff->idx];
            NE->x          = set->width;
            NE->y          = set->height;
            NE->z          = 0;
            NE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        NE->next_point = sec_seg->head;
        sec_seg->head  = NE;
    }

    if ((set->width != sec_seg->end->x) || (0 != sec_seg->end->y))
    {
        note_plpath_point_t *SE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SE             = &pt_buff->buffer[pt_buff->idx];
            SE->x          = set->width;
            SE->y          = 0;
            SE->z          = 0;
            SE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        sec_seg->end->next_point = SE;
        sec_seg->end             = SE;
    }

    return COMP_DEFS_COMPUTE_SUCCESS;
}

/**
 * \brief Attach the fixed points of the tangle with parity \f$0\f$ to the corners of it's bounding
 *box.
 *
 * \param set The segment set for the tangle to normalize
 * \return A status indicator for the tangle creation.
 */
STATIC_INLINE_UINT8 normalize_zero(segset_t *set)
{
    note_plpath_point_buffer_t *pt_buff = comp_itt_to_path_localcfg->out_path->pnt_buff;
    seg_t *NW_seg  = set->NW_seg;
    seg_t *sec_seg = set->second_seg;

    if ((0 != sec_seg->head->x) || (0 != sec_seg->head->y))
    {
        note_plpath_point_t *SW = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SW             = &pt_buff->buffer[pt_buff->idx];
            SW->x          = 0;
            SW->y          = 0;
            SW->z          = 0;
            SW->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        SW->next_point = sec_seg->head;
        sec_seg->head  = SW;
    }

    if ((set->width != NW_seg->end->x) || (set->height != NW_seg->end->y))
    {
        note_plpath_point_t *NE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            NE             = &pt_buff->buffer[pt_buff->idx];
            NE->x          = set->width;
            NE->y          = set->height;
            NE->z          = 0;
            NE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        NW_seg->end->next_point = NE;
        NW_seg->end             = NE;
    }

    if ((set->width != sec_seg->end->x) || (0 != sec_seg->end->y))
    {
        note_plpath_point_t *SE = NULL;
        if (pt_buff->idx < pt_buff->size)
        {
            SE             = &pt_buff->buffer[pt_buff->idx];
            SE->x          = set->width;
            SE->y          = 0;
            SE->z          = 0;
            SE->next_point = NULL;
            pt_buff->idx++;
        }
        else
        {
            return COMP_DEFS_COMPUTE_FAIL;
        }

        sec_seg->end->next_point = SE;
        sec_seg->end             = SE;
    }
    return COMP_DEFS_COMPUTE_SUCCESS;
}

/**
 * \brief Reverse the direction of a segment.
 *
 * Reverse linkage of the points in a segment and swap the head and end points.
 *
 * \param seg The segment to reverse.
 */
STATIC_INLINE void reverse_segment(seg_t *seg)
{
    note_plpath_point_t *cur_head = seg->head;
    note_plpath_point_t *cur_end  = seg->end;

    reverse_path(seg->head);
    seg->end  = cur_head;
    seg->head = cur_end;
}

/**
 * \brief Reverse the path (linked list) formed by points.
 *
 * \param head The head of the linked list.
 */
STATIC_INLINE void reverse_path(note_plpath_point_t *head)
{
    note_plpath_point_t *next_pos = head->next_point;
    note_plpath_point_t *cur_head = head;

    while (NULL != next_pos)
    {
        note_plpath_point_t *temp = next_pos->next_point;
        next_pos->next_point = cur_head;
        cur_head             = next_pos;
        next_pos             = temp;
    }
    head->next_point = NULL;
}

/**
 * \brief Translate all points of a segment set by a given vector.
 *
 * Translate by a given vector the points found in the NW, second, and internally knotted segments
 *of a segment set.
 *
 * \param set The segment set to translate.
 * \param x The x distance to translate.
 * \param y The y distance to translate.
 * \param z The Z distance to translate.
 */
STATIC_INLINE void translate_segset(segset_t *set, double x, double y, double z)
{
    for (note_plpath_point_t *p = set->NW_seg->head; NULL != p;
         p = p->next_point)
    {
        translate_point(p, x, y, z);
    }

    for (note_plpath_point_t *p = set->second_seg->head; NULL != p;
         p = p->next_point)
    {
        translate_point(p, x, y, z);
    }

    for (note_plpath_segment_t *seg = set->knotted_segs; NULL != seg;
         seg = seg->next_seg)
    {
        for (note_plpath_point_t *p = seg->head; NULL != p;
             p = p->next_point)
        {
            translate_point(p, x, y, z);
        }
    }
}

/**
 * \brief Translate a point by a given vector.
 *
 * \param point The point to translate
 * \param x The x distance to translate.
 * \param y The y distance to translate.
 * \param z The Z distance to translate.
 */
STATIC_INLINE void translate_point(note_plpath_point_t *point, double x, double y, double z)
{
    point->x += x;
    point->y += y;
    point->z += z;
}
