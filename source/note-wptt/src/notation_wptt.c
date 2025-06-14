/*!
 *  @file notation_wptt.c
 *
 *  @brief  Notation module for template.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "notation_wptt.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/******************************************************************************/
/************************** Private Typedef ***********************************/
/******************************************************************************/

/*!
 * @brief The function pointer type for decode dictionary functions.
 */
typedef uint8_t (*char_handler_funptr_t)(char **str);

/*!
 * @brief The type for the elements of the decode dictionary.
 */
typedef struct note_wptt_decode_char_dic_t
{
    char *char_class;
    char_handler_funptr_t funptr;

} note_wptt_decode_char_dic_t;

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief The character for the identity label.
 */
#define NOTE_wptt_V4_LABEL_I_STR ('i')

/*!
 * @brief The character for the x rotation label.
 */
#define NOTE_wptt_V4_LABEL_X_STR ('x')

/*!
 * @brief The character for the y rotation label.
 */
#define NOTE_wptt_V4_LABEL_Y_STR ('y')

/*!
 * @brief The character for the z rotation label.
 */
#define NOTE_wptt_V4_LABEL_Z_STR ('z')

/*!
 * @brief The size of the decode stack.
 *
 */
#define NOTE_wptt_STACK_SIZE (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/*!
 * @brief The size of the dictionary of decode functions.
 *
 */
#define NOTE_wptt_DECODE_DICT_SIZE (6u)

/*!
 * @brief The number base used for str->int functions.
 *
 */
#define NOTE_wptt_INT_BASE (10u)

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/************************** Decode path Function Declarations *****************/
STATIC_INLINE_UINT8 note_wptt_decode_push_node();
STATIC_INLINE note_wptt_V4_label_e note_wptt_decode_get_v4_label(char label);
STATIC_INLINE bool note_wptt_decode_check_charset(const char *valid_chars,
                                                   const char str);
STATIC_INLINE_UINT8 note_wptt_decode_add_child();
STATIC_INLINE_UINT8 note_wptt_decode_space_handler(char **str);
STATIC_INLINE_UINT8 note_wptt_decode_opn_p_handler(char **str);
STATIC_INLINE_UINT8 note_wptt_decode_opn_a_handler(char **str);
STATIC_INLINE_UINT8 note_wptt_decode_opn_b_handler(char **str);
STATIC_INLINE_UINT8 note_wptt_decode_cls_handler(char **str);
STATIC_INLINE_UINT8 note_wptt_decode_weight_handler(char **str);

/************************** Encode path Function Declarations *****************/

STATIC_INLINE bool note_wptt_encode_stick_check(note_wptt_node_t *active_node_p);
STATIC_INLINE_UINT8 note_wptt_encode_get_child_ordered_idx(
    const note_wptt_node_t *active_node_p);
STATIC_INLINE_UINT8 note_wptt_encode_insert_label(note_wptt_V4_label_e label,
                                                   char **str_p,
                                                   const char *buffer_end_p);

STATIC_INLINE_UINT8 note_wptt_encode_insert_char(char new_char,
                                                  char **str_p,
                                                  const char *buffer_end_p);

STATIC_INLINE_UINT8 note_wptt_encode_insert_int(int8_t new_int,
                                                 char **str_p,
                                                 const char *buffer_end_p);

STATIC_INLINE_UINT8 note_wptt_encode_insert_space(char **str_p,
                                                   const char *buffer_start_p,
                                                   const char *buffer_end_p);

STATIC_INLINE_UINT8 note_wptt_encode_insert_stick(note_wptt_node_t *active_node_p,
                                                   char **str_p,
                                                   const char *buffer_end_p);

STATIC_INLINE_UINT8 note_wptt_encode_complete_active_node(
    const note_wptt_node_t *active_node_p,
    char **str_p,
    size_t ordered_child_idx,
    const char *buffer_start_p,
    const char *buffer_end_p);
