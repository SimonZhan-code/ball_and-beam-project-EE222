/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_mpcmoveCodeGeneration_api.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

#ifndef _CODER_MPCMOVECODEGENERATION_API_H
#define _CODER_MPCMOVECODEGENERATION_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_struct10_T
#define typedef_struct10_T
typedef struct {
  real_T A[25];
  real_T B[5];
  real_T C[10];
  real_T D[2];
  real_T X[5];
  real_T U;
  real_T Y[2];
  real_T DX[5];
} struct10_T;
#endif /* typedef_struct10_T */

#ifndef typedef_struct11_T
#define typedef_struct11_T
typedef struct {
  real_T Uopt[41];
  real_T Yopt[82];
  real_T Xopt[246];
  real_T Topt[41];
  real_T Slack;
  real_T Iterations;
  real_T Cost;
} struct11_T;
#endif /* typedef_struct11_T */

#ifndef typedef_struct4_T
#define typedef_struct4_T
typedef struct {
  real_T Plant[5];
  real_T Disturbance;
  real_T LastMove;
  real_T Covariance[36];
  boolean_T iA[200];
} struct4_T;
#endif /* typedef_struct4_T */

#ifndef typedef_struct6_T
#define typedef_struct6_T
typedef struct {
  real_T ym[2];
  real_T ref[80];
} struct6_T;
#endif /* typedef_struct6_T */

#ifndef typedef_struct5_T
#define typedef_struct5_T
typedef struct {
  struct6_T signals;
  struct10_T model;
} struct5_T;
#endif /* typedef_struct5_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void mpcmoveCodeGeneration(struct4_T *statedata, struct5_T *onlinedata,
                           real_T *u, struct11_T *Info);

void mpcmoveCodeGeneration_api(const mxArray *const prhs[3], int32_T nlhs,
                               const mxArray *plhs[3]);

void mpcmoveCodeGeneration_atexit(void);

void mpcmoveCodeGeneration_initialize(void);

void mpcmoveCodeGeneration_terminate(void);

void mpcmoveCodeGeneration_xil_shutdown(void);

void mpcmoveCodeGeneration_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_mpcmoveCodeGeneration_api.h
 *
 * [EOF]
 */
