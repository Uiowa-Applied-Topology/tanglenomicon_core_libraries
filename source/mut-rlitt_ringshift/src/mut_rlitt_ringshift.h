/*!
 *  @file mut_rlitt_ringshift.h
 *
 *  @brief  A module for compute rlitt_ringshift
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef MUTATOR_RLITT_RINGSHIFT_H
#define MUTATOR_RLITT_RINGSHIFT_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "mutator_defs.h"
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
#define MUT_RLITT_RINGSHIFT_CONFIG_WPTT       (0X1U << 1U)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define MUT_RLITT_RINGSHIFT_CONFIG_IS_NULL    (0X1U << 2U)

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
#define MUT_RLITT_RINGSHIFT_MUTATE_CFG_ERROR    (0X1U << 1U)


/*!
 * @brief Failed to configure the module due to the config having been previously computed against.
 *
 */
#define MUT_RLITT_RINGSHIFT_MUTATE_ALREADY_COMPUTED    (0X1U << 2U)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the rlitt_ringshift computation.
 *
 */
typedef struct {
    note_wptt_t *wptt;
} mut_rlitt_ringshift_config_t;

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
uint8_t mut_rlitt_ringshift_config(mut_rlitt_ringshift_config_t *config_arg);

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
uint8_t mut_rlitt_ringshift_mutate();

#ifdef __cplusplus
}
#endif

#endif /* end MUTATOR_RLITT_RINGSHIFT_H */