STATIC_INLINE_UINT8 note_wptt_encode_process_active_node(
    note_wptt_node_t *active_node_p,
    char **str_p,
    size_t ordered_child_idx,
    const char *buffer_start_p,
    const char *buffer_end_p);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/
/*!
 * @brief The wptt stack used in the encode and decode functions. This needs
 *        to be initialized at the beginning of the using function.
 */
static note_wptt_node_t *wptt_node_stack[NOTE_wptt_STACK_SIZE] = {NULL};

/*!
 * @brief The current number of elements on the wptt stack.
 */
static size_t wptt_stack_len = 0;

/*!
 * @brief Pointer to a buffer of wptt nodes. Used by decode path functions.
 */
static note_wptt_node_buffer_t *decode_buffer = NULL;

/*!
 * @brief The stack containing the current child index used in the encode path
 *        functions.
 */
uint8_t child_idx_stack[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t note_wptt_decode(char *str, note_wptt_t *wptt)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    /*Clear the buffer and stack*/
    decode_buffer = NULL;
    wptt_node_stack[0] = NULL;
    wptt_stack_len = 0;

    /*Initialize the character checking dictionary*/
    const note_wptt_decode_char_dic_t charcheck_dict[] = {
        {"(", &note_wptt_decode_opn_p_handler},
        {"<", &note_wptt_decode_opn_a_handler},
        {"[", &note_wptt_decode_opn_b_handler},
        {")>", &note_wptt_decode_cls_handler},
        {" ", &note_wptt_decode_space_handler},
        {"-0123456789", &note_wptt_decode_weight_handler}};

    /*Do basic error checking.*/
    if (strlen(str) <= 2)
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_EMPTY_STR);
    }
    else if (NULL == wptt)
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_NULL_DEST);
    }
    else if ((NULL == wptt->node_buffer.buffer) ||
             (0 == wptt->node_buffer.size))
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_BUFFER_ERROR);
    }
    else
    {
        /*Main logic of the decode flow*/

        /*Initialize buffer reference to node buffer*/
        decode_buffer = &(wptt->node_buffer);

        /*Initialize wptt root from buffer*/
        wptt->root = &(decode_buffer->buffer[0]);
        wptt->root->order = NOTE_wptt_ORDER_FORWARD;

        /*Check if the string has a V_4 label*/
        wptt->label = note_wptt_decode_get_v4_label(str[0]);
        if (NOTE_wptt_V4_LABEL_NONE != wptt->label)
        {
            str++;
        }

        /*While string still has content and nothing has gone wrong*/
        while (str[0] != '\0' && (NOTE_DEFS_DECODE_SUCCESS == retval))
        {
            size_t i;

            /*For each item in the dictionary*/
            for (i = 0u; i < NOTE_wptt_DECODE_DICT_SIZE; i++)
            {
                if (true == note_wptt_decode_check_charset(
                                charcheck_dict[i].char_class, str[0]))
                {
                    retval |= charcheck_dict[i].funptr(&str);
                    break;
                }
            }
            /*If current character is not in any set throw error*/
            if (i == NOTE_wptt_DECODE_DICT_SIZE)
            {
                retval |= NOTE_STATUS_BLDR(
                    NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_BAD_STR);
            }
        }
    }
    return retval;
}

/*
 *  Documentation in header
 */
