/* */
/* Created by joe on 4/25/25. */
/* */
#ifndef UTILS_H
#define UTILS_H
#include "notation_plpath.h"

extern note_plpath_point_t p03;
extern note_plpath_point_t p02;
extern note_plpath_point_t p01;
extern note_plpath_point_t p00;

extern note_plpath_point_t p12;
extern note_plpath_point_t p11;
extern note_plpath_point_t p10;

extern note_plpath_point_t p20;



extern note_plpath_segment_t sp20;
extern note_plpath_segment_t sp10;
extern note_plpath_segment_t sp00;
extern note_plpath_segment_t sp00ss;

bool test_util_path_equal(const note_plpath_t *tree1, const note_plpath_t *tree2);

#endif /* UTILS_H */
