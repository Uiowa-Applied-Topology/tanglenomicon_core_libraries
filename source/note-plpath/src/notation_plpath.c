/*!
 *  @file notation_plpath.c
 *
 *  @brief  Notation module for weighted planar tangle trees.
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

STATIC_INLINE char * note_plpath_strip_lws(char *str_p, const char *str_end_p);
STATIC_INLINE char * note_plpath_move_nl(char *str_p, const char *str_end_p);
STATIC_INLINE char * note_plpath_strip_com(char *str_p, const char *str_end_p);
STATIC_INLINE char * note_plpath_build_pt(char *str_p, note_plpath_point_t *point);

STATIC_INLINE char *note_plpath_insert_double(double new_double,
                                              char *str_p,
                                              const char *str_end_p);
STATIC_INLINE char * note_plpath_writeseg(const note_plpath_point_t *start,
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
    uint8_t     retval  = NOTE_DEFS_DECODE_SUCCESS;
    const char *str_end = str + strlen(str) - 1;

    while ((NOTE_DEFS_DECODE_SUCCESS == retval) && (str < str_end))
    {
        str = note_plpath_strip_lws(str, str_end);
        if ('\n' == *str)
        {
            if ('\n' == *(str + 1))
            {
                path->segement_count++;
                path->segments[path->segement_count - 1] = NULL;
            }
            str = note_plpath_move_nl(str, str_end);
        }
        else if (('/' == *str) && ('/' == *(str + 1)))
        {
            str = note_plpath_strip_com(str, str_end);
        }
        else if ((('0' <= *str) && (*str <= '9')) || ('-' == *str))
        {
            if (0 == path->segement_count)
            {
                path->segement_count++;
                path->segments[path->segement_count - 1] = NULL;
            }
            if (path->buffer->idx < path->buffer->size)
            {
                note_plpath_point_t *new_point = &(path->buffer->buffer[path->buffer->idx]);
                path->buffer->idx++;
                str = note_plpath_build_pt(str, new_point);
                if (NULL != str)
                {
                    new_point->next_point = path->segments[path->segement_count - 1];
                    path->segments[path->segement_count - 1] = new_point;
                }
                else
                {
                    retval = NOTE_DEFS_DECODE_FAIL; /*@@@TODO: add custom error*/
                    break;
                }
            }
            else
            {
                retval = NOTE_DEFS_DECODE_FAIL; /*@@@TODO: Add sepecific failure */
                break;
            }
        }
        else
        {
            retval = NOTE_DEFS_DECODE_FAIL;     /*@@@TODO: Add sepecific failure */
            break;
        }
    }
    return retval;
}

/*
 *  Documentation in header
 */
/* cppcheck-suppress constParameterPointer */
uint8_t note_plpath_encode(note_plpath_t path, char *str, size_t buffer_size)
{
    uint8_t     retval = NOTE_DEFS_ENCODE_SUCCESS;
    size_t      i;
    const char *str_end = str + buffer_size;

    for (i = 0; i < path.segement_count; i++)
    {
        if (NULL != path.segments[i])
        {
            str = note_plpath_writeseg((const note_plpath_point_t *)path.segments[i],
                                       str,
                                       str_end);
        }
        if (NULL == str)
        {
            retval = NOTE_DEFS_ENCODE_FAIL;/*@@@TODO: add custom error*/
            break;
        }
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

STATIC_INLINE char * note_plpath_build_pt(char *str_p, note_plpath_point_t *point)
{
    char * str_end_p;
    double val = strtod(str_p, &str_end_p);

    str_p = str_end_p;
    if ((0 != errno) || (',' != *str_p))
    {
        errno = 0;
        return NULL;
    }
    point->x = val;
    str_p++;

    val   = strtod(str_p, &str_end_p);
    str_p = str_end_p;
    if ((0 != errno) || (',' != *str_p))
    {
        errno = 0;
        return NULL;
    }
    point->y = val;
    str_p++;


    val   = strtod(str_p, &str_end_p);
    str_p = str_end_p;
    if (0 != errno)
    {
        errno = 0;
        return NULL;
    }
    point->z = val;

    return str_p;
}

STATIC_INLINE char * note_plpath_strip_com(char *str_p, const char *str_end_p)
{
    while (('\n' != *str_p) && (str_p < str_end_p))
    {
        str_p++;
    }
    return str_p;
}

STATIC_INLINE char * note_plpath_move_nl(char *str_p, const char *str_end_p)
{
    while (('\n' == *str_p) && (str_p < str_end_p))
    {
        str_p++;
    }
    return str_p;
}

STATIC_INLINE char * note_plpath_strip_mnl(char *str_p, const char *str_end_p)
{
    char *curchar = str_p;

    while (('\n' == *curchar) && (curchar < str_end_p))
    {
        curchar++;
    }
    return curchar;
}

STATIC_INLINE char * note_plpath_strip_lws(char *str_p, const char *str_end_p)
{
    while (((' ' == *str_p) || ('\t' == *str_p)) && (str_p < str_end_p))
    {
        str_p++;
    }
    return str_p;
}

/*!
 * @brief Insert the base 10 string representation of an integer into the output string.
 *
 * @param new_int An integer to insert.
 * @param str_p A pointer to the pointer of current index of the output string.
 * @param buffer_end_p A pointer to the end of the output string buffer.
 * @return A status flag indicating successful completion of the subroutine.
 */
char * note_plpath_insert_double(double new_double,
                                 char *str_p,
                                 const char *str_end_p)
{
    size_t local_offset = 0;
    char   local_str[4 + DBL_DIG + -DBL_MIN_10_EXP];

    sprintf(local_str, "%f", new_double);
    local_offset = strlen(local_str);

    if ((str_p + local_offset) < str_end_p)
    {
        strcpy(str_p, local_str);
        (*str_p) += local_offset;
    }
    else
    {
        return NULL;
    }
    return str_p;
}

char * note_plpath_writeseg(const note_plpath_point_t *start,
                            char *str,
                            const char *str_end)
{
    if (NULL != start->next_point)
    {
        str = note_plpath_writeseg(start->next_point, str, str_end);
    }

    if ((NULL != str) && (str < str_end))
    {
        str = note_plpath_insert_double(start->x, str, str_end);
    }
    else
    {
        return NULL;
    }

    if ((NULL != str) && (str < str_end))
    {
        str = note_plpath_insert_double(start->y, str, str_end);
    }
    else
    {
        return NULL;
    }

    if ((NULL != str) && (str < str_end))
    {
        str = note_plpath_insert_double(start->z, str, str_end);
    }

    return str;
}