uint8_t note_wptt_encode(note_wptt_t wptt, char *str, size_t buffer_size)
{
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    const char *buffer_end_p;
    const char *buffer_start_p;
    wptt_node_stack[0] = wptt.root;
    wptt_stack_len = 0x1u;
    child_idx_stack[0u] = 0;

    /*Do basic error checking.*/
    if (0 == buffer_size)
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_STR_BUF);
    }
    else if (NULL == str)
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_STR_BUF);
    }
    else
    {
        buffer_end_p = str + (buffer_size - 1);
        buffer_start_p = str;
        retval |= note_wptt_encode_insert_label(
            wptt.label, &str, buffer_end_p);
        /*While stack is not empty and string buffer has space*/
        while ((0 < wptt_stack_len) && (str < buffer_end_p) &&
               (NOTE_DEFS_ENCODE_SUCCESS == retval))
        {

            note_wptt_node_t *active_node_p =
                wptt_node_stack[wptt_stack_len - 1];

            /*Do basic error checking.*/
            if (NULL == active_node_p)
            {
                retval |= NOTE_STATUS_BLDR(
                    NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_MALFORMED);
                break;
            }
            else if (active_node_p->order == NOTE_wptt_ORDER_UNINIT)
            {
                retval |= NOTE_STATUS_BLDR(
                    NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_MALFORMED);
                break;
            }
            else
            {
                size_t ordered_child_idx =
                    note_wptt_encode_get_child_ordered_idx(active_node_p);
                /*Check if active node is complete*/
                if (active_node_p->number_of_children <
                    child_idx_stack[wptt_stack_len - 1])
                {
                    retval |= note_wptt_encode_complete_active_node(
                        active_node_p,
                        &str,
                        ordered_child_idx,
                        buffer_start_p,
                        buffer_end_p);

                    /*Pop stack*/
                    if (0 < wptt_stack_len)
                    {
                        wptt_stack_len--;
                    }
                    else
                    {
                        retval |= NOTE_STATUS_BLDR(
                            NOTE_DEFS_ENCODE_FAIL,
                            NOTE_wptt_ENCODE_OVRUNDR_ERROR);
                    }
                }
                else
                {
                    retval |= note_wptt_encode_process_active_node(
                        active_node_p,
                        &str,
                        ordered_child_idx,
                        buffer_start_p,
                        buffer_end_p);
                }
            }
        }
        /*Finish string*/
        if (str < buffer_end_p)
        {
            str[0] = '\0';
        }
        else
        {
            retval |= NOTE_STATUS_BLDR(
                NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_OVRUNDR_ERROR);
        }
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/

/************************** Decode Path Functions *****************************/

/*!
 * @brief Get the label for the input string.
 * @param label The first char of the input string.
 * @return The designator for the label.
 */
STATIC_INLINE note_wptt_V4_label_e note_wptt_decode_get_v4_label(char label)
{
    note_wptt_V4_label_e retval = NOTE_wptt_V4_LABEL_UNINIT;
    /*Check if the string has a V_4 label*/
    switch (label)
    {
    case NOTE_wptt_V4_LABEL_I_STR:
    {
        retval = NOTE_wptt_V4_LABEL_I;
        break;
    }
    case NOTE_wptt_V4_LABEL_X_STR:
    {
        retval = NOTE_wptt_V4_LABEL_X;
        break;
    }
    case NOTE_wptt_V4_LABEL_Y_STR:
    {
        retval = NOTE_wptt_V4_LABEL_Y;
        break;
    }
    case NOTE_wptt_V4_LABEL_Z_STR:
    {
        retval = NOTE_wptt_V4_LABEL_Z;
        break;
    }
    default:
    {
        retval = NOTE_wptt_V4_LABEL_NONE;
    }
    }
    return retval;
}

/*!
 * @brief Determine if a character from the input string is one of the valid
 * characters.
 * @param valid_chars The list of valid characters.
 * @param str_char A character form the input string.
 * @return The truthiness of if the character is one of the valid characters.
 */
STATIC_INLINE bool note_wptt_decode_check_charset(const char *valid_chars,
                                                   const char str_char)
{
    bool retval = false;
    size_t i;
    for (i = 0; i < strlen(valid_chars); i++)
    {
        if (str_char == valid_chars[i])
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*!
 * @brief Dictionary function to consume and advance the to the the next
 * character of the input string.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
/* cppcheck-suppress constParameterPointer*/
STATIC_INLINE_UINT8 note_wptt_decode_space_handler(char **str)
{
    /* cppcheck-suppress uselessAssignmentPtrArg*/
    /* cppcheck-suppress unreadVariable*/
    (*str)++;
    return NOTE_DEFS_DECODE_SUCCESS;
}

/*!
 * @brief Dictionary function to initialize and push a child node onto the
 * stack.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_opn_p_handler(char **str)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    retval |= note_wptt_decode_push_node();
    retval |= note_wptt_decode_add_child();
    (*str)++;
    return retval;
}

/*!
 * @brief Dictionary function to process and create a stick subtree.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_opn_b_handler(char **str)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    int8_t weights[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};
    size_t num_of_weights = 0;
    (*str)++;
    while ((']' != (*str)[0]) && ('\0' != (*str)[0]) &&
           (NOTE_DEFS_DECODE_SUCCESS == retval))
    {
        if ((('0' <= (*str)[0]) && ((*str)[0] <= '9')) || ((*str)[0] == '-'))
        {
            weights[num_of_weights] = strtol(*str, str, NOTE_wptt_INT_BASE);
            num_of_weights++;
            if (' ' == (*str)[0])
            {
                (*str)++;
            }
        }
        else
        {
            retval |= NOTE_STATUS_BLDR(
                NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_BAD_STR);
        }
    }

    if ((']' == (*str)[0]) && (NOTE_DEFS_DECODE_SUCCESS == retval))
    {
        size_t i;
        uint8_t pre_stick_stack_len = wptt_stack_len;
        (*str)++;
        for (i = 1; i < num_of_weights; i++)
        {
            retval |= note_wptt_decode_push_node();
            retval |= note_wptt_decode_add_child();
            wptt_node_stack[wptt_stack_len - 1]->weights[1u] =
                weights[num_of_weights - i];
        }
        retval |= note_wptt_decode_push_node();
        retval |= note_wptt_decode_add_child();
        wptt_node_stack[wptt_stack_len - 1]->weights[0] = weights[0];
        wptt_stack_len = pre_stick_stack_len;
    }
    else
    {
        retval |= NOTE_STATUS_BLDR(
            NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_BAD_STR);
    }

    return retval;
}

/*!
 * @brief Dictionary function to initialize and push a child node onto the stack
 * with a ring number.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_opn_a_handler(char **str)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    retval |= note_wptt_decode_push_node();
    retval |= note_wptt_decode_add_child();
    (*str)++;

    if (NOTE_DEFS_ENCODE_SUCCESS == retval)
    {
        /*Check that the char looks like the start of an integer.*/
        if (!(('0' <= ((*str))[0]) && ((*str)[0] <= '9')) && ((*str)[0] != '-'))
        {
            retval |= NOTE_STATUS_BLDR(
                NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_BAD_STR);
        }
        else if (0 == wptt_stack_len)
        {
            retval |= NOTE_STATUS_BLDR(
                NOTE_DEFS_DECODE_FAIL, NOTE_wptt_DECODE_OVRUNDR_ERROR);
        }
        else
        {
            note_wptt_node_t *active_node_p =
                wptt_node_stack[wptt_stack_len - 1];
            active_node_p->number_of_rings = strtol(
                *str, str, NOTE_wptt_INT_BASE);
        }
    }
    return retval;
}

/*!
 * @brief Dictionary function to pop a node off of the wptt stack and advance
 * to the next character of the string.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_cls_handler(char **str)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    wptt_stack_len--;
    (*str)++;
    return retval;
}

/*!
 * @brief Dictionary function to process an integer weight and advance the input
 * string.
 *
 * @param str A pointer to the pointer a the current character of the input
 * string.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_weight_handler(char **str)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    note_wptt_node_t *active_node_p = wptt_node_stack[wptt_stack_len - 1];
    active_node_p->weights[active_node_p->number_of_children] = strtol(
        *str, str, NOTE_wptt_INT_BASE);
    if (' ' == (*str)[0])
    {
        retval |= NOTE_STATUS_BLDR(
            NOTE_DEFS_DECODE_FAIL,
            NOTE_wptt_DECODE_OVRUNDR_ERROR | NOTE_wptt_DECODE_BAD_STR);
    }
    return retval;
}

/*!
 * @brief Initializes and pushes a node to the wptt stack.
 *
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_push_node()
{
    uint8_t retval = NOTE_STATUS_BLDR(
        NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_OVRUNDR_ERROR);

    /* Check that we don't have a buffer overflow*/
    if ((decode_buffer->idx) + 1 < (decode_buffer->size) &&
        (wptt_stack_len + 1 < NOTE_wptt_STACK_SIZE))
    {
        size_t i;
        note_wptt_node_t *new_node = &decode_buffer->buffer[decode_buffer->idx];
        retval = NOTE_DEFS_DECODE_SUCCESS;
        /*Clear out new node*/
        for (i = 0; i < NOTE_wptt_DECODE_MAX_WEIGHTS; i++)
        {
            new_node->weights[i] = 0;
        }

        for (i = 0; i < NOTE_wptt_DECODE_MAX_CHILDREN; i++)
        {
            new_node->children[i] = NULL;
        }
        new_node->number_of_children = 0;
        new_node->number_of_rings = 0;
        new_node->order = NOTE_wptt_ORDER_FORWARD;

        /*Push new node to stack*/
        wptt_node_stack[wptt_stack_len] = new_node;

        /*Move buffer position to clean block*/
        decode_buffer->idx++;
        /* Move stack pointer up*/
        wptt_stack_len++;
    }
    return retval;
}

