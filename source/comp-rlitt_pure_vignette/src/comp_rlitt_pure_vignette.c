/*!
 *  @file comp_rlitt_pure_vignette.c
 *
 *  @brief  A rlitt_pure_vignette module
 *
 *
 *  @author   Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "comp_rlitt_pure_vignette.h"
#include "bits/stdint-uintn.h"
#include "computation_defs.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "tang_defs.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

#define COMP_RLITT_PURE_VIGNETTE_STACK_SIZE       (UTIL_TANG_DEFS_MAX_CROSSINGNUM)
#define COMP_RLITT_PURE_VIGNETTE_STR_BUFF_SIZE    (UTIL_TANG_DEFS_MAX_CROSSINGNUM * 0x3u)

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/


/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE_UINT8 comp_rlitt_pure_vignette_walk_tree(const note_wptt_t *tree);


/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the RLITT pure vignette computation module.
 *
 */
static comp_rlitt_pure_vignette_config_t *comp_rlitt_pure_vignette_localcfg = NULL;

/*!
 * @brief The local result of the RLITT pure vignette computation module.
 *
 */
static comp_rlitt_pure_vignette_result_t comp_rlitt_pure_vignette_localrestult = {};

/*!
 * @brief The local string buffer of the RLITT pure vignette computation module.
 *
 */
static char comp_rlitt_pure_vignette_str[COMP_RLITT_PURE_VIGNETTE_STR_BUFF_SIZE] = { '\0' };

/*!
 * @brief The local computation status of the RLITT pure vignette computation module.
 *
 */
static bool comp_rlitt_pure_vignette_executed = false;

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_pure_vignette_config(comp_rlitt_pure_vignette_config_t *config_arg)
{
    uint8_t ret_val = COMP_DEFS_CONFIG_FAIL;

    comp_rlitt_pure_vignette_localcfg = NULL;

    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= COMP_RLITT_PURE_VIGNETTE_CONFIG_IS_NULL;
    } /*Ensure the wptt is not empty.*/
    else if (config_arg->wptt == NULL)
    {
        ret_val |= COMP_RLITT_PURE_VIGNETTE_CONFIG_NULLTREE;
    }
    else
    {
        size_t i;
        /* Set the config. */
        comp_rlitt_pure_vignette_localcfg = config_arg;

        /* Clear the return value*/
        comp_rlitt_pure_vignette_localrestult.result = NULL;

        for (i = 0; i < COMP_RLITT_PURE_VIGNETTE_STR_BUFF_SIZE; i++)
        {
            comp_rlitt_pure_vignette_str[i] = '\0';
        }

        /*clear the executed status*/
        comp_rlitt_pure_vignette_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t comp_rlitt_pure_vignette_compute()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (comp_rlitt_pure_vignette_localcfg == NULL)
    {
        ret_val |= COMP_RLITT_PURE_VIGNETTE_COMPUTE_CFG_ERROR;
    } /*Ensure not previously executed.*/
    else if (comp_rlitt_pure_vignette_executed != false)
    {
        ret_val |= COMP_RLITT_PURE_VIGNETTE_COMPUTE_ALREADY_COMPUTED;
    }
    else
    {
        comp_rlitt_pure_vignette_executed = true;
        ret_val = COMP_DEFS_COMPUTE_SUCCESS;

        ret_val |= comp_rlitt_pure_vignette_walk_tree(comp_rlitt_pure_vignette_localcfg->wptt);
        comp_rlitt_pure_vignette_localrestult.result = (const char *)comp_rlitt_pure_vignette_str;

        if ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) &&
            (comp_rlitt_pure_vignette_localcfg->storage_write != NULL))
        {
            uint8_t write_retval = NOTE_DEFS_ENCODE_SUCCESS;
            char    result_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };
            write_retval |= note_wptt_encode(*comp_rlitt_pure_vignette_localcfg->wptt,
                                             result_str,
                                             NOTE_WPTT_MAX_STR_LEN);

            if (write_retval == NOTE_DEFS_ENCODE_SUCCESS)
            {
                comp_rlitt_pure_vignette_localcfg->storage_write(result_str,
                                                                 "pure_vignette",
                                                                 comp_rlitt_pure_vignette_localrestult
                                                                 .result);
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
const comp_rlitt_pure_vignette_result_t *comp_rlitt_pure_vignette_result()
{
    const comp_rlitt_pure_vignette_result_t *ret_val = NULL;

    if (comp_rlitt_pure_vignette_localcfg == NULL)
    {
        ret_val = NULL;
    } /*Ensure not previously executed.*/
    else if (comp_rlitt_pure_vignette_executed == false)
    {
        ret_val = NULL;
    }
    else
    {
        ret_val = (const comp_rlitt_pure_vignette_result_t *)&comp_rlitt_pure_vignette_localrestult;
    }
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief Walk the input tree and determine paren set for each vertex.
 *
 * @param tree The tree to walk.
 * @return A status indicator for the function.
 */
STATIC_INLINE_UINT8 comp_rlitt_pure_vignette_walk_tree(const note_wptt_t *tree)
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_SUCCESS;
    char *  str_p   = comp_rlitt_pure_vignette_str;
    char *  str_end = &comp_rlitt_pure_vignette_str[COMP_RLITT_PURE_VIGNETTE_STR_BUFF_SIZE - 1];

    *str_p = 'i';
    str_p++;

    /* We are going to use count instead of index. This helps with intuiting the state of the stack.
     * The count starts at 1 since the root is going to be added to the stack before the main loop.
     */
    size_t            stack_count = 1;
    note_wptt_node_t *stack[COMP_RLITT_PURE_VIGNETTE_STACK_SIZE]          = { NULL };
    size_t            childidx_stack[COMP_RLITT_PURE_VIGNETTE_STACK_SIZE] = { 0 };

    stack[stack_count - 1] = tree->root;

    while ((COMP_DEFS_COMPUTE_SUCCESS == ret_val) && (stack_count != 0))
    {
        note_wptt_node_t *active_vertex = stack[stack_count - 1];

        if (0 == active_vertex->number_of_children)
        {
            if (str_p + 1 <= str_end)
            {
                *str_p = '[';
                str_p++;
                *str_p = ']';
                str_p++;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_RLITT_PURE_VIGNETTE_COMPUTE_STR_BUFFER);
            }
        }
        else if (0 == childidx_stack[stack_count - 1])
        {
            if (str_p <= str_end)
            {
                *str_p = '(';
                str_p++;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_RLITT_PURE_VIGNETTE_COMPUTE_STR_BUFFER);
            }
        }
        else if (active_vertex->number_of_children == childidx_stack[stack_count - 1])
        {
            if (str_p <= str_end)
            {
                *str_p = ')';
                str_p++;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_RLITT_PURE_VIGNETTE_COMPUTE_STR_BUFFER);
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
            if (stack_count < COMP_RLITT_PURE_VIGNETTE_STACK_SIZE)
            {
                stack_count++;
                stack[stack_count - 1]          = active_vertex->children[child_idx];
                childidx_stack[stack_count - 1] = 0;
            }
            else
            {
                ret_val |= COMP_STATUS_BLDR(COMP_DEFS_COMPUTE_FAIL,
                                            COMP_RLITT_PURE_VIGNETTE_COMPUTE_STACK_OVRFLW);
            }
        }
    }

    return ret_val;
}
