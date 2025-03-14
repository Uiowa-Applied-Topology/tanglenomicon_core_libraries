/*!
 *  @file comp_rational_data.h
 *
 *  @brief  A module for compute rational tangle data: fraction, algebraic
 * equivlance, and parity.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Joe Starr
 *
 */

#ifndef COMPUTATION_RATIONAL_DATA_H
#define COMPUTATION_RATIONAL_DATA_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include "computation_defs.h"
#include "notation_tv.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Write Keys   *************************************/

/*!
 * @brief The key for the rational data computation
 *
 */
#define COMP_RATIONAL_DAT_STORAGE_UKEY ("COMP_RATIONAL_DAT")
/*@@@TODO: add keys*/

/*************************** Config *******************************************/

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define COMP_RATIONAL_DAT_CONFIG_IS_NULL (0x1u << 1u)
/*!
 * @brief Failed to configure the module due to issue in buffer.
 *
 */
#define COMP_RATIONAL_DAT_CONFIG_BUFFER (0x1u << 2u)
/*!
 * @brief Failed to configure the module due to issue in string buffer.
 *
 */
#define COMP_RATIONAL_DAT_CONFIG_STR_BUFFER (0x1u << 3u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * @brief The type definition for configuring the rational data computation.
     *
     */
    typedef struct
    {
        uint8_t (*storage_write)(char *key, char *index, char *value);
        const char *(*storage_read)(char *key, char *index);
        note_tv_t *tv_n;
        char *tv_str_buff;
        size_t tv_str_buff_len;
    } comp_rational_data_config_t;
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
    uint8_t comp_rational_data_config(comp_rational_data_config_t *config_arg);
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
    uint8_t comp_rational_data_compute();
#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RATIONAL_DATA_H */