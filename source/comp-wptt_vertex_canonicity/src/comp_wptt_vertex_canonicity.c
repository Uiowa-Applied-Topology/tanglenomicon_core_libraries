/*!
 *  @file comp_wptt_vert_canon.c
 *
 *  @brief  A wptt vertex canonicity computation module
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_wptt_vertex_canonicity.h"
#include "bits/stdint-uintn.h"
#include "computation_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the WPTT vertex canonicity module.
 *
 */
#define COMP_WPTT_VERT_CANON_STACK_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the WPTT vertex canonicity module.
 *
 */
static comp_wptt_vert_canon_config_t *comp_wptt_vert_canon_localcfg = NULL;

/*!
 * @brief The local result of the WPTT vertex canonicity module.
 *
 */
static comp_wptt_vert_canon_result_t comp_wptt_vert_canon_localrestult = {};

/*!
 * @brief The local computation status of the WPTT vertex canonicity module.
 *
 */
static bool comp_wptt_vert_canon_executed = false;

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

STATIC_INLINE bool comp_wptt_vert_canon_weights(const note_wptt_node_t *vertex);
STATIC_INLINE bool comp_wptt_vert_canon_stick(const note_wptt_node_t *vertex,
                                              const note_wptt_node_t *parent,
                                              bool parent_is_root);
STATIC_INLINE bool comp_wptt_vert_canon_positivity(const note_wptt_node_t *vertex,
                                                   const note_wptt_node_t *parent);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_wptt_vert_canon_config(comp_wptt_vert_canon_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_wptt_vert_canon_localcfg = NULL;
    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_WPTT_VERT_CANON_CONFIG_IS_NULL;
    } /*Ensure the wptt is not empty.*/
    else if ((config_arg->vertex == NULL) ||
             (config_arg->positivity == COMP_WPTT_VERT_CANON_POS_UNINIT))
    {
        ret_val |= COMP_WPTT_VERT_CANON_CONFIG_PARAM;
    }
    else
    {
        /* Set the config. */
        comp_wptt_vert_canon_localcfg = config_arg;

        /* Clear the return value*/
        comp_wptt_vert_canon_localrestult.is_canonical = COMP_WPTT_VERT_CANON_CAN_UNINIT;

        /*clear the executed status*/
        comp_wptt_vert_canon_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_wptt_vert_canon_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_wptt_vert_canon_localcfg == NULL)
    {
        ret_val |= COMP_WPTT_VERT_CANON_COMPUTE_CFG_ERROR;
    }
    /*Ensure not previously executed.*/
    else if (comp_wptt_vert_canon_executed != false)
    {
        ret_val |= COMP_WPTT_VERT_CANON_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        const note_wptt_node_t *vertex = comp_wptt_vert_canon_localcfg->vertex;
        const note_wptt_node_t *parent = comp_wptt_vert_canon_localcfg->parent;
        bool parent_is_root            = comp_wptt_vert_canon_localcfg->parent_is_root;
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;
        comp_wptt_vert_canon_executed = true;

        if (true == comp_wptt_vert_canon_weights(vertex))
        {
            if (NULL == parent)
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_CANONICAL;
            }
            else
            {
                if ((true == comp_wptt_vert_canon_stick(vertex,
                                                        parent,
                                                        parent_is_root)) &&
                    (true == comp_wptt_vert_canon_positivity(vertex, parent)))
                {
                    comp_wptt_vert_canon_localrestult.is_canonical =
                        COMP_WPTT_VERT_CANON_IS_CANONICAL;
                }
            }
        }

        if (NULL != comp_wptt_vert_canon_localcfg->storage_write)
        {
            char result_str[NOTE_WPTT_MAX_STR_LEN] = "is_canon_vertex";
            if (NULL != comp_wptt_vert_canon_localcfg->wptt)
            {
                (void)note_wptt_encode(*comp_wptt_vert_canon_localcfg->wptt,
                                       result_str,
                                       NOTE_WPTT_MAX_STR_LEN);
            }

            if (comp_wptt_vert_canon_localrestult.is_canonical ==
                COMP_WPTT_VERT_CANON_IS_CANONICAL)
            {
                comp_wptt_vert_canon_localcfg->storage_write(result_str,
                                                             "is_canon_vertex",
                                                             "true");
            }
            else if (comp_wptt_vert_canon_localrestult.is_canonical ==
                     COMP_WPTT_VERT_CANON_IS_NONCANONICAL
                     )
            {
                comp_wptt_vert_canon_localcfg->storage_write(result_str,
                                                             "is_canon_vertex",
                                                             "false");
            }
        }
    }

    return ret_val;
}

