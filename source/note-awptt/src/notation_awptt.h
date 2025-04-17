/*!
 *  @file notation_awptt.h
 *
 *  @brief  Notation module for template notation.
 *
 *
 *  @author    author
 *
 */

#ifndef NOTATION_AWPTT_H
#define NOTATION_AWPTT_H

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


/******************************************************************************/
/***************************Function Declarations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a string and encode it as a note_awptt_t
     *
     * @param str Input string to encode as note_awptt_t
     * @param att the note_awptt_t pointer to store the encoded string into.
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_awptt_encode(char *str, note_awptt_t *att);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a note_awptt_t and decode it as a string
     *
     * @param att the note_awptt_t pointer to decode.
     * @param str Output string for decoded note_awptt_t
     * @return uint8_t The return code for the decoding operation.
     */
    uint8_t note_awptt_decode(note_awptt_t att, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_AWPTT_H */