/*!
 * @brief Makes the active node on the wptt stack a child of the node below it
 * on the stack.
 *
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_decode_add_child()
{
    uint8_t retval = NOTE_STATUS_BLDR(
        NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_OVRUNDR_ERROR);
    /*Check if there is open space on the stack*/
    if ((0 < wptt_stack_len) && (wptt_stack_len < NOTE_wptt_STACK_SIZE))
    {
        retval = NOTE_DEFS_DECODE_SUCCESS;

        /*Check if the active node is the root*/
        if (1 < wptt_stack_len)
        {
            note_wptt_node_t *active_node_p =
                wptt_node_stack[wptt_stack_len - 2];

            /*Add child to active node*/
            active_node_p->children[active_node_p->number_of_children] =
                wptt_node_stack[wptt_stack_len - 1];
            active_node_p->number_of_children++;
        }
    }
    return retval;
}

/************************** Encode Path Functions   **************************/

/*!
 * @brief Determine whether the active node is the root of stick.
 *
 * @param active_node A wptt node and potential stick root.
 * @return The truthiness of whether the active node is the root of stick.
 */
STATIC_INLINE bool note_wptt_encode_stick_check(note_wptt_node_t *active_node_p)
{
    bool retval = false;
    note_wptt_node_t *child_node = active_node_p;
    while ((child_node != NULL) && (0 < child_node->number_of_children) &&
           (child_node->number_of_children < 2) &&
           (0 == child_node->number_of_rings) && (0 == child_node->weights[0]))
    {
        child_node = child_node->children[0];
        if (0 == child_node->number_of_children)
        {
            retval = true;
            break;
        }
    }

    return retval;
}

