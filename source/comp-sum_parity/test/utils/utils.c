#include "utils.h"
#include "comp_sum_parity.h"
#include "test_storage_stubs.h"


/*
 * | $+$      | $0$      | $\chi$   | $\infty$ |
 * | -------- | -------- | -------- | -------- |
 * | $0$      | $0$      | $\chi$   | $\infty$ |
 * | $\chi$   | $\chi$   | $0$      | $\infty$ |
 * | $\infty$ | $\infty$ | $\infty$ | $\infty$ |
 **************************************************************************************************
 **************************************************************************************************
 * | $\vee$   | $0$ | $\chi$   | $\infty$ |
 * | -------- | --- | -------- | -------- |
 * | $0$      | $0$ | $0$      | $0$      |
 * | $\chi$   | $0$ | $\infty$ | $\chi$   |
 * | $\infty$ | $0$ | $\chi$   | $\infty$ |
 * */

test_holder_t compute_valid_set[] = {
/*** T1C1 ****************************************************************************************/
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "0+0", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, "0+c", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "0+i", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_PLUS }
    },
/*** T1C2 ****************************************************************************************/
    {
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, "c+0", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "c+c", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "c+i", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_PLUS }
    },
/*** T1C3 ****************************************************************************************/
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "i+0", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "i+c", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_PLUS }
    },
    {
        "Inf",
        1,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "i+i", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_PLUS }
    },
/*************************************************************************************************/
/*************************************************************************************************/
/*************************************************************************************************/
/*** T2C1 ****************************************************************************************/
    {
        "0",
        1,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "0v0", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "0vc", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "0vi", COMP_SUM_PARITY_PAR_ZERO, COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_VEE }
    },
/*** T2C2 ****************************************************************************************/
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "cv0", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "cvc", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, "cvi", COMP_SUM_PARITY_PAR_CHI,  COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_VEE }
    },
/*** T2C3 ****************************************************************************************/
    {
        "0",
        0,
        COMP_SUM_PARITY_PAR_ZERO,
        { &test_stub_write_success, "iv0", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_ZERO,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "X",
        0,
        COMP_SUM_PARITY_PAR_CHI,
        { &test_stub_write_success, "ivc", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_CHI,
          COMP_SUM_PARITY_OP_VEE }
    },
    {
        "Inf",
        0,
        COMP_SUM_PARITY_PAR_INF,
        { &test_stub_write_success, "ivi", COMP_SUM_PARITY_PAR_INF,  COMP_SUM_PARITY_PAR_INF,
          COMP_SUM_PARITY_OP_VEE }
    },

    { NULL }
};
