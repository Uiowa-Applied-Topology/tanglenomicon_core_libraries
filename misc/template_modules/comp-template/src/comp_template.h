/*!
 *  @file comp_template.h
 *
 *  @brief  A module for compute template
 *
 *
 *  @author    author
 *
 */

#ifndef COMPUTATION_TEMPLATE_H
#define COMPUTATION_TEMPLATE_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/


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
    uint8_t comp_template_config(comp_template_config_t *config_arg);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief A public function, calling this executes the computation on the
     * configured tangle.
     * @return uint8_t Generation status info.
     */
    uint8_t comp_template_compute();
#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_template_H */