/*!
 * @brief Determine the next child index by the order of the active node.
 *
 * @param active_node The node under investigation.
 * @return The next ordered child index.
 */
STATIC_INLINE_UINT8 note_wptt_encode_get_child_ordered_idx(
    const note_wptt_node_t *active_node_p)
{
    size_t ordered_child_idx = 0;
    if (NOTE_wptt_ORDER_FORWARD == active_node_p->order)
    {
        ordered_child_idx = child_idx_stack[wptt_stack_len - 1];
    }
    else if (NOTE_wptt_ORDER_REVERSE == active_node_p->order)
    {
        ordered_child_idx = active_node_p->number_of_children -
                            child_idx_stack[wptt_stack_len - 1];
    }

    return ordered_child_idx;
}

/*!
 * @brief Process and insert a stick subtree into the output string.
 *
 * @param active_node The node under investigation.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_insert_stick(note_wptt_node_t *active_node_p,
                                                   char **str_p,
                                                   const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    uint8_t weights[UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {0};
    uint8_t weight_idx = 0;
    note_wptt_node_t *child_node = active_node_p;
    size_t i = 0;
    retval = note_wptt_encode_insert_char('[', str_p, buffer_end_p);

    /*Collect interior weights*/
    while (0 < child_node->number_of_children)
    {
        weights[weight_idx] = child_node->weights[1];
        weight_idx++;
        child_node = child_node->children[0];
    }
    /*Collect leaf weight*/
    weights[weight_idx] = child_node->weights[0];

    /*Stringify weights*/
    for (i = 0; i < weight_idx; i++)
    {
        retval |= note_wptt_encode_insert_int(
            weights[weight_idx - i], str_p, buffer_end_p);
        retval |= note_wptt_encode_insert_char(' ', str_p, buffer_end_p);
    }
    retval |= note_wptt_encode_insert_int(weights[0], str_p, buffer_end_p);
    retval |= note_wptt_encode_insert_char(']', str_p, buffer_end_p);
    return retval;
}

