/*!
 *  @file generator_defs.h
 *
 *  @brief  Common defintions for generator objects.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef GENERATOR_DEFS_H
#define GENERATOR_DEFS_H

/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Macro *****************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines ***************************************/
/******************************************************************************/

/****************************** Encode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for generator specific
 * codes */
#define GEN_DEFS_CONFIG_SUCCESS (0u)
/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher
 * bits. */
#define GEN_DEFS_CONFIG_FAIL (1u)

/****************************** Decode Status *********************************/

/*! @brief Success is a 0. That lets us use hight bits for generator specific
 * codes */
#define GEN_DEFS_GENERATION_SUCCESS (0u)
/*! @brief We use bit 0 to indicate a fail. Specific failures encoded in higher
 * bits. */
#define GEN_DEFS_GENERATION_FAIL (1u)

#endif /* end GENERATOR_DEFS_H */