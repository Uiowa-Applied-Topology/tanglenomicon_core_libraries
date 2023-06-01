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

#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
/*! For portability we're using the old style "unsafe" string interfaces. We
can suppress warning on windows. */
#define _CRT_SECURE_NO_WARNINGS (1u)
#else
#if (_CRT_SECURE_NO_WARNINGS != 1u)
#error                                                                         \
    "Something has gone wrong. We want this define to be 1 and it's already not"
#else
#endif
#endif
#ifndef _CRT_DEPRECATE_TEXT
/*! For portability we're using the old style "unsafe" string interfaces. We
can suppress warning on windows. */
#define _CRT_DEPRECATE_TEXT (1u)
#else
#if (_CRT_DEPRECATE_TEXT != 1u)
#error                                                                         \
    "Something has gone wrong. We want this define to be 1 and it's already not"
#else
#endif
#endif
#endif

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
/************************** Private Function Declerations *********************/
/******************************************************************************/

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
    char substring[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
    uint8_t i;
    uint8_t start_idx = 0;
    uint8_t tv_idx = 0;
    str = _strrev(str);

    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            /*@@@TODO: Add checking her for array sizes. strncpy is not safe.*/
            strncpy(substring, &str[start_idx], (i - start_idx));
            twistv->twist_vector[tv_idx] = (uint8_t)atoi(substring);
            tv_idx++;
            start_idx = i + 1;
        }
    }

    return retval;
}

/*
 *  Documentation in header
 */
int note_tv_decode(note_tv_t twistv, char *str)
{
    /*@@@TODO: the return logic here needs to be inverted when error handing is
     * added*/
    uint8_t retval = NOTE_DEFS_ENCODE_SUCCESS;
    char substring[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
    uint8_t i = 0;
    uint8_t tv_idx = 0;

    for (i = 0; i < twistv.tv_length; i++)
    {
        /*@@@TODO: Should make sure that these functions are actually portable*/
        _itoa(twistv.twist_vector[i], substring, NOTE_TV_INT_BASE);
        strncpy(&str[tv_idx], substring, strlen(substring));
        tv_idx += strlen(substring) + 1;
        str[tv_idx] = ' ';
        tv_idx++;
    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/
