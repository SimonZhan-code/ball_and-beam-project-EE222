/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: trisolve.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "trisolve.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double A[441]
 *                double B[441]
 * Return Type  : void
 */
void trisolve(const double A[441], double B[441])
{
  double d;
  int b_i;
  int i;
  int i1;
  int i2;
  int j;
  int jBcol;
  int k;
  int kAcol;
  for (j = 0; j < 21; j++) {
    jBcol = 21 * j - 1;
    for (k = 0; k < 21; k++) {
      kAcol = 21 * k - 1;
      i = (k + jBcol) + 1;
      d = B[i];
      if (d != 0.0) {
        B[i] = d / A[(k + kAcol) + 1];
        i1 = k + 2;
        for (b_i = i1; b_i < 22; b_i++) {
          i2 = b_i + jBcol;
          B[i2] -= B[i] * A[b_i + kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for trisolve.c
 *
 * [EOF]
 */
