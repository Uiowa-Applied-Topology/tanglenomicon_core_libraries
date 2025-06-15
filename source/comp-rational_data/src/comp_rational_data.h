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
#include "storage_defs.h"
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
        int numerator;
        int denominator;
        char *parity;
        int num_algebraic_equ;
        int den_algebraic_equ;
    } comp_rational_data_result_t;
#ifdef __cplusplus
}
#endif

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
        storage_write_funptr_t storage_write;
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
     * @return uint8_t computation status info.
     */
    uint8_t comp_rational_data_compute();
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
extern "C"
{
#endif
    /*!
     * @brief A public function, calling this retrieves the results of the last
     * computation
     * @return comp_rational_data_result_t Computation results.
     */
    const comp_rational_data_result_t *  comp_rational_data_result();
#ifdef __cplusplus
}
#endif
#endif /* end COMPUTATION_RATIONAL_DATA_H */

