/*!
 *  @file comp_rlitt_pure_vignette.h
 *
 *  @brief  A module for compute rlitt_pure_vignette
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_RLITT_PURE_VIGNETTE_H
#define COMPUTATION_RLITT_PURE_VIGNETTE_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "notation_wptt.h"
#include "stdlib.h"
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
 | Config is null             | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_CONFIG_NULLTREE    (0X1U << 1U)


/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_CONFIG_IS_NULL    (0X1U << 3U)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Config error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Already Computed           | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | String buffer error        | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Stack overflow error       | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | `
 |
 */



/*!
 * @brief Failed to configure the module due to config error
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_COMPUTE_CFG_ERROR           (0X1U << 1U)

/*!
 * @brief Failed to configure the module due to config already having been processed.
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_COMPUTE_ALREADY_COMPUTED    (0X1U << 2U)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_COMPUTE_STR_BUFFER          (0X1U << 3U)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define COMP_RLITT_PURE_VIGNETTE_COMPUTE_STACK_OVRFLW        (0X1U << 4U)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/


/*!
 * @brief The type definition for reporting the results of rlitt_pure_vignette computation.
 *
 */
typedef struct {
    const char *result;
} comp_rlitt_pure_vignette_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the rlitt_pure_vignette computation.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write;
    const note_wptt_t *wptt;
} comp_rlitt_pure_vignette_config_t;
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
uint8_t comp_rlitt_pure_vignette_config(comp_rlitt_pure_vignette_config_t *config_arg);

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
uint8_t comp_rlitt_pure_vignette_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this retrieves the results of the last computation
 * @return comp_rlitt_pure_vignette_result_t Computation results.
 */
const comp_rlitt_pure_vignette_result_t *comp_rlitt_pure_vignette_result();

#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RLITT_PURE_VIGNETTE_H */
