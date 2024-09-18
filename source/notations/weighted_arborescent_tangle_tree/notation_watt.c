/*!
 *  @file notation_watt.c
 *
 *  @brief  Notation module for weighted arborescent tangle trees.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "notation_watt.h"
#include "notation_tv.h"
#include "stdio.h"
#include "stdlib.h"

/******************************************************************************/
/************************** Defines *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************** Local Variables ***********************************/
/******************************************************************************/


/******************************************************************************/
/************************** Private Function Declarations *********************/
/******************************************************************************/

/******************************************************************************/
/************************** Public Function Definitions ***********************/
/******************************************************************************/

/*
 *  Documentation in header
 */
uint8_t note_watt_encode(char *str, note_watt_node_t *watt)
{

    uint8_t retval = NOTE_DEFS_DECODE_SUCCESS;
    if ((str == NULL) || (watt == NULL))
    {
        retval = NOTE_DEFS_DECODE_FAIL;
    }
    else if ((watt->node_buffer == NULL) || (watt->tv_buffer == NULL) ||
             (watt->tv_buffer_len == 0) || (watt->node_buffer_len == 0))
    {
        retval = NOTE_DEFS_DECODE_FAIL;
    }
    else
    {

    }
    return retval;
}

/*
 *  Documentation in header
 */
uint8_t note_watt_decode(note_watt_node_t watt, char *str)
{

    uint8_t retval = NOTE_DEFS_ENCODE_FAIL;
    uint8_t result = NOTE_WATT_TRAVERSE_FAIL;
    if (str == NULL)
    {
        retval = NOTE_DEFS_ENCODE_FAIL;
    }
    else if ((watt.root) == NULL)
    {
        retval = NOTE_DEFS_ENCODE_FAIL;
    }
    else
    {

    }
    return retval;
}

/******************************************************************************/
/************************** Private Function Definitions **********************/
/******************************************************************************/
