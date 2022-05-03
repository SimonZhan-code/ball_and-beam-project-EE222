/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xpotrf.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "xpotrf.h"
#include "mpcmoveCodeGeneration_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double A[441]
 * Return Type  : int
 */
int xpotrf(double A[441])
{
  double c;
  double ssq;
  int i;
  int i1;
  int ia;
  int ia0;
  int iac;
  int idxAjj;
  int idxAjp1j;
  int info;
  int j;
  int k;
  boolean_T exitg1;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 21)) {
    idxAjj = j + j * 21;
    ssq = 0.0;
    if (j >= 1) {
      for (k = 0; k < j; k++) {
        c = A[j + k * 21];
        ssq += c * c;
      }
    }
    ssq = A[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      A[idxAjj] = ssq;
      if (j + 1 < 21) {
        ia0 = j + 2;
        idxAjp1j = idxAjj + 2;
        if (j != 0) {
          i = (j + 21 * (j - 1)) + 2;
          for (iac = ia0; iac <= i; iac += 21) {
            k = iac - j;
            c = -A[j + div_nde_s32_floor(k - 2) * 21];
            k += 19;
            for (ia = iac; ia <= k; ia++) {
              i1 = ((idxAjj + ia) - iac) + 1;
              A[i1] += A[ia - 1] * c;
            }
          }
        }
        ssq = 1.0 / ssq;
        i = (idxAjj - j) + 21;
        for (k = idxAjp1j; k <= i; k++) {
          A[k - 1] *= ssq;
        }
      }
      j++;
    } else {
      A[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }
  return info;
}

/*
 * File trailer for xpotrf.c
 *
 * [EOF]
 */
