/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mpcmoveCodeGeneration_types.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

#ifndef MPCMOVECODEGENERATION_TYPES_H
#define MPCMOVECODEGENERATION_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct10_T
#define typedef_struct10_T
typedef struct {
  double A[25];
  double B[5];
  double C[10];
  double D[2];
  double X[5];
  double U;
  double Y[2];
  double DX[5];
} struct10_T;
#endif /* typedef_struct10_T */

#ifndef typedef_struct11_T
#define typedef_struct11_T
typedef struct {
  double Uopt[41];
  double Yopt[82];
  double Xopt[246];
  double Topt[41];
  double Slack;
  double Iterations;
  double Cost;
} struct11_T;
#endif /* typedef_struct11_T */

#ifndef typedef_struct4_T
#define typedef_struct4_T
typedef struct {
  double Plant[5];
  double Disturbance;
  double LastMove;
  double Covariance[36];
  boolean_T iA[200];
} struct4_T;
#endif /* typedef_struct4_T */

#ifndef typedef_struct6_T
#define typedef_struct6_T
typedef struct {
  double ym[2];
  double ref[80];
} struct6_T;
#endif /* typedef_struct6_T */

#ifndef typedef_struct5_T
#define typedef_struct5_T
typedef struct {
  struct6_T signals;
  struct10_T model;
} struct5_T;
#endif /* typedef_struct5_T */

#endif
/*
 * File trailer for mpcmoveCodeGeneration_types.h
 *
 * [EOF]
 */
