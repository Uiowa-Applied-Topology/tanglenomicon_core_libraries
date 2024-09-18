/*!
 *  @file notation_watt.h
 *
 *  @brief  Notation module for weighted arborescent tangle trees.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_WATT_H
#define NOTATION_WATT_H

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

/*!
 * @brief
 *
 */
#define NOTE_WATT_TRAVERSE_FAIL (0x01u)

/*!
 * @brief
 *
 */
#define NOTE_WATT_TRAVERSE_SUCCESS (0x00u)

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     */
    typedef enum
    {
        NOTE_WATT_ORDER_UNINIT,
        NOTE_WATT_ORDER_CW,
        NOTE_WATT_ORDER_CCW

    } note_watt_order_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief The core structure for algebraic tangle trees.
     */
    typedef struct
    {
        note_watt_order_t order;
        size_t number_of_children;
        size_t weights[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
        note_watt_node_t *children[UTIL_TANG_DEFS_MAX_CROSSINGNUM];
    } note_watt_node_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     */
    typedef struct
    {
        note_watt_node_t *root;
        note_watt_node_t *node_buffer;
        size_t node_buffer_len;
        note_tv_t *tv_buffer;
        size_t tv_buffer_len;
    } note_watt_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/***************************Function Declarations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a string and encode it as a note_att_t
     *
     * @param str Input string to encode as note_att_t
     * @param watt the note_watt_t pointer to store the encoded string into.
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_watt_encode(char *str, note_watt_t *watt);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     *
     * @param watt the note_watt_t pointer to decode.
     * @param str Output string for decoded note_att_t
     * @return uint8_t The return code for the decoding operation.
     */
    uint8_t note_watt_decode(note_watt_t watt, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_WATT_H */