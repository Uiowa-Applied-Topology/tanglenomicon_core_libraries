/*!
 *  @file notation_att.c
 *
 *  @brief  Notation module for twist vectors.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "notation_att.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief store-storage_interface for the current string index.
 */
static size_t note_att_str_idx = 0u;

/*!
 * @brief store-storage_interface for the current twist vector index.
 */
static size_t note_att_tv_idx = 0u;
/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

static inline uint8_t note_att_traverse(note_att_node_t *node, char *str);
static inline uint8_t note_att_add_tv(note_tv_t *tv, char *str);
static inline uint8_t note_att_traverse_string(note_att_t *att,
                                               note_att_node_t *node, char *str,
                                               size_t att_node_idx);
static inline uint8_t note_att_process_tv(char *str, note_att_t *att);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t note_att_encode(char *str, note_att_t *att)
{

    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    if ((str == NULL) || (att == NULL))
    {
        retval = NOTE_DEFS_DECODE_FAIL;
    }
    else if ((att->node_buffer == NULL) || (att->tv_buffer == NULL) ||
             (att->tv_buffer_len == 0) || (att->node_buffer_len == 0))
    {
        retval = NOTE_DEFS_DECODE_FAIL;
    }
    else
    {
        att->root = &(att->node_buffer[0]);
        note_att_str_idx = 0u;
        note_att_tv_idx = 0u;
        if (str[0] == '+')
        {
            NOTE_ATT_CLR_OP(att->root->flavor);
            NOTE_ATT_SET_OP(att->root->flavor, NOTE_ATT_OP_PLUS);
        }
        else if (str[0] == 'v')
        {
            NOTE_ATT_CLR_OP(att->root->flavor);
            NOTE_ATT_SET_OP(att->root->flavor, NOTE_ATT_OP_VEE);
        }
        else
        {
            retval = NOTE_DEFS_DECODE_FAIL;
        }
        note_att_str_idx++;
        retval = note_att_traverse_string(att, att->root, str, 0x0u);
    }
    return retval;
}

/*
 *  Documentation in header
 */
