/* */
/* Created by joe on 6/23/25. */
/* */

#ifndef TEST_COMP_ITT_TO_PLPATH_UTILS_H
#define TEST_COMP_ITT_TO_PLPATH_UTILS_H

#include "comp_itt_to_path.h"
#include "notation_wptt.h"
#include "notation_plpath.h"
#include <stdint.h>

/************************************************************************************************/
/*  Base */
/************************************************************************************************/

typedef struct {
    char *                    itt_string;
    char *                    pl_path_string;
    note_plpath_t             path;
    comp_itt_to_path_config_t cfg;
}test_holder_t;

extern test_holder_t *compute_valid_set[];

bool plpath_match(const note_plpath_t *pathA, const note_plpath_t *pathB);
void clear_buffers(void);
void print_to_file(note_plpath_t path);

#endif /* TEST_COMP_ITT_TO_PLPATH_UTILS_H */
