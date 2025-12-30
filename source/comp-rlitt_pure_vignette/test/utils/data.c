#include "data.h"
#include "notation_wptt.h"
/* clang-format off */
/************************************************************************************************/
/*  Base */
/************************************************************************************************/

note_wptt_node_t b3b  = { { NULL }, { 3, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bm3p= { { &b3b }, { 0,-3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bm3p3p= { { &pb3bm3p }, {0, 3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3bm3p3pm3p= { { &ppb3bm3p3p }, {0, -3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb3bb3b3p= { { &b3b, &b3b }, {0,0, 3, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3b3ppb3bb3b3ppb3bb3b3pp= { { &pb3bb3b3p, &pb3bb3b3p,&pb3bb3b3p}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb3bb3bp= { { &b3b, &b3b }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3bpm3p= { { &pb3bb3bp}, { 0,-3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3bb3bpm3p3p= { { &ppb3bb3bpm3p}, { 0,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
/* clang-format on */
