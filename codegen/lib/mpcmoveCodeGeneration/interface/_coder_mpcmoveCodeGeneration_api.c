/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_mpcmoveCodeGeneration_api.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "_coder_mpcmoveCodeGeneration_api.h"
#include "_coder_mpcmoveCodeGeneration_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131626U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "mpcmoveCodeGeneration",                              /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[80]);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct4_T *y);

static const mxArray *b_emlrt_marshallOut(const struct4_T *u);

static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[5]);

static const mxArray *c_emlrt_marshallOut(const struct11_T *u);

static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[25]);

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId,
                                real_T ret[10]);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *statedata,
                             const char_T *identifier, struct4_T *y);

static const mxArray *emlrt_marshallOut(const real_T u);

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[36]);

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               boolean_T y[200]);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *onlinedata,
                               const char_T *identifier, struct5_T *y);

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct5_T *y);

static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct6_T *y);

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[2]);

static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[80]);

static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct10_T *y);

static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[25]);

static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[10]);

static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[5]);

static real_T u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId);

static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[36]);

static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               boolean_T ret[200]);

static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[2]);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[80]
 * Return Type  : void
 */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId, real_T ret[80])
{
  static const int32_T dims[2] = {40, 2};
  real_T(*r)[80];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[80])emlrtMxGetData(src);
  for (i = 0; i < 80; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct4_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct4_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[6] = {"Plant",    "Disturbance", "Noise",
                                        "LastMove", "Covariance",  "iA"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 6,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "Plant";
  c_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"Plant")),
                     &thisId, y->Plant);
  thisId.fIdentifier = "Disturbance";
  y->Disturbance = d_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                     (const char_T *)"Disturbance")),
      &thisId);
  thisId.fIdentifier = "Noise";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"Noise")),
                     &thisId);
  thisId.fIdentifier = "LastMove";
  y->LastMove = d_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                     (const char_T *)"LastMove")),
      &thisId);
  thisId.fIdentifier = "Covariance";
  f_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b(
                         (emlrtCTX)sp, u, 0, 4, (const char_T *)"Covariance")),
                     &thisId, y->Covariance);
  thisId.fIdentifier = "iA";
  g_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 5,
                                                    (const char_T *)"iA")),
                     &thisId, y->iA);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const struct4_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const struct4_T *u)
{
  static const int32_T iv[2] = {6, 6};
  static const int32_T i = 5;
  static const int32_T i1 = 0;
  static const int32_T i3 = 200;
  static const char_T *sv[6] = {"Plant",    "Disturbance", "Noise",
                                "LastMove", "Covariance",  "iA"};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i2;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&sv[0]));
  b_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (b_i = 0; b_i < 5; b_i++) {
    pData[b_i] = u->Plant[b_i];
  }
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Plant", b_y, 0);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Disturbance",
                      emlrt_marshallOut(u->Disturbance), 1);
  c_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i1, mxDOUBLE_CLASS, mxREAL);
  emlrtAssign(&c_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Noise", c_y, 2);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"LastMove",
                      emlrt_marshallOut(u->LastMove), 3);
  d_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i2 = 0;
  for (b_i = 0; b_i < 6; b_i++) {
    for (c_i = 0; c_i < 6; c_i++) {
      pData[i2 + c_i] = u->Covariance[c_i + 6 * b_i];
    }
    i2 += 6;
  }
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Covariance", d_y, 4);
  e_y = NULL;
  m = emlrtCreateLogicalArray(1, &i3);
  emlrtInitLogicalArray(200, m, &u->iA[0]);
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"iA", e_y, 5);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : void
 */
