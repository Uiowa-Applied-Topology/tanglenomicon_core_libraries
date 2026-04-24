/**
 *  \file comp_itt_to_path.h
 *
 *  \brief A module for computing a PL path for a given ITT.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef COMPUTATION_ITT_TO_PATH_H
#define COMPUTATION_ITT_TO_PATH_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "notation_wptt.h"
#include "notation_plpath.h"
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
/**
 * \brief Failed to configure the module due to issue in the configuration parameters.
 *
 * Missing or null ITT or output path found in the configuration.
 *
 */
#define COMP_ITT_TO_PATH_CONFIG_PARAM      (0x1u << 1u)

/**
 * \brief Failed to configure the module due to supplied config being null.
 *
 */
#define COMP_ITT_TO_PATH_CONFIG_IS_NULL    (0x1u << 2u)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Config error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Already Computed           | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Segment Buffer             | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Point Buffer               | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | Stack Error                | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 | `
 |
 */

/**
 * \brief Failed to execute computation of the module due to an issue in set configuration.
 *
 */
#define COMP_ITT_TO_PATH_COMPUTE_CFG_ERROR           (0x1u << 1u)

/**
 * \brief Failed to execute the computation as the set configuration has been computed on.
 *
 */
#define COMP_ITT_TO_PATH_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

/**
 * \brief
 *
 */
#define COMP_ITT_TO_PATH_COMPUTE_SEG_BUFF_ERROR      (0x1u << 3u)

/**
 * \brief
 *
 */
#define COMP_ITT_TO_PATH_COMPUTE_PNT_BUFF_ERROR      (0x1u << 3u)

/**
 * \brief
 *
 */
#define COMP_ITT_TO_PATH_COMPUTE_STACK_ERROR         (0x1u << 3u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief The type definition of the result type for the component.
 *
 * Contains a pointer to a notation PL path.
 *
 * > [!note] Path
 * >
 * > The path pointer in the result points at the same `out_path` passed in the configuration
 * > which is modified during computation.
 *
 */
typedef struct {
    note_plpath_t *path; /**< A pointer to the computed PL path. */
} comp_itt_to_path_result_t;
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
 * Contains a pointer to an input ITT and an output PL path. The ITT is converted to a collection of
 *points in $\R^3$ which in turn forms linear segments stored in `out_path`.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write; /**< A pointer to a write function. */
    const note_wptt_t *    itt;           /**< A const pointer to a ITT. */
    note_plpath_t *        out_path;      /**< A pointer to the output PL path container. */
} comp_itt_to_path_config_t;
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
 * \brief The public configuration function.
 * \param config_arg The config to set.
 * \return uint8_t Configuration status info.
 */
uint8_t comp_itt_to_path_config(comp_itt_to_path_config_t *config_arg);

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
uint8_t comp_itt_to_path_compute(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief A public function, calling this retrieves the results of the last computation
 * \return comp_itt_to_path_result_t Computation results.
 */
const comp_itt_to_path_result_t *comp_itt_to_path_result(void);

#ifdef __cplusplus
}
#endif
#endif /* COMPUTATION_ITT_TO_PATH_H */
