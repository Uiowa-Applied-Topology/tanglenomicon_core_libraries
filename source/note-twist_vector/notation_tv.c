/*!
 *  @file notation_tv.c
 *
 *  @brief  Notation module for twist vectors.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "notation_tv.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/*!
 * @brief The number base used for str->int functions.
 *
 */
#define NOTE_TV_INT_BASE (10u)

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/*!
 * @brief A function to reverse the order of the twist vector.
 *
 * @param tv Twist vector to work on.
 * @return note_tv_t a pointer to the reversed object, needed for nesting.
 */
static inline note_tv_t *note_tv_tvrev(note_tv_t *tv);

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t note_tv_encode(char *str, note_tv_t *twistv)
{
    /*@@@TODO: the return logic here needs to be inverted when error handing is
     * added*/
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    uint8_t tv_idx = 0u;
    str++;
    char *str_end = str + strlen(str) - 1;

    /* Iterate over string. */
    while (str < str_end)
    {
        /* strtoul splits str around ' ' outputing an usigned long. */
        twistv->twist_vector[tv_idx] = strtoul(str, &str, NOTE_TV_INT_BASE);
        tv_idx++;
    }

    twistv->tv_length = tv_idx;

    /* The tv string stores values in the opposite direction as the ary. This
     * could be done simultaneously with two counters this is more maintainable.
     */
    note_tv_tvrev(twistv);

    return retval;
}

/*
 *  Documentation in header
 */
uint8_t note_tv_decode(note_tv_t twistv, char *str)
{
    /*@@@TODO: the return logic here needs to be inverted when error handing is
     * added*/
    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    char local_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    char *str_p = str;
    strcpy(str_p, "[");
    str_p++;

    /* Iterate over tv backwards. */
    size_t i = twistv.tv_length;
    while (i > 0)
    {
        /* Length is off by one so decrementing first aligns the counter. */
        i--;
        /* String to int. Store in local_str. then copy to output string.*/
        sprintf(local_str, "%u", twistv.twist_vector[i]);
        strcpy(str_p, local_str);

        /* Move the output string pointer.*/
        str_p += strlen(local_str);
        /* Insert spaces where needed. */
        if (i >= 1)
        {
            strcpy(str_p, " ");
            str_p++;
        }
    }
    strcpy(str_p, "]");
    str_p++;

    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

/*
 *  Documentation at declaration
 */
static note_tv_t *note_tv_tvrev(note_tv_t *tv)
{
    uint8_t *left_p, *right_p;

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