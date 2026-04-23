/**
 *  \file comp_i2pp_buf_size.h
 *
 *  \brief A component to compute the buffer seize needed to turn an ITT into a PL path.
 *
 *  \author Joe Starr
 *
 */

#ifndef COMPUTATION_W2PP_BUF_SIZE_H
#define COMPUTATION_W2PP_BUF_SIZE_H

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
/**
 * \brief Failed to configure the module due to issue in a parameter.
 *
 */
#define COMP_W2PP_BUF_SIZE_CONFIG_PARAM      (0x1u << 1u)

/**
 * \brief Failed to configure the module due to null config
 *
 */
#define COMP_W2PP_BUF_SIZE_CONFIG_IS_NULL    (0x1u << 2u)

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
#define COMP_W2PP_BUF_SIZE_COMPUTE_CFG_ERROR           (0x1u << 1u)

/**
 * \brief Failed to compute the module due to config having been processed.
 *
 */
#define COMP_W2PP_BUF_SIZE_COMPUTE_ALREADY_COMPUTED    (0x1u << 2u)

/**
 * \brief A stack overflow error has occurred.
 *
 */
#define COMP_W2PP_BUF_SIZE_COMPUTE_STACK_ERROR         (0x1 << 3u)


/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief Defines the return type containing the computed value.
 *
 */
typedef struct {
    uint64_t buff_size;/**< The size of buffer needed to contain the PL path */
} comp_i2pp_buf_size_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief The type definition for configuring the component.
 *
 */
typedef struct {
    storage_write_funptr_t storage_write; /**< A standard write interface*/
    const note_wptt_t *    itt;           /**< The itt being converted to a PL path */
} comp_i2pp_buf_size_config_t;
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
 * \return uint8_t Configuration status info.
 */
uint8_t comp_i2pp_buf_size_config(comp_i2pp_buf_size_config_t *config_arg);

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
uint8_t comp_i2pp_buf_size_compute(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief A public function, calling this retrieves the results of the last computation.
 * \return comp_i2pp_buf_size_result_t Computation results.
 */
const comp_i2pp_buf_size_result_t *comp_i2pp_buf_size_result(void);

#ifdef __cplusplus
}
#endif
#endif /* COMPUTATION_W2PP_BUF_SIZE_H */
