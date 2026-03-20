#include "utils.h"
#include "comp_wptt_vertex_parity.h"
#include "test_storage_stubs.h"
note_wptt_node_t b3b    = { { NULL }, { 3 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
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


note_wptt_node_t pb3b3p             = { { &b3b }, { 0, 3 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t p1b3b1b2b2pb3b3p4p = { { &b3b, &b2b, &pb3b3p }, { 1, 1, 2, 4 }, 3, 0,
                                        NOTE_WPTT_ORDER_FORWARD };


note_wptt_t wptt_b3b                = { &b3b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b2b                = { &b2b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b1b                = { &b1b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b0b                = { &b0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm1b               = { &bm1b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm2b               = { &bm2b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm3b               = { &bm3b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b3_0b              = { &b3_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b2_0b              = { &b2_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b1_0b              = { &b1_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_b0_0b              = { &b0_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm1_0b             = { &bm1_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm2_0b             = { &bm2_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_bm3_0b             = { &bm3_0b, NULL, NOTE_WPTT_V4_LABEL_I };
note_wptt_t wptt_p1b3b1b2b2pb3b3p4p = { &p1b3b1b2b2pb3b3p4p, NULL, NOTE_WPTT_V4_LABEL_I };

test_holder_t compute_valid_set[] = {
    { "i(1[3]1[2]2[-3 3]4)",
        "Inf",
        1,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, &wptt_p1b3b1b2b2pb3b3p4p, &p1b3b1b2b2pb3b3p4p } },
    { "i[3]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_b3b,                &b3b                } },
    { "i[2]",
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, &wptt_b2b,                &b2b                } },
    { "i[1]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_b1b,                &b1b                } },
    { "i[0]",
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, &wptt_b0b,                &b0b                } },
    { "i[-1]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_bm1b,               &bm1b               } },
    { "i[-2]",
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, &wptt_bm2b,               &bm2b               } },
    { "i[-3]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_bm3b,               &bm3b               } },
    { "i[-3 0]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_b3_0b,              &b3_0b              } },
    { "i[-2 0]",
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, &wptt_b2_0b,              &b2_0b              } },
    { "i[-1 0]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_b1_0b,              &b1_0b              } },
    { "i[0 0]",
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, &wptt_b0_0b,              &b0_0b              } },
    { "i[1 0]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_bm1_0b,             &bm1_0b             } },
    { "i[2 0]",
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, &wptt_bm2_0b,             &bm2_0b             } },
    { "i[3 0]",
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, &wptt_bm3_0b,             &bm3_0b             } },
    { NULL }
};