/*
 *  Documentation in header
 */
const comp_wptt_vert_canon_result_t *comp_wptt_vert_canon_result()
{
    const comp_wptt_vert_canon_result_t *ret_val = NULL;

    if (comp_wptt_vert_canon_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_wptt_vert_canon_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_wptt_vert_canon_result_t *)&comp_wptt_vert_canon_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Check the weight condition of the vertex.
 *
 * @param vertex The object vertex.
 * @return True when canonical false otherwise
 */
STATIC_INLINE bool comp_wptt_vert_canon_weights(const note_wptt_node_t *vertex)
{
    bool   nonzero_seen = false;
    size_t i;

    /* For each child of the vertex.*/
    for (i = 0; i < vertex->number_of_children; i++)
    {
        if (0 != vertex->weights[i])
        {
            if (true == nonzero_seen)
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
                return false;
            }
            else
            {
                nonzero_seen = true;
            }
        }
    }

    if ((0 != vertex->weights[vertex->number_of_children]) &&
        (true == nonzero_seen))
    {
        comp_wptt_vert_canon_localrestult.is_canonical = COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
        return false;
    }

    return true;
}

/*!
 * @brief Check the stick condition of the vertex looking up.
 *
 * @param parent The parent vertex.
 * @param active_weight The weight carried by the object vertex.
 * @param number_of_children The number of children of the object vertex.
 * @return True if canonical false otherwise.
 */
STATIC_INLINE bool comp_wptt_vert_canon_stick_parent(const note_wptt_node_t *parent,
                                                     int active_weight,
                                                     size_t number_of_children)
{
    /* Check if parent exists*/
    if (NULL != parent)
    {
        int    parent_weight = 0;
        size_t i;
        for (i = 0; i <= parent->number_of_children; i++)
        {
            parent_weight += parent->weights[i];
        }

        /* Check that object vertex is not at the end of a stick with weight $\pm 1$. */
        if (1 < parent->number_of_children)
        {
            if ((1 == number_of_children) && ((-1 == active_weight) ||
                                              (1 == active_weight)))
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
                return false;
            }
        }
        else if (number_of_children < 2)
        {
            /* If not on the end of a stick then we are in the middle and need to check if we
             * alternate sign.
             */
            if (((active_weight < 0) && (parent_weight < 0)) ||
                ((active_weight > 0) && (parent_weight > 0)))
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
                return false;
            }
        }
    }

    return true;
}

/*!
 * @brief Check the stick condition of the vertex looking down.
 *
 * @param child The child vertex of the object vertex.
 * @param number_of_children The number of children of the object vertex.
 * @param active_weight The weight carried by the object vertex.
 * @return True if canonical false otherwise.
 */
STATIC_INLINE bool comp_wptt_vert_canon_stick_child(const note_wptt_node_t *child,
                                                    size_t number_of_children,
                                                    int active_weight)
{
    /* Check if we are on a vertex that is a non-leaf stick vertex. */
    if (1 == number_of_children)
    {
        int    child_weight = 0;
        size_t i;

        for (i = 0; i <= child->number_of_children; i++)
        {
            child_weight += child->weights[i];
        }

        /* Check the zero portion of the stick condition. */
        if (0 == active_weight)
        {
            comp_wptt_vert_canon_localrestult.is_canonical =
                COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
            return false;
        }

        /* Check that object vertex is not at the end of a stick with weight $\pm 1$. */
        if (1 < child->number_of_children)
        {
            if ((-1 == active_weight) ||
                (1 == active_weight))
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
                return false;
            }
        }
        else
        {
            /* If not on the end of a stick then we are in the middle and need to check if we
             * alternate sign.
             */
            if (((active_weight < 0) && (child_weight < 0)) ||
                ((active_weight > 0) && (child_weight > 0)))
            {
                comp_wptt_vert_canon_localrestult.is_canonical =
                    COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
                return false;
            }
        }
    }

    return true;
}

