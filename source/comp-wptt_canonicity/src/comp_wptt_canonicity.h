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
    COMP_WPTT_CANONICITY_CAN_UNINIT,
    COMP_WPTT_CANONICITY_IS_CANONICAL,
    COMP_WPTT_CANONICITY_IS_NONCANONICAL,
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
 * @brief A public function, calling this executes the computation on the configured tangle.
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
 * @brief A public function, calling this executes the computation on the configured tangle.
 * @return uint8_t Generation status info.
 */
const comp_wptt_canonicity_result_t * comp_wptt_canonicity_result();

#ifdef __cplusplus
}
#endif

#endif /* end COMPUTATION_WPTT_CANONICITY_H */
