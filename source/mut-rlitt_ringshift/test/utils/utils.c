/* */
/* Created by joe on 4/25/25. */
/* */
#include "utils.h"
#include "storage_defs.h"
#include "stdbool.h"

static bool nodes_walk(const note_wptt_node_t *node1,
                       const note_wptt_node_t *node2);

/******************************************************************************/
/*******************************Test Data******** ************************/
/******************************************************************************/
static note_wptt_node_t        note_wptt_nodes[2 * UTIL_TANG_DEFS_MAX_CROSSINGNUM];
static note_wptt_node_buffer_t node_buffer = { note_wptt_nodes,
                                               2u * UTIL_TANG_DEFS_MAX_CROSSINGNUM,
                                               0 };
/******************************************************************************/
/*******************************Test Functions******** ************************/
/******************************************************************************/

static bool nodes_walk(const note_wptt_node_t *node1,
                       const note_wptt_node_t *node2)
{
    if ((node1->number_of_rings == node2->number_of_rings) &&
        (node1->number_of_children == node2->number_of_children) &&
        (node1->order == node2->order))
    {
        int i = 0;
        for (; i < node1->number_of_children; i++)
        {
            if (node1->weights[i] != node2->weights[i])
            {
                return false;
            }
            if (false == nodes_walk(node1->children[i], node2->children[i]))
            {
                return false;
            }
        }
        if (node1->weights[node1->number_of_children] !=
            node2->weights[node1->number_of_children])
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool test_util_trees_equal(const note_wptt_t *tree1, const note_wptt_t *tree2)
{
    if ((tree1->label == tree2->label))
    {
        return nodes_walk(tree1->root, tree2->root);
    }
    return false;
}

note_wptt_node_buffer_t *test_util_get_buffer(void)
{
    return &node_buffer;
}

void test_util_clear_buffer()
{
    size_t i;

    for (i = 0; i < 2 * UTIL_TANG_DEFS_MAX_CROSSINGNUM; i++)
    {
        size_t j;
        for (j = 0; j < UTIL_TANG_DEFS_MAX_CROSSINGNUM; j++)
        {
            node_buffer.buffer[i].children[j] = NULL;
            node_buffer.buffer[i].weights[j]  = 0;
        }
        node_buffer.buffer[i].weights[j]         = 0;
        node_buffer.buffer[i].number_of_children = 0;
        node_buffer.buffer[i].number_of_rings    = 0;
        node_buffer.buffer[i].order = NOTE_WPTT_ORDER_UNINIT;
    }
    node_buffer.idx  = 0;
    node_buffer.size = 2 * UTIL_TANG_DEFS_MAX_CROSSINGNUM;
}