/*!
 * @brief Insert the V4 label into the output string.
 *
 * @param label The V4 of a wptt.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_insert_label(note_wptt_V4_label_e label,
                                                   char **str_p,
                                                   const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    switch (label)
    {
    case NOTE_wptt_V4_LABEL_NONE:
    {
        break;
    }
    case NOTE_wptt_V4_LABEL_I:
    {
        retval |= note_wptt_encode_insert_char('i', str_p, buffer_end_p);
        break;
    }
    case NOTE_wptt_V4_LABEL_X:
    {
        retval |= note_wptt_encode_insert_char('x', str_p, buffer_end_p);
        break;
    }
    case NOTE_wptt_V4_LABEL_Y:
    {
        retval |= note_wptt_encode_insert_char('y', str_p, buffer_end_p);
        break;
    }
    case NOTE_wptt_V4_LABEL_Z:
    {
        retval |= note_wptt_encode_insert_char('z', str_p, buffer_end_p);
        break;
    }
    default:
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_MALFORMED);
    }
    }

    return retval;
}

/*!
 * @brief Insert a space into the output string to delimit two integers.
 *
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_start_p A pointer to the start of the output string buffer.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_insert_space(char **str_p,
                                                   const char *buffer_start_p,
                                                   const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    /*Check if there is room in string buffer*/
    if (((*str_p + 1) < buffer_end_p) && (buffer_start_p < (*str_p)))
    {
        retval = NOTE_DEFS_ENCODE_SUCCESS;
        /*Look backward for an integer*/
        if (((*str_p - 1)[0] >= '0') && ((*str_p - 1)[0] <= '9'))
        {
            (*str_p)[0] = ' ';
            (*str_p)++;
        }
    }
    else
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_STR_BUF);
    }
    return retval;
}

