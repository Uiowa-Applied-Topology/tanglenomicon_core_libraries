/*!
 *  @file computation_defs.h
 *
 *  @brief  Common definitions for computation objects.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_DEFS_H
#define COMPUTATION_DEFS_H

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

/****************************** Config Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for computation specific codes */
#define COMP_DEFS_CONFIG_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define COMP_DEFS_CONFIG_FAIL       (1u)

/****************************** Compute Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for computation specific codes */
#define COMP_DEFS_COMPUTE_SUCCESS    (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher bits. */
#define COMP_DEFS_COMPUTE_FAIL       (1u)

/****************************** Flag Builder Macro ****************************/

/*!
 * @brief A function like macro for building bitfield flags
 *
 */
#define COMP_STATUS_BLDR(FLAG, HIGH_BITS)    ((FLAG) | (HIGH_BITS))

#endif /* end COMPUTATION_DEFS_H */
