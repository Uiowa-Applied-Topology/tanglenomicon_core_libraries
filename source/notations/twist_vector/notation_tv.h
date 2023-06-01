/*!
 *  @file notation_tv.h
 *
 *  @brief  Notaiton module for twist vector notation.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_tv
#define NOTATION_tv

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "tang_defs.h"
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
        uint8_t *twist_vector; /*! A pointer to an array of ints. We pick uint8,
                                  that's 0-255 here since 256 is larger than any
                                  reasonable single integral subtangle in a
                                  rational tangle. */
        uint8_t tv_length;/*! The length of the twist_vector*/
    } note_tv_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/***************************Function Declerations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     * @param str
     */
    int note_tv_encode(char *str, note_tv_t *twistv);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     * @param item
     */
    int note_tv_decode(note_tv_t twistv, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_tv */