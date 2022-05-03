/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qpkwik.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

#ifndef QPKWIK_H
#define QPKWIK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void qpkwik(const double Linv[441], const double Hinv[441], const double f[21],
            const double Ac[4200], const double b[200], boolean_T iA[200],
            double x[21], double lambda[200], int *status);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for qpkwik.h
 *
 * [EOF]
 */
