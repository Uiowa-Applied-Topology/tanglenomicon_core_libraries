/*!
 *  @file comp_rlitt_ringshift.h
 *
 *  @brief  A module for compute rlitt_ringshift
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_RLITT_RINGSHIFT_H
#define COMPUTATION_RLITT_RINGSHIFT_H

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
 | Wptt error                 | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Is Null error              | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define COMP_RLITT_RINGSHIFT_CONFIG_WPTT       (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_RLITT_RINGSHIFT_CONFIG_IS_NULL    (0x1u << 2u)

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
 * @brief Failed to configure the module due to null config.
 *
 */
#define COMP_RLITT_RINGSHIFT_COMPUTE_CFG_ERROR    (0x1u << 1u)


/*!
 * @brief Failed to configure the module due to the config having been previously computed against.
 *
 */
#define COMP_RLITT_RINGSHIFT_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for reporting the rlitt_ringshift computation results.
 *
 */
typedef struct {
    note_wptt_t *ringshiftd_wptt;
} comp_rlitt_ringshift_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the rlitt_ringshift computation.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write;
    note_wptt_t *          wptt;
} comp_rlitt_ringshift_config_t;
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
uint8_t comp_rlitt_ringshift_config(comp_rlitt_ringshift_config_t *config_arg);

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
uint8_t comp_rlitt_ringshift_compute();

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
uint8_t comp_rlitt_ringshift_compute();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this retrieves the results of the last computation
 * @return comp_rlitt_ringshift_result_t Computation results.
 */
const comp_rlitt_ringshift_result_t *comp_rlitt_ringshift_result();

#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RLITT_RINGSHIFT_H */
