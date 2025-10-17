/*!
 *  @file comp_rlitt_grafting.h
 *
 *  @brief  A module for compute rlitt_grafting
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_RLITT_GRAFTING_H
#define COMPUTATION_RLITT_GRAFTING_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "storage_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

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
 | Rootstock error            | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Scion error                | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Config is null             | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Buffer error               | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_RLITT_GRAFTING_CONFIG_ROOTSTOCK    (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define COMP_RLITT_GRAFTING_CONFIG_SCION        (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_RLITT_GRAFTING_CONFIG_IS_NULL      (0x1u << 3u)

/*!
 * @brief Failed to configure the module due to error in config buffer
 *
 */
#define COMP_RLITT_GRAFTING_CONFIG_BUFFER       (0x1u << 4u)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Rootstock error            | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Grafting error             | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Config error               | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Copy Error                 | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | Already Computed           | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_RLITT_GRAFTING_COMPUTE_ROOTSTOCK           (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to issue in the grafting operation.
 *
 */
#define COMP_RLITT_GRAFTING_COMPUTE_GRAFTING_RLITT      (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to config error
 *
 */
#define COMP_RLITT_GRAFTING_COMPUTE_CFG_ERROR           (0x1u << 3u)

/*!
 * @brief Failed to configure the module due to error in copying.
 *
 */
#define COMP_RLITT_GRAFTING_COMPUTE_COPYERROR           (0x1u << 4u)

/*!
 * @brief Failed to configure the module due to config having previously been processed
 *
 */
#define COMP_RLITT_GRAFTING_COMPUTE_ALREADY_COMPUTED    (0x1u << 5u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for the result reporting of the rlitt_grafting computation.
 *
 */
typedef struct {
    note_wptt_t *grafted_wptt;
} comp_rlitt_grafting_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the rlitt_grafting computation.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write;
    const note_wptt_t *    rootstock;
    const note_wptt_t *    scion;
    size_t                 rlitt_grafting_idx;
    note_wptt_t *          output_wptt;
} comp_rlitt_grafting_config_t;
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
uint8_t comp_rlitt_grafting_config(comp_rlitt_grafting_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this executes the computation on the configured tangle.
 * @return uint8_t computation status info.
 */
uint8_t comp_rlitt_grafting_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this executes the computation on the configured tangle.
 * @return uint8_t computation status info.
 */
uint8_t comp_rlitt_grafting_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this retrieves the results of the last computation
 * @return comp_rlitt_grafting_result_t Computation results.
 */
const comp_rlitt_grafting_result_t *comp_rlitt_grafting_result();

#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RLITT_GRAFTING_H */
