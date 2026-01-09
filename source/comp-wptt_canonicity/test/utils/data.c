#include "data.h"
#include "notation_wptt.h"
/* clang-format off */
/************************************************************************************************/
/*  Base */
/************************************************************************************************/


note_wptt_node_t b3b  = { { NULL }, { -3, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm3b  = { { NULL }, { 3, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b2b  = { { NULL }, { 2, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm2b  = { { NULL }, { -2, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1b  = { { NULL }, { 1, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm1b  = { { NULL }, { -1, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0b  = { { NULL }, { 0, 0, 0 }, 0, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3_3b= { { &b3b }, { 0,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t p3b3b3p= { { &b3b }, { 3,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3_m3b= { { &b3b }, { 0,-3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0_0b= { { &b0b }, { 0, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1_m1b= { { &b1b }, { 0,1, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b1_3b= { { &b1b }, { 0,-3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t bm1_m3b= { { &bm1b }, { 0,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b0_3b= { { &b0b }, { 0,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3_0b= { { &b3b }, { 0,0, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t b3_0_3b= { { &b3_0b }, { 0,3, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t p3b3b3b3bp= { { &b3b, &b3b}, { 3, 3, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3bp3b3b3pp= { { &b3b, &p3b3b3p}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb2bb3bp= { { &b2b, &bm3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pbm2bb3bp= { { &bm2b, &bm3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bb3_3bb0bp= { { &b3_3b, &b3_3b,&b0b}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3b3b3_3bp= { { &b3_3b, &b3_3b}, { 0, 3, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bpp= { { &pb3_3b3b3_3bp}, { 0, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_m3b3b3_3bp= { { &b3_m3b, &b3_3b}, { 0, 3, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bp3p= { { &pb3_3b3b3_3bp}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bp2p= { { &pb3_3b3b3_3bp}, { 0, 2, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bpm2p= { { &pb3_3b3b3_3bp}, { 0, -2, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bp0p= { { &pb3_3b3b3_3bp}, { 0, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bpm3p= { { &pb3_3b3b3_3bp}, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bp1p= { { &pb3_3b3b3_3bp}, { 0, 1, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bpm1p= { { &pb3_3b3b3_3bp}, { 0, -1, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_m3b3b3_3bp3p= { { &pb3_m3b3b3_3bp}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp3pm3p= { { &ppb3_3b3b3_3bp3p}, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp3p3p= { { &ppb3_3b3b3_3bp3p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_m3b3b3_3bp3pm3p= { { &ppb3_m3b3b3_3bp3p}, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppb3_3b3b3_3bp3pppb3_3b3b3_3bp3p3pp= { { &pb3_3b3b3_3bp,&pppb3_3b3b3_3bp3p3p}, { 0, 3, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bb3_3bppb3_3b3b3_3bp1pp= { {&b3_3b,&b3_3b, &ppb3_3b3b3_3bp1p}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bb3_3bppb3_3b3b3_3bpm1pp= { {&b3_3b,&b3_3b, &ppb3_3b3b3_3bpm1p}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bppb3_3b3b3_3bp2pp = { {&b3_3b,&ppb3_3b3b3_3bp2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bppb3_3b3b3_3bpm2pp = { {&b3_3b,&ppb3_3b3b3_3bpm2p }, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pb3_3bb3_3bb1bp ={ { &b3_3b, &b3_3b,&b1b}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pb3_3bb3_3bbm1bp ={ { &b3_3b, &b3_3b,&bm1b}, { 0, 0, 0 }, 3, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t pppb3_3b3b3_3bp1p3p= { { &ppb3_3b3b3_3bp1p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bpm1p3p= { { &ppb3_3b3b3_3bpm1p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp1pm3p= { { &ppb3_3b3b3_3bp1p}, { 0, -3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp3p1p= { { &ppb3_3b3b3_3bpm3p}, { 0, 1, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp3pm1p= { { &ppb3_3b3b3_3bp3p}, { 0, -1, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp3p0p= { { &ppb3_3b3b3_3bp3p}, { 0, 0, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp0p3p= { { &ppb3_3b3b3_3bp0p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bpm3p1p= { { &ppb3_3b3b3_3bpm3p}, { 0, 1, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t pppb3_3b3b3_3bp0pb3_3bp= { { &ppb3_3b3b3_3bp0p,&b3_3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };

note_wptt_node_t ppppb3_3b3b3_3bp1pm3pb3_3bp = { { &pppb3_3b3b3_3bp1pm3p,&b3_3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppppb3_3b3b3_3bpm1p3pb3_3bp = { { &pppb3_3b3b3_3bpm1p3p,&b3_3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppppb3_3b3b3_3bp3pm1pb3_3bp = { { &pppb3_3b3b3_3bp3pm1p,&b3_3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppppb3_3b3b3_3bpm3p1pb3_3bp = { { &pppb3_3b3b3_3bpm3p1p,&b3_3b}, { 0, 0, 0 }, 2, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppppb3_3b3b3_3bp3p0p3p = { { &pppb3_3b3b3_3bp3p0p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };
note_wptt_node_t ppppb3_3b3b3_3bp0p3p3p = { { &pppb3_3b3b3_3bp0p3p}, { 0, 3, 0 }, 1, 0, NOTE_WPTT_ORDER_FORWARD };


/*good*/
note_wptt_t ib3_3b = {&b3_3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib3_0b = {&b3_0b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t xpb3_3b3b3_3bp = {&pb3_3b3b3_3bp,NULL,NOTE_WPTT_V4_LABEL_X};
note_wptt_t xppb3_3b3b3_3bpp= {&ppb3_3b3b3_3bpp,NULL,NOTE_WPTT_V4_LABEL_X};
note_wptt_t ipppb3_3b3b3_3bp3pm3p= {&pppb3_3b3b3_3bp3pm3p,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib3b= {&b3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib0b= {&b0b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib0_0b= {&b0_0b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib2b= {&b2b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ibm2b= {&bm2b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ib1b= {&b1b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ibm1b= {&bm1b,NULL,NOTE_WPTT_V4_LABEL_I};

/*Stick*/

/*S.A*/
note_wptt_t ib3_m3b = {&b3_m3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipppb3_m3b3b3_3bp3pm3p= {&pppb3_m3b3b3_3bp3pm3p,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipppb3_3b3b3_3bp3p3p= {&pppb3_3b3b3_3bp3p3p,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippb3_3b3b3_3bp3pppb3_3b3b3_3bp3p3pp= {&ppb3_3b3b3_3bp3pppb3_3b3b3_3bp3p3pp,NULL,NOTE_WPTT_V4_LABEL_I};

/*S.1*/

note_wptt_t ib1_3b = {&b1_3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ibm1_m3b = {&bm1_m3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bb3_3bppb3_3b3b3_3bp1pp= {&pb3_3bb3_3bppb3_3b3b3_3bp1pp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bb3_3bppb3_3b3b3_3bpm1pp= {&pb3_3bb3_3bppb3_3b3b3_3bpm1pp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bb3_3bb1bp= {&pb3_3bb3_3bb1bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bb3_3bbm1bp= {&pb3_3bb3_3bbm1bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bp1pm3pb3_3bp = {&ppppb3_3b3b3_3bp1pm3pb3_3bp ,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bpm1p3pb3_3bp = {&ppppb3_3b3b3_3bpm1p3pb3_3bp ,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bp3pm1pb3_3bp = {&ppppb3_3b3b3_3bp3pm1pb3_3bp ,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bpm3p1pb3_3bp = {&ppppb3_3b3b3_3bpm3p1pb3_3bp ,NULL,NOTE_WPTT_V4_LABEL_I};


/*S.0*/

note_wptt_t ib3_0_3b = {&b3_0_3b,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bb3_3bb0bp = {&pb3_3bb3_3bb0bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipppb3_3b3b3_3bp0pb3_3bp= {&pppb3_3b3b3_3bp0pb3_3bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bp3p0p3p= {&ppppb3_3b3b3_3bp3p0p3p,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ippppb3_3b3b3_3bp0p3p3p= {&ppppb3_3b3b3_3bp0p3p3p,NULL,NOTE_WPTT_V4_LABEL_I};

/*positivity*/
/*P.P*/

note_wptt_t ipbm2bb3bp = {&pbm2bb3bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bppb3_3b3b3_3bpm2pp = {&pb3_3bppb3_3b3b3_3bpm2pp,NULL,NOTE_WPTT_V4_LABEL_I};

/*P.N*/
note_wptt_t ipb2bb3bp = {&pb2bb3bp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3_3bppb3_3b3b3_3bp2pp = {&pb3_3bppb3_3b3b3_3bp2pp,NULL,NOTE_WPTT_V4_LABEL_I};

/* weight */
note_wptt_t ip3b3b3p = {&p3b3b3p,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ipb3bp3b3b3pp = {&pb3bp3b3b3pp,NULL,NOTE_WPTT_V4_LABEL_I};
note_wptt_t ip3b3b3b3bp= {&p3b3b3b3bp,NULL,NOTE_WPTT_V4_LABEL_I};

/* clang-format on */
