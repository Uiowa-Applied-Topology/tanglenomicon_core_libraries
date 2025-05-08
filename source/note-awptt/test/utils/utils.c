//
// Created by joe on 4/25/25.
//
#include "utils.h"

static bool nodes_walk(const note_awptt_node_t *node1,
                       const note_awptt_node_t *node2);
/******************************************************************************/
/*******************************Test Functions******** ************************/
/******************************************************************************/

static bool nodes_walk(const note_awptt_node_t *node1,
                       const note_awptt_node_t *node2)
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
bool trees_equal(const note_awptt_t *tree1, const note_awptt_t *tree2)
{
    if ((tree1->label == tree2->label))
    {
        return nodes_walk(tree1->root, tree2->root);
    }
    return false;
}