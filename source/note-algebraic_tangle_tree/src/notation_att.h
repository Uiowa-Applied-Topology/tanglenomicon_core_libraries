/**
 *  \file notation_att.h
 *
 *  \brief Notation module for twist vector notation.
 *
 *
 *  \author Isabel Darcy
 *  \author Zachary Bryhtan
 *  \author Joe Starr
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
 *
 | Flv      | NA  | NA  | NA  | NA  | NA  | NA  | Op  | Op  |
 |----------|-----|-----|-----|-----|-----|-----|-----|-----|
 | uninit   |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  0  |
 |----------|-----|-----|-----|-----|-----|-----|-----|-----|
 | Plus     |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  1  |
 |----------|-----|-----|-----|-----|-----|-----|-----|-----|
 | Vee      |  0  |  0  |  0  |  0  |  0  |  0  |  1  |  0  |
 */

/**
 * \brief The length to shift for the operation.
 *
 */
#define NOTE_ATT_OP_SHIFT_LEN    (0x00u)

/**
 * \brief Indicates an uninitialized operation.
 *
 */
#define NOTE_ATT_OP_UNINIT       (0x00u << NOTE_ATT_OP_SHIFT_LEN)

/**
 * \brief Indicates a \f$ +\f$ operation.
 *
 */
#define NOTE_ATT_OP_PLUS         (0x01u << NOTE_ATT_OP_SHIFT_LEN)

/**
 * \brief Indicates a \f$\vee\f$ operation.
 *
 */
#define NOTE_ATT_OP_VEE          (0x02u << NOTE_ATT_OP_SHIFT_LEN)

/**
 * \brief Function like macro to clear the current operation.
 *
 */
#define NOTE_ATT_CLR_OP(FLV)        (FLV = ((FLV)&(~(0x03u << NOTE_ATT_OP_SHIFT_LEN))))

/**
 * \brief Function Like macro to set an operation.
 *
 */
#define NOTE_ATT_SET_OP(FLV, OP)    (FLV = (((FLV) | (OP))))

/**
 * \brief Function like macro to check an operation.
 *
 */
#define NOTE_ATT_CHK_OP(FLVR, OP) \
        (((FLVR) & (0x03u << NOTE_ATT_OP_SHIFT_LEN)) == (OP) ? (true) : (false))

/**
 * \brief Indicates a failure in traversal.
 *
 */
#define NOTE_ATT_TRAVERSE_FAIL       (0x01u)

/**
 * \brief Indicates a successful traversal.
 *
 */
#define NOTE_ATT_TRAVERSE_SUCCESS    (0x00u)

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief The core structure for algebraic tangle trees.
 */
typedef struct note_att_node_t {
    struct note_att_node_t *L_child;   /**< The left child of the current operation.*/
    struct note_att_node_t *R_child;   /**< The right child of the current operation.*/
    note_tv_t *             L_tv;      /**< The left twist vector child of the current operation.*/
    note_tv_t *             R_tv;      /**< The right twist vector child of the current operation.*/
    uint8_t                 operation; /**< The current operation.*/
} note_att_node_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief The core structure for algebraic tangle trees.
 */
typedef struct {
    note_att_node_t *root;            /**< The root of the ATT.*/
    note_att_node_t *node_buffer;     /**< A buffer of nodes used to construct an ATT.*/
    size_t           node_buffer_len; /**< The length of the node buffer.*/
    note_tv_t *      tv_buffer;       /**< A buffer of twist vectors for the leaf nodes of the
                                       * ATT.*/
    size_t           tv_buffer_len;   /**< The length of the twist vector buffer.*/
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

/**
 * \brief Function to take a string and decode it as a note_att_t
 *
 * \param str Input string to decode as note_att_t
 * \param att the note_att_t pointer to store the decoded string into.
 * \return uint8_t The return code for the encoding operation.
 */
uint8_t note_att_decode(char *str, note_att_t *att);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief Function to take a note_att_t and encode it as a string
 *
 * \param att the note_att_t pointer to encode.
 * \param str Output string for encoded note_att_t
 * \param buffer_size The size of the string buffer
 * \return uint8_t The return code for the encoding operation.
 */
uint8_t note_att_encode(note_att_t att, char *str, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* end NOTATION_ATT_H */
