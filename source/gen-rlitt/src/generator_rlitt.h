/*!
 *  @file generator_rlitt.h
 *
 *  @brief  Generator module for rlitt generator.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef GENERATOR_RLITT_H
#define GENERATOR_RLITT_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "generator_defs.h"
#include "notation_wptt.h"
#include "storage_defs.h"

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

/*************************** Config Flags**************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Is null                    | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Rootstock error            | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Scion error                | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define GEN_RLITT_CONFIG_IS_NULL             (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define GEN_RLITT_CONFIG_ROOTSTOCKS_ERROR    (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_CONFIG_SCIONS_ERROR        (0x1u << 3u)

/*************************** Compute Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Rootstock error            | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Scion error                | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Grafting error             | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Neutrality error           | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | Already Computed           | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 | Shift Error                | 0   | 1   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Print Error                | 0   | 0   | 0   | 0   | 0   | 1   | 1   | 0   |
 | Config Error               | 0   | 0   | 0   | 0   | 1   | 1   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief Failed to configure the module due to issue in rootstock.
 *
 */
#define GEN_RLITT_GENERATE_ROOTSTOCK           (0x1u << 1u)

/*!
 * @brief Failed to configure the module due to issue in scion.
 *
 */
#define GEN_RLITT_GENERATE_SCION               (0x1u << 2u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_GRAFTING            (0x1u << 3u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_NEUTRALITY          (0x1u << 4u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_ALREADY_COMPUTED    (0x1u << 5u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_SHIFT               (0x1u << 6u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_PRINT_ERROR         (0x2u << 1u)

/*!
 * @brief Failed to configure the module due to null config
 *
 */
#define GEN_RLITT_GENERATE_CFG_ERROR           (0x2u << 2u)

/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Type defining the $V_4$ label for a wptt
 */
typedef enum gen_rlitt_positivity_e {
    GEN_RLITT_UNINIT,
    GEN_RLITT_POS,
    GEN_RLITT_NEG,
    GEN_RLITT_NEU
} gen_rlitt_positivity_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief The type definition for configuring the rlitt generation.
 *
 */
typedef struct gen_rlitt_config_t {
    storage_write_funptr_t storage_write;
    const note_wptt_t **   rootstocks;
    size_t                 rootstocks_len;
    const note_wptt_t **   scions;
    size_t                 scions_len;
} gen_rlitt_config_t;
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/***************************Function Declarations******************************/
/******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief The public configuration function.
 * @param config_arg The config to set.
 */
uint8_t gen_rlitt_config(gen_rlitt_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief The public generation function. When called the module will work against the current
 *config.
 *
 * @return uint8_t Generation status info.
 */
uint8_t gen_rlitt_generate();

#ifdef __cplusplus
}
#endif

#endif /* end GENERATOR_RLITT_H */