uint8_t note_att_decode(note_att_t att, char *str)
{

    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    uint8_t result = NOTE_ATT_TRAVERSE_FAIL;
    if (str == NULL)
    {
        retval = NOTE_DEFS_ENCODE_FAIL;
    }
    else if ((att.root) == NULL)
    {
        retval = NOTE_DEFS_ENCODE_FAIL;
    }
    else
    {
        result = note_att_traverse(att.root, str);
        if (result == NOTE_ATT_TRAVERSE_SUCCESS)
        {
            retval = NOTE_DEFS_ENCODE_SUCCESS;
        }
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

/*!
 *
 * @param node
 * @param str
 * @return
 */
static uint8_t note_att_traverse(note_att_node_t *node, char *str)
{
    uint8_t retval = NOTE_ATT_TRAVERSE_SUCCESS;

    if (NOTE_ATT_CHK_OP(node->flavor, NOTE_ATT_OP_PLUS) == true)
    {
        strcpy(str, "+");
    }
    else if (NOTE_ATT_CHK_OP(node->flavor, NOTE_ATT_OP_VEE) == true)
    {
        strcpy(str, "v");
    }
    else
    {
        retval = NOTE_ATT_TRAVERSE_FAIL;
    }
    str += strlen(str);

    if (retval != NOTE_ATT_TRAVERSE_FAIL)
    {
        if (NOTE_ATT_CHK_L_TYPE(node->flavor, NOTE_ATT_TYPE_L_OP) == true)
        {
            retval = note_att_traverse((note_att_node_t *)node->L_child, str);
        }
        else if (NOTE_ATT_CHK_L_TYPE(node->flavor, NOTE_ATT_TYPE_L_TANG) ==
                 true)
        {
            retval = note_att_add_tv((note_tv_t *)node->L_child, str);
        }
        else
        {
            retval = NOTE_ATT_TRAVERSE_FAIL;
        }
    }
    str += strlen(str);

    if (retval != NOTE_ATT_TRAVERSE_FAIL)
    {
        if (NOTE_ATT_CHK_R_TYPE(node->flavor, NOTE_ATT_TYPE_R_OP) == true)
        {
            retval = note_att_traverse((note_att_node_t *)node->R_child, str);
        }
        else if (NOTE_ATT_CHK_R_TYPE(node->flavor, NOTE_ATT_TYPE_R_TANG) ==
                 true)
        {

            retval = note_att_add_tv((note_tv_t *)node->R_child, str);
        }
        else
        {
            retval = NOTE_ATT_TRAVERSE_FAIL;
        }
    }

    return retval;
}

/*!
 * @brief Decode a string into a twist vector and report succes.
 * @param tv The note_tv_t store-storage_interface to store the data to.
 * @param str The data to decode.
 * @return Indicate succes failure of adding the twist vector.
 */
static uint8_t note_att_add_tv(note_tv_t *tv, char *str)
{
    uint8_t ret_val = NOTE_ATT_TRAVERSE_SUCCESS;
    uint8_t result = NOTE_DEFS_DECODE_FAIL;
    result = note_tv_decode(*tv, str);
    if (result != NOTE_DEFS_DECODE_SUCCESS)
    {
        ret_val = NOTE_ATT_TRAVERSE_FAIL;
    }
    return ret_val;
}

/*!
 * @brief Walk the string converting it to an algebraic tangle tree.
 * @param att The store-storage_interface location for the algebraic tangle
 * tree.
 * @param node
 * @param str
 * @param att_node_idx
 * @return
 */
static uint8_t note_att_traverse_string(note_att_t *att, note_att_node_t *node,
                                        char *str, size_t att_node_idx)
{
    uint8_t ret_val = NOTE_ATT_TRAVERSE_SUCCESS;
    size_t new_att_gen = 0x0u;
    // +[4 3 3 5 6]v+[3 3 3][2 2 3]
    if (str[note_att_str_idx] == '+')
    {
        NOTE_ATT_CLR_L_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_L_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_L_OP);
        new_att_gen++;
        node->L_child = (void *)&(att->node_buffer[att_node_idx + new_att_gen]);
        NOTE_ATT_CLR_OP(att->node_buffer[att_node_idx + new_att_gen].flavor);
        NOTE_ATT_SET_OP(att->node_buffer[att_node_idx + new_att_gen].flavor,
                        NOTE_ATT_OP_PLUS);
        note_att_str_idx++;
        ret_val =
            note_att_traverse_string(att, (note_att_node_t *)node->L_child, str,
                                     att_node_idx + new_att_gen);
    }
    else if (str[note_att_str_idx] == 'v')
    {
        NOTE_ATT_CLR_L_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_L_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_L_OP);
        new_att_gen++;
        node->L_child = (void *)&(att->node_buffer[att_node_idx + new_att_gen]);
        NOTE_ATT_CLR_OP(att->node_buffer[att_node_idx + new_att_gen].flavor);
        NOTE_ATT_SET_OP(att->node_buffer[att_node_idx + new_att_gen].flavor,
                        NOTE_ATT_OP_VEE);
        note_att_str_idx++;
        ret_val =
            note_att_traverse_string(att, (note_att_node_t *)node->L_child, str,
                                     att_node_idx + new_att_gen);
    }
    else if (str[note_att_str_idx] == '[')
    {
        NOTE_ATT_CLR_L_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_L_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_L_TANG);
        node->L_child = (void *)&(att->tv_buffer[note_att_tv_idx]);
        ret_val = note_att_process_tv(str, att);
        note_att_tv_idx++;
    }
    else
    {
        ret_val = NOTE_DEFS_DECODE_FAIL;
    }

    if ((str[note_att_str_idx] == '+') &&
        (ret_val == NOTE_ATT_TRAVERSE_SUCCESS))
    {
        NOTE_ATT_CLR_R_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_R_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_R_OP);
        new_att_gen++;
        node->R_child = (void *)&(att->node_buffer[att_node_idx + new_att_gen]);
        NOTE_ATT_CLR_OP(att->node_buffer[att_node_idx + new_att_gen].flavor);
        NOTE_ATT_SET_OP(att->node_buffer[att_node_idx + new_att_gen].flavor,
                        NOTE_ATT_OP_PLUS);
        note_att_str_idx++;
        ret_val =
            note_att_traverse_string(att, (note_att_node_t *)node->R_child, str,
                                     att_node_idx + new_att_gen);
    }
    else if (str[note_att_str_idx] == 'v')
    {
        NOTE_ATT_CLR_R_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_R_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_R_OP);
        new_att_gen++;
        node->R_child = (void *)&(att->node_buffer[att_node_idx]);
        NOTE_ATT_CLR_OP(att->node_buffer[att_node_idx + new_att_gen].flavor);
        NOTE_ATT_SET_OP(att->node_buffer[att_node_idx + new_att_gen].flavor,
                        NOTE_ATT_OP_VEE);
        note_att_str_idx++;
        ret_val =
            note_att_traverse_string(att, (note_att_node_t *)node->R_child, str,
                                     att_node_idx + new_att_gen);
    }
    else if (str[note_att_str_idx] == '[')
    {
        NOTE_ATT_CLR_R_TYPE(att->node_buffer[att_node_idx].flavor);
        NOTE_ATT_SET_R_TYPE(att->node_buffer[att_node_idx].flavor,
                            NOTE_ATT_TYPE_R_TANG);
        node->R_child = (void *)&(att->tv_buffer[note_att_tv_idx]);
        ret_val = note_att_process_tv(str, att);
        note_att_tv_idx++;
    }
    else
    {
        ret_val = NOTE_DEFS_DECODE_FAIL;
    }

    return ret_val;
}

/*!
 *
 * @param str
 * @param att
 * @return
 */
static uint8_t note_att_process_tv(char *str, note_att_t *att)
{
    uint8_t ret_val = NOTE_ATT_TRAVERSE_FAIL;
    char string_buffer[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10];
    size_t i;
    for (i = 0; i < strlen(str); i++)
    {
        string_buffer[i] = str[note_att_str_idx + i];
        if (str[note_att_str_idx + i] == ']')
        {
            string_buffer[i + 1] = '\0';
            note_tv_encode(string_buffer, &att->tv_buffer[note_att_tv_idx]);
            note_att_str_idx += i + 1;
            ret_val = NOTE_ATT_TRAVERSE_SUCCESS;
            break;
        }
    }
    return ret_val;
}