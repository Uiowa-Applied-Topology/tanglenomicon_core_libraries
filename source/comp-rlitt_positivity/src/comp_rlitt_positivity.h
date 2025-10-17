/*!
 *  @file comp_rlitt_positivity.h
 *
 *  @brief  A module for compute rlitt_positivity
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_RLITT_POSITIVITY_H
#define COMPUTATION_RLITT_POSITIVITY_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "notation_wptt.h"
#include "storage_defs.h"
#include "computation_defs.h"

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
 | NULL TREE                  | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Scion error                | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Config is null             | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_RLITT_POSITIVITY_CONFIG_NULLTREE    (0X1U << 1U)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define COMP_RLITT_POSITIVITY_CONFIG_SCION       (0X1U << 2U)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_RLITT_POSITIVITY_CONFIG_IS_NULL     (0X1U << 3U)

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
 * @brief Failed to configure the module due to config error
 *
 */
#define COMP_RLITT_POSITIVITY_COMPUTE_CFG_ERROR           (0X1U << 1U)

/*!
 * @brief Failed to configure the module due to config already having been processed.
 *
 */
#define COMP_RLITT_POSITIVITY_COMPUTE_ALREADY_COMPUTED    (0X1U << 2U)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the positivity states for a WPTT.
 */
typedef enum comp_rlitt_positivity_flvrs_e {
    COMP_RLITT_POSITIVITY_FLVR_UNINIT,
    COMP_RLITT_POSITIVITY_FLVR_POS,
    COMP_RLITT_POSITIVITY_FLVR_NEG,
    COMP_RLITT_POSITIVITY_FLVR_NEU,
    COMP_RLITT_POSITIVITY_FLVR_UND
} comp_rlitt_positivity_flvrs_e;
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for reporting the results of rlitt_positivity computation.
 *
 */
typedef struct {
    comp_rlitt_positivity_flvrs_e positivity;
} comp_rlitt_positivity_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the rlitt_positivity computation.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write;
    const note_wptt_t *    wptt;
} comp_rlitt_positivity_config_t;
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
uint8_t comp_rlitt_positivity_config(comp_rlitt_positivity_config_t *config_arg);

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
uint8_t comp_rlitt_positivity_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this retrieves the results of the last computation
 * @return comp_rlitt_positivity_result_t Computation results.
 */
const comp_rlitt_positivity_result_t *comp_rlitt_positivity_result();

#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RLITT_POSITIVITY_H */
