/*!
 *  @file notation_plpath.h
 *
 *  @brief  Notation module for PL paths.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_PLPATH_H
#define NOTATION_PLPATH_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/******************************************************************************/
/*******************************Defines ***************************************/
/******************************************************************************/

/*!
 * @brief The maximum number of weights in a node.
 */
#define NOTE_PLPATH_DECODE_MAX_SEGMENTS    (UTIL_TANG_DEFS_MAX_CROSSINGNUM + 1)

/*!
 * @brief The maximum number of children in a node.
 */
#define NOTE_PLPATH_DECODE_MAX_CHILDREN    (UTIL_TANG_DEFS_MAX_CROSSINGNUM)

/*!
 * @brief The maximum number of children in a node.
 */
#define NOTE_PLPATH_MAX_STR_LEN            ((UTIL_TANG_DEFS_MAX_CROSSINGNUM + 1) * 5u)

/*******************************Decode Flags***********************************/

/*
 *
 | Flag\bit               | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | ---------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Decode String Error    | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Decode Dest Error      | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Malformed String Error | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Buffer Error           | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | Over/Underflow Error   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 */

/*!
 * @brief Decode plpath error flag indicating an empty string.
 *
 */
#define NOTE_PLPATH_DECODE_EMPTY_STR        (0x01u << 0x01u)

/*!
 * @brief Decode plpath error flag indicating a null destination.
 *
 */
#define NOTE_PLPATH_DECODE_NULL_DEST        (0x01u << 0x02u)

/*!
 * @brief Decode plpath error flag indicating a malformed string.
 *
 */
#define NOTE_PLPATH_DECODE_BAD_STR          (0x01u << 0x03u)

/*!
 * @brief Decode plpath error flag indicating a node buffer error.
 *
 */
#define NOTE_PLPATH_DECODE_BUFFER_ERROR     (0x01u << 0x04u)

/*!
 * @brief Decode plpath error flag indicating an over/under flow error.
 *
 */
#define NOTE_PLPATH_DECODE_OVRUNDR_ERROR    (0x01u << 0x05u)

/*******************************Decode Flags***********************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Encode String Buf Error    | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Malformed plpath Error       | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Over/Underflow Error       | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief Encode plpath error flag indicating an error with the string buffer.
 *
 */
#define NOTE_PLPATH_ENCODE_STR_BUF          (0x01u << 0x01u)

/*!
 * @brief Encode plpath error flag indicating a malformed path tree.
 *
 */
#define NOTE_PLPATH_ENCODE_MALFORMED        (0x01u << 0x02u)

/*!
 * @brief Encode plpath error flag indicating an over/under flow error.
 *
 */
#define NOTE_PLPATH_ENCODE_OVRUNDR_ERROR    (0x01u << 0x03u)

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the data of a plpath node.
 */
typedef struct note_plpath_point_t {
    double                      x;
    double                      y;
    double                      z;
    struct note_plpath_point_t *next_point;
} note_plpath_point_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the data of a buffer of plpath nodes.
 */
typedef struct note_plpath_point_buffer_t {
    note_plpath_point_t *buffer;
    size_t               size;
    size_t               idx;
} note_plpath_point_buffer_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the notation for a plpath.
 */
typedef struct {
    note_plpath_point_t *       segments[NOTE_PLPATH_DECODE_MAX_SEGMENTS];
    size_t                      segment_count;
    note_plpath_point_buffer_t *buffer;
} note_plpath_t;
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
 * @brief Function to take a note_plpath_t and decode it as a string
 *
 * @param att the note_plpath_t pointer to decode.
 * @param str Output string for decoded note_plpath_t
 * @return uint8_t The return code for the decoding operation.
 */
uint8_t note_plpath_decode(char *str, note_plpath_t *path);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Function to take a string and decode it as a note_plpath_t. NOTE:
 * This function modifies the input PATH. The input is normalized so all nodes have "forward" order.
 *This does not change the topology.
 *
 * @param str Input string to encode as note_plpath_t
 * @param att the note_plpath_t pointer to store the encoded string into.
 * @return uint8_t The return code for the encoding operation.
 */
uint8_t note_plpath_encode(note_plpath_t path, char *str, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_PLPATH_H */
