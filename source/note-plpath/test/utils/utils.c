/* */
/* Created by joe on 4/25/25. */
/* */
#include "utils.h"
#include <stdbool.h>

static bool nodes_walk(const note_plpath_t *node1,
                       const note_plpath_t *node2);

/******************************************************************************/
/*******************************Test Functions******** ************************/
/******************************************************************************/

static bool nodes_walk(const note_plpath_t *node1,
                       const note_plpath_t *node2)
{
    return true;
}

bool test_util_path_equal(const note_plpath_t *tree1, const note_plpath_t *tree2)
{
    return false;
}
