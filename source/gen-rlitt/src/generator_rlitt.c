/*!
 *  @file generator_rlitt.c
 *
 *  @brief  generator module for rlitt.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "generator_rlitt.h"
#include "bits/stdint-uintn.h"
#include "comp_rlitt_grafting.h"
#include "comp_wptt_vertex_canonicity.h"
#include "comp_rlitt_positivity.h"
#include "mut_rlitt_ringshift.h"
#include "computation_defs.h"
#include "generator_defs.h"
#include "notation_wptt.h"
#include "stdbool.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/
STATIC_INLINE const char *gen_rlitt_get_posstr(comp_rlitt_positivity_flvrs_e positivity);
STATIC_INLINE_UINT8 gen_rlitt_store_tangle(const note_wptt_t *result,
                                           const note_wptt_t *rootstock,
                                           const note_wptt_t *scion,
                                           const char *positivity);
STATIC_INLINE bool gen_rlitt_root_canon(const note_wptt_node_t *root,
                                        comp_wptt_vert_canon_positivity_e positivity);
STATIC_INLINE_UINT8 gen_rlitt_grafting_handler(size_t rootstock_idx, size_t scion_idx);

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/

/*!
 * @brief The local configuration of the rlitt gen module.
 *
 */
static gen_rlitt_config_t *gen_rlitt_localcfg = NULL;

/*!
 * @brief The local configuration of the rlitt gen module.
 *
 */
static bool gen_rlitt_executed = false;

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t gen_rlitt_config(gen_rlitt_config_t *config_arg)
{
    uint8_t ret_val = GEN_DEFS_CONFIG_FAIL;

    gen_rlitt_localcfg = NULL;

    /*Ensure the cfg is not empty.*/
    if (config_arg == NULL)
    {
        ret_val |= GEN_RLITT_CONFIG_IS_NULL;
    }
    /*Ensure the rootstock is not empty.*/
    else if ((config_arg->rootstocks == NULL) ||
             (config_arg->rootstocks_len == 0))
    {
        ret_val |= GEN_RLITT_CONFIG_ROOTSTOCKS_ERROR;
    }
    /*Ensure the scion is not empty.*/
    else if ((config_arg->scions == NULL) ||
             (config_arg->scions_len == 0))
    {
        ret_val |= GEN_RLITT_CONFIG_SCIONS_ERROR;
    }
    else
    {
        /* Set the config. */
        gen_rlitt_localcfg = config_arg;

        /*clear the executed status*/
        gen_rlitt_executed = false;

        ret_val = COMP_DEFS_CONFIG_SUCCESS;
    }
    return ret_val;
}

/*
 *  Documentation in header
 */