/*!
 * @brief Compute the canonicity of the object vertex against the stick condition.
 *
 * @param vertex The object vertex.
 * @param parent The parent vertex (if any).
 * @param parent_is_root A flag indicating if the object vertex is near the root.
 * @return True if canonical false otherwise.
 */
STATIC_INLINE bool comp_wptt_vert_canon_stick(const note_wptt_node_t *vertex,
                                              const note_wptt_node_t *parent,
                                              bool parent_is_root)
{
    int    active_weight = 0;
    size_t i             = 0;

    for (i = 0; i <= vertex->number_of_children; i++)
    {
        active_weight += vertex->weights[i];
    }

    if ((false == comp_wptt_vert_canon_stick_parent(parent,
                                                    active_weight,
                                                    vertex->number_of_children)) ||

        /*@@@HACK: This is passing potentially undefined data. It's not a big deal since we are
         * checking right away, but is technically wrong. */
        (false == comp_wptt_vert_canon_stick_child(vertex->children[0],
                                                   vertex->number_of_children,
                                                   active_weight)))
    {
        return false;
    }

    /* If we are on a leaf vertex. */
    else if (0 == vertex->number_of_children)
    {
        int parent_weight = 0;
        if (NULL != parent)
        {
            for (i = 0; i <= parent->number_of_children; i++)
            {
                parent_weight += parent->weights[i];
            }
        }

        /* Check that the weight is not $\pm 1$, and not zero (unless the parent is the root,
         * infinity tangle)*/
        if ((-1 == active_weight) ||
            (1 == active_weight) ||
            ((0 == active_weight) &&
             ((false == parent_is_root) ||
              ((true == parent_is_root) &&
               ((1 < parent->number_of_children) ||
                ((1 == parent->number_of_children) && (0 != parent_weight)))))))
        {
            comp_wptt_vert_canon_localrestult.is_canonical =
                COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
            return false;
        }
    }

    return true;
}

/*!
 * @brief Compute the canonicity of the object vertex against the positivity condition.
 *
 * @param vertex The object vertex.
 * @param parent The parent vertex.
 * @return True if canonical false otherwise.
 */
STATIC_INLINE bool comp_wptt_vert_canon_positivity(const note_wptt_node_t *vertex,
                                                   const note_wptt_node_t *parent)
{
    int sign = 1;

    if (COMP_WPTT_VERT_CANON_POS_POS == comp_wptt_vert_canon_localcfg->positivity)
    {
        sign *= -1;
    }

    /* If the object vertex has a single child, weight $\pm2$, and both the parent and child are
     * essential.*/
    if ((1 == vertex->number_of_children) &&
        ((sign * 2 == vertex->weights[0]) ||
         (sign * 2 == vertex->weights[1])) &&
        (1 < parent->number_of_children) &&
        (1 < vertex->children[0]->number_of_children))
    {
        comp_wptt_vert_canon_localrestult.is_canonical =
            COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
        return false;
    }
    /* If the object vertex is a leaf with sign $\pm 2$*/
    if ((0 == vertex->number_of_children) &&
        ((sign * 2 == vertex->weights[0]) ||
         (sign * 2 == vertex->weights[1])))
    {
        comp_wptt_vert_canon_localrestult.is_canonical =
            COMP_WPTT_VERT_CANON_IS_NONCANONICAL;
        return false;
    }
    return true;
}
