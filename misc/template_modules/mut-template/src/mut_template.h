/*!
 *  @file mut_template.h
 *
 *  @brief  A module for compute template
 *
 *
 *  @author    author
 *
 */

#ifndef MUTATOR_TEMPLATE_H
#define MUTATOR_TEMPLATE_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "mutator_defs.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/


/*!
 * @brief The type definition for configuring the template computation.
 *
 */
typedef struct {
} mut_template_config_t;
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
uint8_t mut_template_config(mut_template_config_t *config_arg);

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
uint8_t mut_template_mutate();

#ifdef __cplusplus
}
#endif



#endif /* end MUTATOR_TEMPLATE_H */