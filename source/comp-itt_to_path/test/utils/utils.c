#include "utils.h"
#include "comp_itt_to_path.h"
#include "notation_plpath.h"
#include "test_storage_stubs.h"
#include <string.h>
#include "unity.h"


#define UTIL_BUFFER_SIZE    (200u)

static note_plpath_point_t points[UTIL_BUFFER_SIZE] = { { 0, 0, 0, NULL } };


static note_plpath_point_buffer_t pnt_buffer = { (note_plpath_point_t *)&points,
                                                 UTIL_BUFFER_SIZE,
                                                 0 };

static note_plpath_segment_t segments[UTIL_BUFFER_SIZE] = { { NULL, NULL } };

static note_plpath_segment_buffer_t seg_buffer = { (note_plpath_segment_t *)&segments,
                                                   UTIL_BUFFER_SIZE,
                                                   0 };
static note_plpath_t outpath = { .segments = NULL,
                                 .pnt_buff = &pnt_buffer,
                                 .seg_buff = &seg_buffer };


STATIC_INLINE bool plpath_point_match(const note_plpath_point_t *pathA,
                                      const note_plpath_point_t *pathB);
STATIC_INLINE bool plpath_segement_match(const note_plpath_segment_t *segmentA,
                                         const note_plpath_segment_t *segmentB);


