/*!
 *  @file notation_plpath.c
 *
 *  @brief  Notation module for PL paths.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "notation_plpath.h"
#include "notation_defs.h"
#include "tang_defs.h"
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

/******************************************************************************/
/************************** Private Typedef ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

STATIC_INLINE_UINT8 note_plpath_dp_process_str(char *str, note_plpath_t *path);
STATIC_INLINE char * note_plpath_dp_strip_lws(char *str, const char *str_end);
STATIC_INLINE char * note_plpath_dp_move_nl(char *str, const char *str_end);
STATIC_INLINE char * note_plpath_dp_strip_com(char *str, const char *str_end);
STATIC_INLINE char * note_plpath_dp_build_pt(char *str, note_plpath_point_t *point,
                                             const char *str_end);
STATIC_INLINE char *note_plpath_ep_insert_double(double new_double,
                                                 char *str,
                                                 const char *str_end);
STATIC_INLINE char * note_plpath_ep_writeseg(note_plpath_point_t *active_point,
                                             char *str,
                                             const char *str_end);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
/* cppcheck-suppress constParameterPointer */
uint8_t note_plpath_decode(char *str, note_plpath_t *path)
{
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;

    if (NULL == str)
    {
        retval |= NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_EMPTY_STR);
    }
    else if (NULL == path)
    {
        retval |= NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_NULL_DEST);
    }
    else
    {
        retval |= note_plpath_dp_process_str(str, path);
    }
    return retval;
}

/*
 *  Documentation in header
 */
/* cppcheck-suppress constParameterPointer */
uint8_t note_plpath_encode(note_plpath_t path, char *str, size_t buffer_size)
{
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;

    if (NULL == str)
    {
        retval |= NOTE_STATUS_BLDR(NOTE_DEFS_ENCODE_FAIL, NOTE_PLPATH_ENCODE_STR_BUF);
    }
    else
    {
        size_t      i;
        const char *str_end = str + buffer_size;
        retval = NOTE_DEFS_ENCODE_SUCCESS;

        for (i = 0; i < buffer_size; i++)
        {
            char *ptr = str + i;
            *ptr = '\0';
        }

        for (i = 0; i < path.segment_count; i++)
        {
            /* if the segment exists write it to a string*/
            if (NULL != path.segments[i])
            {
                str = note_plpath_ep_writeseg(path.segments[i],
                                              str,
                                              str_end);
                if (NULL == str)
                {
                    retval |= NOTE_STATUS_BLDR(NOTE_DEFS_ENCODE_FAIL,
                                               NOTE_PLPATH_ENCODE_OVRUNDR_ERROR);
                    break;
                }
            }

            /* Except for the last segment write two new lines*/
            if (i + 1 < path.segment_count)
            {
                if (str < str_end - 1)
                {
                    *str = '\n';
                    str++;
                    *str = '\n';
                    str++;
                }
                else
                {
                    retval |= NOTE_STATUS_BLDR(NOTE_DEFS_ENCODE_FAIL,
                                               NOTE_PLPATH_ENCODE_OVRUNDR_ERROR);
                    break;
                }
            }
        }
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

/************************** Decode Path ***************************************/

/**
 * @brief Build a pointer object from start of the string.
 *
 * @param str The start of the input string.
 * @param point A pointer to the new pointer object.
 * @param str_end The end of the input string.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_dp_build_pt(char *str,
                                             note_plpath_point_t *point,
                                             const char *str_end)
{
    char * str_offset;
    double val = strtod(str, &str_offset);

    /*Build x*/
    str = str_offset;
    if ((0 != errno) || (str == str_end) || (',' != *str) ||
        !((('0' <= *(str + 1) && (*(str + 1) <= '9')) || ('-' == *(str + 1)))))
    {
        errno = 0;
        return NULL;
    }
    point->x = val;
    str++;

    /*Build y*/
    val = strtod(str, &str_offset);
    str = str_offset;
    if ((0 != errno) || (str == str_end) || (',' != *str) ||
        !((('0' <= *(str + 1)) && (*(str + 1) <= '9')) || ('-' == *(str + 1))))
    {
        errno = 0;
        return NULL;
    }
    point->y = val;
    str++;


    /*Build y*/
    val = strtod(str, &str_offset);
    str = str_offset;
    if (0 != errno)
    {
        errno = 0;
        return NULL;
    }
    point->z = val;

    return str;
}

/**
 * @brief Strip a comment line from the input string.
 *
 * @param str A pointer to the current location in the input string.
 * @param str_end The end of the input string.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_dp_strip_com(char *str, const char *str_end)
{
    while (('\n' != *str) && (str < str_end))
    {
        str++;
    }
    return str;
}

/**
 * @brief Strip new lines from the front of the input string.
 *
 * @param str A pointer to the current location in the input string.
 * @param str_end The end of the input string.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_dp_move_nl(char *str, const char *str_end)
{
    while (('\n' == *str) && (str < str_end))
    {
        str++;
    }
    return str;
}

/**
 * @brief Strip white space chars from the front of the input string.
 *
 * @param str A pointer to the current location in the input string.
 * @param str_end The end of the input string.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_dp_strip_lws(char *str, const char *str_end)
{
    while (((' ' == *str) || ('\t' == *str)) && (str < str_end))
    {
        str++;
    }
    return str;
}

/**
 * @brief Process and input string into a new point.
 *
 * @param str The input string to process.
 * @param path The location to store the path.
 * @return A status flag indicating the success or failure of the operation.
 */
STATIC_INLINE_UINT8 note_plpath_dp_process_str(char *str, note_plpath_t *path)
{
    uint8_t              retval       = NOTE_DEFS_DECODE_SUCCESS;
    const char *         str_end      = str + strlen(str);
    note_plpath_point_t *active_point = NULL;

    /* while the string is not exhausted */
    while ((NOTE_DEFS_DECODE_SUCCESS == retval) && (str < str_end))
    {
        str = note_plpath_dp_strip_lws(str, str_end);

        if ('\n' == *str)
        {
            if (('\n' == *(str + 1)) && (NULL != path->segments[path->segment_count - 1]))
            {
                path->segment_count++;
                path->segments[path->segment_count - 1] = NULL;
            }
            str = note_plpath_dp_move_nl(str, str_end);
        }
        else if (('/' == *str) && ('/' == *(str + 1)))
        {
            str = note_plpath_dp_strip_com(str, str_end);
        }
        else if ((('0' <= *str) && (*str <= '9')) || ('-' == *str))
        {
            /* If there are no segments add one*/
            if (0 == path->segment_count)
            {
                path->segment_count++;
                path->segments[path->segment_count - 1] = NULL;
            }

            if (path->buffer->idx < path->buffer->size)
            {
                note_plpath_point_t *new_point = &(path->buffer->buffer[path->buffer->idx]);
                path->buffer->idx++;
                str = note_plpath_dp_build_pt(str, new_point, str_end);
                if (NULL != str)
                {
                    /* If the segement has no points add this one`.*/
                    if (NULL == path->segments[path->segment_count - 1])
                    {
                        path->segments[path->segment_count - 1] = new_point;
                    }
                    else
                    {
                        /* Otherwise, add this the next point in the chain active_point.*/
                        active_point->next_point = new_point;
                    }
                    active_point = new_point;
                }
                else
                {
                    retval |= NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR);
                    break;
                }
            }
            else
            {
                retval |= NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BUFFER_ERROR);
                break;
            }
        }
        else
        {
            retval |= NOTE_STATUS_BLDR(NOTE_DEFS_DECODE_FAIL, NOTE_PLPATH_DECODE_BAD_STR);
            break;
        }
    }
    return retval;
}

