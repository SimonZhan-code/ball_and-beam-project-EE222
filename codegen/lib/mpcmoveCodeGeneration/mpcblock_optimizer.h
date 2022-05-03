/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mpcblock_optimizer.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

#ifndef MPCBLOCK_OPTIMIZER_H
#define MPCBLOCK_OPTIMIZER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void mpcblock_optimizer(const double rseq[80], const double x[6], double old_u,
                        const boolean_T iA[200], const double Mlim[200],
                        double Mx[1200], double Mu1[200], double Mv[8200],
                        const double utarget[40], double uoff, double H[441],
                        double Ac[4200], const double A[36], const double Bu[6],
                        const double Bv[6], const double C[12],
                        const double Dv[2], const int Mrows[200], double *u,
                        double *cost, double useq[41], double *status,
                        boolean_T iAout[200], double *slack);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for mpcblock_optimizer.h
 *
 * [EOF]
 */
