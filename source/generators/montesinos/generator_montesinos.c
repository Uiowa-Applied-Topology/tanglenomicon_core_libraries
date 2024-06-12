/*!
 *  @file generator_montesinos.c
 *
 *  @brief  A module for generating montesinos tangles.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

/******************************************************************************/
/************************** Includes ******************************************/
/******************************************************************************/

#include "generator_montesinos.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Typedefs ******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
static inline uint8_t gen_montesinos_process_lists();
static inline uint8_t gen_montesinos_process_loop_state(size_t *stack);
/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the montesinos gen module.
 *
 */
static gen_montesinos_config_t *gen_montesinos_localcfg = NULL;

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t gen_montesinos_config(gen_montesinos_config_t *config_arg)
{
    uint8_t ret_val = GEN_DEFS_CONFIG_FAIL;
    if (config_arg == NULL)
    {
        ret_val |= GEN_MONTESINOS_CONFIG_IS_NULL;
    }
    else
    {
        /* Set the config. */
        gen_montesinos_localcfg = config_arg;

        ret_val = GEN_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t gen_montesinos_generate()
{

    uint8_t ret_val = GEN_DEFS_GENERATION_FAIL;
    // build tree
    size_t i = 0;
    note_att_t *att_local = gen_montesinos_localcfg->att_n;
    size_t num_of_tv_sets = gen_montesinos_localcfg->tv_sets_len;
    note_att_node_t *node = NULL;
    att_local->root = &(att_local->node_buffer[0]);

    for (i = 0; i < num_of_tv_sets - 2; i++)
    {
        node = &(att_local->node_buffer[i]);
        node->flavor = NOTE_ATT_FLVR(NOTE_ATT_OP_PLUS, NOTE_ATT_TYPE_L_TANG,
                                     NOTE_ATT_TYPE_R_OP);
        node->R_child = (void *)&(att_local->node_buffer[i + 1]);
    }

    node = &(att_local->node_buffer[num_of_tv_sets - 2]);
    node->flavor = NOTE_ATT_FLVR(NOTE_ATT_OP_PLUS, NOTE_ATT_TYPE_L_TANG,
                                 NOTE_ATT_TYPE_R_TANG);

    // process lists
    ret_val = gen_montesinos_process_lists();
    return ret_val;
}

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
static uint8_t gen_montesinos_process_lists()
{
    uint8_t ret_val = GEN_DEFS_GENERATION_SUCCESS;
    note_att_t *att_local = gen_montesinos_localcfg->att_n;
    size_t stack[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
    size_t stack_ptr = 0;
    size_t *loop_lims = gen_montesinos_localcfg->tv_set_lens;
    size_t list_cnt = gen_montesinos_localcfg->tv_sets_len;

    stack[0] = 0;
    while ((stack[0] < loop_lims[0]) &&
           (ret_val == GEN_DEFS_GENERATION_SUCCESS))
    {
        if (stack[stack_ptr] < loop_lims[stack_ptr])
        {
            if (stack_ptr < (list_cnt - 1))
            {
                stack_ptr++;
                stack[stack_ptr] = 0;
            }
            else
            {
                ret_val = gen_montesinos_process_loop_state(stack);
                stack[stack_ptr]++;
            }
        }
        else
        {
            stack_ptr--;
            stack[stack_ptr]++;
        }
    }

    return ret_val;
}
static uint8_t gen_montesinos_process_loop_state(size_t *stack)
{
    uint8_t ret_val = GEN_DEFS_GENERATION_FAIL;
    uint8_t decode_result = NOTE_DEFS_ENCODE_FAIL;
    uint8_t write_status = STORE_DEFS_WRITE_FAIL;
    size_t num_of_tv_sets = gen_montesinos_localcfg->tv_sets_len;
    note_tv_t **tvs = gen_montesinos_localcfg->tv_sets;
    note_att_t *att_local = gen_montesinos_localcfg->att_n;
    note_att_node_t *node = NULL;
    char *value = "att";
    size_t i = 0;
    size_t stack_val = 0;

    gen_montesinos_localcfg->str_buff[0] = '\0';
    for (i = 0u; i < num_of_tv_sets - 2; i++)
    {
        node = &(att_local->node_buffer[i]);
        stack_val = stack[i];
        node->L_child = (void *)&(tvs[i][stack_val]);
    }
    node = &(att_local->node_buffer[num_of_tv_sets - 2]);
    stack_val = stack[num_of_tv_sets - 2];
    node->L_child = (void *)&(tvs[num_of_tv_sets - 2][stack_val]);
    stack_val = stack[num_of_tv_sets - 1];
    node->R_child = (void *)&(tvs[num_of_tv_sets - 1][stack_val]);

    decode_result =
        note_att_decode(*att_local, gen_montesinos_localcfg->str_buff);

    if (decode_result == NOTE_DEFS_ENCODE_SUCCESS)
    {
        /* Write the data to the storage device. */
        /*@@@TODO: we need to add the correct document values.*/
        write_status = gen_montesinos_localcfg->storage_write(
            gen_montesinos_localcfg->str_buff, value,
            gen_montesinos_localcfg->str_buff);
        if (write_status == STORE_DEFS_WRITE_SUCCESS)
        {
            ret_val = GEN_DEFS_GENERATION_SUCCESS;
        }
    }

    return ret_val;
}