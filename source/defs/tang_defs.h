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

#include "stdint.h"

/******************************************************************************/
/****************************** Pre processor Switches ************************/
/******************************************************************************/
#ifndef __PYX_EXTERN_C
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
#endif

#ifndef STATIC_INLINE
#if defined(__GNUC__) || defined(__cplusplus) ||                               \
    (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#define STATIC_INLINE static inline
#else
#define STATIC_INLINE static
#endif
#endif /* STATIC_INLINE */

#define STATIC_INLINE_UINT8 STATIC_INLINE uint8_t
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

#ifndef UTIL_TANG_DEFS_INF_TANG_STR
/*! @brief The string representation for infinity tangle. */
#define UTIL_TANG_DEFS_INF_TANG_STR ("infty")
#endif

#ifndef UTIL_TANG_DEFS_ZERO_TANG_STR
/*! @brief The string representation for zero tangle. */
#define UTIL_TANG_DEFS_ZERO_TANG_STR ("0")
#endif

#ifndef UTIL_TANG_DEFS_ONE_TANG_STR
/*! @brief The string representation for 1 tangle. */
#define UTIL_TANG_DEFS_ONE_TANG_STR ("1")
#endif

#ifndef UTIL_TANG_DEFS_M_ONE_TANG_STR
/*! @brief The string representation for -1 tangle. */
#define UTIL_TANG_DEFS_M_ONE_TANG_STR ("-1")
#endif

#endif /* end UTIL_TANG_DEF_H */