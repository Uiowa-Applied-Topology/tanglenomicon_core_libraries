#include "data.h"
#include "notation_wptt.h"
/* clang-format off */
/************************************************************************************************/
/*  Base */
/************************************************************************************************/

note_wptt_node_t b3b  = { { NULL }, { 3, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm3b = { { NULL }, { -3, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2b  = { { NULL }, { 2, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm2b = { { NULL }, { -2, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb2bbm2bp = { { &b2b, &bm2b }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb2bb3bp  = { { &b2b, &b3b }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pbm2bb3bp = { { &bm2b, &b3b }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bb3bp = { { &b3b, &b3b }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb2bm3p   = { { &b2b }, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb2bm2p   = { { &b2b }, { 0, -2, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pbm2bm3p = { { &bm2b }, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb2bm3p3p  = { { &pb2bm3p }, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppbm2b3pm3p = { { &pbm2bb3bp }, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3bp2p = { { &pb3bb3bp }, { 0, 2, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3bpm2p = { { &pb3bb3bp }, { 0, -2, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3bb3bp3p = { { &pb3bb3bp }, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bppb3bb3bp2pp = { { &b3b, &ppb3bb3bp2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bppb3bb3bpm2pp = { { &b3b, &ppb3bb3bpm2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bppb3bb3bp3pp = { { &b3b, &ppb3bb3bp3p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3bb3bp2pppb3bb3bpm2pp = { { &ppb3bb3bp2p , &ppb3bb3bpm2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb2bb22bp = { { &b2b, &pb2bm2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
/* clang-format on */
