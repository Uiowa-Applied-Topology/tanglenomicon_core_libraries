/*!
 *  @file tang_defs.h
 *
 *  @brief  Common defintions for the tanglenomicon project.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef UTIL_TANG_DEF_H
#define UTIL_TANG_DEF_H

/******************************************************************************/
/****************************** Pre processor Switches ************************/
/******************************************************************************/

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

/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** TypeDefs **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines **************************************/
/******************************************************************************/

#ifndef UTIL_TANG_DEFS_MAX_CROSSINGNUM
/*! @brief The max number of crossings that the tooling is configured for. */
#define UTIL_TANG_DEFS_MAX_CROSSINGNUM (20u)
#endif

#endif /* end UTIL_TANG_DEF_H */