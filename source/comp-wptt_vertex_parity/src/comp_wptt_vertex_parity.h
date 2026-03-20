/**
 *  \file comp_wptt_vertex_parity.h
 *
 *  \brief A module for computing the parity of a vertex in a WPTT.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef COMPUTATION_WPTT_VERTEX_PARITY_H
#define COMPUTATION_WPTT_VERTEX_PARITY_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "notation_wptt.h"
#include "stdbool.h"
#include "storage_defs.h"
#include "computation_defs.h"
#include "comp_sum_parity.h"

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
/**
 * \brief Failed to configure the module due to issue in a parameter.
 *
 */
#define COMP_WPTT_VERT_PARITY_CONFIG_PARAM      (0x1u << 1u)

/**
 * \brief Failed to configure the module due to null config
 *
 */
#define COMP_WPTT_VERT_PARITY_CONFIG_IS_NULL    (0x1u << 2u)

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

/**
 * \brief Failed to compute the module due to a configuration error.
 *
 */
#define COMP_WPTT_VERT_PARITY_COMPUTE_CFG_ERROR           (0x1u << 1u)

/**
 * \brief Failed to compute the module due to config having been processed.
 *
 */
#define COMP_WPTT_VERT_PARITY_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief Type of the result of the computation.
 *
 * Contains a parity value as well as a count of internal components.
 *
 */
typedef struct {
    comp_sum_parity_parity_e parity;
    uint16_t                 component_count;
} comp_wptt_vertex_parity_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief The type definition for configuring the computation.
 *
 * Contains a:
 * - Write interface.
 * - A WPTT pointer for write.
 * - An object vertex.
 *
 */
typedef struct {
    storage_write_funptr_t  storage_write;
    const note_wptt_t *     wptt;
    const note_wptt_node_t *vertex;
} comp_wptt_vertex_parity_config_t;
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

/**
 * \brief The public configuration function for the computation.
 * \param config_arg The config to set.
 */
uint8_t comp_wptt_vertex_parity_config(comp_wptt_vertex_parity_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief A public function, calling this executes the computation on the configured tangle.
 * \return uint8_t Generation status info.
 */
uint8_t comp_wptt_vertex_parity_compute(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief A public function, calling this retrieves the results of the last computation.
 * \return comp_wptt_vertex_parity_result_t Computation results.
 */
const comp_wptt_vertex_parity_result_t *comp_wptt_vertex_parity_result(void);

#ifdef __cplusplus
}
#endif
#endif /* COMPUTATION_WPTT_VERTEX_PARITY_H */
