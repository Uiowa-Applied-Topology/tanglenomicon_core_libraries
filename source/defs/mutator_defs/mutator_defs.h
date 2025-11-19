/*!
 *  @file computation_defs.h
 *
 *  @brief  Common definitions for computation objects.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef MUTATOR_DEFS_H
#define MUTATOR_DEFS_H

/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/
#include "tang_defs.h"
#include "stdlib.h"

/******************************************************************************/
/****************************** Macro *****************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines ***************************************/
/******************************************************************************/

/****************************** Encode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for computation specific codes */
#define MUT_DEFS_CONFIG_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define MUT_DEFS_CONFIG_FAIL       (1u)

/****************************** Decode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for computation specific codes */
#define MUT_DEFS_MUTATE_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define MUT_DEFS_MUTATE_FAIL       (1u)

/****************************** Flag Builder Macro ****************************/

/*!
 * @brief A function like macro for building bitfield flags
 *
 */
#define MUT_STATUS_BLDR(FLAG, HIGH_BITS)    ((FLAG) | (HIGH_BITS))

#endif /* end MUTATOR_DEFS_H */