/*!
 * @brief Insert a character into the output string.
 *
 * @param new_char A character to insert.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_insert_char(char new_char,
                                                  char **str_p,
                                                  const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    if ((*str_p + 1) < buffer_end_p)
    {
        (*str_p)[0] = new_char;
        (*str_p)++;
        retval = NOTE_DEFS_ENCODE_SUCCESS;
    }
    else
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_STR_BUF);
    }
    return retval;
}

/*!
 * @brief Insert the base 10 string representation of an integer into the output
 * string.
 *
 * @param new_int An integer to insert.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_insert_int(int8_t new_int,
                                                 char **str_p,
                                                 const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    size_t local_offset = 0;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];

    sprintf(local_str, "%d", new_int);
    local_offset = strlen(local_str);

    if ((*str_p + local_offset) < buffer_end_p)
    {
        strcpy(*str_p, local_str);
        (*str_p) += local_offset;
        retval = NOTE_DEFS_ENCODE_SUCCESS;
    }
    else
    {
        retval = NOTE_STATUS_BLDR(
            NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_STR_BUF);
    }
    return retval;
}

/*!
 * @brief Cap off the string representation of a node.
 *
 * @param active_node The node under investigation.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param ordered_child_idx The next child index in the order of the active
 * node.
 * @param buffer_start_p A pointer to the start of the output string buffer.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_complete_active_node(
    const note_wptt_node_t *active_node_p,
    char **str_p,
    size_t ordered_child_idx,
    const char *buffer_start_p,
    const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    /*Insert final weight*/
    if (0 != active_node_p->weights[ordered_child_idx])
    {
        retval |= note_wptt_encode_insert_space(
            str_p, buffer_start_p, buffer_end_p);
        retval |= note_wptt_encode_insert_int(
            active_node_p->weights[ordered_child_idx], str_p, buffer_end_p);
    }

    /*Close node*/
    if (0 < active_node_p->number_of_rings)
    {
        retval |= note_wptt_encode_insert_char('>', str_p, buffer_end_p);
    }
    else
    {
        retval |= note_wptt_encode_insert_char(')', str_p, buffer_end_p);
    }
    return retval;
}

/*!
 * @brief Determine the next action in the processing of the active node.
 *
 * @param active_node The node under investigation.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param ordered_child_idx The next child index in the order of the active
 * node.
 * @param buffer_start_p A pointer to the start of the output string buffer.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
STATIC_INLINE_UINT8 note_wptt_encode_process_active_node(
    note_wptt_node_t *active_node,
    char **str_p,
    size_t ordered_child_idx,
    const char *buffer_start_p,
    const char *buffer_end_p)
{
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    bool found_stick = note_wptt_encode_stick_check(active_node);

    /*Check if node has more children and start new node*/
    /* cppcheck-suppress negativeIndex */
    if (0 == child_idx_stack[wptt_stack_len - 1])
    {
        if (0 < active_node->number_of_rings)
        {
            retval |= note_wptt_encode_insert_char('<', str_p, buffer_end_p);
            retval |= note_wptt_encode_insert_int(
                active_node->number_of_rings, str_p, buffer_end_p);
        }
        else if (true == found_stick)
        {
            retval |= note_wptt_encode_insert_stick(
                active_node, str_p, buffer_end_p);
            /*pop stack*/
            if (0 < wptt_stack_len)
            {
                wptt_stack_len--;
            }
            else
            {
                retval |= NOTE_STATUS_BLDR(
                    NOTE_DEFS_ENCODE_FAIL, NOTE_wptt_ENCODE_OVRUNDR_ERROR);
            }
        }
        else
        {
            retval |= note_wptt_encode_insert_char('(', str_p, buffer_end_p);
        }
    }

    if (false == found_stick)
    {
        /*Stringify weight*/
        if ((0 != active_node->weights[ordered_child_idx]) &&
            (false == found_stick))
        {
            retval |= note_wptt_encode_insert_space(
                str_p, buffer_start_p, buffer_end_p);
            retval |= note_wptt_encode_insert_int(
                active_node->weights[ordered_child_idx], str_p, buffer_end_p);
        }

        /*Push child to stack*/
        child_idx_stack[wptt_stack_len - 1]++;
        if (child_idx_stack[wptt_stack_len - 1] <=
            active_node->number_of_children)
        {
            wptt_stack_len++;
            wptt_node_stack[wptt_stack_len - 1] =
                active_node->children[ordered_child_idx];
            child_idx_stack[wptt_stack_len - 1] = 0;
        }
    }
    return retval;
}