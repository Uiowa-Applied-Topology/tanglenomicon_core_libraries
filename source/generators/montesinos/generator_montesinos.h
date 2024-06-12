/*!
 *  @file generator_montesinos.h
 *
 *  @brief  A module for generating montesinos tangles.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef GENERATOR_MONTESINOS_H
#define GENERATOR_MONTESINOS_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "generator_defs.h"
#include "storage_defs.h"
#include "notation_att.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Write Keys
 * *******************************************/

/*!
 * @brief The key for
 *
 */
#define GEN_MONTESINOS_STORAGE_UKEY ("GEN_MONTESINOS")
/*@@@TODO: add keys*/

/*************************** Config *******************************************/

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_MONTESINOS_CONFIG_IS_NULL (0x1u << 1u)
/*!
 * @brief Failed to configure the module due to issue in buffer.
 *
 */
#define GEN_MONTESINOS_CONFIG_BUFFER (0x1u << 2u)
/*!
 * @brief Failed to configure the module due to issue in string buffer.
 *
 */
#define GEN_MONTESINOS_CONFIG_STR_BUFFER (0x1u << 3u)

/*************************** Generate *****************************************/


/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * @brief The type definition for configuring the montesinos generation.
     *
     */
    typedef struct
    {
        gen_storage_write_fun_t storage_write;
        gen_storage_read_fun_t storage_read;
        note_att_t *att_n;
        note_tv_t **tv_sets;
        size_t *tv_set_lens;
        size_t tv_sets_len;
        char * str_buff;
        size_t str_buff_len;
    } gen_montesinos_config_t;
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
    uint8_t gen_montesinos_config(gen_montesinos_config_t *config_arg);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief The public generation function. When called the module will work
     * against the current config.
     *
     * @return uint8_t Generation status info.
     */
    uint8_t gen_montesinos_generate();
#ifdef __cplusplus
}
#endif
#endif /* end GENERATOR_MONTESINOS_H */