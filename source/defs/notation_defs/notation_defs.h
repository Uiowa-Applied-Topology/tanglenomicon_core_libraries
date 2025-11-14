/*!
 *  @file notation_defs.h
 *
 *  @brief  Common definitions for notation objects.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_DEFS_H
#define NOTATION_DEFS_H

/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/
#include "tang_defs.h"

/******************************************************************************/
/****************************** Macro *****************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines ***************************************/
/******************************************************************************/

/****************************** Encode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for notation specific codes */
#define NOTE_DEFS_ENCODE_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define NOTE_DEFS_ENCODE_FAIL       (1u)

/****************************** Decode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for notation specific codes */
#define NOTE_DEFS_DECODE_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define NOTE_DEFS_DECODE_FAIL       (1u)

/****************************** Flag Builder Macro ****************************/

/*!
 * @brief A function like macro for building bitfield flags
 *
 */
#define NOTE_STATUS_BLDR(FLAG, HIGH_BITS)    ((FLAG) | (HIGH_BITS))

#endif /* end NOTATION_DEFS_H */