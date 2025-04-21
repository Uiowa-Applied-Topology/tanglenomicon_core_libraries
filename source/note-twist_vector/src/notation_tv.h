/*!
 *  @file notation_tv.h
 *
 *  @brief  Notation module for twist vector notation.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_TV_H
#define NOTATION_TV_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "notation_defs.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief The core structure for twist vectors.
     */
    typedef struct
    {
        /*@@@TODO: We should think about how much memory this is going to use.*/
        uint8_t
            twist_vector[UTIL_TANG_DEFS_MAX_CROSSINGNUM]; /*! An
                              array of ints. We pick uint8, that's 0-255 here
                              since 256 is larger than any reasonable single
                              integral subtangle in a rational tangle. */
        size_t tv_length; /*! The length of the note-twist_vector*/
    } note_tv_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/***************************Function Declarations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a string and decode it as a note_tv_t
     *
     * @param str Input string to encode as note_tv_t
     * @param twistv the note_tv_t pointer to store the string into.
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_tv_decode(char *str, note_tv_t *twistv);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a note_tv_t and encode it as a string
     *
     * @param twistv the note_tv_t pointer to encode.
     * @param str Output string for encoded note_tv_t
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_tv_encode(note_tv_t twistv, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_TV_H */