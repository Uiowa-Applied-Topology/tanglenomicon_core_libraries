/*!
 *  @file notation_conway.h
 *
 *  @brief  Notaiton module for conway notation.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_CONWAY
#define NOTATION_CONWAY

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/

#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

/*!
 * @brief
 */

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct
    {

    } note_conway_t;
#ifdef __cplusplus
}
#endif
/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

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
    note_conway_t note_conway_parse(char *str);
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
    char *note_conway_encode(note_conway_t item);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_CONWAY */