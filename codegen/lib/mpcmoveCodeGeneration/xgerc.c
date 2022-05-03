/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgerc.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "xgerc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                double alpha1
 *                int ix0
 *                const double y[21]
 *                double A[441]
 *                int ia0
 * Return Type  : void
 */
void xgerc(int m, int n, double alpha1, int ix0, const double y[21],
           double A[441], int ia0)
{
  double temp;
  int i;
  int ijA;
  int j;
  int jA;
  if (!(alpha1 == 0.0)) {
    jA = ia0;
    for (j = 0; j < n; j++) {
      temp = y[j];
      if (temp != 0.0) {
        temp *= alpha1;
        i = m + jA;
        for (ijA = jA; ijA < i; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }
      jA += 21;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