/************************** Encode Path ***************************************/

/*!
 * @brief Insert the base 10 string representation of a double into the output string.
 *
 * @param new_int A double to insert.
 * @param str A pointer of current index of the output string.
 * @param buffer_end A pointer to the end of the output string buffer.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_ep_insert_double(double new_double,
                                                  char *str,
                                                  const char *str_end)
{
    size_t local_offset = 0;
    char   local_str[4 + DBL_DIG + -DBL_MIN_10_EXP];

    sprintf(local_str, "%f", new_double);
    local_offset = strlen(local_str);

    if ((str + local_offset) < str_end)
    {
        strcpy(str, local_str);
        str += local_offset;
    }
    else
    {
        return NULL;
    }
    return str;
}

/**
 * @brief Convert a segment (connected component) of the PL path into a string.
 * @param active_point The start of the segment.
 * @param str A pointer to the current location in the output string.
 * @param str_end A pointer to the end of the output string.
 * @return A pointer to the next char in the string after parsing the point. Alternatively a null
 *pointer if something has gone wrong.
 */
STATIC_INLINE char * note_plpath_ep_writeseg(note_plpath_point_t *active_point,
                                             char *str,
                                             const char *str_end)
{
    const note_plpath_point_t *first_pt = active_point;

    while ((NULL != str) && (NULL != active_point))
    {
        if (str < str_end)
        {
            str = note_plpath_ep_insert_double(active_point->x, str, str_end);
        }
        else
        {
            return NULL;
        }

        if (str < str_end)
        {
            *str = ',';
            str++;
        }
        else
        {
            return NULL;
        }

        if (str < str_end)
        {
            str = note_plpath_ep_insert_double(active_point->y, str, str_end);
        }
        else
        {
            return NULL;
        }

        if (str < str_end)
        {
            *str = ',';
            str++;
        }
        else
        {
            return NULL;
        }

        if (str < str_end)
        {
            str = note_plpath_ep_insert_double(active_point->z, str, str_end);
        }
        else
        {
            return NULL;
        }
        /*Only add a new line if we're not at the end of a segment. */
        if (NULL != active_point->next_point)
        {
            if (str < str_end)
            {
                *str = '\n';
                str++;
            }
            else
            {
                return NULL;
            }
        }
        active_point = active_point->next_point;
        if (active_point == first_pt)
        {
            return NULL;
        }
    }
    return str;
}
