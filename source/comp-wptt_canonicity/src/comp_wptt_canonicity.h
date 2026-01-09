/*!
 *  @file comp_wptt_canonicity.h
 *
 *  @brief  A module for compute wptt_canonicity
 *
 *
 *  @author    author
 *
 */

#ifndef COMPUTATION_WPTT_CANONICITY_H
#define COMPUTATION_WPTT_CANONICITY_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "notation_wptt.h"
#include "storage_defs.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Config Flags**************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Param                      | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Config is null             | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | positivity is uninit       | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | tree is null               | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_WPTT_CANON_CONFIG_PARAM         (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_CANON_CONFIG_IS_NULL       (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to uninit positivity
 *
 */
#define COMP_WPTT_CANON_CONFIG_POS_ERROR     (0x1u << 3u)

/*!
 * @brief Failed to configure the module due to tree as null
 *
 */
#define COMP_WPTT_CANON_CONFIG_TREE_ERROR    (0x1u << 4u)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Config error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Already Computed           | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Vertex computation error   | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Stack error                | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_CANON_COMPUTE_CFG_ERROR           (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to config previously executed against
 *
 */
#define COMP_WPTT_CANON_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to error in the vertex computation
 *
 */
#define COMP_WPTT_CANON_COMPUTE_VERTCOMP_ERROR      (0x1u << 3u)

/*!
 * @brief Failed to configure the module due to error in the vertex stack
 *
 */
#define COMP_WPTT_CANON_COMPUTE_STACK_ERROR         (0x1u << 4u)


/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the order direction of a node in a wptt.
 */
typedef enum comp_wptt_canonicity_canon_e {
    COMP_WPTT_CANON_CAN_UNINIT,
    COMP_WPTT_CANON_IS_CANONICAL,
    COMP_WPTT_CANON_IS_NONCANONICAL,
} comp_wptt_canonicity_canon_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the order direction of a node in a wptt.
 */
typedef enum comp_wptt_cononicity_positivity_e {
    COMP_WPTT_CANON_POS_UNINIT,
    COMP_WPTT_CANON_POS_POS,
    COMP_WPTT_CANON_POS_NEG,
} comp_wptt_cononicity_positivity_e;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the wptt_canonicity computation.
 *
 */
typedef struct {
    comp_wptt_canonicity_canon_e is_canonical;
} comp_wptt_canonicity_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the wptt_canonicity computation.
 *
 */
typedef struct {
    storage_write_funptr_t            storage_write;
    note_wptt_t *                     wptt;
    comp_wptt_cononicity_positivity_e positivity;
} comp_wptt_canonicity_config_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*************************** Public Function Declarations *********************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The public configuration function.
 * @param config_arg The config to set.
 */
uint8_t comp_wptt_canonicity_config(comp_wptt_canonicity_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The public compute function. Calling this executes the computation on the configured data.
 * @return uint8_t Generation status info.
 */
uint8_t comp_wptt_canonicity_compute();

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The public result function. Calling this retrieves the result of the computation on the
 *configured data.
 * @return uint8_t Generation status info.
 */
const comp_wptt_canonicity_result_t * comp_wptt_canonicity_result();

#ifdef __cplusplus
}
#endif

#endif /* end COMPUTATION_WPTT_CANONICITY_H */