note_wptt_node_t bm3b = { { NULL }, { -3 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm2b = { { NULL }, { -2 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm1b = { { NULL }, { -1 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0b  = { { NULL }, { 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1b  = { { NULL }, { 1 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2b  = { { NULL }, { 2 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3b  = { { NULL }, { 3 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t b3_0b = { { &bm3b }, { 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2_0b = { { &bm2b }, { 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t b0_0b = { { &b0b }, { 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
/************************************************************************************************/
/***** 0   ********************************************************************************/
/************************************************************************************************/
char char_wptt_b0b[] = "i[0]";
char char_pl_b0b[]   = "0.000000,2.000000,0.000000\n"
                       "1.000000,1.500000,0.000000\n"
                       "2.000000,2.000000,0.000000\n"
                       "\n"
                       "0.000000,0.000000,0.000000\n"
                       "1.000000,0.500000,0.000000\n"
                       "2.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_b0b[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_b0b +1},
{.x=1.000000,.y=1.500000,.z=0.000000,.next_point=point_b0b +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_b0b +4},
{.x=1.000000,.y=0.500000,.z=0.000000,.next_point=point_b0b +5},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=NULL}};

note_plpath_segment_t segs_b0b []={
{.head=point_b0b     ,.next_seg=segs_b0b +1},
{.head=point_b0b + 3 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_t wptt_b0b = { &b0b, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_b0b = { .itt_string     = char_wptt_b0b,
                             .pl_path_string = char_pl_b0b,
                             .path           = { .segments = segs_b0b,
                                                 .pnt_buff = NULL,
                                                 .seg_buff = NULL },
                             .cfg                = {
                                 .storage_write = &test_stub_write_success,
                                 .itt           = &wptt_b0b,
                                 .out_path      = &outpath
                             } };


/************************************************************************************************/
/***** inf   ********************************************************************************/
/************************************************************************************************/
char char_wptt_b0_0b[] = "i[0 0]";
char char_pl_b0_0b[]   = "0.000000,2.000000,0.000000\n"
                         "0.500000,1.000000,0.000000\n"
                         "0.000000,0.000000,0.000000\n"
                         "\n"
                         "2.000000,2.000000,0.000000\n"
                         "1.500000,1.000000,0.000000\n"
                         "2.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_b0_0b[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_b0_0b +1},
{.x=0.500000,.y=1.000000,.z=0.000000,.next_point=point_b0_0b +2},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_b0_0b +4},
{.x=1.500000,.y=1.000000,.z=0.000000,.next_point=point_b0_0b +5},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=NULL}};

note_plpath_segment_t segs_b0_0b []={
{.head=point_b0_0b     ,.next_seg=segs_b0_0b +1},
{.head=point_b0_0b + 3 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_t wptt_b0_0b = { &b0_0b, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_b0_0b = { .itt_string     = char_wptt_b0_0b,
                               .pl_path_string = char_pl_b0_0b,
                               .path           = { .segments = segs_b0_0b,
                                                   .pnt_buff = NULL,
                                                   .seg_buff = NULL },
                               .cfg                = {
                                   .storage_write = &test_stub_write_success,
                                   .itt           = &wptt_b0_0b,
                                   .out_path      = &outpath
                               } };


/************************************************************************************************/
/***** -1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_bm1b[] = "i[-1]";
char char_pl_bm1b[]   = "0.000000,2.000000,0.000000\n"
                        "1.000000,1.000000,1.000000\n"
                        "2.000000,0.000000,0.000000\n"
                        "\n"
                        "0.000000,0.000000,0.000000\n"
                        "1.000000,1.000000,-1.000000\n"
                        "2.000000,2.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_bm1b[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_bm1b +1},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_bm1b +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_bm1b +4},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_bm1b +5},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=NULL}};

note_plpath_segment_t segs_bm1b []={
{.head=point_bm1b     ,.next_seg=segs_bm1b +1},
{.head=point_bm1b + 3 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_t wptt_bm1b = { &bm1b, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_bm1b = { .itt_string     = char_wptt_bm1b,
                              .pl_path_string = char_pl_bm1b,
                              .path           = { .segments = segs_bm1b,
                                                  .pnt_buff = NULL,
                                                  .seg_buff = NULL },
                              .cfg                = {
                                  .storage_write = &test_stub_write_success,
                                  .itt           = &wptt_bm1b,
                                  .out_path      = &outpath
                              } };

/************************************************************************************************/
/***** 1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_b1b[] = "i[1]";
char char_pl_b1b[]   = "0.000000,2.000000,0.000000\n"
                       "1.000000,1.000000,-1.000000\n"
                       "2.000000,0.000000,0.000000\n"
                       "\n"
                       "0.000000,0.000000,0.000000\n"
                       "1.000000,1.000000,1.000000\n"
                       "2.000000,2.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_b1b[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_b1b +1},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_b1b +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_b1b +4},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_b1b +5},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=NULL}};

note_plpath_segment_t segs_b1b []={
{.head=point_b1b     ,.next_seg=segs_b1b +1},
{.head=point_b1b + 3 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_t wptt_b1b = { &b1b, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_b1b = { .itt_string     = char_wptt_b1b,
                             .pl_path_string = char_pl_b1b,
                             .path           = { .segments = segs_b1b,
                                                 .pnt_buff = NULL,
                                                 .seg_buff = NULL },
                             .cfg                = {
                                 .storage_write = &test_stub_write_success,
                                 .itt           = &wptt_b1b,
                                 .out_path      = &outpath
                             } };

/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/


/************************************************************************************************/
/************************************************************************************************/
/* inf + X   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf + 1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0bbm1bp[] = "i([0][-1])";
char char_pl_pb0bbm1bp[]   = "0.000000,2.000000,0.000000\n"
                             "0.500000,1.000000,0.000000\n"
                             "0.000000,0.000000,0.000000\n"
                             "0.000000,0.000000,0.000000\n"
                             "\n"
                             "6.000000,2.000000,0.000000\n"
                             "5.000000,1.000000,1.000000\n"
                             "4.000000,0.000000,0.000000\n"
                             "2.000000,0.000000,0.000000\n"
                             "1.500000,1.000000,0.000000\n"
                             "2.000000,2.000000,0.000000\n"
                             "4.000000,2.000000,0.000000\n"
                             "5.000000,1.000000,-1.000000\n"
                             "6.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb0bbm1bp[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bbm1bp +1},
{.x=0.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bbm1bp +2},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bbm1bp +3},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bbm1bp +5},
{.x=5.000000,.y=1.000000,.z=1.000000,.next_point=point_pb0bbm1bp +6},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bbm1bp +7},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bbm1bp +8},
{.x=1.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bbm1bp +9},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bbm1bp +10},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bbm1bp +11},
{.x=5.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb0bbm1bp +12},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL}};

note_plpath_segment_t segs_pb0bbm1bp []={
{.head=point_pb0bbm1bp     ,.next_seg=segs_pb0bbm1bp +1},
{.head=point_pb0bbm1bp + 4 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb0bbm1bp = { { &b0b, &bm1b }, { 0, 0, 0 }, 2, 0,
                               NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0bbm1bp = { &pb0bbm1bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0bbm1bp = { .itt_string     = char_wptt_pb0bbm1bp,
                                   .pl_path_string = char_pl_pb0bbm1bp,
                                   .path           = { .segments = segs_pb0bbm1bp,
                                                       .pnt_buff = NULL,
                                                       .seg_buff = NULL },
                                   .cfg                = {
                                       .storage_write = &test_stub_write_success,
                                       .itt           = &wptt_pb0bbm1bp,
                                       .out_path      = &outpath
                                   } };

/************************************************************************************************/
/***** 1/2 + 3  *********************************************************************************/
/************************************************************************************************/
char char_wptt_pbm2bb3_0bp[] = "i([-2][3 0])";
char char_pl_pbm2bb3_0bp[]   = "0.000000,4.000000,0.000000\n"
                               "1.000000,3.000000,-1.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "1.000000,1.000000,1.000000\n"
                               "0.000000,0.000000,0.000000\n"
                               "0.000000,0.000000,0.000000\n"
                               "\n"
                               "10.000000,4.000000,0.000000\n"
                               "10.000000,3.000000,0.000000\n"
                               "9.000000,2.000000,-1.000000\n"
                               "8.000000,1.000000,0.000000\n"
                               "7.000000,2.000000,1.000000\n"
                               "6.000000,3.000000,0.000000\n"
                               "5.000000,2.000000,-1.000000\n"
                               "4.000000,1.000000,0.000000\n"
                               "2.000000,0.000000,0.000000\n"
                               "1.000000,1.000000,-1.000000\n"
                               "0.000000,2.000000,0.000000\n"
                               "1.000000,3.000000,1.000000\n"
                               "2.000000,4.000000,0.000000\n"
                               "4.000000,3.000000,0.000000\n"
                               "5.000000,2.000000,1.000000\n"
                               "6.000000,1.000000,0.000000\n"
                               "7.000000,2.000000,-1.000000\n"
                               "8.000000,3.000000,0.000000\n"
                               "9.000000,2.000000,1.000000\n"
                               "10.000000,1.000000,0.000000\n"
                               "10.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pbm2bb3_0bp[]={
{.x=0.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +1},
{.x=1.000000,.y=3.000000,.z=-1.000000,.next_point=point_pbm2bb3_0bp +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +3},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm2bb3_0bp +4},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +5},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=10.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +7},
{.x=10.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +8},
{.x=9.000000,.y=2.000000,.z=-1.000000,.next_point=point_pbm2bb3_0bp +9},
{.x=8.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +10},
{.x=7.000000,.y=2.000000,.z=1.000000,.next_point=point_pbm2bb3_0bp +11},
{.x=6.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +12},
{.x=5.000000,.y=2.000000,.z=-1.000000,.next_point=point_pbm2bb3_0bp +13},
{.x=4.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +14},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +15},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm2bb3_0bp +16},
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +17},
{.x=1.000000,.y=3.000000,.z=1.000000,.next_point=point_pbm2bb3_0bp +18},
{.x=2.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +19},
{.x=4.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +20},
{.x=5.000000,.y=2.000000,.z=1.000000,.next_point=point_pbm2bb3_0bp +21},
{.x=6.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +22},
{.x=7.000000,.y=2.000000,.z=-1.000000,.next_point=point_pbm2bb3_0bp +23},
{.x=8.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +24},
{.x=9.000000,.y=2.000000,.z=1.000000,.next_point=point_pbm2bb3_0bp +25},
{.x=10.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb3_0bp +26},
{.x=10.000000,.y=0.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm2bb3_0bp     []={
{.head=point_pbm2bb3_0bp    ,.next_seg=segs_pbm2bb3_0bp     +1},
{.head=point_pbm2bb3_0bp + 6 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm2bb3_0bp = { { &bm2b, &b3_0b }, { 0, 0, 0 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm2bb3_0bp = { &pbm2bb3_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm2bb3_0bp = { .itt_string     = char_wptt_pbm2bb3_0bp,
                                     .pl_path_string = char_pl_pbm2bb3_0bp,
                                     .path           = { .segments = segs_pbm2bb3_0bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pbm2bb3_0bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/************************************************************************************************/
/* inf + 0   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf + 0   ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0bb0_0bp[] = "i([0][0 0])";
char char_pl_pb0bb0_0bp[]   = "0.000000,2.000000,0.000000\n"
                              "0.500000,1.000000,0.000000\n"
                              "0.000000,0.000000,0.000000\n"
                              "0.000000,0.000000,0.000000\n"
                              "\n"
                              "6.000000,2.000000,0.000000\n"
                              "5.000000,1.500000,0.000000\n"
                              "4.000000,2.000000,0.000000\n"
                              "2.000000,2.000000,0.000000\n"
                              "1.500000,1.000000,0.000000\n"
                              "2.000000,0.000000,0.000000\n"
                              "4.000000,0.000000,0.000000\n"
                              "5.000000,0.500000,0.000000\n"
                              "6.000000,0.000000,0.000000";

/* clang-format off */
note_plpath_point_t point_pb0bb0_0bp[]={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+1},
{.x=0.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+2},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+3},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+5},
{.x=5.000000,.y=1.500000,.z=0.000000,.next_point=point_pb0bb0_0bp+6},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+7},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+8},
{.x=1.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+9},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+10},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0_0bp+11},
{.x=5.000000,.y=0.500000,.z=0.000000,.next_point=point_pb0bb0_0bp+12},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},};

note_plpath_segment_t segs_pb0bb0_0bp  []={
{.head=point_pb0bb0_0bp    ,.next_seg=segs_pb0bb0_0bp  +1},
{.head=point_pb0bb0_0bp+ 4 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb0bb0_0bp = { { &b0b, &b0_0b }, { 0, 0, 0 }, 2, 0,
                                NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0bb0_0bp = { &pb0bb0_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0bb0_0bp = { .itt_string     = char_wptt_pb0bb0_0bp,
                                    .pl_path_string = char_pl_pb0bb0_0bp,
                                    .path           = { .segments = segs_pb0bb0_0bp,
                                                        .pnt_buff = NULL,
                                                        .seg_buff = NULL },
                                    .cfg                = {
                                        .storage_write = &test_stub_write_success,
                                        .itt           = &wptt_pb0bb0_0bp,
                                        .out_path      = &outpath
                                    } };

/************************************************************************************************/
/***** 1/2 + 2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_pbm2bb2_0bp [] = "i([-2][2 0])";
char char_pl_pbm2bb2_0bp []   = "0.000000,4.000000,0.000000\n"
                                "1.000000,3.000000,-1.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "1.000000,1.000000,1.000000\n"
                                "0.000000,0.000000,0.000000\n"
                                "0.000000,0.000000,0.000000\n"
                                "\n"
                                "8.000000,4.000000,0.000000\n"
                                "8.000000,3.000000,0.000000\n"
                                "7.000000,2.000000,-1.000000\n"
                                "6.000000,1.000000,0.000000\n"
                                "5.000000,2.000000,1.000000\n"
                                "4.000000,3.000000,0.000000\n"
                                "2.000000,4.000000,0.000000\n"
                                "1.000000,3.000000,1.000000\n"
                                "0.000000,2.000000,0.000000\n"
                                "1.000000,1.000000,-1.000000\n"
                                "2.000000,0.000000,0.000000\n"
                                "4.000000,1.000000,0.000000\n"
                                "5.000000,2.000000,-1.000000\n"
                                "6.000000,3.000000,0.000000\n"
                                "7.000000,2.000000,1.000000\n"
                                "8.000000,1.000000,0.000000\n"
                                "8.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pbm2bb2_0bp []={
{.x=0.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +1},
{.x=1.000000,.y=3.000000,.z=-1.000000,.next_point=point_pbm2bb2_0bp  +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +3},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm2bb2_0bp  +4},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +5},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=8.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +7},
{.x=8.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +8},
{.x=7.000000,.y=2.000000,.z=-1.000000,.next_point=point_pbm2bb2_0bp  +9},
{.x=6.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +10},
{.x=5.000000,.y=2.000000,.z=1.000000,.next_point=point_pbm2bb2_0bp  +11},
{.x=4.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +12},
{.x=2.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +13},
{.x=1.000000,.y=3.000000,.z=1.000000,.next_point=point_pbm2bb2_0bp  +14},
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +15},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm2bb2_0bp  +16},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +17},
{.x=4.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +18},
{.x=5.000000,.y=2.000000,.z=-1.000000,.next_point=point_pbm2bb2_0bp  +19},
{.x=6.000000,.y=3.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +20},
{.x=7.000000,.y=2.000000,.z=1.000000,.next_point=point_pbm2bb2_0bp  +21},
{.x=8.000000,.y=1.000000,.z=0.000000,.next_point=point_pbm2bb2_0bp  +22},
{.x=8.000000,.y=0.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm2bb2_0bp  []={
{.head=point_pbm2bb2_0bp     ,.next_seg=segs_pbm2bb2_0bp   +1},
{.head=point_pbm2bb2_0bp  + 6 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm2bb2_0bp = { { &bm2b, &b2_0b }, { 0, 0, 0 }, 2,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm2bb2_0bp = { &pbm2bb2_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm2bb2_0bp = { .itt_string     = char_wptt_pbm2bb2_0bp,
                                     .pl_path_string = char_pl_pbm2bb2_0bp,
                                     .path           = { .segments = segs_pbm2bb2_0bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pbm2bb2_0bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/************************************************************************************************/
/* inf + inf ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf + inf ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0bb0bp[] = "i([0][0])";
char char_pl_pb0bb0bp[]   = "0.000000,2.000000,0.000000\n"
                            "0.500000,1.000000,0.000000\n"
                            "0.000000,0.000000,0.000000\n"
                            "0.000000,0.000000,0.000000\n"
                            "\n"
                            "6.000000,2.000000,0.000000\n"
                            "5.500000,1.000000,0.000000\n"
                            "6.000000,0.000000,0.000000\n"
                            "\n"
                            "4.000000,2.000000,0.000000\n"
                            "4.500000,1.000000,0.000000\n"
                            "4.000000,0.000000,0.000000\n"
                            "2.000000,0.000000,0.000000\n"
                            "1.500000,1.000000,0.000000\n"
                            "2.000000,2.000000,0.000000\n"
                            "4.000000,2.000000,0.000000";

/* clang-format off */

note_plpath_point_t point_pb0bb0bp []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0bp +1},
{.x=0.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0bp +2},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0bp +3},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0bp +5},
{.x=5.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0bp +6},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0bp +8},
{.x=4.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0bp +9},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0bp +10},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0bb0bp +11},
{.x=1.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0bb0bp +12},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0bb0bp +13},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=NULL},};

note_plpath_segment_t segs_pb0bb0bp   []={
{.head=point_pb0bb0bp     ,.next_seg=segs_pb0bb0bp   +1},
{.head=point_pb0bb0bp + 4 ,.next_seg=segs_pb0bb0bp   +2},
{.head=point_pb0bb0bp + 7 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb0bb0bp = { { &b0b, &b0b }, { 0, 0, 0 }, 2, 0,
                              NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0bb0bp = { &pb0bb0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0bb0bp = { .itt_string     = char_wptt_pb0bb0bp,
                                  .pl_path_string = char_pl_pb0bb0bp,
                                  .path           = { .segments = segs_pb0bb0bp,
                                                      .pnt_buff = NULL,
                                                      .seg_buff = NULL },
                                  .cfg                = {
                                      .storage_write = &test_stub_write_success,
                                      .itt           = &wptt_pb0bb0bp,
                                      .out_path      = &outpath
                                  } };

/************************************************************************************************/
/***** 1/2 + 1/2  *******************************************************************************/
/************************************************************************************************/
char char_wptt_pbm2bbm2bp [] = "i([-2][-2])";
char char_pl_pbm2bbm2bp []   = "0.000000,4.000000,0.000000\n"
                               "1.000000,3.000000,-1.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "1.000000,1.000000,1.000000\n"
                               "0.000000,0.000000,0.000000\n"
                               "0.000000,0.000000,0.000000\n"
                               "\n"
                               "6.000000,4.000000,0.000000\n"
                               "5.000000,3.000000,1.000000\n"
                               "4.000000,2.000000,0.000000\n"
                               "5.000000,1.000000,-1.000000\n"
                               "6.000000,0.000000,0.000000\n"
                               "\n"
                               "4.000000,4.000000,0.000000\n"
                               "5.000000,3.000000,-1.000000\n"
                               "6.000000,2.000000,0.000000\n"
                               "5.000000,1.000000,1.000000\n"
                               "4.000000,0.000000,0.000000\n"
                               "2.000000,0.000000,0.000000\n"
                               "1.000000,1.000000,-1.000000\n"
                               "0.000000,2.000000,0.000000\n"
                               "1.000000,3.000000,1.000000\n"
                               "2.000000,4.000000,0.000000\n"
                               "4.000000,4.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pbm2bbm2bp []={
{.x=0.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +1},
{.x=1.000000,.y=3.000000,.z=-1.000000,.next_point=point_pbm2bbm2bp   +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +3},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm2bbm2bp   +4},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +5},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +7},
{.x=5.000000,.y=3.000000,.z=1.000000,.next_point=point_pbm2bbm2bp   +8},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +9},
{.x=5.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm2bbm2bp   +10},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=4.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +12},
{.x=5.000000,.y=3.000000,.z=-1.000000,.next_point=point_pbm2bbm2bp   +13},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +14},
{.x=5.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm2bbm2bp   +15},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +16},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +17},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm2bbm2bp   +18},
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +19},
{.x=1.000000,.y=3.000000,.z=1.000000,.next_point=point_pbm2bbm2bp   +20},
{.x=2.000000,.y=4.000000,.z=0.000000,.next_point=point_pbm2bbm2bp   +21},
{.x=4.000000,.y=4.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm2bbm2bp  []={
{.head=point_pbm2bbm2bp     ,.next_seg=segs_pbm2bbm2bp   +1},
{.head=point_pbm2bbm2bp +6    ,.next_seg=segs_pbm2bbm2bp   +2},
{.head=point_pbm2bbm2bp  + 11 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm2bbm2bp = { { &bm2b, &bm2b }, { 0, 0, 0 }, 2, 0,
                                NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm2bbm2bp = { &pbm2bbm2bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm2bbm2bp = { .itt_string     = char_wptt_pbm2bbm2bp,
                                    .pl_path_string = char_pl_pbm2bbm2bp,
                                    .path           = { .segments = segs_pbm2bbm2bp,
                                                        .pnt_buff = NULL,
                                                        .seg_buff = NULL },
                                    .cfg                = {
                                        .storage_write = &test_stub_write_success,
                                        .itt           = &wptt_pbm2bbm2bp,
                                        .out_path      = &outpath
                                    } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 + X     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 + 1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0_0bbm1bp[] = "i([0 0][-1])";
char char_pl_pb0_0bbm1bp[]   = "0.000000,2.000000,0.000000\n"
                               "1.000000,1.500000,0.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "4.000000,2.000000,0.000000\n"
                               "5.000000,1.000000,-1.000000\n"
                               "6.000000,0.000000,0.000000\n"
                               "\n"
                               "0.000000,0.000000,0.000000\n"
                               "1.000000,0.500000,0.000000\n"
                               "2.000000,0.000000,0.000000\n"
                               "4.000000,0.000000,0.000000\n"
                               "5.000000,1.000000,1.000000\n"
                               "6.000000,2.000000,0.000000";

/* clang-format off */

note_plpath_point_t point_pb0_0bbm1bp  []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +1},
{.x=1.000000,.y=1.500000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +3},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +4},
{.x=5.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb0_0bbm1bp +5},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +7},
{.x=1.000000,.y=0.500000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +8},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +9},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bbm1bp  +10},
{.x=5.000000,.y=1.000000,.z=1.000000,.next_point=point_pb0_0bbm1bp  +11},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=NULL},};

note_plpath_segment_t segs_pb0_0bbm1bp    []={
{.head=point_pb0_0bbm1bp     ,.next_seg=segs_pb0_0bbm1bp +1},
{.head=point_pb0_0bbm1bp + 6 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb0_0bbm1bp = { { &b0_0b, &bm1b }, { 0, 0, 0 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0_0bbm1bp = { &pb0_0bbm1bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0_0bbm1bp = { .itt_string     = char_wptt_pb0_0bbm1bp,
                                     .pl_path_string = char_pl_pb0_0bbm1bp,
                                     .path           = { .segments = segs_pb0_0bbm1bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pb0_0bbm1bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/***** 2 + 3  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_pb2_0bb3_0bp [] = "i([2 0][3 0])";
char char_pl_pb2_0bb3_0bp []   = "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,1.000000\n"
                                 "2.000000,0.000000,0.000000\n"
                                 "3.000000,1.000000,-1.000000\n"
                                 "4.000000,2.000000,0.000000\n"
                                 "6.000000,2.000000,0.000000\n"
                                 "7.000000,1.000000,1.000000\n"
                                 "8.000000,0.000000,0.000000\n"
                                 "9.000000,1.000000,-1.000000\n"
                                 "10.000000,2.000000,0.000000\n"
                                 "11.000000,1.000000,1.000000\n"
                                 "12.000000,0.000000,0.000000\n"
                                 "\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "1.000000,1.000000,-1.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "3.000000,1.000000,1.000000\n"
                                 "4.000000,0.000000,0.000000\n"
                                 "6.000000,0.000000,0.000000\n"
                                 "7.000000,1.000000,-1.000000\n"
                                 "8.000000,2.000000,0.000000\n"
                                 "9.000000,1.000000,1.000000\n"
                                 "10.000000,0.000000,0.000000\n"
                                 "11.000000,1.000000,-1.000000\n"
                                 "12.000000,2.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb2_0bb3_0bp []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +1},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pb2_0bb3_0bp    +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +3},
{.x=3.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb2_0bb3_0bp    +4},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +5},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +6},
{.x=7.000000,.y=1.000000,.z=1.000000,.next_point=point_pb2_0bb3_0bp    +7},
{.x=8.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +8},
{.x=9.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb2_0bb3_0bp    +9},
{.x=10.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +10},
{.x=11.000000,.y=1.000000,.z=1.000000,.next_point=point_pb2_0bb3_0bp    +11},
{.x=12.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +13},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb2_0bb3_0bp    +14},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +15},
{.x=3.000000,.y=1.000000,.z=1.000000,.next_point=point_pb2_0bb3_0bp    +16},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +17},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +18},
{.x=7.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb2_0bb3_0bp    +19},
{.x=8.000000,.y=2.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +20},
{.x=9.000000,.y=1.000000,.z=1.000000,.next_point=point_pb2_0bb3_0bp    +21},
{.x=10.000000,.y=0.000000,.z=0.000000,.next_point=point_pb2_0bb3_0bp    +22},
{.x=11.000000,.y=1.000000,.z=-1.000000,.next_point=point_pb2_0bb3_0bp    +23},
{.x=12.000000,.y=2.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pb2_0bb3_0bp  []={
{.head=point_pb2_0bb3_0bp     ,.next_seg=segs_pb2_0bb3_0bp  +1},
{.head=point_pb2_0bb3_0bp  + 12,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb2_0bb3_0bp = { { &b2_0b, &b3_0b }, { 0, 0, 0 }, 2, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb2_0bb3_0bp = { &pb2_0bb3_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb2_0bb3_0bp = { .itt_string     = char_wptt_pb2_0bb3_0bp,
                                      .pl_path_string = char_pl_pb2_0bb3_0bp,
                                      .path           = { .segments = segs_pb2_0bb3_0bp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_pb2_0bb3_0bp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 + 0     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 + 0     ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0_0bb0_0bp[] = "i([0 0][0 0])";
char char_pl_pb0_0bb0_0bp[]   = "0.000000,2.000000,0.000000\n"
                                "1.000000,1.500000,0.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "4.000000,2.000000,0.000000\n"
                                "5.000000,1.500000,0.000000\n"
                                "6.000000,2.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,0.500000,0.000000\n"
                                "2.000000,0.000000,0.000000\n"
                                "4.000000,0.000000,0.000000\n"
                                "5.000000,0.500000,0.000000\n"
                                "6.000000,0.000000,0.000000";

/* clang-format off */

note_plpath_point_t point_pb0_0bb0_0bp   []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +1},
{.x=1.000000,.y=1.500000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +3},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +4},
{.x=5.000000,.y=1.500000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +5},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +7},
{.x=1.000000,.y=0.500000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +8},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +9},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +10},
{.x=5.000000,.y=0.500000,.z=0.000000,.next_point=point_pb0_0bb0_0bp   +11},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},};

note_plpath_segment_t segs_pb0_0bb0_0bp     []={
{.head=point_pb0_0bb0_0bp ,.next_seg=segs_pb0_0bb0_0bp +1},
{.head=point_pb0_0bb0_0bp + 6 ,.next_seg=NULL},
};

/* clang-format on */

note_wptt_node_t pb0_0bb0_0bp = { { &b0_0b, &b0_0b }, { 0, 0, 0 }, 2, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0_0bb0_0bp = { &pb0_0bb0_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0_0bb0_0bp = { .itt_string     = char_wptt_pb0_0bb0_0bp,
                                      .pl_path_string = char_pl_pb0_0bb0_0bp,
                                      .path           = { .segments = segs_pb0_0bb0_0bp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_pb0_0bb0_0bp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/***** 2 + 2  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_pb2_0bb2_0bp [] = "i([2 0][2 0])";
char char_pl_pb2_0bb2_0bp []   = "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,1.000000\n"
                                 "2.000000,0.000000,0.000000\n"
                                 "3.000000,1.000000,-1.000000\n"
                                 "4.000000,2.000000,0.000000\n"
                                 "6.000000,2.000000,0.000000\n"
                                 "7.000000,1.000000,1.000000\n"
                                 "8.000000,0.000000,0.000000\n"
                                 "9.000000,1.000000,-1.000000\n"
                                 "10.000000,2.000000,0.000000\n"
                                 "\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "1.000000,1.000000,-1.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "3.000000,1.000000,1.000000\n"
                                 "4.000000,0.000000,0.000000\n"
                                 "6.000000,0.000000,0.000000\n"
                                 "7.000000,1.000000,-1.000000\n"
                                 "8.000000,2.000000,0.000000\n"
                                 "9.000000,1.000000,1.000000\n"
                                 "10.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb2_0bb2_0bp []={
{.x=0.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +1},
{.x=1.0,.y=1.0,.z=1.0,.next_point=point_pb2_0bb2_0bp  +2},
{.x=2.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +3},
{.x=3.0,.y=1.0,.z=-1.0,.next_point=point_pb2_0bb2_0bp  +4},
{.x=4.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +5},
{.x=6.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +6},
{.x=7.0,.y=1.0,.z=1.0,.next_point=point_pb2_0bb2_0bp  +7},
{.x=8.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +8},
{.x=9.0,.y=1.0,.z=-1.0,.next_point=point_pb2_0bb2_0bp  +9},
{.x=10.0,.y=2.0,.z=0.0,.next_point=NULL},

{.x=0.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +11},
{.x=1.0,.y=1.0,.z=-1.0,.next_point=point_pb2_0bb2_0bp  +12},
{.x=2.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +13},
{.x=3.0,.y=1.0,.z=1.0,.next_point=point_pb2_0bb2_0bp  +14},
{.x=4.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +15},
{.x=6.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +16},
{.x=7.0,.y=1.0,.z=-1.0,.next_point=point_pb2_0bb2_0bp  +17},
{.x=8.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bb2_0bp  +18},
{.x=9.0,.y=1.0,.z=1.0,.next_point=point_pb2_0bb2_0bp  +19},
{.x=10.0,.y=0.0,.z=0.0,.next_point=NULL},
};

note_plpath_segment_t segs_pb2_0bb2_0bp  []={
{.head=point_pb2_0bb2_0bp     ,.next_seg=segs_pb2_0bb2_0bp  +1},
{.head=point_pb2_0bb2_0bp  + 10 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb2_0bb2_0bp = { { &b2_0b, &b2_0b }, { 0, 0, 0 },
                                  2, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb2_0bb2_0bp = { &pb2_0bb2_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb2_0bb2_0bp = { .itt_string     = char_wptt_pb2_0bb2_0bp,
                                      .pl_path_string = char_pl_pb2_0bb2_0bp,
                                      .path           = { .segments = segs_pb2_0bb2_0bp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_pb2_0bb2_0bp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 + inf   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 + inf   ********************************************************************************/
/************************************************************************************************/
char char_wptt_pb0_0bb0bp[] = "i([0 0][0])";
char char_pl_pb0_0bb0bp[]   = "0.000000,2.000000,0.000000\n"
                              "1.000000,1.500000,0.000000\n"
                              "2.000000,2.000000,0.000000\n"
                              "4.000000,2.000000,0.000000\n"
                              "4.500000,1.000000,0.000000\n"
                              "4.000000,0.000000,0.000000\n"
                              "2.000000,0.000000,0.000000\n"
                              "1.000000,0.500000,0.000000\n"
                              "0.000000,0.000000,0.000000\n"
                              "0.000000,0.000000,0.000000\n"
                              "\n"
                              "6.000000,2.000000,0.000000\n"
                              "5.500000,1.000000,0.000000\n"
                              "6.000000,0.000000,0.000000";

/* clang-format off */
note_plpath_point_t point_pb0_0bb0bp []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +1},
{.x=1.000000,.y=1.500000,.z=0.000000,.next_point=point_pb0_0bb0bp +2},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +3},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +4},
{.x=4.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +5},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +6},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +7},
{.x=1.000000,.y=0.500000,.z=0.000000,.next_point=point_pb0_0bb0bp +8},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +9},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +11},
{.x=5.500000,.y=1.000000,.z=0.000000,.next_point=point_pb0_0bb0bp +12},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pb0_0bb0bp      []={
{.head=point_pb0_0bb0bp  ,.next_seg=segs_pb0_0bb0bp  +1},
{.head=point_pb0_0bb0bp  + 10 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb0_0bb0bp = { { &b0_0b, &b0b }, { 0, 0, 0 }, 2, 0,
                                NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb0_0bb0bp = { &pb0_0bb0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb0_0bb0bp = { .itt_string     = char_wptt_pb0_0bb0bp,
                                    .pl_path_string = char_pl_pb0_0bb0bp,
                                    .path           = { .segments = segs_pb0_0bb0bp,
                                                        .pnt_buff = NULL,
                                                        .seg_buff = NULL },
                                    .cfg                = {
                                        .storage_write = &test_stub_write_success,
                                        .itt           = &wptt_pb0_0bb0bp,
                                        .out_path      = &outpath
                                    } };


/************************************************************************************************/
/***** 2 + 1/2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_pb2_0bbm2bp [] = "i([2 0][-2])";
char char_pl_pb2_0bbm2bp []   = "0.000000,4.000000,0.000000\n"
                                "0.000000,3.000000,0.000000\n"
                                "1.000000,2.000000,1.000000\n"
                                "2.000000,1.000000,0.000000\n"
                                "3.000000,2.000000,-1.000000\n"
                                "4.000000,3.000000,0.000000\n"
                                "6.000000,4.000000,0.000000\n"
                                "7.000000,3.000000,-1.000000\n"
                                "8.000000,2.000000,0.000000\n"
                                "7.000000,1.000000,1.000000\n"
                                "6.000000,0.000000,0.000000\n"
                                "4.000000,1.000000,0.000000\n"
                                "3.000000,2.000000,1.000000\n"
                                "2.000000,3.000000,0.000000\n"
                                "1.000000,2.000000,-1.000000\n"
                                "0.000000,1.000000,0.000000\n"
                                "0.000000,0.000000,0.000000\n"
                                "\n"
                                "8.000000,4.000000,0.000000\n"
                                "7.000000,3.000000,1.000000\n"
                                "6.000000,2.000000,0.000000\n"
                                "7.000000,1.000000,-1.000000\n"
                                "8.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb2_0bbm2bp []={
{.x=0.0,.y=4.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +1},
{.x=0.0,.y=3.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +2},
{.x=1.0,.y=2.0,.z=1.0,.next_point=point_pb2_0bbm2bp  +3},
{.x=2.0,.y=1.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +4},
{.x=3.0,.y=2.0,.z=-1.0,.next_point=point_pb2_0bbm2bp  +5},
{.x=4.0,.y=3.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +6},
{.x=6.0,.y=4.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +7},
{.x=7.0,.y=3.0,.z=-1.0,.next_point=point_pb2_0bbm2bp  +8},
{.x=8.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +9},
{.x=7.0,.y=1.0,.z=1.0,.next_point=point_pb2_0bbm2bp  +10},
{.x=6.0,.y=0.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +11},
{.x=4.0,.y=1.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +12},
{.x=3.0,.y=2.0,.z=1.0,.next_point=point_pb2_0bbm2bp  +13},
{.x=2.0,.y=3.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +14},
{.x=1.0,.y=2.0,.z=-1.0,.next_point=point_pb2_0bbm2bp  +15},
{.x=0.0,.y=1.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +16},
{.x=0.0,.y=0.0,.z=0.0,.next_point=NULL},

{.x=8.0,.y=4.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +18},
{.x=7.0,.y=3.0,.z=1.0,.next_point=point_pb2_0bbm2bp  +19},
{.x=6.0,.y=2.0,.z=0.0,.next_point=point_pb2_0bbm2bp  +20},
{.x=7.0,.y=1.0,.z=-1.0,.next_point=point_pb2_0bbm2bp  +21},
{.x=8.0,.y=0.0,.z=0.0,.next_point=NULL},
};

note_plpath_segment_t segs_pb2_0bbm2bp  []={
{.head=point_pb2_0bbm2bp     ,.next_seg=segs_pb2_0bbm2bp  +1},
{.head=point_pb2_0bbm2bp  + 17 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb2_0bbm2bp = { { &b2_0b, &bm2b }, { 0, 0, 0 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb2_0bbm2bp = { &pb2_0bbm2bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb2_0bbm2bp = { .itt_string     = char_wptt_pb2_0bbm2bp,
                                     .pl_path_string = char_pl_pb2_0bbm2bp,
                                     .path           = { .segments = segs_pb2_0bbm2bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pb2_0bbm2bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/************************************************************************************************/
/* X + X     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 + 1     ********************************************************************************/
/************************************************************************************************/
char char_wptt_pbm1bbm1bp[] = "i([-1][-1])";
char char_pl_pbm1bbm1bp[]   = "0.000000,2.000000,0.000000\n"
                              "1.000000,1.000000,-1.000000\n"
                              "2.000000,0.000000,0.000000\n"
                              "4.000000,0.000000,0.000000\n"
                              "5.000000,1.000000,1.000000\n"
                              "6.000000,2.000000,0.000000\n"
                              "\n"
                              "0.000000,0.000000,0.000000\n"
                              "1.000000,1.000000,1.000000\n"
                              "2.000000,2.000000,0.000000\n"
                              "4.000000,2.000000,0.000000\n"
                              "5.000000,1.000000,-1.000000\n"
                              "6.000000,0.000000,0.000000";

/* clang-format off */
note_plpath_point_t point_pbm1bbm1bp []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +1},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm1bbm1bp +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +3},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +4},
{.x=5.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm1bbm1bp +5},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +7},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm1bbm1bp +8},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +9},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bbm1bp +10},
{.x=5.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm1bbm1bp +11},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm1bbm1bp       []={
{.head=point_pbm1bbm1bp ,.next_seg=segs_pbm1bbm1bp +1},
{.head=point_pbm1bbm1bp + 6,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm1bbm1bp = { { &bm1b, &bm1b }, { 0, 0, 0 }, 2, 0,
                                NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm1bbm1bp = { &pbm1bbm1bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm1bbm1bp = { .itt_string     = char_wptt_pbm1bbm1bp,
                                    .pl_path_string = char_pl_pbm1bbm1bp,
                                    .path           = { .segments = segs_pbm1bbm1bp,
                                                        .pnt_buff = NULL,
                                                        .seg_buff = NULL },
                                    .cfg                = {
                                        .storage_write = &test_stub_write_success,
                                        .itt           = &wptt_pbm1bbm1bp,
                                        .out_path      = &outpath
                                    } };

/************************************************************************************************/
/***** 3 + 1/3  *********************************************************************************/
/************************************************************************************************/
char char_wptt_pb3_0bbm3bp [] = "i([3 0][-3])";
char char_pl_pb3_0bbm3bp []   = "0.000000,6.000000,0.000000\n"
                                "0.000000,4.000000,0.000000\n"
                                "1.000000,3.000000,1.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "3.000000,3.000000,-1.000000\n"
                                "4.000000,4.000000,0.000000\n"
                                "5.000000,3.000000,1.000000\n"
                                "6.000000,2.000000,0.000000\n"
                                "8.000000,0.000000,0.000000\n"
                                "9.000000,1.000000,1.000000\n"
                                "10.000000,2.000000,0.000000\n"
                                "9.000000,3.000000,-1.000000\n"
                                "8.000000,4.000000,0.000000\n"
                                "9.000000,5.000000,1.000000\n"
                                "10.000000,6.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "0.000000,2.000000,0.000000\n"
                                "1.000000,3.000000,-1.000000\n"
                                "2.000000,4.000000,0.000000\n"
                                "3.000000,3.000000,1.000000\n"
                                "4.000000,2.000000,0.000000\n"
                                "5.000000,3.000000,-1.000000\n"
                                "6.000000,4.000000,0.000000\n"
                                "8.000000,6.000000,0.000000\n"
                                "9.000000,5.000000,-1.000000\n"
                                "10.000000,4.000000,0.000000\n"
                                "9.000000,3.000000,1.000000\n"
                                "8.000000,2.000000,0.000000\n"
                                "9.000000,1.000000,-1.000000\n"
                                "10.000000,0.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb3_0bbm3bp []={
{.x=0.0,.y=6.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +1},
{.x=0.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +2},
{.x=1.0,.y=3.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +3},
{.x=2.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +4},
{.x=3.0,.y=3.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +5},
{.x=4.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +6},
{.x=5.0,.y=3.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +7},
{.x=6.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +8},
{.x=8.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +9},
{.x=9.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +10},
{.x=10.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +11},
{.x=9.0,.y=3.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +12},
{.x=8.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +13},
{.x=9.0,.y=5.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +14},
{.x=10.0,.y=6.0,.z=0.0,.next_point=NULL},

{.x=0.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +16},
{.x=0.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +17},
{.x=1.0,.y=3.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +18},
{.x=2.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +19},
{.x=3.0,.y=3.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +20},
{.x=4.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +21},
{.x=5.0,.y=3.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +22},
{.x=6.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +23},
{.x=8.0,.y=6.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +24},
{.x=9.0,.y=5.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +25},
{.x=10.0,.y=4.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +26},
{.x=9.0,.y=3.0,.z=1.0,.next_point=point_pb3_0bbm3bp  +27},
{.x=8.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bbm3bp  +28},
{.x=9.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bbm3bp  +29},
{.x=10.0,.y=0.0,.z=0.0,.next_point=NULL},

};

note_plpath_segment_t segs_pb3_0bbm3bp  []={
{.head=point_pb3_0bbm3bp     ,.next_seg=segs_pb3_0bbm3bp  +1},
{.head=point_pb3_0bbm3bp  + 15 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb3_0bbm3bp = { { &b3_0b, &bm3b }, { 0, 0, 0 }, 2,
                                 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb3_0bbm3bp = { &pb3_0bbm3bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb3_0bbm3bp = { .itt_string     = char_wptt_pb3_0bbm3bp,
                                     .pl_path_string = char_pl_pb3_0bbm3bp,
                                     .path           = { .segments = segs_pb3_0bbm3bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pb3_0bbm3bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/************************************************************************************************/
/* X + 0     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 + 0     ********************************************************************************/
/************************************************************************************************/

char char_wptt_pbm1bb0_0bp[] = "i([-1][0 0])";
char char_pl_pbm1bb0_0bp[]   = "0.000000,2.000000,0.000000\n"
                               "1.000000,1.000000,-1.000000\n"
                               "2.000000,0.000000,0.000000\n"
                               "4.000000,0.000000,0.000000\n"
                               "5.000000,0.500000,0.000000\n"
                               "6.000000,0.000000,0.000000\n"
                               "\n"
                               "0.000000,0.000000,0.000000\n"
                               "1.000000,1.000000,1.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "4.000000,2.000000,0.000000\n"
                               "5.000000,1.500000,0.000000\n"
                               "6.000000,2.000000,0.000000";

/* clang-format off */
note_plpath_point_t point_pbm1bb0_0bp  []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +1},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm1bb0_0bp  +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +3},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +4},
{.x=5.000000,.y=0.500000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +5},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +7},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm1bb0_0bp  +8},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +9},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +10},
{.x=5.000000,.y=1.500000,.z=0.000000,.next_point=point_pbm1bb0_0bp  +11},
{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm1bb0_0bp        []={
{.head=point_pbm1bb0_0bp ,.next_seg=segs_pbm1bb0_0bp +1},
{.head=point_pbm1bb0_0bp + 6,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm1bb0_0bp = { { &bm1b, &b0_0b }, { 0, 0, 0 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm1bb0_0bp = { &pbm1bb0_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm1bb0_0bp = { .itt_string     = char_wptt_pbm1bb0_0bp,
                                     .pl_path_string = char_pl_pbm1bb0_0bp,
                                     .path           = { .segments = segs_pbm1bb0_0bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pbm1bb0_0bp,
                                         .out_path      = &outpath
                                     } };
/************************************************************************************************/
/***** 3 + 2  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_pb3_0bb2_0bp [] = "i([3 0][2 0])";
char char_pl_pb3_0bb2_0bp []   = "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,1.000000\n"
                                 "2.000000,0.000000,0.000000\n"
                                 "3.000000,1.000000,-1.000000\n"
                                 "4.000000,2.000000,0.000000\n"
                                 "5.000000,1.000000,1.000000\n"
                                 "6.000000,0.000000,0.000000\n"
                                 "8.000000,0.000000,0.000000\n"
                                 "9.000000,1.000000,-1.000000\n"
                                 "10.000000,2.000000,0.000000\n"
                                 "11.000000,1.000000,1.000000\n"
                                 "12.000000,0.000000,0.000000\n"
                                 "\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "1.000000,1.000000,-1.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "3.000000,1.000000,1.000000\n"
                                 "4.000000,0.000000,0.000000\n"
                                 "5.000000,1.000000,-1.000000\n"
                                 "6.000000,2.000000,0.000000\n"
                                 "8.000000,2.000000,0.000000\n"
                                 "9.000000,1.000000,1.000000\n"
                                 "10.000000,0.000000,0.000000\n"
                                 "11.000000,1.000000,-1.000000\n"
                                 "12.000000,2.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pb3_0bb2_0bp []={
{.x=0.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +1},
{.x=1.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bb2_0bp  +2},
{.x=2.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +3},
{.x=3.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bb2_0bp  +4},
{.x=4.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +5},
{.x=5.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bb2_0bp  +6},
{.x=6.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +7},
{.x=8.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +8},
{.x=9.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bb2_0bp  +9},
{.x=10.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +10},
{.x=11.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bb2_0bp  +11},
{.x=12.0,.y=0.0,.z=0.0,.next_point=NULL},

{.x=0.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +13},
{.x=1.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bb2_0bp  +14},
{.x=2.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +15},
{.x=3.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bb2_0bp  +16},
{.x=4.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +17},
{.x=5.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bb2_0bp  +18},
{.x=6.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +19},
{.x=8.0,.y=2.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +20},
{.x=9.0,.y=1.0,.z=1.0,.next_point=point_pb3_0bb2_0bp  +21},
{.x=10.0,.y=0.0,.z=0.0,.next_point=point_pb3_0bb2_0bp  +22},
{.x=11.0,.y=1.0,.z=-1.0,.next_point=point_pb3_0bb2_0bp  +23},
{.x=12.0,.y=2.0,.z=0.0,.next_point=NULL},

};

note_plpath_segment_t segs_pb3_0bb2_0bp  []={
{.head=point_pb3_0bb2_0bp     ,.next_seg=segs_pb3_0bb2_0bp  +1},
{.head=point_pb3_0bb2_0bp  + 12 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pb3_0bb2_0bp = { { &b3_0b, &b2_0b }, { 0, 0, 0 },
                                  2, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pb3_0bb2_0bp = { &pb3_0bb2_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pb3_0bb2_0bp = { .itt_string     = char_wptt_pb3_0bb2_0bp,
                                      .pl_path_string = char_pl_pb3_0bb2_0bp,
                                      .path           = { .segments = segs_pb3_0bb2_0bp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_pb3_0bb2_0bp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/************************************************************************************************/
/* X + inf    ***********************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 + inf   ********************************************************************************/
/************************************************************************************************/

char char_wptt_pbm1bb0bp[] = "i([-1][0])";
char char_pl_pbm1bb0bp[]   = "0.000000,2.000000,0.000000\n"
                             "1.000000,1.000000,-1.000000\n"
                             "2.000000,0.000000,0.000000\n"
                             "4.000000,0.000000,0.000000\n"
                             "4.500000,1.000000,0.000000\n"
                             "4.000000,2.000000,0.000000\n"
                             "2.000000,2.000000,0.000000\n"
                             "1.000000,1.000000,1.000000\n"
                             "0.000000,0.000000,0.000000\n"
                             "0.000000,0.000000,0.000000\n"
                             "\n"
                             "6.000000,2.000000,0.000000\n"
                             "5.500000,1.000000,0.000000\n"
                             "6.000000,0.000000,0.000000";

/* clang-format off */
note_plpath_point_t point_pbm1bb0bp  []={
{.x=0.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +1},
{.x=1.000000,.y=1.000000,.z=-1.000000,.next_point=point_pbm1bb0bp  +2},
{.x=2.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +3},
{.x=4.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +4},
{.x=4.500000,.y=1.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +5},
{.x=4.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +6},
{.x=2.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +7},
{.x=1.000000,.y=1.000000,.z=1.000000,.next_point=point_pbm1bb0bp  +8},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +9},
{.x=0.000000,.y=0.000000,.z=0.000000,.next_point=NULL},

{.x=6.000000,.y=2.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +11},
{.x=5.500000,.y=1.000000,.z=0.000000,.next_point=point_pbm1bb0bp  +12},
{.x=6.000000,.y=0.000000,.z=0.000000,.next_point=NULL},
};

note_plpath_segment_t segs_pbm1bb0bp []={
{.head=point_pbm1bb0bp ,.next_seg=segs_pbm1bb0bp +1},
{.head=point_pbm1bb0bp + 10,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm1bb0bp = { { &bm1b, &b0b }, { 0, 0, 0 }, 2, 0,
                               NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm1bb0bp = { &pbm1bb0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm1bb0bp = { .itt_string     = char_wptt_pbm1bb0bp,
                                   .pl_path_string = char_pl_pbm1bb0bp,
                                   .path           = { .segments = segs_pbm1bb0bp,
                                                       .pnt_buff = NULL,
                                                       .seg_buff = NULL },
                                   .cfg                = {
                                       .storage_write = &test_stub_write_success,
                                       .itt           = &wptt_pbm1bb0bp,
                                       .out_path      = &outpath
                                   } };

/************************************************************************************************/
/***** 3 + 1/2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_pbm3bb2_0bp [] = "i([-3][2 0])";
char char_pl_pbm3bb2_0bp []   = "0.000000,6.000000,0.000000\n"
                                "1.000000,5.000000,-1.000000\n"
                                "2.000000,4.000000,0.000000\n"
                                "1.000000,3.000000,1.000000\n"
                                "0.000000,2.000000,0.000000\n"
                                "1.000000,1.000000,-1.000000\n"
                                "2.000000,0.000000,0.000000\n"
                                "4.000000,2.000000,0.000000\n"
                                "5.000000,3.000000,-1.000000\n"
                                "6.000000,4.000000,0.000000\n"
                                "7.000000,3.000000,1.000000\n"
                                "8.000000,2.000000,0.000000\n"
                                "8.000000,0.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,1.000000,1.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "1.000000,3.000000,-1.000000\n"
                                "0.000000,4.000000,0.000000\n"
                                "1.000000,5.000000,1.000000\n"
                                "2.000000,6.000000,0.000000\n"
                                "4.000000,4.000000,0.000000\n"
                                "5.000000,3.000000,1.000000\n"
                                "6.000000,2.000000,0.000000\n"
                                "7.000000,3.000000,-1.000000\n"
                                "8.000000,4.000000,0.000000\n"
                                "8.000000,6.000000,0.000000";


/* clang-format off */
note_plpath_point_t point_pbm3bb2_0bp []={
{.x=0.0,.y=6.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +1},
{.x=1.0,.y=5.0,.z=-1.0,.next_point=point_pbm3bb2_0bp  +2},
{.x=2.0,.y=4.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +3},
{.x=1.0,.y=3.0,.z=1.0,.next_point=point_pbm3bb2_0bp  +4},
{.x=0.0,.y=2.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +5},
{.x=1.0,.y=1.0,.z=-1.0,.next_point=point_pbm3bb2_0bp  +6},
{.x=2.0,.y=0.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +7},
{.x=4.0,.y=2.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +8},
{.x=5.0,.y=3.0,.z=-1.0,.next_point=point_pbm3bb2_0bp  +9},
{.x=6.0,.y=4.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +10},
{.x=7.0,.y=3.0,.z=1.0,.next_point=point_pbm3bb2_0bp  +11},
{.x=8.0,.y=2.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +12},
{.x=8.0,.y=0.0,.z=0.0,.next_point=NULL},

{.x=0.0,.y=0.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +14},
{.x=1.0,.y=1.0,.z=1.0,.next_point=point_pbm3bb2_0bp  +15},
{.x=2.0,.y=2.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +16},
{.x=1.0,.y=3.0,.z=-1.0,.next_point=point_pbm3bb2_0bp  +17},
{.x=0.0,.y=4.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +18},
{.x=1.0,.y=5.0,.z=1.0,.next_point=point_pbm3bb2_0bp  +19},
{.x=2.0,.y=6.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +20},
{.x=4.0,.y=4.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +21},
{.x=5.0,.y=3.0,.z=1.0,.next_point=point_pbm3bb2_0bp  +22},
{.x=6.0,.y=2.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +23},
{.x=7.0,.y=3.0,.z=-1.0,.next_point=point_pbm3bb2_0bp  +24},
{.x=8.0,.y=4.0,.z=0.0,.next_point=point_pbm3bb2_0bp  +25},
{.x=8.0,.y=6.0,.z=0.0,.next_point=NULL}

};

note_plpath_segment_t segs_pbm3bb2_0bp  []={
{.head=point_pbm3bb2_0bp     ,.next_seg=segs_pbm3bb2_0bp  +1},
{.head=point_pbm3bb2_0bp  + 13 ,.next_seg=NULL},
};
/* clang-format on */

note_wptt_node_t pbm3bb2_0bp = { { &bm3b, &b2_0b }, { 0, 0, 0 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_pbm3bb2_0bp = { &pbm3bb2_0bp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_pbm3bb2_0bp = { .itt_string     = char_wptt_pbm3bb2_0bp,
                                     .pl_path_string = char_pl_pbm3bb2_0bp,
                                     .path           = { .segments = segs_pbm3bb2_0bp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_pbm3bb2_0bp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/


/************************************************************************************************/
/************************************************************************************************/
/* inf v X   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf v 1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0bbm1bpp [] = "i(([0][-1]))";

char char_pl_ppb0bbm1bpp   [] = "0.000000,6.000000,0.000000\n"
                                "1.000000,5.500000,0.000000\n"
                                "2.000000,6.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,1.000000,-1.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "2.000000,4.000000,0.000000\n"
                                "1.000000,4.500000,0.000000\n"
                                "0.000000,4.000000,0.000000\n"
                                "0.000000,2.000000,0.000000\n"
                                "1.000000,1.000000,1.000000\n"
                                "2.000000,0.000000,0.000000";

note_plpath_point_t point_ppb0bbm1bpp    [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 1  },
    { .x = 1.0, .y = 5.5, .z =  0.0, .next_point = point_ppb0bbm1bpp + 2  },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = NULL                   },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 4  },
    { .x = 1.0, .y = 1.0, .z = -1.0, .next_point = point_ppb0bbm1bpp + 5  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 6  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 7  },
    { .x = 1.0, .y = 4.5, .z =  0.0, .next_point = point_ppb0bbm1bpp + 8  },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 9  },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppb0bbm1bpp + 10 },
    { .x = 1.0, .y = 1.0, .z =  1.0, .next_point = point_ppb0bbm1bpp + 11 },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = NULL                   },
};


note_plpath_segment_t segs_ppb0bbm1bpp [] = {
    { .head = point_ppb0bbm1bpp,     .next_seg = segs_ppb0bbm1bpp + 1 },
    { .head = point_ppb0bbm1bpp + 3, .next_seg = NULL                 },
};

note_wptt_node_t ppb0bbm1bpp = { { &pb0bbm1bp }, { 0, 0, 0 }, 1, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0bbm1bpp = { &ppb0bbm1bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0bbm1bpp = { .itt_string     = char_wptt_ppb0bbm1bpp,
                                     .pl_path_string = char_pl_ppb0bbm1bpp,
                                     .path           = { .segments = segs_ppb0bbm1bpp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_ppb0bbm1bpp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/***** 1/2 v 3  *********************************************************************************/
/************************************************************************************************/
char char_wptt_ppbm2bb3_0bpp [] = "i(([-2][3 0]))";


char char_pl_ppbm2bb3_0bpp [] = "0.000000,10.000000,0.000000\n"
                                "1.000000,9.000000,1.000000\n"
                                "2.000000,8.000000,0.000000\n"
                                "3.000000,9.000000,-1.000000\n"
                                "4.000000,10.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,0.000000,0.000000\n"
                                "2.000000,1.000000,1.000000\n"
                                "3.000000,2.000000,0.000000\n"
                                "2.000000,3.000000,-1.000000\n"
                                "1.000000,4.000000,0.000000\n"
                                "2.000000,5.000000,1.000000\n"
                                "3.000000,6.000000,0.000000\n"
                                "4.000000,8.000000,0.000000\n"
                                "3.000000,9.000000,1.000000\n"
                                "2.000000,10.000000,0.000000\n"
                                "1.000000,9.000000,-1.000000\n"
                                "0.000000,8.000000,0.000000\n"
                                "1.000000,6.000000,0.000000\n"
                                "2.000000,5.000000,-1.000000\n"
                                "3.000000,4.000000,0.000000\n"
                                "2.000000,3.000000,1.000000\n"
                                "1.000000,2.000000,0.000000\n"
                                "2.000000,1.000000,-1.000000\n"
                                "3.000000,0.000000,0.000000\n"
                                "4.000000,0.000000,0.000000";

note_plpath_point_t point_ppbm2bb3_0bpp [] = {
    { .x = 0.0, .y = 10.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 1  },
    { .x = 1.0, .y =  9.0, .z =  1.0, .next_point = point_ppbm2bb3_0bpp + 2  },
    { .x = 2.0, .y =  8.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 3  },
    { .x = 3.0, .y =  9.0, .z = -1.0, .next_point = point_ppbm2bb3_0bpp + 4  },
    { .x = 4.0, .y = 10.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 6  },
    { .x = 1.0, .y =  0.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 7  },
    { .x = 2.0, .y =  1.0, .z =  1.0, .next_point = point_ppbm2bb3_0bpp + 8  },
    { .x = 3.0, .y =  2.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 9  },
    { .x = 2.0, .y =  3.0, .z = -1.0, .next_point = point_ppbm2bb3_0bpp + 10 },
    { .x = 1.0, .y =  4.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 11 },
    { .x = 2.0, .y =  5.0, .z =  1.0, .next_point = point_ppbm2bb3_0bpp + 12 },
    { .x = 3.0, .y =  6.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 13 },
    { .x = 4.0, .y =  8.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 14 },
    { .x = 3.0, .y =  9.0, .z =  1.0, .next_point = point_ppbm2bb3_0bpp + 15 },
    { .x = 2.0, .y = 10.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 16 },
    { .x = 1.0, .y =  9.0, .z = -1.0, .next_point = point_ppbm2bb3_0bpp + 17 },
    { .x = 0.0, .y =  8.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 18 },
    { .x = 1.0, .y =  6.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 19 },
    { .x = 2.0, .y =  5.0, .z = -1.0, .next_point = point_ppbm2bb3_0bpp + 20 },
    { .x = 3.0, .y =  4.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 21 },
    { .x = 2.0, .y =  3.0, .z =  1.0, .next_point = point_ppbm2bb3_0bpp + 22 },
    { .x = 1.0, .y =  2.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 23 },
    { .x = 2.0, .y =  1.0, .z = -1.0, .next_point = point_ppbm2bb3_0bpp + 24 },
    { .x = 3.0, .y =  0.0, .z =  0.0, .next_point = point_ppbm2bb3_0bpp + 25 },
    { .x = 4.0, .y =  0.0, .z =  0.0, .next_point = NULL                     },
};


note_plpath_segment_t segs_ppbm2bb3_0bpp     [] = {
    { .head = point_ppbm2bb3_0bpp,     .next_seg = segs_ppbm2bb3_0bpp + 1 },
    { .head = point_ppbm2bb3_0bpp + 5, .next_seg = NULL                   },
};


note_wptt_node_t ppbm2bb3_0bpp = { { &pbm2bb3_0bp }, { 0, 0, 0 }, 1, 0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm2bb3_0bpp = { &ppbm2bb3_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm2bb3_0bpp = { .itt_string     = char_wptt_ppbm2bb3_0bpp,
                                       .pl_path_string = char_pl_ppbm2bb3_0bpp,
                                       .path           = { .segments = segs_ppbm2bb3_0bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppbm2bb3_0bpp,
                                           .out_path      = &outpath
                                       } };

/************************************************************************************************/
/************************************************************************************************/
/* inf v 0   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf v 0   ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0bb0_0bpp [] = "i(([0][0 0]))";



char char_pl_ppb0bb0_0bpp [] = "0.000000,6.000000,0.000000\n"
                               "1.000000,5.500000,0.000000\n"
                               "2.000000,6.000000,0.000000\n"
                               "\n"
                               "0.000000,0.000000,0.000000\n"
                               "0.500000,1.000000,0.000000\n"
                               "0.000000,2.000000,0.000000\n"
                               "0.000000,4.000000,0.000000\n"
                               "1.000000,4.500000,0.000000\n"
                               "2.000000,4.000000,0.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "1.500000,1.000000,0.000000\n"
                               "2.000000,0.000000,0.000000";

note_plpath_point_t point_ppb0bb0_0bpp [] = {
    { .x = 0.0, .y = 6.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 1  },
    { .x = 1.0, .y = 5.5, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 2  },
    { .x = 2.0, .y = 6.0, .z = 0.0, .next_point = NULL                    },

    { .x = 0.0, .y = 0.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 4  },
    { .x = 0.5, .y = 1.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 5  },
    { .x = 0.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 6  },
    { .x = 0.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 7  },
    { .x = 1.0, .y = 4.5, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 8  },
    { .x = 2.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 9  },
    { .x = 2.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 10 },
    { .x = 1.5, .y = 1.0, .z = 0.0, .next_point = point_ppb0bb0_0bpp + 11 },
    { .x = 2.0, .y = 0.0, .z = 0.0, .next_point = NULL                    },
};



note_plpath_segment_t segs_ppb0bb0_0bpp  [] = {
    { .head = point_ppb0bb0_0bpp,     .next_seg = segs_ppb0bb0_0bpp + 1 },
    { .head = point_ppb0bb0_0bpp + 3, .next_seg = NULL                  },
};

note_wptt_node_t ppb0bb0_0bpp = { { &pb0bb0_0bp }, { 0, 0, 0 }, 1, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0bb0_0bpp = { &ppb0bb0_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0bb0_0bpp = { .itt_string     = char_wptt_ppb0bb0_0bpp,
                                      .pl_path_string = char_pl_ppb0bb0_0bpp,
                                      .path           = { .segments = segs_ppb0bb0_0bpp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_ppb0bb0_0bpp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/***** 1/2 v 2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_ppbm2bb2_0bpp [] = "i(([-2][2 0]))";


char char_pl_ppbm2bb2_0bpp [] = "0.000000,8.000000,0.000000\n"
                                "1.000000,7.000000,1.000000\n"
                                "2.000000,6.000000,0.000000\n"
                                "3.000000,7.000000,-1.000000\n"
                                "4.000000,8.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,0.000000,0.000000\n"
                                "2.000000,1.000000,1.000000\n"
                                "3.000000,2.000000,0.000000\n"
                                "2.000000,3.000000,-1.000000\n"
                                "1.000000,4.000000,0.000000\n"
                                "0.000000,6.000000,0.000000\n"
                                "1.000000,7.000000,-1.000000\n"
                                "2.000000,8.000000,0.000000\n"
                                "3.000000,7.000000,1.000000\n"
                                "4.000000,6.000000,0.000000\n"
                                "3.000000,4.000000,0.000000\n"
                                "2.000000,3.000000,1.000000\n"
                                "1.000000,2.000000,0.000000\n"
                                "2.000000,1.000000,-1.000000\n"
                                "3.000000,0.000000,0.000000\n"
                                "4.000000,0.000000,0.000000";

note_plpath_point_t point_ppbm2bb2_0bpp [] = {
    { .x = 0.0, .y = 8.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 1  },
    { .x = 1.0, .y = 7.0, .z =  1.0, .next_point = point_ppbm2bb2_0bpp + 2  },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 3  },
    { .x = 3.0, .y = 7.0, .z = -1.0, .next_point = point_ppbm2bb2_0bpp + 4  },
    { .x = 4.0, .y = 8.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 6  },
    { .x = 1.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 7  },
    { .x = 2.0, .y = 1.0, .z =  1.0, .next_point = point_ppbm2bb2_0bpp + 8  },
    { .x = 3.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 9  },
    { .x = 2.0, .y = 3.0, .z = -1.0, .next_point = point_ppbm2bb2_0bpp + 10 },
    { .x = 1.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 11 },
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 12 },
    { .x = 1.0, .y = 7.0, .z = -1.0, .next_point = point_ppbm2bb2_0bpp + 13 },
    { .x = 2.0, .y = 8.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 14 },
    { .x = 3.0, .y = 7.0, .z =  1.0, .next_point = point_ppbm2bb2_0bpp + 15 },
    { .x = 4.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 16 },
    { .x = 3.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 17 },
    { .x = 2.0, .y = 3.0, .z =  1.0, .next_point = point_ppbm2bb2_0bpp + 18 },
    { .x = 1.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 19 },
    { .x = 2.0, .y = 1.0, .z = -1.0, .next_point = point_ppbm2bb2_0bpp + 20 },
    { .x = 3.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm2bb2_0bpp + 21 },
    { .x = 4.0, .y = 0.0, .z =  0.0, .next_point = NULL                     },
};


note_plpath_segment_t segs_ppbm2bb2_0bpp  [] = {
    { .head = point_ppbm2bb2_0bpp,     .next_seg = segs_ppbm2bb2_0bpp + 1 },
    { .head = point_ppbm2bb2_0bpp + 5, .next_seg = NULL                   },
};

note_wptt_node_t ppbm2bb2_0bpp = { { &pbm2bb2_0bp }, { 0, 0, 0 }, 1,
                                   0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm2bb2_0bpp = { &ppbm2bb2_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm2bb2_0bpp = { .itt_string     = char_wptt_ppbm2bb2_0bpp,
                                       .pl_path_string = char_pl_ppbm2bb2_0bpp,
                                       .path           = { .segments = segs_ppbm2bb2_0bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppbm2bb2_0bpp,
                                           .out_path      = &outpath
                                       } };

/************************************************************************************************/
/************************************************************************************************/
/* inf v inf ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** inf v inf ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0bb0bpp [] = "i(([0][0]))";


char char_pl_ppb0bb0bpp      [] = "0.000000,6.000000,0.000000\n"
                                  "1.000000,5.500000,0.000000\n"
                                  "2.000000,6.000000,0.000000\n"
                                  "\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "1.000000,0.500000,0.000000\n"
                                  "2.000000,0.000000,0.000000\n"
                                  "\n"
                                  "0.000000,2.000000,0.000000\n"
                                  "1.000000,1.500000,0.000000\n"
                                  "2.000000,2.000000,0.000000\n"
                                  "2.000000,4.000000,0.000000\n"
                                  "1.000000,4.500000,0.000000\n"
                                  "0.000000,4.000000,0.000000\n"
                                  "0.000000,2.000000,0.000000";

note_plpath_point_t point_ppb0bb0bpp    [] = {
    { .x = 0.0, .y = 6.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 1  },
    { .x = 1.0, .y = 5.5, .z = 0.0, .next_point = point_ppb0bb0bpp + 2  },
    { .x = 2.0, .y = 6.0, .z = 0.0, .next_point = NULL                  },

    { .x = 0.0, .y = 0.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 4  },
    { .x = 1.0, .y = 0.5, .z = 0.0, .next_point = point_ppb0bb0bpp + 5  },
    { .x = 2.0, .y = 0.0, .z = 0.0, .next_point = NULL                  },

    { .x = 0.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 7  },
    { .x = 1.0, .y = 1.5, .z = 0.0, .next_point = point_ppb0bb0bpp + 8  },
    { .x = 2.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 9  },
    { .x = 2.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 10 },
    { .x = 1.0, .y = 4.5, .z = 0.0, .next_point = point_ppb0bb0bpp + 11 },
    { .x = 0.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0bb0bpp + 12 },
    { .x = 0.0, .y = 2.0, .z = 0.0, .next_point = NULL                  },
};

note_plpath_segment_t segs_ppb0bb0bpp   [] = {
    { .head = point_ppb0bb0bpp,     .next_seg = segs_ppb0bb0bpp + 1 },
    { .head = point_ppb0bb0bpp + 3, .next_seg = segs_ppb0bb0bpp + 2 },
    { .head = point_ppb0bb0bpp + 6, .next_seg = NULL                },
};

note_wptt_node_t ppb0bb0bpp = { { &pb0bb0bp }, { 0, 0, 0 }, 1, 0,
                                NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0bb0bpp = { &ppb0bb0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0bb0bpp = { .itt_string     = char_wptt_ppb0bb0bpp,
                                    .pl_path_string = char_pl_ppb0bb0bpp,
                                    .path           = { .segments = segs_ppb0bb0bpp,
                                                        .pnt_buff = NULL,
                                                        .seg_buff = NULL },
                                    .cfg                = {
                                        .storage_write = &test_stub_write_success,
                                        .itt           = &wptt_ppb0bb0bpp,
                                        .out_path      = &outpath
                                    } };

/************************************************************************************************/
/***** 1/2 v 1/2  *******************************************************************************/
/************************************************************************************************/
char char_wptt_ppbm2bbm2bpp [] = "i(([-2][-2]))";



char char_pl_ppbm2bbm2bpp [] = "0.000000,6.000000,0.000000\n"
                               "1.000000,5.000000,1.000000\n"
                               "2.000000,4.000000,0.000000\n"
                               "3.000000,5.000000,-1.000000\n"
                               "4.000000,6.000000,0.000000\n"
                               "\n"
                               "0.000000,0.000000,0.000000\n"
                               "1.000000,1.000000,-1.000000\n"
                               "2.000000,2.000000,0.000000\n"
                               "3.000000,1.000000,1.000000\n"
                               "4.000000,0.000000,0.000000\n"
                               "\n"
                               "0.000000,2.000000,0.000000\n"
                               "1.000000,1.000000,1.000000\n"
                               "2.000000,0.000000,0.000000\n"
                               "3.000000,1.000000,-1.000000\n"
                               "4.000000,2.000000,0.000000\n"
                               "4.000000,4.000000,0.000000\n"
                               "3.000000,5.000000,1.000000\n"
                               "2.000000,6.000000,0.000000\n"
                               "1.000000,5.000000,-1.000000\n"
                               "0.000000,4.000000,0.000000\n"
                               "0.000000,2.000000,0.000000";

note_plpath_point_t point_ppbm2bbm2bpp    [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 1  },
    { .x = 1.0, .y = 5.0, .z =  1.0, .next_point = point_ppbm2bbm2bpp + 2  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 3  },
    { .x = 3.0, .y = 5.0, .z = -1.0, .next_point = point_ppbm2bbm2bpp + 4  },
    { .x = 4.0, .y = 6.0, .z =  0.0, .next_point = NULL                    },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 6  },
    { .x = 1.0, .y = 1.0, .z = -1.0, .next_point = point_ppbm2bbm2bpp + 7  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 8  },
    { .x = 3.0, .y = 1.0, .z =  1.0, .next_point = point_ppbm2bbm2bpp + 9  },
    { .x = 4.0, .y = 0.0, .z =  0.0, .next_point = NULL                    },

    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 11 },
    { .x = 1.0, .y = 1.0, .z =  1.0, .next_point = point_ppbm2bbm2bpp + 12 },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 13 },
    { .x = 3.0, .y = 1.0, .z = -1.0, .next_point = point_ppbm2bbm2bpp + 14 },
    { .x = 4.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 15 },
    { .x = 4.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 16 },
    { .x = 3.0, .y = 5.0, .z =  1.0, .next_point = point_ppbm2bbm2bpp + 17 },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 18 },
    { .x = 1.0, .y = 5.0, .z = -1.0, .next_point = point_ppbm2bbm2bpp + 19 },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm2bbm2bpp + 20 },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = NULL                    },
};



note_plpath_segment_t segs_ppbm2bbm2bpp  [] = {
    { .head = point_ppbm2bbm2bpp,      .next_seg = segs_ppbm2bbm2bpp + 1 },
    { .head = point_ppbm2bbm2bpp + 5,  .next_seg = segs_ppbm2bbm2bpp + 2 },
    { .head = point_ppbm2bbm2bpp + 10, .next_seg = NULL                  },
};

note_wptt_node_t ppbm2bbm2bpp = { { &pbm2bbm2bp }, { 0, 0, 0 }, 1, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm2bbm2bpp = { &ppbm2bbm2bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm2bbm2bpp = { .itt_string     = char_wptt_ppbm2bbm2bpp,
                                      .pl_path_string = char_pl_ppbm2bbm2bpp,
                                      .path           = { .segments = segs_ppbm2bbm2bpp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_ppbm2bbm2bpp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 v X     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 v 1   ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0_0bbm1bpp [] = "i(([0 0][-1]))";

char char_pl_ppb0_0bbm1bpp      [] = "0.000000,6.000000,0.000000\n"
                                     "0.500000,5.000000,0.000000\n"
                                     "0.000000,4.000000,0.000000\n"
                                     "0.000000,2.000000,0.000000\n"
                                     "1.000000,1.000000,1.000000\n"
                                     "2.000000,0.000000,0.000000\n"
                                     "\n"
                                     "0.000000,0.000000,0.000000\n"
                                     "1.000000,1.000000,-1.000000\n"
                                     "2.000000,2.000000,0.000000\n"
                                     "2.000000,4.000000,0.000000\n"
                                     "1.500000,5.000000,0.000000\n"
                                     "2.000000,6.000000,0.000000";

note_plpath_point_t   point_ppb0_0bbm1bpp       [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 1  },
    { .x = 0.5, .y = 5.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 2  },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 3  },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 4  },
    { .x = 1.0, .y = 1.0, .z =  1.0, .next_point = point_ppb0_0bbm1bpp + 5  },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 7  },
    { .x = 1.0, .y = 1.0, .z = -1.0, .next_point = point_ppb0_0bbm1bpp + 8  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 9  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 10 },
    { .x = 1.5, .y = 5.0, .z =  0.0, .next_point = point_ppb0_0bbm1bpp + 11 },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = NULL                     },
};
note_plpath_segment_t segs_ppb0_0bbm1bpp    [] = {
    { .head = point_ppb0_0bbm1bpp,     .next_seg = segs_ppb0_0bbm1bpp + 1 },
    { .head = point_ppb0_0bbm1bpp + 6, .next_seg = NULL                   },
};

note_wptt_node_t ppb0_0bbm1bpp = { { &pb0_0bbm1bp }, { 0, 0, 0 }, 1, 0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0_0bbm1bpp = { &ppb0_0bbm1bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0_0bbm1bpp = { .itt_string     = char_wptt_ppb0_0bbm1bpp,
                                       .pl_path_string = char_pl_ppb0_0bbm1bpp,
                                       .path           = { .segments = segs_ppb0_0bbm1bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppb0_0bbm1bpp,
                                           .out_path      = &outpath
                                       } };

/************************************************************************************************/
/***** 2 v 3  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb2_0bb3_0bpp [] = "i(([2 0][3 0]))";


char char_pl_ppb2_0bb3_0bpp [] = "0.000000,12.000000,0.000000\n"
                                 "1.000000,11.000000,-1.000000\n"
                                 "2.000000,10.000000,0.000000\n"
                                 "1.000000,9.000000,1.000000\n"
                                 "0.000000,8.000000,0.000000\n"
                                 "0.000000,6.000000,0.000000\n"
                                 "1.000000,5.000000,-1.000000\n"
                                 "2.000000,4.000000,0.000000\n"
                                 "1.000000,3.000000,1.000000\n"
                                 "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,-1.000000\n"
                                 "2.000000,0.000000,0.000000\n"
                                 "\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "1.000000,1.000000,1.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "1.000000,3.000000,-1.000000\n"
                                 "0.000000,4.000000,0.000000\n"
                                 "1.000000,5.000000,1.000000\n"
                                 "2.000000,6.000000,0.000000\n"
                                 "2.000000,8.000000,0.000000\n"
                                 "1.000000,9.000000,-1.000000\n"
                                 "0.000000,10.000000,0.000000\n"
                                 "1.000000,11.000000,1.000000\n"
                                 "2.000000,12.000000,0.000000";

note_plpath_point_t point_ppb2_0bb3_0bpp [] = {
    { .x = 0.0, .y = 12.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 1  },
    { .x = 1.0, .y = 11.0, .z = -1.0, .next_point = point_ppb2_0bb3_0bpp + 2  },
    { .x = 2.0, .y = 10.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 3  },
    { .x = 1.0, .y =  9.0, .z =  1.0, .next_point = point_ppb2_0bb3_0bpp + 4  },
    { .x = 0.0, .y =  8.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 5  },
    { .x = 0.0, .y =  6.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 6  },
    { .x = 1.0, .y =  5.0, .z = -1.0, .next_point = point_ppb2_0bb3_0bpp + 7  },
    { .x = 2.0, .y =  4.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 8  },
    { .x = 1.0, .y =  3.0, .z =  1.0, .next_point = point_ppb2_0bb3_0bpp + 9  },
    { .x = 0.0, .y =  2.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 10 },
    { .x = 1.0, .y =  1.0, .z = -1.0, .next_point = point_ppb2_0bb3_0bpp + 11 },
    { .x = 2.0, .y =  0.0, .z =  0.0, .next_point = NULL                      },

    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 13 },
    { .x = 1.0, .y =  1.0, .z =  1.0, .next_point = point_ppb2_0bb3_0bpp + 14 },
    { .x = 2.0, .y =  2.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 15 },
    { .x = 1.0, .y =  3.0, .z = -1.0, .next_point = point_ppb2_0bb3_0bpp + 16 },
    { .x = 0.0, .y =  4.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 17 },
    { .x = 1.0, .y =  5.0, .z =  1.0, .next_point = point_ppb2_0bb3_0bpp + 18 },
    { .x = 2.0, .y =  6.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 19 },
    { .x = 2.0, .y =  8.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 20 },
    { .x = 1.0, .y =  9.0, .z = -1.0, .next_point = point_ppb2_0bb3_0bpp + 21 },
    { .x = 0.0, .y = 10.0, .z =  0.0, .next_point = point_ppb2_0bb3_0bpp + 22 },
    { .x = 1.0, .y = 11.0, .z =  1.0, .next_point = point_ppb2_0bb3_0bpp + 23 },
    { .x = 2.0, .y = 12.0, .z =  0.0, .next_point = NULL                      },
};


note_plpath_segment_t segs_ppb2_0bb3_0bpp  [] = {
    { .head = point_ppb2_0bb3_0bpp,      .next_seg = segs_ppb2_0bb3_0bpp + 1 },
    { .head = point_ppb2_0bb3_0bpp + 12, .next_seg = NULL                    },
};

note_wptt_node_t ppb2_0bb3_0bpp = { { &pb2_0bb3_0bp }, { 0, 0, 0 }, 1, 0,
                                    NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb2_0bb3_0bpp = { &ppb2_0bb3_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb2_0bb3_0bpp = { .itt_string     = char_wptt_ppb2_0bb3_0bpp,
                                        .pl_path_string = char_pl_ppb2_0bb3_0bpp,
                                        .path           = { .segments = segs_ppb2_0bb3_0bpp,
                                                            .pnt_buff = NULL,
                                                            .seg_buff = NULL },
                                        .cfg                = {
                                            .storage_write = &test_stub_write_success,
                                            .itt           = &wptt_ppb2_0bb3_0bpp,
                                            .out_path      = &outpath
                                        } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 v 0     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 v 0     ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0_0bb0_0bpp [] = "i(([0 0][0 0]))";

char char_pl_ppb0_0bb0_0bpp   [] = "0.000000,6.000000,0.000000\n"
                                   "0.500000,5.000000,0.000000\n"
                                   "0.000000,4.000000,0.000000\n"
                                   "0.000000,2.000000,0.000000\n"
                                   "0.500000,1.000000,0.000000\n"
                                   "0.000000,0.000000,0.000000\n"
                                   "0.000000,0.000000,0.000000\n"
                                   "\n"
                                   "2.000000,6.000000,0.000000\n"
                                   "1.500000,5.000000,0.000000\n"
                                   "2.000000,4.000000,0.000000\n"
                                   "2.000000,2.000000,0.000000\n"
                                   "1.500000,1.000000,0.000000\n"
                                   "2.000000,0.000000,0.000000";

note_plpath_point_t   point_ppb0_0bb0_0bpp    [] = {
    { .x = 0.0, .y = 6.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 1  },
    { .x = 0.5, .y = 5.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 2  },
    { .x = 0.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 3  },
    { .x = 0.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 4  },
    { .x = 0.5, .y = 1.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 5  },
    { .x = 0.0, .y = 0.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 6  },
    { .x = 0.0, .y = 0.0, .z = 0.0, .next_point = NULL                      },

    { .x = 2.0, .y = 6.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 8  },
    { .x = 1.5, .y = 5.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 9  },
    { .x = 2.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 10 },
    { .x = 2.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 11 },
    { .x = 1.5, .y = 1.0, .z = 0.0, .next_point = point_ppb0_0bb0_0bpp + 12 },
    { .x = 2.0, .y = 0.0, .z = 0.0, .next_point = NULL                      },
};
note_plpath_segment_t segs_ppb0_0bb0_0bpp     [] = {
    { .head = point_ppb0_0bb0_0bpp,     .next_seg = segs_ppb0_0bb0_0bpp + 1 },
    { .head = point_ppb0_0bb0_0bpp + 7, .next_seg = NULL                    },
};


note_wptt_node_t ppb0_0bb0_0bpp = { { &pb0_0bb0_0bp }, { 0, 0, 0 }, 1, 0,
                                    NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0_0bb0_0bpp = { &ppb0_0bb0_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0_0bb0_0bpp = { .itt_string     = char_wptt_ppb0_0bb0_0bpp,
                                        .pl_path_string = char_pl_ppb0_0bb0_0bpp,
                                        .path           = { .segments = segs_ppb0_0bb0_0bpp,
                                                            .pnt_buff = NULL,
                                                            .seg_buff = NULL },
                                        .cfg                = {
                                            .storage_write = &test_stub_write_success,
                                            .itt           = &wptt_ppb0_0bb0_0bpp,
                                            .out_path      = &outpath
                                        } };

/************************************************************************************************/
/***** 2 v 2  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb2_0bb2_0bpp [] = "i(([2 0][2 0]))";

char char_pl_ppb2_0bb2_0bpp   [] = "0.000000,10.000000,0.000000\n"
                                   "1.000000,9.000000,-1.000000\n"
                                   "2.000000,8.000000,0.000000\n"
                                   "1.000000,7.000000,1.000000\n"
                                   "0.000000,6.000000,0.000000\n"
                                   "0.000000,4.000000,0.000000\n"
                                   "1.000000,3.000000,-1.000000\n"
                                   "2.000000,2.000000,0.000000\n"
                                   "1.000000,1.000000,1.000000\n"
                                   "0.000000,0.000000,0.000000\n"
                                   "0.000000,0.000000,0.000000\n"
                                   "\n"
                                   "2.000000,10.000000,0.000000\n"
                                   "1.000000,9.000000,1.000000\n"
                                   "0.000000,8.000000,0.000000\n"
                                   "1.000000,7.000000,-1.000000\n"
                                   "2.000000,6.000000,0.000000\n"
                                   "2.000000,4.000000,0.000000\n"
                                   "1.000000,3.000000,1.000000\n"
                                   "0.000000,2.000000,0.000000\n"
                                   "1.000000,1.000000,-1.000000\n"
                                   "2.000000,0.000000,0.000000";

note_plpath_point_t   point_ppb2_0bb2_0bpp    [] = {
    { .x = 0.0, .y = 10.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 1  },
    { .x = 1.0, .y =  9.0, .z = -1.0, .next_point = point_ppb2_0bb2_0bpp + 2  },
    { .x = 2.0, .y =  8.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 3  },
    { .x = 1.0, .y =  7.0, .z =  1.0, .next_point = point_ppb2_0bb2_0bpp + 4  },
    { .x = 0.0, .y =  6.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 5  },
    { .x = 0.0, .y =  4.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 6  },
    { .x = 1.0, .y =  3.0, .z = -1.0, .next_point = point_ppb2_0bb2_0bpp + 7  },
    { .x = 2.0, .y =  2.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 8  },
    { .x = 1.0, .y =  1.0, .z =  1.0, .next_point = point_ppb2_0bb2_0bpp + 9  },
    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 10 },
    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = NULL                      },

    { .x = 2.0, .y = 10.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 12 },
    { .x = 1.0, .y =  9.0, .z =  1.0, .next_point = point_ppb2_0bb2_0bpp + 13 },
    { .x = 0.0, .y =  8.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 14 },
    { .x = 1.0, .y =  7.0, .z = -1.0, .next_point = point_ppb2_0bb2_0bpp + 15 },
    { .x = 2.0, .y =  6.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 16 },
    { .x = 2.0, .y =  4.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 17 },
    { .x = 1.0, .y =  3.0, .z =  1.0, .next_point = point_ppb2_0bb2_0bpp + 18 },
    { .x = 0.0, .y =  2.0, .z =  0.0, .next_point = point_ppb2_0bb2_0bpp + 19 },
    { .x = 1.0, .y =  1.0, .z = -1.0, .next_point = point_ppb2_0bb2_0bpp + 20 },
    { .x = 2.0, .y =  0.0, .z =  0.0, .next_point = NULL                      },
};
note_plpath_segment_t segs_ppb2_0bb2_0bpp  [] = {
    { .head = point_ppb2_0bb2_0bpp,      .next_seg = segs_ppb2_0bb2_0bpp + 1 },
    { .head = point_ppb2_0bb2_0bpp + 11, .next_seg = NULL                    },
};

note_wptt_node_t ppb2_0bb2_0bpp = { { &pb2_0bb2_0bp }, { 0, 0, 0 },
                                    1, 0,
                                    NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb2_0bb2_0bpp = { &ppb2_0bb2_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb2_0bb2_0bpp = { .itt_string     = char_wptt_ppb2_0bb2_0bpp,
                                        .pl_path_string = char_pl_ppb2_0bb2_0bpp,
                                        .path           = { .segments = segs_ppb2_0bb2_0bpp,
                                                            .pnt_buff = NULL,
                                                            .seg_buff = NULL },
                                        .cfg                = {
                                            .storage_write = &test_stub_write_success,
                                            .itt           = &wptt_ppb2_0bb2_0bpp,
                                            .out_path      = &outpath
                                        } };

/************************************************************************************************/
/************************************************************************************************/
/* 0 v inf   ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 0 v inf   ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb0_0bb0bpp [] = "i(([0 0][0]))";

char char_pl_ppb0_0bb0bpp   [] = "0.000000,6.000000,0.000000\n"
                                 "0.500000,5.000000,0.000000\n"
                                 "0.000000,4.000000,0.000000\n"
                                 "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.500000,0.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "2.000000,4.000000,0.000000\n"
                                 "1.500000,5.000000,0.000000\n"
                                 "2.000000,6.000000,0.000000\n"
                                 "\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "1.000000,0.500000,0.000000\n"
                                 "2.000000,0.000000,0.000000";

note_plpath_point_t   point_ppb0_0bb0bpp    [] = {
    { .x = 0.0, .y = 6.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 1  },
    { .x = 0.5, .y = 5.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 2  },
    { .x = 0.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 3  },
    { .x = 0.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 4  },
    { .x = 1.0, .y = 1.5, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 5  },
    { .x = 2.0, .y = 2.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 6  },
    { .x = 2.0, .y = 4.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 7  },
    { .x = 1.5, .y = 5.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 8  },
    { .x = 2.0, .y = 6.0, .z = 0.0, .next_point = NULL                    },

    { .x = 0.0, .y = 0.0, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 10 },
    { .x = 1.0, .y = 0.5, .z = 0.0, .next_point = point_ppb0_0bb0bpp + 11 },
    { .x = 2.0, .y = 0.0, .z = 0.0, .next_point = NULL                    },
};
note_plpath_segment_t segs_ppb0_0bb0bpp      [] = {
    { .head = point_ppb0_0bb0bpp,     .next_seg = segs_ppb0_0bb0bpp + 1 },
    { .head = point_ppb0_0bb0bpp + 9, .next_seg = NULL                  },
};

note_wptt_node_t ppb0_0bb0bpp = { { &pb0_0bb0bp }, { 0, 0, 0 }, 1, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb0_0bb0bpp = { &ppb0_0bb0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb0_0bb0bpp = { .itt_string     = char_wptt_ppb0_0bb0bpp,
                                      .pl_path_string = char_pl_ppb0_0bb0bpp,
                                      .path           = { .segments = segs_ppb0_0bb0bpp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_ppb0_0bb0bpp,
                                          .out_path      = &outpath
                                      } };


/************************************************************************************************/
/***** 2 v 1/2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb2_0bbm2bpp [] = "i(([2 0][-2]))";

char char_pl_ppb2_0bbm2bpp   [] = "0.000000,8.000000,0.000000\n"
                                  "1.000000,8.000000,0.000000\n"
                                  "2.000000,7.000000,-1.000000\n"
                                  "3.000000,6.000000,0.000000\n"
                                  "2.000000,5.000000,1.000000\n"
                                  "1.000000,4.000000,0.000000\n"
                                  "0.000000,2.000000,0.000000\n"
                                  "1.000000,1.000000,1.000000\n"
                                  "2.000000,0.000000,0.000000\n"
                                  "3.000000,1.000000,-1.000000\n"
                                  "4.000000,2.000000,0.000000\n"
                                  "3.000000,4.000000,0.000000\n"
                                  "2.000000,5.000000,-1.000000\n"
                                  "1.000000,6.000000,0.000000\n"
                                  "2.000000,7.000000,1.000000\n"
                                  "3.000000,8.000000,0.000000\n"
                                  "4.000000,8.000000,0.000000\n"
                                  "\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "1.000000,1.000000,-1.000000\n"
                                  "2.000000,2.000000,0.000000\n"
                                  "3.000000,1.000000,1.000000\n"
                                  "4.000000,0.000000,0.000000";

note_plpath_point_t point_ppb2_0bbm2bpp    [] = {
    { .x = 0.0, .y = 8.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 1  },
    { .x = 1.0, .y = 8.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 2  },
    { .x = 2.0, .y = 7.0, .z = -1.0, .next_point = point_ppb2_0bbm2bpp + 3  },
    { .x = 3.0, .y = 6.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 4  },
    { .x = 2.0, .y = 5.0, .z =  1.0, .next_point = point_ppb2_0bbm2bpp + 5  },
    { .x = 1.0, .y = 4.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 6  },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 7  },
    { .x = 1.0, .y = 1.0, .z =  1.0, .next_point = point_ppb2_0bbm2bpp + 8  },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 9  },
    { .x = 3.0, .y = 1.0, .z = -1.0, .next_point = point_ppb2_0bbm2bpp + 10 },
    { .x = 4.0, .y = 2.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 11 },
    { .x = 3.0, .y = 4.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 12 },
    { .x = 2.0, .y = 5.0, .z = -1.0, .next_point = point_ppb2_0bbm2bpp + 13 },
    { .x = 1.0, .y = 6.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 14 },
    { .x = 2.0, .y = 7.0, .z =  1.0, .next_point = point_ppb2_0bbm2bpp + 15 },
    { .x = 3.0, .y = 8.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 16 },
    { .x = 4.0, .y = 8.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 18 },
    { .x = 1.0, .y = 1.0, .z = -1.0, .next_point = point_ppb2_0bbm2bpp + 19 },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppb2_0bbm2bpp + 20 },
    { .x = 3.0, .y = 1.0, .z =  1.0, .next_point = point_ppb2_0bbm2bpp + 21 },
    { .x = 4.0, .y = 0.0, .z =  0.0, .next_point = NULL                     },
};

note_plpath_segment_t segs_ppb2_0bbm2bpp  [] = {
    { .head = point_ppb2_0bbm2bpp,      .next_seg = segs_ppb2_0bbm2bpp + 1 },
    { .head = point_ppb2_0bbm2bpp + 17, .next_seg = NULL                   },
};

note_wptt_node_t ppb2_0bbm2bpp = { { &pb2_0bbm2bp }, { 0, 0, 0 }, 1, 0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb2_0bbm2bpp = { &ppb2_0bbm2bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb2_0bbm2bpp = { .itt_string     = char_wptt_ppb2_0bbm2bpp,
                                       .pl_path_string = char_pl_ppb2_0bbm2bpp,
                                       .path           = { .segments = segs_ppb2_0bbm2bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppb2_0bbm2bpp,
                                           .out_path      = &outpath
                                       } };

/************************************************************************************************/
/************************************************************************************************/
/* X v X     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 v 1     ********************************************************************************/
/************************************************************************************************/
char char_wptt_ppbm1bbm1bpp [] = "i(([-1][-1]))";


char char_pl_ppbm1bbm1bpp   [] = "0.000000,6.000000,0.000000\n"
                                 "1.000000,5.000000,1.000000\n"
                                 "2.000000,4.000000,0.000000\n"
                                 "2.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,-1.000000\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "0.000000,0.000000,0.000000\n"
                                 "\n"
                                 "2.000000,6.000000,0.000000\n"
                                 "1.000000,5.000000,-1.000000\n"
                                 "0.000000,4.000000,0.000000\n"
                                 "0.000000,2.000000,0.000000\n"
                                 "1.000000,1.000000,1.000000\n"
                                 "2.000000,0.000000,0.000000";

note_plpath_point_t point_ppbm1bbm1bpp    [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 1  },
    { .x = 1.0, .y = 5.0, .z =  1.0, .next_point = point_ppbm1bbm1bpp + 2  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 3  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 4  },
    { .x = 1.0, .y = 1.0, .z = -1.0, .next_point = point_ppbm1bbm1bpp + 5  },
    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 6  },
    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = NULL                    },

    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 8  },
    { .x = 1.0, .y = 5.0, .z = -1.0, .next_point = point_ppbm1bbm1bpp + 9  },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 10 },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bbm1bpp + 11 },
    { .x = 1.0, .y = 1.0, .z =  1.0, .next_point = point_ppbm1bbm1bpp + 12 },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = NULL                    },
};

note_plpath_segment_t segs_ppbm1bbm1bpp       [] = {
    { .head = point_ppbm1bbm1bpp,     .next_seg = segs_ppbm1bbm1bpp + 1 },
    { .head = point_ppbm1bbm1bpp + 7, .next_seg = NULL                  },
};

note_wptt_node_t ppbm1bbm1bpp = { { &pbm1bbm1bp }, { 0, 0, 0 }, 1, 0,
                                  NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm1bbm1bpp = { &ppbm1bbm1bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm1bbm1bpp = { .itt_string     = char_wptt_ppbm1bbm1bpp,
                                      .pl_path_string = char_pl_ppbm1bbm1bpp,
                                      .path           = { .segments = segs_ppbm1bbm1bpp,
                                                          .pnt_buff = NULL,
                                                          .seg_buff = NULL },
                                      .cfg                = {
                                          .storage_write = &test_stub_write_success,
                                          .itt           = &wptt_ppbm1bbm1bpp,
                                          .out_path      = &outpath
                                      } };

/************************************************************************************************/
/***** 3 v 1/3  *********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb3_0bbm3bpp [] = "i(([3 0][-3]))";


char char_pl_ppb3_0bbm3bpp   [] = "0.000000,10.000000,0.000000\n"
                                  "2.000000,10.000000,0.000000\n"
                                  "3.000000,9.000000,-1.000000\n"
                                  "4.000000,8.000000,0.000000\n"
                                  "3.000000,7.000000,1.000000\n"
                                  "2.000000,6.000000,0.000000\n"
                                  "3.000000,5.000000,-1.000000\n"
                                  "4.000000,4.000000,0.000000\n"
                                  "6.000000,2.000000,0.000000\n"
                                  "5.000000,1.000000,-1.000000\n"
                                  "4.000000,0.000000,0.000000\n"
                                  "3.000000,1.000000,1.000000\n"
                                  "2.000000,2.000000,0.000000\n"
                                  "1.000000,1.000000,-1.000000\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "\n"
                                  "6.000000,10.000000,0.000000\n"
                                  "4.000000,10.000000,0.000000\n"
                                  "3.000000,9.000000,1.000000\n"
                                  "2.000000,8.000000,0.000000\n"
                                  "3.000000,7.000000,-1.000000\n"
                                  "4.000000,6.000000,0.000000\n"
                                  "3.000000,5.000000,1.000000\n"
                                  "2.000000,4.000000,0.000000\n"
                                  "0.000000,2.000000,0.000000\n"
                                  "1.000000,1.000000,1.000000\n"
                                  "2.000000,0.000000,0.000000\n"
                                  "3.000000,1.000000,-1.000000\n"
                                  "4.000000,2.000000,0.000000\n"
                                  "5.000000,1.000000,1.000000\n"
                                  "6.000000,0.000000,0.000000";

note_plpath_point_t point_ppb3_0bbm3bpp    [] = {
    { .x = 0.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 1  },
    { .x = 2.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 2  },
    { .x = 3.0, .y =  9.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 3  },
    { .x = 4.0, .y =  8.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 4  },
    { .x = 3.0, .y =  7.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 5  },
    { .x = 2.0, .y =  6.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 6  },
    { .x = 3.0, .y =  5.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 7  },
    { .x = 4.0, .y =  4.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 8  },
    { .x = 6.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 9  },
    { .x = 5.0, .y =  1.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 10 },
    { .x = 4.0, .y =  0.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 11 },
    { .x = 3.0, .y =  1.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 12 },
    { .x = 2.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 13 },
    { .x = 1.0, .y =  1.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 14 },
    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 15 },
    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = NULL                     },

    { .x = 6.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 17 },
    { .x = 4.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 18 },
    { .x = 3.0, .y =  9.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 19 },
    { .x = 2.0, .y =  8.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 20 },
    { .x = 3.0, .y =  7.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 21 },
    { .x = 4.0, .y =  6.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 22 },
    { .x = 3.0, .y =  5.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 23 },
    { .x = 2.0, .y =  4.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 24 },
    { .x = 0.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 25 },
    { .x = 1.0, .y =  1.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 26 },
    { .x = 2.0, .y =  0.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 27 },
    { .x = 3.0, .y =  1.0, .z = -1.0, .next_point = point_ppb3_0bbm3bpp + 28 },
    { .x = 4.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bbm3bpp + 29 },
    { .x = 5.0, .y =  1.0, .z =  1.0, .next_point = point_ppb3_0bbm3bpp + 30 },
    { .x = 6.0, .y =  0.0, .z =  0.0, .next_point = NULL                     },
};

note_plpath_segment_t segs_ppb3_0bbm3bpp  [] = {
    { .head = point_ppb3_0bbm3bpp,      .next_seg = segs_ppb3_0bbm3bpp + 1 },
    { .head = point_ppb3_0bbm3bpp + 16, .next_seg = NULL                   },
};

note_wptt_node_t ppb3_0bbm3bpp = { { &pb3_0bbm3bp }, { 0, 0, 0 }, 1,
                                   0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb3_0bbm3bpp = { &ppb3_0bbm3bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb3_0bbm3bpp = { .itt_string     = char_wptt_ppb3_0bbm3bpp,
                                       .pl_path_string = char_pl_ppb3_0bbm3bpp,
                                       .path           = { .segments = segs_ppb3_0bbm3bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppb3_0bbm3bpp,
                                           .out_path      = &outpath
                                       } };

/************************************************************************************************/
/************************************************************************************************/
/* X v 0     ************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 v 0     ********************************************************************************/
/************************************************************************************************/

char char_wptt_ppbm1bb0_0bpp [] = "i(([-1][0 0]))";


char char_pl_ppbm1bb0_0bpp   [] = "0.000000,6.000000,0.000000\n"
                                  "1.000000,5.000000,1.000000\n"
                                  "2.000000,4.000000,0.000000\n"
                                  "2.000000,2.000000,0.000000\n"
                                  "1.500000,1.000000,0.000000\n"
                                  "2.000000,0.000000,0.000000\n"
                                  "\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "0.500000,1.000000,0.000000\n"
                                  "0.000000,2.000000,0.000000\n"
                                  "0.000000,4.000000,0.000000\n"
                                  "1.000000,5.000000,-1.000000\n"
                                  "2.000000,6.000000,0.000000";

note_plpath_point_t point_ppbm1bb0_0bpp    [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 1  },
    { .x = 1.0, .y = 5.0, .z =  1.0, .next_point = point_ppbm1bb0_0bpp + 2  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 3  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 4  },
    { .x = 1.5, .y = 1.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 5  },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 7  },
    { .x = 0.5, .y = 1.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 8  },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 9  },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bb0_0bpp + 10 },
    { .x = 1.0, .y = 5.0, .z = -1.0, .next_point = point_ppbm1bb0_0bpp + 11 },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = NULL                     },
};

note_plpath_segment_t segs_ppbm1bb0_0bpp        [] = {
    { .head = point_ppbm1bb0_0bpp,     .next_seg = segs_ppbm1bb0_0bpp + 1 },
    { .head = point_ppbm1bb0_0bpp + 6, .next_seg = NULL                   },
};


note_wptt_node_t ppbm1bb0_0bpp = { { &pbm1bb0_0bp }, { 0, 0, 0 }, 1, 0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm1bb0_0bpp = { &ppbm1bb0_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm1bb0_0bpp = { .itt_string     = char_wptt_ppbm1bb0_0bpp,
                                       .pl_path_string = char_pl_ppbm1bb0_0bpp,
                                       .path           = { .segments = segs_ppbm1bb0_0bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppbm1bb0_0bpp,
                                           .out_path      = &outpath
                                       } };
/************************************************************************************************/
/***** 3 v 2  ***********************************************************************************/
/************************************************************************************************/
char char_wptt_ppb3_0bb2_0bpp [] = "i(([3 0][2 0]))";

char char_pl_ppb3_0bb2_0bpp   [] = "0.000000,12.000000,0.000000\n"
                                   "1.000000,11.000000,-1.000000\n"
                                   "2.000000,10.000000,0.000000\n"
                                   "1.000000,9.000000,1.000000\n"
                                   "0.000000,8.000000,0.000000\n"
                                   "1.000000,7.000000,-1.000000\n"
                                   "2.000000,6.000000,0.000000\n"
                                   "2.000000,4.000000,0.000000\n"
                                   "1.000000,3.000000,1.000000\n"
                                   "0.000000,2.000000,0.000000\n"
                                   "1.000000,1.000000,-1.000000\n"
                                   "2.000000,0.000000,0.000000\n"
                                   "\n"
                                   "0.000000,0.000000,0.000000\n"
                                   "1.000000,1.000000,1.000000\n"
                                   "2.000000,2.000000,0.000000\n"
                                   "1.000000,3.000000,-1.000000\n"
                                   "0.000000,4.000000,0.000000\n"
                                   "0.000000,6.000000,0.000000\n"
                                   "1.000000,7.000000,1.000000\n"
                                   "2.000000,8.000000,0.000000\n"
                                   "1.000000,9.000000,-1.000000\n"
                                   "0.000000,10.000000,0.000000\n"
                                   "1.000000,11.000000,1.000000\n"
                                   "2.000000,12.000000,0.000000";

note_plpath_point_t point_ppb3_0bb2_0bpp    [] = {
    { .x = 0.0, .y = 12.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 1  },
    { .x = 1.0, .y = 11.0, .z = -1.0, .next_point = point_ppb3_0bb2_0bpp + 2  },
    { .x = 2.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 3  },
    { .x = 1.0, .y =  9.0, .z =  1.0, .next_point = point_ppb3_0bb2_0bpp + 4  },
    { .x = 0.0, .y =  8.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 5  },
    { .x = 1.0, .y =  7.0, .z = -1.0, .next_point = point_ppb3_0bb2_0bpp + 6  },
    { .x = 2.0, .y =  6.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 7  },
    { .x = 2.0, .y =  4.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 8  },
    { .x = 1.0, .y =  3.0, .z =  1.0, .next_point = point_ppb3_0bb2_0bpp + 9  },
    { .x = 0.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 10 },
    { .x = 1.0, .y =  1.0, .z = -1.0, .next_point = point_ppb3_0bb2_0bpp + 11 },
    { .x = 2.0, .y =  0.0, .z =  0.0, .next_point = NULL                      },

    { .x = 0.0, .y =  0.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 13 },
    { .x = 1.0, .y =  1.0, .z =  1.0, .next_point = point_ppb3_0bb2_0bpp + 14 },
    { .x = 2.0, .y =  2.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 15 },
    { .x = 1.0, .y =  3.0, .z = -1.0, .next_point = point_ppb3_0bb2_0bpp + 16 },
    { .x = 0.0, .y =  4.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 17 },
    { .x = 0.0, .y =  6.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 18 },
    { .x = 1.0, .y =  7.0, .z =  1.0, .next_point = point_ppb3_0bb2_0bpp + 19 },
    { .x = 2.0, .y =  8.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 20 },
    { .x = 1.0, .y =  9.0, .z = -1.0, .next_point = point_ppb3_0bb2_0bpp + 21 },
    { .x = 0.0, .y = 10.0, .z =  0.0, .next_point = point_ppb3_0bb2_0bpp + 22 },
    { .x = 1.0, .y = 11.0, .z =  1.0, .next_point = point_ppb3_0bb2_0bpp + 23 },
    { .x = 2.0, .y = 12.0, .z =  0.0, .next_point = NULL                      },
};

note_plpath_segment_t segs_ppb3_0bb2_0bpp  [] = {
    { .head = point_ppb3_0bb2_0bpp,      .next_seg = segs_ppb3_0bb2_0bpp + 1 },
    { .head = point_ppb3_0bb2_0bpp + 12, .next_seg = NULL                    },
};

note_wptt_node_t ppb3_0bb2_0bpp = { { &pb3_0bb2_0bp }, { 0, 0, 0 },
                                    1, 0,
                                    NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppb3_0bb2_0bpp = { &ppb3_0bb2_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppb3_0bb2_0bpp = { .itt_string     = char_wptt_ppb3_0bb2_0bpp,
                                        .pl_path_string = char_pl_ppb3_0bb2_0bpp,
                                        .path           = { .segments = segs_ppb3_0bb2_0bpp,
                                                            .pnt_buff = NULL,
                                                            .seg_buff = NULL },
                                        .cfg                = {
                                            .storage_write = &test_stub_write_success,
                                            .itt           = &wptt_ppb3_0bb2_0bpp,
                                            .out_path      = &outpath
                                        } };

/************************************************************************************************/
/************************************************************************************************/
/* X v inf    ***********************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/************************************************************************************************/
/***** 1 v inf   ********************************************************************************/
/************************************************************************************************/

char char_wptt_ppbm1bb0bpp [] = "i(([-1][0]))";


char char_pl_ppbm1bb0bpp   [] = "0.000000,6.000000,0.000000\n"
                                "1.000000,5.000000,1.000000\n"
                                "2.000000,4.000000,0.000000\n"
                                "2.000000,2.000000,0.000000\n"
                                "1.000000,1.500000,0.000000\n"
                                "0.000000,2.000000,0.000000\n"
                                "0.000000,4.000000,0.000000\n"
                                "1.000000,5.000000,-1.000000\n"
                                "2.000000,6.000000,0.000000\n"
                                "\n"
                                "0.000000,0.000000,0.000000\n"
                                "1.000000,0.500000,0.000000\n"
                                "2.000000,0.000000,0.000000";

note_plpath_point_t point_ppbm1bb0bpp    [] = {
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 1  },
    { .x = 1.0, .y = 5.0, .z =  1.0, .next_point = point_ppbm1bb0bpp + 2  },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 3  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 4  },
    { .x = 1.0, .y = 1.5, .z =  0.0, .next_point = point_ppbm1bb0bpp + 5  },
    { .x = 0.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 6  },
    { .x = 0.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 7  },
    { .x = 1.0, .y = 5.0, .z = -1.0, .next_point = point_ppbm1bb0bpp + 8  },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = NULL                   },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm1bb0bpp + 10 },
    { .x = 1.0, .y = 0.5, .z =  0.0, .next_point = point_ppbm1bb0bpp + 11 },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = NULL                   },
};

note_plpath_segment_t segs_ppbm1bb0bpp [] = {
    { .head = point_ppbm1bb0bpp,     .next_seg = segs_ppbm1bb0bpp + 1 },
    { .head = point_ppbm1bb0bpp + 9, .next_seg = NULL                 },
};

note_wptt_node_t ppbm1bb0bpp = { { &pbm1bb0bp }, { 0, 0, 0 }, 1, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm1bb0bpp = { &ppbm1bb0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm1bb0bpp = { .itt_string     = char_wptt_ppbm1bb0bpp,
                                     .pl_path_string = char_pl_ppbm1bb0bpp,
                                     .path           = { .segments = segs_ppbm1bb0bpp,
                                                         .pnt_buff = NULL,
                                                         .seg_buff = NULL },
                                     .cfg                = {
                                         .storage_write = &test_stub_write_success,
                                         .itt           = &wptt_ppbm1bb0bpp,
                                         .out_path      = &outpath
                                     } };

/************************************************************************************************/
/***** 3 v 1/2  *********************************************************************************/
/************************************************************************************************/
char char_wptt_ppbm3bb2_0bpp [] = "i(([-3][2 0]))";


char char_pl_ppbm3bb2_0bpp   [] = "0.000000,8.000000,0.000000\n"
                                  "1.000000,7.000000,1.000000\n"
                                  "2.000000,6.000000,0.000000\n"
                                  "3.000000,7.000000,-1.000000\n"
                                  "4.000000,8.000000,0.000000\n"
                                  "5.000000,7.000000,1.000000\n"
                                  "6.000000,6.000000,0.000000\n"
                                  "4.000000,4.000000,0.000000\n"
                                  "3.000000,3.000000,1.000000\n"
                                  "2.000000,2.000000,0.000000\n"
                                  "3.000000,1.000000,-1.000000\n"
                                  "4.000000,0.000000,0.000000\n"
                                  "6.000000,0.000000,0.000000\n"
                                  "\n"
                                  "0.000000,0.000000,0.000000\n"
                                  "2.000000,0.000000,0.000000\n"
                                  "3.000000,1.000000,1.000000\n"
                                  "4.000000,2.000000,0.000000\n"
                                  "3.000000,3.000000,-1.000000\n"
                                  "2.000000,4.000000,0.000000\n"
                                  "0.000000,6.000000,0.000000\n"
                                  "1.000000,7.000000,-1.000000\n"
                                  "2.000000,8.000000,0.000000\n"
                                  "3.000000,7.000000,1.000000\n"
                                  "4.000000,6.000000,0.000000\n"
                                  "5.000000,7.000000,-1.000000\n"
                                  "6.000000,8.000000,0.000000";

note_plpath_point_t point_ppbm3bb2_0bpp    [] = {
    { .x = 0.0, .y = 8.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 1  },
    { .x = 1.0, .y = 7.0, .z =  1.0, .next_point = point_ppbm3bb2_0bpp + 2  },
    { .x = 2.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 3  },
    { .x = 3.0, .y = 7.0, .z = -1.0, .next_point = point_ppbm3bb2_0bpp + 4  },
    { .x = 4.0, .y = 8.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 5  },
    { .x = 5.0, .y = 7.0, .z =  1.0, .next_point = point_ppbm3bb2_0bpp + 6  },
    { .x = 6.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 7  },
    { .x = 4.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 8  },
    { .x = 3.0, .y = 3.0, .z =  1.0, .next_point = point_ppbm3bb2_0bpp + 9  },
    { .x = 2.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 10 },
    { .x = 3.0, .y = 1.0, .z = -1.0, .next_point = point_ppbm3bb2_0bpp + 11 },
    { .x = 4.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 12 },
    { .x = 6.0, .y = 0.0, .z =  0.0, .next_point = NULL                     },

    { .x = 0.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 14 },
    { .x = 2.0, .y = 0.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 15 },
    { .x = 3.0, .y = 1.0, .z =  1.0, .next_point = point_ppbm3bb2_0bpp + 16 },
    { .x = 4.0, .y = 2.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 17 },
    { .x = 3.0, .y = 3.0, .z = -1.0, .next_point = point_ppbm3bb2_0bpp + 18 },
    { .x = 2.0, .y = 4.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 19 },
    { .x = 0.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 20 },
    { .x = 1.0, .y = 7.0, .z = -1.0, .next_point = point_ppbm3bb2_0bpp + 21 },
    { .x = 2.0, .y = 8.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 22 },
    { .x = 3.0, .y = 7.0, .z =  1.0, .next_point = point_ppbm3bb2_0bpp + 23 },
    { .x = 4.0, .y = 6.0, .z =  0.0, .next_point = point_ppbm3bb2_0bpp + 24 },
    { .x = 5.0, .y = 7.0, .z = -1.0, .next_point = point_ppbm3bb2_0bpp + 25 },
    { .x = 6.0, .y = 8.0, .z =  0.0, .next_point = NULL                     },
};

note_plpath_segment_t segs_ppbm3bb2_0bpp  [] = {
    { .head = point_ppbm3bb2_0bpp,      .next_seg = segs_ppbm3bb2_0bpp + 1 },
    { .head = point_ppbm3bb2_0bpp + 13, .next_seg = NULL                   },
};

note_wptt_node_t ppbm3bb2_0bpp = { { &pbm3bb2_0bp }, { 0, 0, 0 }, 1, 0,
                                   NOTE_WPTT_ORDER_FORWARD };
note_wptt_t      wptt_ppbm3bb2_0bpp = { &ppbm3bb2_0bpp, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t holder_ppbm3bb2_0bpp = { .itt_string     = char_wptt_ppbm3bb2_0bpp,
                                       .pl_path_string = char_pl_ppbm3bb2_0bpp,
                                       .path           = { .segments = segs_ppbm3bb2_0bpp,
                                                           .pnt_buff = NULL,
                                                           .seg_buff = NULL },
                                       .cfg                = {
                                           .storage_write = &test_stub_write_success,
                                           .itt           = &wptt_ppbm3bb2_0bpp,
                                           .out_path      = &outpath
                                       } };



/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

test_holder_t *compute_valid_set[] = {
    &holder_b0b,
    &holder_b0_0b,
    &holder_bm1b,
    &holder_b1b,

    &holder_ppb0bbm1bpp,
    &holder_ppbm2bb3_0bpp,
    &holder_ppb0bb0_0bpp,
    &holder_ppbm2bb2_0bpp,
    &holder_ppb0bb0bpp,
    &holder_ppbm2bbm2bpp,
    &holder_ppb0_0bbm1bpp,
    &holder_ppb2_0bb3_0bpp,
    &holder_ppb0_0bb0_0bpp,
    &holder_ppb2_0bb2_0bpp,
    &holder_ppb0_0bb0bpp,
    &holder_ppb2_0bbm2bpp,
    &holder_ppbm1bbm1bpp,
    &holder_ppb3_0bbm3bpp,
    &holder_ppbm1bb0_0bpp,
    &holder_ppb3_0bb2_0bpp,
    &holder_ppbm1bb0bpp,
    &holder_ppbm3bb2_0bpp,

    &holder_pbm2bb3_0bp,
    &holder_pbm2bb2_0bp,
    &holder_pbm2bbm2bp,
    &holder_pb2_0bb3_0bp,
    &holder_pb2_0bb2_0bp,
    &holder_pb2_0bbm2bp,
    &holder_pb3_0bbm3bp,
    &holder_pb3_0bb2_0bp,
    &holder_pbm3bb2_0bp,
    &holder_pb0bbm1bp,
    &holder_pb0bb0_0bp,
    &holder_pb0bb0bp,
    &holder_pb0_0bbm1bp,
    &holder_pb0_0bb0_0bp,
    &holder_pb0_0bb0bp,
    &holder_pbm1bbm1bp,
    &holder_pbm1bb0_0bp,
    &holder_pbm1bb0bp,
    NULL
};



STATIC_INLINE bool plpath_point_match(const note_plpath_point_t *pathA,
                                      const note_plpath_point_t *pathB)
{
    if (pathA->x != pathB->x)
    {
        return false;
    }
    if (pathA->y != pathB->y)
    {
        return false;
    }
    if (pathA->z != pathB->z)
    {
        return false;
    }
    if (((pathA->next_point == NULL) && (pathB->next_point != NULL)) ||
        ((pathA->next_point != NULL) && (pathB->next_point == NULL)))
    {
        return false;
    }

    return true;
}

STATIC_INLINE bool plpath_segement_match(const note_plpath_segment_t *segmentA,
                                         const note_plpath_segment_t *segmentB)
{
    note_plpath_point_t *pntA = segmentA->head;
    note_plpath_point_t *pntB = segmentB->head;

    while ((NULL != pntA) || (NULL != pntB))
    {
        if (false == plpath_point_match(pntA, pntB))
        {
            return false;
        }

        pntA = pntA->next_point;
        pntB = pntB->next_point;
    }
    return true;
}

bool plpath_match(const note_plpath_t *pathA, const note_plpath_t *pathB)
{
    note_plpath_segment_t *segA = pathA->segments;
    note_plpath_segment_t *segB = pathB->segments;

    while ((NULL != segA) && (NULL != segB))
    {
        if (false == plpath_segement_match(segA, segB))
        {
            return false;
        }

        segA = segA->next_seg;
        segB = segB->next_seg;
    }
    return true;
}

void clear_buffers(void)
{
    for (size_t i = 0; i < UTIL_BUFFER_SIZE; i++)
    {
        points[i].next_point = NULL;
        points[i].x          = 0;
        points[i].y          = 0;
        points[i].z          = 0;
    }
    pnt_buffer.idx = 0;

    for (size_t i = 0; i < UTIL_BUFFER_SIZE    ; i++)
    {
        segments[i].head     = NULL;
        segments[i].next_seg = NULL;
    }
    seg_buffer.idx = 0;
}

void print_to_file(note_plpath_t path)
{
    char outstr[1000000];

    memset(outstr, '\0', 1000000);

    uint8_t retval = note_plpath_encode(path, outstr, 1000000);

    TEST_ASSERT_EQUAL(COMP_DEFS_COMPUTE_SUCCESS, retval);


    /* Define the filename */
    const char *filename = "output.txt";

    /* Open the file for writing */
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the file %s\n", filename);
    }
    else
    {
        fprintf(file, "%s", outstr);

        /* Close the file */
        fclose(file);
    }
}
