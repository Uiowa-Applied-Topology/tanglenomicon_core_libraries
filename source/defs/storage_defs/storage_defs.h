/*!
 *  @file storage_defs.h
 *
 *  @brief  Common defintions for store-storage_interface objects.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef STORAGE_DEFS_H
#define STORAGE_DEFS_H

/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Macro *****************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines ***************************************/
/******************************************************************************/

/****************************** write Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for store-storage_interface specific
 * codes */
#define STORE_DEFS_WRITE_SUCCESS (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures writed in higher
 * bits. */
#define STORE_DEFS_WRITE_FAIL (1u)

/****************************** Read Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for store-storage_interface specific
 * codes */
#define STORE_DEFS_READ_SUCCESS (0u)

/*! @brief We use bit 0 to indicate a fail. Specific failures writed in higher
 * bits. */
#define STORE_DEFS_READ_FAIL (1u)

#endif /* end STORAGE_DEFS_H */