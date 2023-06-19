/*!
 *  @file generator_rational.h
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
/*************************** Includes *****************************************/
/******************************************************************************/

#include "generator_defs.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "notation_tv.h"


/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Config *******************************************/

#define GEN_RATIONAL_CONFIG_IS_NULL (0x1u << 1u)
#define GEN_RATIONAL_CONFIG_BUFFER (0x1u << 2u)
#define GEN_RATIONAL_CONFIG_STR_BUFFER (0x1u << 3u)

/*************************** Generate *****************************************/
#define GEN_RATIONAL_PERMUTATION_FAIL (0x1u << 1u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
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
        uint8_t crossingNumber;
        int (*storage_write)(char *key, char *index, char *value);
        const char *(*storage_read)(char *key, char *index);
        bool generate;
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
     * @brief
     * @param config_arg
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
     * @brief
     */
    uint8_t gen_rational_generate();
#ifdef __cplusplus
}
#endif
#endif /* end GENERATOR_RATIONAL */