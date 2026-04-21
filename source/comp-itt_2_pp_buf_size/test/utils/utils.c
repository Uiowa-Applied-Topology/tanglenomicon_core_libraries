#include "utils.h"
#include "comp_i2pp_buf_size.h"
#include "test_storage_stubs.h"
note_wptt_node_t b3b    = { { NULL }, { 3 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b4b    = { { NULL }, { 4 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2b    = { { NULL }, { 2 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1b    = { { NULL }, { 1 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0b    = { { NULL }, { 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm1b   = { { NULL }, { -1 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm2b   = { { NULL }, { -2 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm3b   = { { NULL }, { -3 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3_0b  = { { &b3b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2_0b  = { { &b2b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1_0b  = { { &b1b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0_0b  = { { &b0b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm1_0b = { { &bm1b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm2_0b = { { &bm2b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm3_0b = { { &bm3b }, { 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };


note_wptt_node_t pb0bb0bp           = { { &b0b, &b0b }, { 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb0bb0bppb0bb0bpp = { { &pb0bb0bp, &pb0bb0bp }, { 0, 0 }, 2, 0,
                                        NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb3bb3b3p = { { &b3b, &b3b }, { 0, 0, 3 }, 2, 0,
                               NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3b3ppb3bb3b3p3p = { { &pb3bb3b3p, &pb3bb3b3p }, { 0, 0, 3 }, 2, 0,
                                           NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t p3b3b3b3b3p = { { &b3b, &b3b }, { 3, 3, 3 }, 2, 0,
                                 NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t p3p3b3b3b3b3p3p3b3b3b3b3p3p = { { &p3b3b3b3b3p, &p3b3b3b3b3p }, { 3, 3, 3 }, 2, 0,
                                                 NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb3b3p             = { { &b3b }, { 0, 3 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t p1b3b1b2b2pb3b3p4p = { { &b3b, &b2b, &pb3b3p }, { 1, 1, 2, 4 }, 3, 0,
                                        NOTE_WPTT_ORDER_FORWARD };


note_wptt_t wptt_b3b                   = { &b3b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b4b                   = { &b4b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_xb4b                  = { &b4b, NULL, NOTE_WPTT_V4_LABEL_X };
note_wptt_t wptt_b2b                   = { &b2b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b1b                   = { &b1b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b0b                   = { &b0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm1b                  = { &bm1b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm2b                  = { &bm2b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm3b                  = { &bm3b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b3_0b                 = { &b3_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b2_0b                 = { &b2_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b1_0b                 = { &b1_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b0_0b                 = { &b0_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm1_0b                = { &bm1_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm2_0b                = { &bm2_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm3_0b                = { &bm3_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_p1b3b1b2b2pb3b3p4p    = { &p1b3b1b2b2pb3b3p4p, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_ppb0bb0bppb0bb0bpp    = { &ppb0bb0bppb0bb0bpp, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_ppb3bb3b3ppb3bb3b3p3p = { &ppb3bb3b3ppb3bb3b3p3p, NULL,
                                           NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_p3p3b3b3b3b3p3p3b3b3b3b3p3p = { &p3p3b3b3b3b3p3p3b3b3b3b3p3p, NULL,
                                                 NOTE_WPTT_V4_LABEL_I };

test_holder_t compute_valid_set[] = {
    { "i[0]",
        10,
        { &test_stub_write_success,      &wptt_b0b,} },
    { "i[0 0]",
        20,
        { &test_stub_write_success,      &wptt_b0_0b,} },
    { "i[4]",
        22,
        { &test_stub_write_success,      &wptt_b4b,} },
    { "x[4]",
        22,
        { &test_stub_write_success,      &wptt_xb4b,} },
    { "i(([0][0])([0][0]))",
        82,
        { &test_stub_write_success,      &wptt_ppb0bb0bppb0bb0bpp,} },
    { "i(3(3[3]3[3]3)3(3[3]3[3]3)3)",
        222,
        { &test_stub_write_success,      &wptt_p3p3b3b3b3b3p3p3b3b3b3b3p3p,} },
    { "i(([3][3]3)([3][3]3)3)",
        150,
        { &test_stub_write_success,      &wptt_ppb3bb3b3ppb3bb3b3p3p,} },
    { NULL,
        0,
        { NULL,                          NULL } }
};
