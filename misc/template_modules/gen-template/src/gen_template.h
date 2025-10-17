/*!
 *  @file gen_template.h
 *
 *  @brief  A module for compute template
 *
 *
 *  @author    author
 *
 */

#ifndef GENERATION_TEMPLATE_H
#define GENERATION_TEMPLATE_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "generation_defs.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

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
 * @brief The type definition for configuring the template generation.
 *
 */
typedef struct {
} gen_template_result_t;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the template generation.
 *
 */
typedef struct {
} gen_template_config_t;
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
uint8_t gen_template_config(gen_template_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this executes the generation on the configured tangle.
 * @return uint8_t Generation status info.
 */
uint8_t gen_template_generate();

#ifdef __cplusplus
}
#endif



#endif /* end generation_template_H */