static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims[2] = {0, 2};
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[5]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[5])
{
  t_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const struct11_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const struct11_T *u)
{
  static const int32_T iv[2] = {41, 2};
  static const int32_T iv1[2] = {41, 6};
  static const int32_T i = 41;
  static const int32_T i2 = 41;
  static const char_T *sv[7] = {"Uopt",  "Yopt",       "Xopt", "Topt",
                                "Slack", "Iterations", "Cost"};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i1;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 7, (const char_T **)&sv[0]));
  b_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (b_i = 0; b_i < 41; b_i++) {
    pData[b_i] = u->Uopt[b_i];
  }
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Uopt", b_y, 0);
  c_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i1 = 0;
  for (b_i = 0; b_i < 2; b_i++) {
    for (c_i = 0; c_i < 41; c_i++) {
      pData[i1 + c_i] = u->Yopt[c_i + 41 * b_i];
    }
    i1 += 41;
  }
  emlrtAssign(&c_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Yopt", c_y, 1);
  d_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv1[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i1 = 0;
  for (b_i = 0; b_i < 6; b_i++) {
    for (c_i = 0; c_i < 41; c_i++) {
      pData[i1 + c_i] = u->Xopt[c_i + 41 * b_i];
    }
    i1 += 41;
  }
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Xopt", d_y, 2);
  e_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i2, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (b_i = 0; b_i < 41; b_i++) {
    pData[b_i] = u->Topt[b_i];
  }
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Topt", e_y, 3);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Slack",
                      emlrt_marshallOut(u->Slack), 4);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Iterations",
                      emlrt_marshallOut(u->Iterations), 5);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Cost", emlrt_marshallOut(u->Cost),
                      6);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[25]
 * Return Type  : void
 */
