/*!
 *  @file notation_tv.c
 *
 *  @brief  Notaiton module for twist vectors.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "notation_tv.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

#define NOTE_TV_INT_BASE (10u)

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief
 *
 *
 * @param str
 * @return
 */
char *note_tv_strrev(char *str);

/*!
 * @brief
 *
 *
 * @param tv
 * @return
 */
note_tv_t *note_tv_tvrev(note_tv_t *tv);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
int note_tv_encode(char *str, note_tv_t *twistv)
{
    /*@@@TODO: the return logic here needs to be inverted when error handing is
     * added*/
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    uint8_t tv_idx = 0u;
    char *str_end = str + strlen(str);
    while (str < str_end)
    {
        twistv->twist_vector[tv_idx] = strtoul(str, &str, NOTE_TV_INT_BASE);
        tv_idx++;
    }

    twistv->tv_length = tv_idx;
    note_tv_tvrev(twistv);
    return retval;
}

/*
 *  Documentation in header
 */
int note_tv_decode(note_tv_t twistv, char *str)
{
    /*@@@TODO: the return logic here needs to be inverted when error handing is
     * added*/
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    uint8_t first_nonzero = 0;
    uint8_t i = 0;
    char *str_p = str;
    note_tv_tvrev(&twistv);

    for (first_nonzero = 0; first_nonzero < twistv.tv_length; first_nonzero++)
    {
        if (twistv.twist_vector[first_nonzero] != 0u)
        {
            break;
        }
    }

    for (i = first_nonzero; i < twistv.tv_length; i++)
    {
        sprintf(local_str, "%u", twistv.twist_vector[i]);
        strcpy(str_p, local_str);
        if (i < (twistv.tv_length - 1))
        {
            strcat(str_p, " ");
            str_p += 1;
        }
        str_p += strlen(local_str);
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

/*
 *  Documentation at declaration
 */
char *note_tv_strrev(char *str)
{
    char *left_p, *right_p;

    /*Error check if string are not empty or void */
    if (!str || !*str)
    {
        return str;
    }

    left_p = str;
    right_p = str + strlen(str) - 1;

    /* While the address for the right_p is bigger then the address on the
     * left_p.*/
    while (right_p > left_p)
    {
        /*Swap the char at left_p with the one at right_p*/
        char placeholder;
        placeholder = *left_p;
        *left_p = *right_p;
        *right_p = placeholder;

        /*Move the left_p right by one*/
        left_p++;
        /*Move the right_p left by one*/
        right_p--;
    }

    return str;
}
/*
 *  Documentation at declaration
 */
note_tv_t *note_tv_tvrev(note_tv_t *tv)
{
    uint8_t *left_p, *right_p;

    /*Error check if string are not empty or void */
    if (!tv || !(*tv->twist_vector))
    {
        return tv;
    }

    left_p = tv->twist_vector;
    right_p = tv->twist_vector + tv->tv_length - 1;

    /* While the address for the right_p is bigger then the address on the
     * left_p.*/
    while (right_p > left_p)
    {
        /*Swap the char at left_p with the one at right_p*/
        uint8_t placeholder;
        placeholder = *left_p;
        *left_p = *right_p;
        *right_p = placeholder;

        /*Move the left_p right by one*/
        left_p++;
        /*Move the right_p left by one*/
        right_p--;
    }

    return tv;
}