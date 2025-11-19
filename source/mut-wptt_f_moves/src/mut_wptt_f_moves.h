/*!
 *  @file mut_wptt_f_moves.h
 *
 *  @brief Mutates a tree by one of the $F_i$ moves.
 *
 *  @author    Joe Starr
 *
 */

#ifndef MUTATOR_WPTT_F_MOVES_H
#define MUTATOR_WPTT_F_MOVES_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

#include <mutator_defs.h>
#include <notation_wptt.h>
#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/*************************** Config Flags**************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | vertex error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Is Null error              | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | F1 error                   | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | F2 error                   | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | F3 error                   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 | Move error                 | 0   | 1   | 0   | 0   | 0   | 0   | 0   | 0   |
 | `
 |
 */
/*!
 * @brief Failed to configure the module due to issue with the object vertex.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_VERTEX     (0X1U << 1U)

/*!
 * @brief Failed to configure the module due to a null config.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_IS_NULL    (0X1U << 2U)

/*!
 * @brief Failed to configure the module due to F1 config issue.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_F1         (0X1U << 3U)

/*!
 * @brief Failed to configure the module due to F2 config issue.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_F2         (0X1U << 4U)

/*!
 * @brief Failed to configure the module due to F3 config issue.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_F3         (0X1U << 5U)

/*!
 * @brief Failed to configure the module due to move config issue.
 *
 */
#define MUT_WPTT_F_MOVES_CONFIG_MOVE       (0X1U << 6U)


/*************************** Mutate Flags************************************/

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | Config error               | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | Already Computed           | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | Move Config                | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | Eq Class                   | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | F3 Error                   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
 | Walk Error                 | 0   | 1   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Label Error                | 1   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 |
 |
 */


/*!
 * @brief Failed to run the module due to null config.
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_CFG_ERROR    (0X1U << 1U)


/*!
 * @brief Failed to run the module due to the config having been previously computed against.
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_ALREADY_COMPUTED    (0X1U << 2U)

/*!
 * @brief Failed to run the module due to move configuration error
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_MOVE_CFG            (0X1U << 3U)

/*!
 * @brief Failed to run the module due to eqclass configuration error.
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_MOVE_EQCLASS        (0X1U << 4U)

/*!
 * @brief Failed to run the module due to mutation $F_3\prime$ error
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_MOVE_F3_ERROR       (0X1U << 5U)

/*!
 * @brief Failed to run the module due to error while walking the tree.
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_MOVE_WALK_ERROR     (0X1U << 6U)

/*!
 * @brief Failed to run the module due to error in label computation.
 *
 */
#define MUT_WPTT_F_MOVES_MUTATE_LABEL_ERROR         (0X1U << 7U)


/******************************************************************************/
/*************************** Typedefs *****************************************/
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the moves available in the module
 */
typedef enum mut_f_moves_e {
    MUT_F_MOVE_UNINIT,
    MUT_F_MOVE_F1,
    MUT_F_MOVE_F2,
    MUT_F_MOVE_F3,
} mut_f_moves_e;
#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the direction to shift a weight in the $F_3\prime$ move.
 */
typedef enum mut_f_moves_direction_e {
    MUT_F_MOVES_DIR_UNINIT,
    MUT_F_MOVES_DIR_FWD,
    MUT_F_MOVES_DIR_BK,
} mut_f_moves_direction_e;
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief Type defining the equivalence class to apply the $F_2$ to.
 */
typedef enum mut_f_moves_eqclass_e {
    MUT_F_MOVES_EQCLASS_UNINIT,
    MUT_F_MOVES_EQCLASS_SELF,
    MUT_F_MOVES_EQCLASS_CHILD,
} mut_f_moves_eqclass_e;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief The type definition for configuring the module.
 *
 */
typedef struct {
    note_wptt_node_t *      vertex;
    note_wptt_V4_label_e *  V4_label;
    mut_f_moves_e           move;
    size_t                  weight_idx;
    mut_f_moves_direction_e direction;
    mut_f_moves_eqclass_e   eqclass;
} mut_wptt_f_moves_config_t;
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
uint8_t mut_wptt_f_moves_config(mut_wptt_f_moves_config_t *config_arg);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief A public function, calling this executes the mutator on the configured data.
 * @return uint8_t Mutation status info.
 */
uint8_t mut_wptt_f_moves_mutate();

#ifdef __cplusplus
}
#endif



#endif /* end MUTATOR_WPTT_F_MOVES_H */
