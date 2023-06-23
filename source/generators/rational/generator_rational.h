/*!
 *  @file generator_rational.h
 *
 *  @brief  A module for generating rational tangles.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef GENERATOR_RATIONAL_H
#define GENERATOR_RATIONAL_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "generator_defs.h"
#include "notation_tv.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Config *******************************************/

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RATIONAL_CONFIG_IS_NULL (0x1u << 1u)
/*!
 * @brief Failed to configure the module due to issue in buffer.
 *
 */
#define GEN_RATIONAL_CONFIG_BUFFER (0x1u << 2u)
/*!
 * @brief Failed to configure the module due to issue in string buffer.
 *
 */
#define GEN_RATIONAL_CONFIG_STR_BUFFER (0x1u << 3u)

/*************************** Generate *****************************************/

/*!
 * @brief Failed to generate due to permutation failure.
 *
 */
#define GEN_RATIONAL_PERMUTATION_FAIL (0x1u << 1u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * @brief The type definition for configuring the rational generation.
     *
     */
    typedef struct
    {
        uint8_t crossingNumber;
        int (*storage_write)(char *key, char *index, char *value);
        const char *(*storage_read)(char *key, char *index);
        note_tv_t *tv_n;
        char *tv_str_buff;
        size_t tv_str_buff_len;
    } gen_rational_config_t;
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
    uint8_t gen_rational_config(gen_rational_config_t *config_arg);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief The public generation function. When called the module will work against the current config.
     *
     * @return uint8_t Generation status info.
     */
    uint8_t gen_rational_generate();
#ifdef __cplusplus
}
#endif
#endif /* end GENERATOR_RATIONAL_H */