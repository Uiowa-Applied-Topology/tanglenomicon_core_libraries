/*!
 *  @file notation_wptt.h
 *
 *  @brief  Notation module for Arborescent Weighted Planar Tree Notation
 * (wptt) notation.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_wptt_H
#define NOTATION_wptt_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "notation_defs.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*******************************Defines ***************************************/
/******************************************************************************/

/*!
 * @brief The maximum number of weights in a node.
 */
#define NOTE_wptt_DECODE_MAX_WEIGHTS (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/*!
 * @brief The maximum number of children in a node.
 */
#define NOTE_wptt_DECODE_MAX_CHILDREN (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/*******************************Decode Flags***********************************/

/*

| Flag\bit               | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ---------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| Success                | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
| Success                | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
| Decode String Error    | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
| Decode Dest Error      | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
| Malformed String Error | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
| Buffer Error           | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
| Over/Underflow Error   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
*/

/*!
 * @brief Decode path error flag indicating an empty string.
 *
 */
#define NOTE_wptt_DECODE_EMPTY_STR (0x01u << 0x01u)

/*!
 * @brief Decode path error flag indicating a null destination.
 *
 */
#define NOTE_wptt_DECODE_NULL_DEST (0x01u << 0x02u)

/*!
 * @brief Decode path error flag indicating a malformed string.
 *
 */
#define NOTE_wptt_DECODE_BAD_STR (0x01u << 0x03u)

/*!
 * @brief Decode path error flag indicating a node buffer error.
 *
 */
#define NOTE_wptt_DECODE_BUFFER_ERROR (0x01u << 0x04u)

/*!
 * @brief Decode path error flag indicating an over/under flow error.
 *
 */
#define NOTE_wptt_DECODE_OVRUNDR_ERROR (0x01u << 0x05u)

/*******************************Decode Flags***********************************/

/*

| Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
| Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
| Encode String Buf Error    | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
| Malformed wptt Error      | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
| Over/Underflow Error       | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
`

*/

/*!
 * @brief Encode path error flag indicating an error with the string buffer.
 *
 */
#define NOTE_wptt_ENCODE_STR_BUF (0x01u << 0x01u)

/*!
 * @brief Encode path error flag indicating a malformed wptt tree.
 *
 */
#define NOTE_wptt_ENCODE_MALFORMED (0x01u << 0x02u)

/*!
 * @brief Encode path error flag indicating an over/under flow error.
 *
 */
#define NOTE_wptt_ENCODE_OVRUNDR_ERROR (0x01u << 0x03u)

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Type defining the $V_4$ label for an wptt
     */
    typedef enum note_wptt_V4_label_e
    {
        NOTE_wptt_V4_LABEL_UNINIT,
        NOTE_wptt_V4_LABEL_NONE,
        NOTE_wptt_V4_LABEL_I,
        NOTE_wptt_V4_LABEL_X,
        NOTE_wptt_V4_LABEL_Y,
        NOTE_wptt_V4_LABEL_Z
    } note_wptt_V4_label_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Type defining the order direction of a node in an wptt.
     */
    typedef enum note_wptt_order_e
    {
        NOTE_wptt_ORDER_UNINIT,
        NOTE_wptt_ORDER_FORWARD,
        NOTE_wptt_ORDER_REVERSE
    } note_wptt_order_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Type defining a the data of an wptt node.
     */
    typedef struct note_wptt_node_t
    {
        struct note_wptt_node_t *children[NOTE_wptt_DECODE_MAX_CHILDREN];
        int8_t weights[NOTE_wptt_DECODE_MAX_WEIGHTS];
        size_t number_of_children;
        uint8_t number_of_rings;
        note_wptt_order_e order;
    } note_wptt_node_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Type defining the data of a buffer of wptt nodes.
     */
    typedef struct note_wptt_node_buffer_t
    {
        note_wptt_node_t *buffer;
        size_t size;
        size_t idx;
    } note_wptt_node_buffer_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Type defining the notation for an wptt.
     */
    typedef struct
    {
        note_wptt_node_t *root;
        note_wptt_node_buffer_t node_buffer;
        note_wptt_V4_label_e label;
    } note_wptt_t;
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
     * @brief Function to take a note_wptt_t and decode it as a string
     *
     * @param att the note_wptt_t pointer to decode.
     * @param str Output string for decoded note_wptt_t
     * @return uint8_t The return code for the decoding operation.
     */
    uint8_t note_wptt_decode(char *str, note_wptt_t *wptt);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a string and decode it as a note_wptt_t
     *
     * @param str Input string to encode as note_wptt_t
     * @param att the note_wptt_t pointer to store the encoded string into.
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_wptt_encode(note_wptt_t wptt, char *str, size_t buffer_size);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_wptt_H */