static void cb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId, real_T ret[25])
{
  static const int32_T dims[2] = {5, 5};
  real_T(*r)[25];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[25])emlrtMxGetData(src);
  for (i = 0; i < 25; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = u_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[10]
 * Return Type  : void
 */
static void db_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                const emlrtMsgIdentifier *msgId, real_T ret[10])
{
  static const int32_T dims[2] = {2, 5};
  real_T(*r)[10];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[10])emlrtMxGetData(src);
  for (i = 0; i < 10; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  v_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *statedata
 *                const char_T *identifier
 *                struct4_T *y
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *statedata,
                             const char_T *identifier, struct4_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(statedata), &thisId, y);
  emlrtDestroyArray(&statedata);
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[36]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[36])
{
  w_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                boolean_T y[200]
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               boolean_T y[200])
{
  x_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *onlinedata
 *                const char_T *identifier
 *                struct5_T *y
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *onlinedata,
                               const char_T *identifier, struct5_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  i_emlrt_marshallIn(sp, emlrtAlias(onlinedata), &thisId, y);
  emlrtDestroyArray(&onlinedata);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct5_T *y
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct5_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[5] = {"signals", "weights", "limits",
                                        "customconstraints", "model"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 5,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "signals";
  j_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"signals")),
                     &thisId, &y->signals);
  thisId.fIdentifier = "weights";
  m_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"weights")),
                     &thisId);
  thisId.fIdentifier = "limits";
  n_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"limits")),
                     &thisId);
  thisId.fIdentifier = "customconstraints";
  o_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                     (const char_T *)"customconstraints")),
      &thisId);
  thisId.fIdentifier = "model";
  q_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4,
                                                    (const char_T *)"model")),
                     &thisId, &y->model);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct6_T *y
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct6_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[5] = {"ym", "ref", "md", "mvTarget",
                                        "externalMV"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 5,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "ym";
  k_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"ym")),
                     &thisId, y->ym);
  thisId.fIdentifier = "ref";
  l_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"ref")),
                     &thisId, y->ref);
  thisId.fIdentifier = "md";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"md")),
                     &thisId);
  thisId.fIdentifier = "mvTarget";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b(
                         (emlrtCTX)sp, u, 0, 3, (const char_T *)"mvTarget")),
                     &thisId);
  thisId.fIdentifier = "externalMV";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b(
                         (emlrtCTX)sp, u, 0, 4, (const char_T *)"externalMV")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[2]
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[2])
{
  y_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[80]
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[80])
{
  ab_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[4] = {"y", "u", "du", "ecr"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 4,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "y";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"y")),
                     &thisId);
  thisId.fIdentifier = "u";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"u")),
                     &thisId);
  thisId.fIdentifier = "du";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"du")),
                     &thisId);
  thisId.fIdentifier = "ecr";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                    (const char_T *)"ecr")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[4] = {"ymin", "ymax", "umin", "umax"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 4,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "ymin";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"ymin")),
                     &thisId);
  thisId.fIdentifier = "ymax";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"ymax")),
                     &thisId);
  thisId.fIdentifier = "umin";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"umin")),
                     &thisId);
  thisId.fIdentifier = "umax";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                    (const char_T *)"umax")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[4] = {"E", "F", "G", "S"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 4,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "E";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"E")),
                     &thisId);
  thisId.fIdentifier = "F";
  p_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"F")),
                     &thisId);
  thisId.fIdentifier = "G";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"G")),
                     &thisId);
  thisId.fIdentifier = "S";
  e_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                    (const char_T *)"S")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  bb_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct10_T *y
 * Return Type  : void
 */
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct10_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[8] = {"A", "B", "C", "D",
                                        "X", "U", "Y", "DX"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 8,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "A";
  r_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"A")),
                     &thisId, y->A);
  thisId.fIdentifier = "B";
  c_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 1,
                                                    (const char_T *)"B")),
                     &thisId, y->B);
  thisId.fIdentifier = "C";
  s_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                                    (const char_T *)"C")),
                     &thisId, y->C);
  thisId.fIdentifier = "D";
  k_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                    (const char_T *)"D")),
                     &thisId, y->D);
  thisId.fIdentifier = "X";
  c_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4,
                                                    (const char_T *)"X")),
                     &thisId, y->X);
  thisId.fIdentifier = "U";
  y->U = d_emlrt_marshallIn(sp,
                            emlrtAlias(emlrtGetFieldR2017b(
                                (emlrtCTX)sp, u, 0, 5, (const char_T *)"U")),
                            &thisId);
  thisId.fIdentifier = "Y";
  k_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 6,
                                                    (const char_T *)"Y")),
                     &thisId, y->Y);
  thisId.fIdentifier = "DX";
  c_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 7,
                                                    (const char_T *)"DX")),
                     &thisId, y->DX);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[25]
 * Return Type  : void
 */
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[25])
{
  cb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[10]
 * Return Type  : void
 */
static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[10])
{
  db_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[5]
 * Return Type  : void
 */
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[5])
{
  static const int32_T dims = 5;
  real_T(*r)[5];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  r = (real_T(*)[5])emlrtMxGetData(src);
  for (i = 0; i < 5; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : void
 */
static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[36]
 * Return Type  : void
 */
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[36])
{
  static const int32_T dims[2] = {6, 6};
  real_T(*r)[36];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[36])emlrtMxGetData(src);
  for (i = 0; i < 36; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                boolean_T ret[200]
 * Return Type  : void
 */
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               boolean_T ret[200])
{
  static const int32_T dims = 200;
  int32_T i;
  boolean_T(*r)[200];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"logical",
                          false, 1U, (void *)&dims);
  r = (boolean_T(*)[200])emlrtMxGetLogicals(src);
  for (i = 0; i < 200; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[2]
 * Return Type  : void
 */
static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[2])
{
  static const int32_T dims = 2;
  real_T(*r)[2];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  r = (real_T(*)[2])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void mpcmoveCodeGeneration_api(const mxArray *const prhs[3], int32_T nlhs,
                               const mxArray *plhs[3])
{
  static const uint32_T uv[4] = {1472384012U, 1248574452U, 3743991634U,
                                 2880243185U};
  static const char_T *s = "configdata";
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  struct11_T Info;
  struct4_T statedata;
  struct5_T onlinedata;
  real_T u;
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  /* Check constant function inputs */
  i = 4;
  emlrtCheckArrayChecksumR2018b(&st, prhs[0], false, &i, (const char_T **)&s,
                                &uv[0]);
  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "statedata", &statedata);
  h_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "onlinedata", &onlinedata);
  /* Invoke the target function */
  mpcmoveCodeGeneration(&statedata, &onlinedata, &u, &Info);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(u);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(&statedata);
  }
  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(&Info);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcmoveCodeGeneration_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  mpcmoveCodeGeneration_xil_terminate();
  mpcmoveCodeGeneration_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcmoveCodeGeneration_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcmoveCodeGeneration_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_mpcmoveCodeGeneration_api.c
 *
 * [EOF]
 */