uint8_t gen_rlitt_generate()
{
    uint8_t ret_val = COMP_DEFS_COMPUTE_FAIL;

    /*Ensure the cfg is not empty.*/
    if (gen_rlitt_localcfg == NULL)
    {
        ret_val |= GEN_RLITT_GENERATE_CFG_ERROR;
    }
    /*Ensure not executed.*/
    else if (gen_rlitt_executed != false)
    {
        ret_val |= GEN_RLITT_GENERATE_ALREADY_COMPUTED;
    }
    else
    {
        gen_rlitt_executed = true;
        ret_val            = GEN_DEFS_GENERATION_SUCCESS;
        size_t i;
        /* for each rootstock */
        for (i = 0; i < gen_rlitt_localcfg->rootstocks_len; i++)
        {
            if (GEN_DEFS_GENERATION_SUCCESS == ret_val)
            {
                size_t j;
                /* for each scion */
                for (j = 0; j < gen_rlitt_localcfg->scions_len; j++)
                {
                    /* Run the grafting process */
                    ret_val |= gen_rlitt_grafting_handler(i, j);
                }
            }
            else
            {
                break;
            }
        }
    }

    return ret_val;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/

/*!
 * @brief Process the grafting of a rootstock and a scion into one or two resulting trees.
 *
 * @param rootstock_idx The index for the rootstock.
 * @param scion_idx The index for the scion.
 * @return The success status of this generation step.
 */
STATIC_INLINE_UINT8 gen_rlitt_grafting_handler(size_t rootstock_idx, size_t scion_idx)
{
    uint8_t ret_val      = GEN_DEFS_GENERATION_SUCCESS;
    uint8_t compute_flag = COMP_DEFS_COMPUTE_SUCCESS;

/* clang-format off */
    note_wptt_node_t note_wptt_node[2 * UTIL_TANG_DEFS_MAX_CROSSINGNUM] = {{ {NULL},
                                                                             {0},
                                                                             0,
                                                                             0,
                                                                             NOTE_WPTT_ORDER_UNINIT 
                                                                           }};
/* clang-format on */
    note_wptt_node_buffer_t             buffer = { note_wptt_node,
                                                   2u * UTIL_TANG_DEFS_MAX_CROSSINGNUM, 0 };
    note_wptt_t                         output_wptt = { NULL, &buffer, NOTE_WPTT_V4_LABEL_I };
    comp_rlitt_grafting_config_t        graft_cfg   = { NULL,
                                                        gen_rlitt_localcfg->rootstocks[rootstock_idx],
                                                        gen_rlitt_localcfg->scions[scion_idx],
                                                        0,
                                                        &output_wptt };
    const comp_rlitt_grafting_result_t *graft_res = NULL;

    /* Compute the grafting operation. */
    compute_flag |= comp_rlitt_grafting_config(&graft_cfg);
    compute_flag |= comp_rlitt_grafting_compute();
    graft_res     = comp_rlitt_grafting_result();

    /* Ensure grafting was successful. */
    if ((COMP_DEFS_COMPUTE_SUCCESS == compute_flag) &&
        (NULL != graft_res))
    {
        note_wptt_t *shifted_wptt;
        mut_rlitt_ringshift_config_t shift_cfg;
        shift_cfg.wptt = graft_res->grafted_wptt;

        /* Compute the right leaning version of the grafted tree. */
        compute_flag |= mut_rlitt_ringshift_config(&shift_cfg);
        compute_flag |= mut_rlitt_ringshift_mutate();
        shifted_wptt  = graft_res->grafted_wptt;

        /* Ensure rings shift was successful. */
        if ((COMP_DEFS_COMPUTE_SUCCESS == compute_flag) &&
            (NULL != shifted_wptt))
        {
            /* Check if the root is plus or minus canonical. */
            if ((true == gen_rlitt_root_canon((const note_wptt_node_t * )shifted_wptt->root,
                                              COMP_WPTT_VERT_CANON_POS_POS)) ||
                (true == gen_rlitt_root_canon((const note_wptt_node_t * )shifted_wptt->root,
                                              COMP_WPTT_VERT_CANON_POS_NEG)))
            {
                comp_rlitt_positivity_config_t        positivity_cfg;
                const comp_rlitt_positivity_result_t *positivity_res = NULL;

                positivity_cfg.storage_write = NULL;
                positivity_cfg.wptt          = shifted_wptt;

                /* Compute the positivity of the grafted and shifted tree. */
                compute_flag  |= comp_rlitt_positivity_config(&positivity_cfg);
                compute_flag  |= comp_rlitt_positivity_compute();
                positivity_res = comp_rlitt_positivity_result();

                /* Verify the positivity is defined.*/
                if ((COMP_DEFS_COMPUTE_SUCCESS == compute_flag) &&
                    (NULL != positivity_res) &&
                    (COMP_RLITT_POSITIVITY_FLVR_UND != positivity_res->positivity) &&
                    (COMP_RLITT_POSITIVITY_FLVR_UNINIT != positivity_res->positivity))
                {
                    /* Store the grafted tangle. */
                    ret_val |= gen_rlitt_store_tangle(shifted_wptt,
                                                      gen_rlitt_localcfg->rootstocks[rootstock_idx],
                                                      gen_rlitt_localcfg->scions[scion_idx],
                                                      gen_rlitt_get_posstr(
                                                          positivity_res->positivity));
/* clang-format off */
                    /* If the tree rootstock is a stick at the root we need to invert the sign of 
                     * the root vertex and store the result.
                     */
                    if (1 == gen_rlitt_localcfg->rootstocks[rootstock_idx]->root->number_of_children) 
/* clang-format on */
                    {
                        uint8_t number_of_children = shifted_wptt->root->number_of_children;
                        shifted_wptt->root->weights[number_of_children] *= -1;
                        ret_val |= gen_rlitt_store_tangle(shifted_wptt,
                                                          gen_rlitt_localcfg->rootstocks[
                                                              rootstock_idx],
                                                          gen_rlitt_localcfg->scions[scion_idx],
                                                          gen_rlitt_get_posstr(
                                                              positivity_res->positivity));
                    }
                }
            }
        }
        else
        {
            ret_val = GEN_STATUS_BLDR(GEN_DEFS_GENERATION_FAIL, GEN_RLITT_GENERATE_NEUTRALITY);
        }
    }
    else
    {
        ret_val = GEN_STATUS_BLDR(GEN_DEFS_GENERATION_FAIL, GEN_RLITT_GENERATE_GRAFTING);
    }

    return ret_val;
}

/*!
 * @brief Compute the string representation for the positivity of a tree.
 *
 * @param positivity The positivity of a tree.
 * @return The string representation of the positivity.
 */
STATIC_INLINE const char *gen_rlitt_get_posstr(comp_rlitt_positivity_flvrs_e positivity)
{
    switch (positivity)
    {
    case COMP_RLITT_POSITIVITY_FLVR_UND:
        return "undefined";

    case COMP_RLITT_POSITIVITY_FLVR_POS:
        return "positive";

    case COMP_RLITT_POSITIVITY_FLVR_NEG:
        return "negative";

    case COMP_RLITT_POSITIVITY_FLVR_NEU:
        return "neutral";

    default:
        break;
    }
    return NULL;
}

/*!
 * @brief Store the grafted tangle.
 *
 * @param result the grafted tangle.
 * @param rootstock the rootstock for the grafted tangle.
 * @param scion the scion for the grafted tangle.
 * @param positivity the positivity string for the grafted tangle.
 * @return The success flag for the operation.
 */
STATIC_INLINE_UINT8 gen_rlitt_store_tangle(const note_wptt_t *result,
                                           const note_wptt_t *rootstock,
                                           const note_wptt_t *scion,
                                           const char *positivity)
{
    uint8_t ret_val = GEN_RLITT_GENERATE_PRINT_ERROR;

    uint8_t encode_ret = NOTE_DEFS_ENCODE_SUCCESS;
    char    result_str[NOTE_WPTT_MAX_STR_LEN]    = { '\0' };
    char    rootstock_str[NOTE_WPTT_MAX_STR_LEN] = { '\0' };
    char    scion_str[NOTE_WPTT_MAX_STR_LEN]     = { '\0' };

    /* Encode the three trees as strings.*/
    encode_ret |= note_wptt_encode(*result,
                                   result_str,
                                   NOTE_WPTT_MAX_STR_LEN);
    encode_ret |= note_wptt_encode(*rootstock,
                                   rootstock_str,
                                   NOTE_WPTT_MAX_STR_LEN);
    encode_ret |= note_wptt_encode(*scion,
                                   scion_str,
                                   NOTE_WPTT_MAX_STR_LEN);

    if (encode_ret == NOTE_DEFS_ENCODE_SUCCESS)
    {
        char *is_good_str = "true";
        /* Determine if the resulting tree is "good". */
        if ((result->root->number_of_children < 2) &&
            (result->root->weights[result->root->number_of_children] == 0))
        {
            is_good_str = "false";
        }
        /* Report the results to the write interface. */
        ret_val  = GEN_DEFS_GENERATION_SUCCESS;
        ret_val |= gen_rlitt_localcfg->storage_write(result_str, "rootstock", rootstock_str);
        ret_val |= gen_rlitt_localcfg->storage_write(result_str, "scion", scion_str);
        ret_val |= gen_rlitt_localcfg->storage_write(result_str, "positivity", positivity);
        ret_val |= gen_rlitt_localcfg->storage_write(result_str, "is_good", is_good_str);
    }
    return ret_val;
}

/*!
 * @brief Determine if the vertices adjacent to the root are canonical.
 *
 * @param root The root vertex for the tree to verify.
 * @param positivity The positivity condition to verify, positive or negative.
 * @return True when the vertices adjacent to the root are canonical, false otherwise.
 */
STATIC_INLINE bool gen_rlitt_root_canon(const note_wptt_node_t *root,
                                        comp_wptt_vert_canon_positivity_e positivity)
{
    uint8_t compute_flag = COMP_DEFS_COMPUTE_SUCCESS;
    const comp_wptt_vert_canon_result_t *canvertex_res = NULL;
    comp_wptt_vert_canon_config_t        canvertex_cfg;

    canvertex_cfg.storage_write  = NULL;
    canvertex_cfg.wptt           = NULL;
    canvertex_cfg.parent         = NULL;
    canvertex_cfg.vertex         = root;
    canvertex_cfg.positivity     = positivity;
    canvertex_cfg.parent_is_root = false;

    /* Compute the vertex canonicity of the root of the resulting tree. */
    compute_flag |= comp_wptt_vert_canon_config(&canvertex_cfg);
    compute_flag |= comp_wptt_vert_canon_compute();
    canvertex_res = comp_wptt_vert_canon_result();
    if ((COMP_DEFS_COMPUTE_SUCCESS == compute_flag) &&
        (COMP_WPTT_VERT_CANON_IS_CANONICAL == canvertex_res->is_canonical))
    {
        size_t i;
        canvertex_cfg.parent         = root;
        canvertex_cfg.parent_is_root = true;
        /* For each child of the root. */
        for (i = 0; i < root->number_of_children; i++)
        {
            canvertex_cfg.vertex = root->children[i];
            compute_flag        |= comp_wptt_vert_canon_config(&canvertex_cfg);
            compute_flag        |= comp_wptt_vert_canon_compute();
            canvertex_res        = comp_wptt_vert_canon_result();
            if ((COMP_DEFS_COMPUTE_SUCCESS == compute_flag) &&
                (COMP_WPTT_VERT_CANON_IS_CANONICAL != canvertex_res->is_canonical))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}
