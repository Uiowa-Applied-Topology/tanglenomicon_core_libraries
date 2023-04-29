/*!
 *  @file generator_pattern.h
 *
 *  @brief  A pattern for generator modules
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef GENERATOR_RATIONAL
#define GENERATOR_RATIONAL

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/

#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

/*!
 * @brief
 */

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        int maxCrossingNumber;
        int (*storage_write)(char *key, char *index, char *value);
        char *(*storage_read)(char *key, char *index);
        bool generate;
    } gen_rational_config_t;
#ifdef __cplusplus
}
#endif
/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

#define GEN_RATIONAL_CONFIG_FAIL (0x1u)
#define GEN_RATIONAL_CONFIG_SUCCESS (0x0u)

/******************************************************************************/
/***************************Function Declerations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief
     * @param config_arg
     */
    int gen_rational_config(gen_rational_config_t *config_arg);
#ifdef __cplusplus
}
#endif
#endif /* end GENERATOR_RATIONAL */