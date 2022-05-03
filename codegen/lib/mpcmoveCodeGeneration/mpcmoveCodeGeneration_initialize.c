/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mpcmoveCodeGeneration_initialize.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "mpcmoveCodeGeneration_initialize.h"
#include "mpcmoveCodeGeneration_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcmoveCodeGeneration_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_mpcmoveCodeGeneration = true;
}

/*
 * File trailer for mpcmoveCodeGeneration_initialize.c
 *
 * [EOF]
 */
