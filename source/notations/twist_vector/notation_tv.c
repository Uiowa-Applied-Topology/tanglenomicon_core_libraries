/*!
 *  @file notation_tv.c
 *
 *  @brief  Notaiton module for twist vectors.
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
    char *str_end = str + strlen(str);

    /* Iterate over string. */
    while (str < str_end)
    {
        /* strtoul splits str around ' ' outputing an usigned long. */
        twistv->twist_vector[tv_idx] = strtoul(str, &str, NOTE_TV_INT_BASE);
        tv_idx++;
    }

    twistv->tv_length = tv_idx;

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

    /* Iterate over tv. */
    size_t i = 0;
    for (i = 0; i < twistv.tv_length; i++)
    {

        /* String to int. Store in local_str. then copy to output string.*/
        sprintf(local_str, "%u", twistv.twist_vector[i]);
        strcpy(str_p, local_str);

        /* Move the output string pointer.*/
        str_p += strlen(local_str);
        /* Insert spaces where needed. */
        if (i < (twistv.tv_length - 1))
        {
            strcat(str_p, " ");
            str_p += 1;
        }
    }

    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/
