/*!
 *  @file notation_att.h
 *
 *  @brief  Notation module for twist vector notation.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef NOTATION_ATT_H
#define NOTATION_ATT_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "notation_defs.h"
#include "notation_tv.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

/*

| Flv      | NA  | NA  | Op  | Op  | Type R | Type R | Type L | Type L |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| Uninit   |  0  |  0  |  0  |  0  |   0    |   0    |   0    |   0    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| L Op     |  0  |  0  |  0  |  0  |   0    |   0    |   0    |   1    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| L Tang   |  0  |  0  |  0  |  0  |   0    |   0    |   1    |   0    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| R Op     |  0  |  0  |  0  |  0  |   0    |   1    |   0    |   0    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| R Tang   |  0  |  0  |  0  |  0  |   1    |   0    |   0    |   0    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| Plus     |  0  |  0  |  0  |  1  |   0    |   0    |   0    |   0    |
|----------|-----|-----|-----|-----|--------|--------|--------|--------|
| Vee      |  0  |  0  |  1  |  0  |   0    |   0    |   0    |   0    |

*/

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_L_TYPE_SHIFT_LEN (0x00u)

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_R_TYPE_SHIFT_LEN (0x02u)

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_SHIFT_LEN (0x04u)

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_UNINIT (0x00u << NOTE_ATT_OP_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_PLUS (0x01u << NOTE_ATT_OP_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_OP_VEE (0x02u << NOTE_ATT_OP_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_L_UNINIT (0x00u << NOTE_ATT_OP_L_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_L_OP (0x01u << NOTE_ATT_OP_L_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_L_TANG (0x02u << NOTE_ATT_OP_L_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_R_UNINIT (0x00u << NOTE_ATT_OP_R_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_R_OP (0x01u << NOTE_ATT_OP_R_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TYPE_R_TANG (0x02u << NOTE_ATT_OP_R_TYPE_SHIFT_LEN)

/*!
 * @brief
 *
 */
#define NOTE_ATT_CLR_OP(FLV)                                                   \
    (FLV = ((FLV) & (~(0x03u << NOTE_ATT_OP_SHIFT_LEN))))
/*!
 * @brief
 *
 */
#define NOTE_ATT_CLR_L_TYPE(FLV)                                               \
    (FLV = ((FLV) & (~(0x03u << NOTE_ATT_OP_L_TYPE_SHIFT_LEN))))
/*!
 * @brief
 *
 */
#define NOTE_ATT_CLR_R_TYPE(FLV)                                               \
    (FLV = ((FLV) & (~(0x03u << NOTE_ATT_OP_R_TYPE_SHIFT_LEN))))

/*!
 * @brief
 *
 */
#define NOTE_ATT_SET_OP(FLV, OP) (FLV = (((FLV) | (OP))))
/*!
 * @brief
 *
 */
#define NOTE_ATT_SET_L_TYPE(FLV, TYPE) (FLV = (((FLV) | (TYPE))))
/*!
 * @brief
 *
 */
#define NOTE_ATT_SET_R_TYPE(FLV, TYPE) (FLV = (((FLV) | (TYPE))))

/*!
 * @brief
 *
 */
#define NOTE_ATT_FLVR(OP, R_TYPE, L_TYPE) (((OP) | (R_TYPE)) | (L_TYPE))

/*!
 * @brief
 *
 */
#define NOTE_ATT_CHK_FLVR(FLVR, OP, R_TYPE, L_TYPE)                            \
    ((FLVR) == NOTE_ATT_FLVR((OP), (R_TYPE), (L_TYPE)) ? (true) : (false))

/*!
 * @brief
 *
 */
#define NOTE_ATT_CHK_OP(FLVR, OP)                                              \
    (((FLVR) & (0x03u << NOTE_ATT_OP_SHIFT_LEN)) == (OP) ? (true) : (false))

/*!
 * @brief
 *
 */
#define NOTE_ATT_CHK_L_TYPE(FLVR, TYPE)                                        \
    (((FLVR) & (0x03u << NOTE_ATT_OP_L_TYPE_SHIFT_LEN)) == (TYPE) ? (true)     \
                                                                  : (false))

/*!
 * @brief
 *
 */
#define NOTE_ATT_CHK_R_TYPE(FLVR, TYPE)                                        \
    (((FLVR) & (0x03u << NOTE_ATT_OP_R_TYPE_SHIFT_LEN)) == (TYPE) ? (true)     \
                                                                  : (false))

/*!
 * @brief
 *
 */
#define NOTE_ATT_FLVR_UNINIT (0x00u)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TRAVERSE_FAIL (0x01u)

/*!
 * @brief
 *
 */
#define NOTE_ATT_TRAVERSE_SUCCESS (0x00u)

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief The core structure for algebraic tangle trees.
     */
    typedef struct
    {
        void *L_child;
        void *R_child;
        uint8_t flavor;
    } note_att_node_t;
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
        note_att_node_t *root;
        note_att_node_t *node_buffer;
        size_t node_buffer_len;
        note_tv_t *tv_buffer;
        size_t tv_buffer_len;
    } note_att_t;
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
     * @brief Function to take a string and decode it as a note_att_t
     *
     * @param str Input string to decode as note_att_t
     * @param att the note_att_t pointer to store the decoded string into.
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_att_decode(char *str, note_att_t *att);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief Function to take a note_att_t and encode it as a string
     *
     * @param att the note_att_t pointer to encode.
     * @param str Output string for encoded note_att_t
     * @return uint8_t The return code for the encoding operation.
     */
    uint8_t note_att_encode(note_att_t att, char *str);
#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_ATT_H */