/*!
 *  @file notation_template.h
 *
 *  @brief  Notation module for template notation.
 *
 *
 *  @author    author
 *
 */

#ifndef NOTATION_TEMPLATE_H
#define NOTATION_TEMPLATE_H

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
     * @brief Function to take a string and decode it as a note_template_t
     *
     * @param str Input string to decode as note_template_t
     * @param att the note_template_t pointer to store the decoded string into.
     * @return uint8_t The return code for the decoding operation.
     */
    uint8_t note_template_decode(char *str, note_template_t *att);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a note_template_t and encode it as a string
     *
     * @param att the note_template_t pointer to encode.
     * @param str Output string for encoded note_template_t
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_template_encode(note_template_t att, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_template_H */