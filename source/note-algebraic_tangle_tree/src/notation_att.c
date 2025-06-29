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

STATIC_INLINE_UINT8 note_att_traverse(note_att_node_t *node,
                                      char *str,
                                      size_t buffer_size);
STATIC_INLINE_UINT8 note_att_add_tv(const note_tv_t *tv,
                                    char *str,
                                    size_t buffer_size);
STATIC_INLINE_UINT8 note_att_traverse_string(note_att_t *att,
                                             note_att_node_t *node,
                                             char *str,
                                             size_t att_node_idx);
STATIC_INLINE_UINT8 note_att_process_tv(const char *str, note_att_t *att);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t note_att_decode(char *str, note_att_t *att)
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
        att->root        = &(att->node_buffer[0]);
        note_att_str_idx = 0u;
        note_att_tv_idx  = 0u;
        if (str[0] == '+')
        {
            NOTE_ATT_SET_OP(att->root->operation, NOTE_ATT_OP_PLUS);
        }
        else if (str[0] == 'v')
        {
            NOTE_ATT_SET_OP(att->root->operation, NOTE_ATT_OP_VEE);
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
uint8_t note_att_encode(note_att_t att, char *str, size_t buffer_size)
{
    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;

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
        uint8_t result = NOTE_ATT_TRAVERSE_FAIL;
        result = note_att_traverse(att.root, str, buffer_size);
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
STATIC_INLINE_UINT8 note_att_traverse(note_att_node_t *node,
                                      char *str,
                                      size_t buffer_size)
{
    uint8_t retval = NOTE_ATT_TRAVERSE_SUCCESS;

    if (NOTE_ATT_CHK_OP(node->operation, NOTE_ATT_OP_PLUS) == true)
    {
        strcpy(str, "+");
    }
    else if (NOTE_ATT_CHK_OP(node->operation, NOTE_ATT_OP_VEE) == true)
    {
        strcpy(str, "v");
    }
    else
    {
        retval = NOTE_ATT_TRAVERSE_FAIL;
    }

    buffer_size -= strlen(str);
    str         += strlen(str);

    if (retval != NOTE_ATT_TRAVERSE_FAIL)
    {
        if (node->L_child != NULL)
        {
            retval = note_att_traverse(node->L_child, str, buffer_size);
        }
        else if (node->L_tv != NULL)
        {
            retval = note_att_add_tv(node->L_tv, str, buffer_size);
        }
        else
        {
            retval = NOTE_ATT_TRAVERSE_FAIL;
        }
    }
    str += strlen(str);

    if (retval != NOTE_ATT_TRAVERSE_FAIL)
    {
        if (node->R_child != NULL)
        {
            retval = note_att_traverse(node->R_child, str, buffer_size);
        }
        else if (node->R_tv != NULL)
        {
            retval = note_att_add_tv(node->R_tv, str, buffer_size);
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
 * @return Indicate success failure of adding the twist vector.
 */
STATIC_INLINE_UINT8 note_att_add_tv(const note_tv_t *tv,
                                    char *str,
                                    size_t buffer_size)
{
    uint8_t ret_val = NOTE_ATT_TRAVERSE_FAIL;

    if (tv != NULL)
    {
        uint8_t result = NOTE_DEFS_ENCODE_FAIL;
        result = note_tv_encode(*tv, str, buffer_size);
        if (result == NOTE_DEFS_ENCODE_SUCCESS)
        {
            ret_val = NOTE_ATT_TRAVERSE_SUCCESS;
        }
    }
    return ret_val;
}

/*!
 * @brief Walk the string converting it to an algebraic tangle tree.
 * @param att The store-storage_interface location for the algebraic tangle tree.
 * @param node
 * @param str
 * @param att_node_idx
 * @return
 */
STATIC_INLINE_UINT8 note_att_traverse_string(note_att_t *att,
                                             note_att_node_t *node,
                                             char *str,
                                             size_t att_node_idx)
{
    uint8_t ret_val     = NOTE_ATT_TRAVERSE_SUCCESS;
    size_t  new_att_gen = 0x0u;

    node->L_child = NULL;
    node->R_child = NULL;
    node->L_tv    = NULL;
    node->R_tv    = NULL;
    /* +[4 3 3 5 6]v+[3 3 3][2 2 3] */
    if (str[note_att_str_idx] == '[')
    {
        node->L_tv = &(att->tv_buffer[note_att_tv_idx]);
        ret_val    = note_att_process_tv(str, att);
        note_att_tv_idx++;
    }
    else
    {
        new_att_gen++;
        node->L_child = &(att->node_buffer[att_node_idx + new_att_gen]);
        if (str[note_att_str_idx] == '+')
        {
            NOTE_ATT_SET_OP(node->L_child->operation, NOTE_ATT_OP_PLUS);
        }
        else if (str[note_att_str_idx] == 'v')
        {
            NOTE_ATT_SET_OP(node->L_child->operation, NOTE_ATT_OP_VEE);
        }
        else
        {
            ret_val = NOTE_DEFS_DECODE_FAIL;
        }
        note_att_str_idx++;
        ret_val = note_att_traverse_string(
            att, node->L_child, str, att_node_idx + new_att_gen);
    }

    if ((str[note_att_str_idx] == '[') && (ret_val == NOTE_ATT_TRAVERSE_SUCCESS))
    {
        node->R_tv = &(att->tv_buffer[note_att_tv_idx]);
        ret_val    = note_att_process_tv(str, att);
        note_att_tv_idx++;
    }
    else
    {
        new_att_gen++;
        node->R_child = &(att->node_buffer[att_node_idx + new_att_gen]);
        if (str[note_att_str_idx] == '+')
        {
            NOTE_ATT_SET_OP(node->R_child->operation, NOTE_ATT_OP_PLUS);
        }
        else if (str[note_att_str_idx] == 'v')
        {
            NOTE_ATT_SET_OP(node->R_child->operation, NOTE_ATT_OP_VEE);
        }
        else
        {
            ret_val = NOTE_DEFS_DECODE_FAIL;
        }
        note_att_str_idx++;
        ret_val = note_att_traverse_string(
            att, node->R_child, str, att_node_idx + new_att_gen);
    }

    return ret_val;
}

/*!
 *
 * @param str
 * @param att
 * @return
 */
STATIC_INLINE_UINT8 note_att_process_tv(const char *str, note_att_t *att)
{
    uint8_t ret_val = NOTE_ATT_TRAVERSE_FAIL;
    char    string_buffer[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10];
    size_t  i;

    for (i = 0; i < strlen(str); i++)
    {
        string_buffer[i] = str[note_att_str_idx + i];
        if (str[note_att_str_idx + i] == ']')
        {
            string_buffer[i + 1] = '\0';
            note_tv_decode(string_buffer, &att->tv_buffer[note_att_tv_idx]);
            note_att_str_idx += i + 1;
            ret_val           = NOTE_ATT_TRAVERSE_SUCCESS;
            break;
        }
    }
    return ret_val;
}
