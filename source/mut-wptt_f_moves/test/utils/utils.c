/* */
/* Created by joe on 4/25/25. */
/* */
#include "utils.h"
#include "bits/stdint-uintn.h"
#include "notation_wptt.h"
#include "storage_defs.h"
#include "stdbool.h"

static bool nodes_walk(const note_wptt_node_t *node1,
                       const note_wptt_node_t *node2);

/******************************************************************************/
/*******************************Test Data******** ************************/
/******************************************************************************/
#define UTIL_TEST_BUFFER_SIZE    (200u * UTIL_TANG_DEFS_MAX_CROSSINGNUM)
static note_wptt_node_t        note_wptt_nodes[UTIL_TEST_BUFFER_SIZE];
static note_wptt_node_buffer_t node_buffer = { note_wptt_nodes,
                                               UTIL_TEST_BUFFER_SIZE,
                                               0 };

static note_wptt_t note_wptt_buffer[UTIL_TEST_BUFFER_SIZE];
static size_t      note_wptt_buffer_idx = 0;
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

    for (i = 0; i < UTIL_TEST_BUFFER_SIZE; i++)
    {
        size_t j;
        for (j = 0; j < NOTE_WPTT_DECODE_MAX_CHILDREN; j++)
        {
            note_wptt_nodes[i].children[j] = NULL;
            note_wptt_nodes[i].weights[j]  = 0;
        }
        note_wptt_nodes[i].weights[NOTE_WPTT_DECODE_MAX_CHILDREN] = 0;
        note_wptt_nodes[i].number_of_children = 0;
        note_wptt_nodes[i].number_of_rings    = 0;
        note_wptt_nodes[i].order = NOTE_WPTT_ORDER_UNINIT;
    }
    node_buffer.idx  = 0;
    node_buffer.size = UTIL_TEST_BUFFER_SIZE;
    for (i = 0; i < UTIL_TEST_BUFFER_SIZE; i++)
    {
        note_wptt_buffer[i].root        = NULL;
        note_wptt_buffer[i].label       = NOTE_WPTT_V4_LABEL_UNINIT;
        note_wptt_buffer[i].node_buffer = NULL;
    }
}

void load_note(note_wptt_t **list, char **strings, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++)
    {
        uint8_t      decode_res;
        char *       string;
        note_wptt_t *note;
        list[i] = &note_wptt_buffer[note_wptt_buffer_idx];
        note    = list[i];
        string  = strings[i];
        note_wptt_buffer_idx++;
        list[i]->node_buffer = &node_buffer;
        decode_res           = note_wptt_decode(string, note);
        if (NOTE_DEFS_DECODE_SUCCESS != decode_res)
        {
            break;
        }
    }
}
