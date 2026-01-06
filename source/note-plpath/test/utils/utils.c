/* */
/* Created by joe on 4/25/25. */
/* */
#include "utils.h"
#include "notation_plpath.h"
#include "stdlib.h"
#include <stdbool.h>

note_plpath_point_t p03 = { 0, 3, 3, NULL };
note_plpath_point_t p02 = { 0, 2, 2, &p03 };
note_plpath_point_t p01 = { 0, 1, 1, &p02 };
note_plpath_point_t p00 = { 0, 0, 0, &p01 };
note_plpath_point_t p12 = { 1, 2, 2, NULL };
note_plpath_point_t p11 = { 1, 1, 1, &p12 };
note_plpath_point_t p10 = { 1, 0, 0, &p11 };
note_plpath_point_t p20 = { 2, 0, 0, NULL };

static bool point_equal(const note_plpath_point_t *point1,
                        const note_plpath_point_t *point2);

/******************************************************************************/
/*******************************Test Functions******** ************************/
/******************************************************************************/

static bool point_equal(const note_plpath_point_t *point1,
                        const note_plpath_point_t *point2)
{
    if (point1->x != point2->x)
    {
        return false;
    }
    if (point1->y != point2->y)
    {
        return false;
    }
    if (point1->z != point2->z)
    {
        return false;
    }
    if (((NULL == point1->next_point) && (NULL != point2->next_point)) ||
        ((NULL != point1->next_point) && (NULL == point2->next_point)))
    {
        return false;
    }
    if (NULL != point1->next_point)
    {
        return point_equal(point1->next_point, point2->next_point);
    }
    return true;
}

bool test_util_path_equal(const note_plpath_t *tree1, const note_plpath_t *tree2)
{
    if (tree1->segment_count == tree2->segment_count)
    {
        size_t i = 0;
        for (i = 0; i < tree1->segment_count; i++)
        {
            if (true != point_equal(tree1->segments[i], tree2->segments[i]))
            {
                return false;
            }
        }
    }
    return true;
}
