/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mpcmoveCodeGeneration_rtwutil.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "mpcmoveCodeGeneration_rtwutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int numerator
 * Return Type  : int
 */
int div_nde_s32_floor(int numerator)
{
  int b_numerator;
  if ((numerator < 0) && (numerator % 21 != 0)) {
    b_numerator = -1;
  } else {
    b_numerator = 0;
  }
  return numerator / 21 + b_numerator;
}

/*
 * File trailer for mpcmoveCodeGeneration_rtwutil.c
 *
 * [EOF]
 */
