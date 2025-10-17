/*!
 *  @file comp_wptt_vertex_canonicity.h
 *
 *  @brief  A module for computing the canonicity of a vertex of a wptt.
 *
 *
 *  @author   Joe Starr
 *
 */

#ifndef COMPUTATION_WPTT_VERTEX_CANONICITY_H
#define COMPUTATION_WPTT_VERTEX_CANONICITY_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "storage_defs.h"
#include <stdint.h>

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
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_WPTT_VERT_CANON_CONFIG_PARAM      (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_VERT_CANON_CONFIG_IS_NULL    (0x1u << 2u)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Config error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Already Computed           | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_VERT_CANON_COMPUTE_CFG_ERROR           (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_VERT_CANON_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

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
typedef enum comp_wptt_vert_canon_positivity_e {
    COMP_WPTT_VERT_CANON_POS_UNINIT,
    COMP_WPTT_VERT_CANON_POS_POS,
    COMP_WPTT_VERT_CANON_POS_NEG,
} comp_wptt_vert_canon_positivity_e;
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
typedef enum comp_wptt_vert_canon_canon_e {
    COMP_WPTT_VERT_CANON_CAN_UNINIT,
    COMP_WPTT_VERT_CANON_IS_CANONICAL,
    COMP_WPTT_VERT_CANON_IS_NONCANONICAL,
} comp_wptt_vert_canon_canon_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the root_neut_rlitt computation.
 *
 */
typedef struct {
    comp_wptt_vert_canon_canon_e is_canonical;
} comp_wptt_vert_canon_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the root_neut_rlitt computation.
 *
 */
typedef struct {
    storage_write_funptr_t            storage_write;
    const note_wptt_t *               wptt;
    const note_wptt_node_t *          vertex;
    const note_wptt_node_t *          parent;
    bool                              parent_is_root;
    comp_wptt_vert_canon_positivity_e positivity;
} comp_wptt_vert_canon_config_t;
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

/*!
 * @brief The public configuration function.
 * @param config_arg The config to set.
 */
uint8_t comp_wptt_vert_canon_config(comp_wptt_vert_canon_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this executes the computation on the configured tangle.
 * @return uint8_t Generation status info.
 */
uint8_t comp_wptt_vert_canon_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this retrieves the results of the last computation
 * @return comp_wptt_vert_canon_result_t Computation results.
 */
const comp_wptt_vert_canon_result_t *comp_wptt_vert_canon_result();

#ifdef __cplusplus
}
#endif
#endif /* COMPUTATION_WPTT_VERTEX_CANONICITY_H */
