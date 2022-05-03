/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mpcblock_optimizer.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "mpcblock_optimizer.h"
#include "minOrMax.h"
#include "qpkwik.h"
#include "rt_nonfinite.h"
#include "trisolve.h"
#include "xpotrf.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Arguments    : const double rseq[80]
 *                const double x[6]
 *                double old_u
 *                const boolean_T iA[200]
 *                const double Mlim[200]
 *                double Mx[1200]
 *                double Mu1[200]
 *                double Mv[8200]
 *                const double utarget[40]
 *                double uoff
 *                double H[441]
 *                double Ac[4200]
 *                const double A[36]
 *                const double Bu[6]
 *                const double Bv[6]
 *                const double C[12]
 *                const double Dv[2]
 *                const int Mrows[200]
 *                double *u
 *                double *cost
 *                double useq[41]
 *                double *status
 *                boolean_T iAout[200]
 *                double *slack
 * Return Type  : void
 */
void mpcblock_optimizer(const double rseq[80], const double x[6], double old_u,
                        const boolean_T iA[200], const double Mlim[200],
                        double Mx[1200], double Mu1[200], double Mv[8200],
                        const double utarget[40], double uoff, double H[441],
                        double Ac[4200], const double A[36], const double Bu[6],
                        const double Bv[6], const double C[12],
                        const double Dv[2], const int Mrows[200], double *u,
                        double *cost, double useq[41], double *status,
                        boolean_T iAout[200], double *slack)
{
  static const double dv[2] = {10000.0, 0.0001};
  static const signed char b_A[1600] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  static const signed char iv[800] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char iv1[800] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0};
  double Hv[3280];
  double Su[3200];
  double SuJm[1600];
  double WySuJm[1600];
  double Kv[820];
  double I2Jm[800];
  double b_WuI2Jm[800];
  double Sx[480];
  double L[441];
  double Linv[441];
  double b_Mlim[200];
  double b_Mv[200];
  double Kx[120];
  double b_CA[82];
  double Su1[80];
  double aux2[80];
  double aux3[40];
  double aux[21];
  double varargin_1[21];
  double b_Su1[20];
  double CA[12];
  double c_CA[12];
  double Sum[2];
  double b_C[2];
  double WuI2Jm;
  double b_Kv;
  double normH;
  double s;
  int Tries;
  int b_i;
  int i;
  int i1;
  int kidx;
  short WduJm[800];
  short ixw;
  signed char b[441];
  signed char rows[2];
  signed char c_i;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *cost = 0.0;
  memset(&iAout[0], 0, 200U * sizeof(boolean_T));
  *slack = 0.0;
  for (i = 0; i < 2; i++) {
    Sum[i] = 0.0;
    b_C[i] = 0.0;
    for (i1 = 0; i1 < 6; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 6; Tries++) {
        WuI2Jm += C[i + (Tries << 1)] * A[Tries + 6 * i1];
      }
      kidx = i + (i1 << 1);
      CA[kidx] = WuI2Jm;
      WuI2Jm = C[kidx];
      Sum[i] += WuI2Jm * Bu[i1];
      b_C[i] += WuI2Jm * Bv[i1];
    }
    Hv[i] = b_C[i];
    Hv[i + 80] = Dv[i];
  }
  for (i = 0; i < 39; i++) {
    kidx = 80 * (i + 2);
    Hv[kidx] = 0.0;
    Hv[kidx + 1] = 0.0;
  }
  for (i = 0; i < 41; i++) {
    memset(&Hv[i * 80 + 2], 0, 78U * sizeof(double));
  }
  for (i = 0; i < 6; i++) {
    kidx = i << 1;
    Sx[80 * i] = CA[kidx];
    Sx[80 * i + 1] = CA[kidx + 1];
    memset(&Sx[i * 80 + 2], 0, 78U * sizeof(double));
  }
  Su1[0] = Sum[0];
  Su1[1] = Sum[1];
  memset(&Su1[2], 0, 78U * sizeof(double));
  Su[0] = Sum[0];
  Su[1] = Sum[1];
  for (i = 0; i < 39; i++) {
    kidx = 80 * (i + 1);
    Su[kidx] = 0.0;
    Su[kidx + 1] = 0.0;
  }
  for (i = 0; i < 40; i++) {
    memset(&Su[i * 80 + 2], 0, 78U * sizeof(double));
  }
  for (b_i = 0; b_i < 39; b_i++) {
    c_i = (signed char)(((b_i + 1) << 1) + 1);
    for (i = 0; i < 2; i++) {
      rows[i] = (signed char)(i + c_i);
      WuI2Jm = 0.0;
      for (i1 = 0; i1 < 6; i1++) {
        WuI2Jm += CA[i + (i1 << 1)] * Bu[i1];
      }
      Sum[i] += WuI2Jm;
    }
    Su1[rows[0] - 1] = Sum[0];
    aux2[0] = Sum[0];
    Su1[rows[1] - 1] = Sum[1];
    aux2[1] = Sum[1];
    for (i = 0; i < 39; i++) {
      kidx = (i + 1) << 1;
      aux2[kidx] = Su[(rows[0] + 80 * i) - 3];
      aux2[kidx + 1] = Su[(rows[1] + 80 * i) - 3];
    }
    for (i = 0; i < 40; i++) {
      kidx = i << 1;
      Su[(rows[0] + 80 * i) - 1] = aux2[kidx];
      Su[(rows[1] + 80 * i) - 1] = aux2[kidx + 1];
    }
    for (i = 0; i < 2; i++) {
      WuI2Jm = 0.0;
      for (i1 = 0; i1 < 6; i1++) {
        WuI2Jm += CA[i + (i1 << 1)] * Bv[i1];
      }
      b_CA[i] = WuI2Jm;
    }
    for (i = 0; i < 40; i++) {
      kidx = (i + 1) << 1;
      b_CA[kidx] = Hv[(rows[0] + 80 * i) - 3];
      b_CA[kidx + 1] = Hv[(rows[1] + 80 * i) - 3];
    }
    for (i = 0; i < 41; i++) {
      kidx = i << 1;
      Hv[(rows[0] + 80 * i) - 1] = b_CA[kidx];
      Hv[(rows[1] + 80 * i) - 1] = b_CA[kidx + 1];
    }
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 6; i1++) {
        WuI2Jm = 0.0;
        for (Tries = 0; Tries < 6; Tries++) {
          WuI2Jm += CA[i + (Tries << 1)] * A[Tries + 6 * i1];
        }
        c_CA[i + (i1 << 1)] = WuI2Jm;
      }
    }
    memcpy(&CA[0], &c_CA[0], 12U * sizeof(double));
    for (i = 0; i < 6; i++) {
      kidx = i << 1;
      Sx[(rows[0] + 80 * i) - 1] = CA[kidx];
      Sx[(rows[1] + 80 * i) - 1] = CA[kidx + 1];
    }
  }
  for (i = 0; i < 80; i++) {
    for (i1 = 0; i1 < 20; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 40; Tries++) {
        WuI2Jm += Su[i + 80 * Tries] * (double)iv[Tries + 40 * i1];
      }
      SuJm[i + 80 * i1] = WuI2Jm;
    }
  }
  b_i = 0;
  exitg1 = false;
  while ((!exitg1) && (b_i < 200)) {
    if (Mrows[b_i] <= 80) {
      for (i = 0; i < 20; i++) {
        Ac[b_i + 200 * i] = -SuJm[(Mrows[b_i] + 80 * i) - 1];
      }
      for (i = 0; i < 6; i++) {
        Mx[b_i + 200 * i] = -Sx[(Mrows[b_i] + 80 * i) - 1];
      }
      Mu1[b_i] = -Su1[Mrows[b_i] - 1];
      for (i = 0; i < 41; i++) {
        Mv[b_i + 200 * i] = -Hv[(Mrows[b_i] + 80 * i) - 1];
      }
      b_i++;
    } else if (Mrows[b_i] <= 160) {
      kidx = Mrows[b_i];
      if (kidx < -2147483568) {
        kidx = MIN_int32_T;
      } else {
        kidx -= 80;
      }
      for (i = 0; i < 20; i++) {
        Ac[b_i + 200 * i] = SuJm[(kidx + 80 * i) - 1];
      }
      for (i = 0; i < 6; i++) {
        Mx[b_i + 200 * i] = Sx[(kidx + 80 * i) - 1];
      }
      Mu1[b_i] = Su1[kidx - 1];
      for (i = 0; i < 41; i++) {
        Mv[b_i + 200 * i] = Hv[(kidx + 80 * i) - 1];
      }
      b_i++;
    } else {
      exitg1 = true;
    }
  }
  kidx = -1;
  for (Tries = 0; Tries < 40; Tries++) {
    for (i1 = 0; i1 < 40; i1++) {
      WySuJm[(kidx + i1) + 1] = b_A[i1 + 40 * Tries];
    }
    kidx += 40;
  }
  for (i = 0; i < 40; i++) {
    for (i1 = 0; i1 < 20; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 40; Tries++) {
        WuI2Jm += WySuJm[i + 40 * Tries] * (double)iv[Tries + 40 * i1];
      }
      I2Jm[i + 40 * i1] = WuI2Jm;
    }
  }
  ixw = 1;
  for (b_i = 0; b_i < 80; b_i++) {
    for (i = 0; i < 20; i++) {
      kidx = b_i + 80 * i;
      WySuJm[kidx] = dv[ixw - 1] * SuJm[kidx];
    }
    ixw++;
    if (ixw > 2) {
      ixw = 1;
    }
  }
  for (b_i = 0; b_i < 40; b_i++) {
    for (i = 0; i < 20; i++) {
      kidx = b_i + 40 * i;
      b_WuI2Jm[kidx] = 25.0 * I2Jm[kidx];
      WduJm[kidx] = (short)(400 * iv[kidx]);
    }
  }
  for (i = 0; i < 20; i++) {
    for (i1 = 0; i1 < 20; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 80; Tries++) {
        WuI2Jm += SuJm[Tries + 80 * i] * WySuJm[Tries + 80 * i1];
      }
      s = 0.0;
      normH = 0.0;
      for (Tries = 0; Tries < 40; Tries++) {
        kidx = Tries + 40 * i1;
        normH += (double)(iv1[i + 20 * Tries] * WduJm[kidx]);
        s += I2Jm[Tries + 40 * i] * b_WuI2Jm[kidx];
      }
      H[i + 21 * i1] = (WuI2Jm + normH) + s;
    }
    WuI2Jm = 0.0;
    for (i1 = 0; i1 < 80; i1++) {
      WuI2Jm += Su1[i1] * WySuJm[i1 + 80 * i];
    }
    s = 0.0;
    for (i1 = 0; i1 < 40; i1++) {
      s += b_WuI2Jm[i1 + 40 * i];
    }
    b_Su1[i] = WuI2Jm + s;
  }
  for (i = 0; i < 800; i++) {
    b_WuI2Jm[i] = -b_WuI2Jm[i];
  }
  for (i = 0; i < 6; i++) {
    for (i1 = 0; i1 < 20; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 80; Tries++) {
        WuI2Jm += Sx[Tries + 80 * i] * WySuJm[Tries + 80 * i1];
      }
      Kx[i + 6 * i1] = WuI2Jm;
    }
  }
  for (i = 0; i < 41; i++) {
    for (i1 = 0; i1 < 20; i1++) {
      WuI2Jm = 0.0;
      for (Tries = 0; Tries < 80; Tries++) {
        WuI2Jm += Hv[Tries + 80 * i] * WySuJm[Tries + 80 * i1];
      }
      Kv[i + 41 * i1] = WuI2Jm;
    }
  }
  for (i = 0; i < 1600; i++) {
    WySuJm[i] = -WySuJm[i];
  }
  i1 = 0;
  for (i = 0; i < 441; i++) {
    WuI2Jm = H[i];
    Linv[i] = WuI2Jm;
    L[i] = WuI2Jm;
  }
  kidx = xpotrf(L);
  guard1 = false;
  if (kidx == 0) {
    for (kidx = 0; kidx < 21; kidx++) {
      varargin_1[kidx] = L[kidx + 21 * kidx];
    }
    if (!(minimum(varargin_1) > 1.4901161193847656E-7)) {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    normH = 0.0;
    b_i = 0;
    exitg2 = false;
    while ((!exitg2) && (b_i < 21)) {
      s = 0.0;
      for (Tries = 0; Tries < 21; Tries++) {
        s += fabs(H[b_i + 21 * Tries]);
      }
      if (rtIsNaN(s)) {
        normH = rtNaN;
        exitg2 = true;
      } else {
        if (s > normH) {
          normH = s;
        }
        b_i++;
      }
    }
    if (normH >= 1.0E+10) {
      i1 = 2;
    } else {
      Tries = 0;
      exitg1 = false;
      while ((!exitg1) && (Tries <= 4)) {
        normH = rt_powd_snf(10.0, Tries) * 1.4901161193847656E-7;
        memset(&b[0], 0, 441U * sizeof(signed char));
        for (kidx = 0; kidx < 21; kidx++) {
          b[kidx + 21 * kidx] = 1;
        }
        for (i = 0; i < 441; i++) {
          WuI2Jm = Linv[i] + normH * (double)b[i];
          Linv[i] = WuI2Jm;
          L[i] = WuI2Jm;
        }
        kidx = xpotrf(L);
        guard2 = false;
        if (kidx == 0) {
          for (kidx = 0; kidx < 21; kidx++) {
            varargin_1[kidx] = L[kidx + 21 * kidx];
          }
          if (minimum(varargin_1) > 1.4901161193847656E-7) {
            i1 = 1;
            exitg1 = true;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }
        if (guard2) {
          i1 = 3;
          Tries++;
        }
      }
    }
  }
  if (i1 > 1) {
    *u = old_u + uoff;
    for (b_i = 0; b_i < 41; b_i++) {
      useq[b_i] = *u;
    }
    *status = -2.0;
  } else {
    memset(&b[0], 0, 441U * sizeof(signed char));
    for (kidx = 0; kidx < 21; kidx++) {
      b[kidx + 21 * kidx] = 1;
    }
    for (Tries = 0; Tries < 21; Tries++) {
      for (b_i = 0; b_i < 21; b_i++) {
        kidx = b_i + 21 * Tries;
        Linv[kidx] = b[kidx];
      }
    }
    trisolve(L, Linv);
    memset(&varargin_1[0], 0, 21U * sizeof(double));
    for (b_i = 0; b_i < 20; b_i++) {
      normH = 0.0;
      for (i = 0; i < 6; i++) {
        normH += Kx[i + 6 * b_i] * x[i];
      }
      s = 0.0;
      for (i = 0; i < 80; i++) {
        s += WySuJm[i + 80 * b_i] * rseq[i];
      }
      b_Kv = 0.0;
      for (i = 0; i < 41; i++) {
        b_Kv += Kv[i + 41 * b_i];
      }
      WuI2Jm = 0.0;
      for (i = 0; i < 40; i++) {
        WuI2Jm += b_WuI2Jm[i + 40 * b_i] * utarget[i];
      }
      varargin_1[b_i] = (((normH + s) + b_Su1[b_i] * old_u) + b_Kv) + WuI2Jm;
    }
    for (b_i = 0; b_i < 200; b_i++) {
      iAout[b_i] = iA[b_i];
      WuI2Jm = 0.0;
      for (i = 0; i < 6; i++) {
        WuI2Jm += Mx[b_i + 200 * i] * x[i];
      }
      b_Mlim[b_i] = (Mlim[b_i] + WuI2Jm) + Mu1[b_i] * old_u;
      WuI2Jm = 0.0;
      for (i = 0; i < 41; i++) {
        WuI2Jm += Mv[b_i + 200 * i];
      }
      b_Mv[b_i] = WuI2Jm;
    }
    for (i = 0; i < 21; i++) {
      for (i1 = 0; i1 < 21; i1++) {
        WuI2Jm = 0.0;
        for (Tries = 0; Tries < 21; Tries++) {
          WuI2Jm += Linv[Tries + 21 * i] * Linv[Tries + 21 * i1];
        }
        L[i + 21 * i1] = WuI2Jm;
      }
    }
    for (i = 0; i < 200; i++) {
      b_Mlim[i] = -(b_Mlim[i] + b_Mv[i]);
    }
    qpkwik(Linv, L, varargin_1, Ac, b_Mlim, iAout, aux, b_Mv, &kidx);
    if ((kidx < 0) || (kidx == 0)) {
      memset(&aux[0], 0, 21U * sizeof(double));
    }
    *status = kidx;
    *slack = aux[20];
    *u = (old_u + aux[0]) + uoff;
    if (kidx > 0) {
      for (i = 0; i < 80; i++) {
        WuI2Jm = 0.0;
        for (i1 = 0; i1 < 6; i1++) {
          WuI2Jm += Sx[i + 80 * i1] * x[i1];
        }
        WuI2Jm += Su1[i] * old_u;
        s = 0.0;
        for (i1 = 0; i1 < 41; i1++) {
          s += Hv[i + 80 * i1];
        }
        Su1[i] = s;
        WuI2Jm = (WuI2Jm + s) - rseq[i];
        aux2[i] = WuI2Jm;
      }
      kidx = -1;
      for (i1 = 0; i1 < 40; i1++) {
        aux3[i1] = old_u - utarget[i1];
        Su1[kidx + 1] = 10000.0;
        Su1[kidx + 2] = 0.0001;
        kidx += 2;
      }
      normH = 0.0;
      for (i = 0; i < 40; i++) {
        WuI2Jm = aux3[i];
        normH += WuI2Jm * (25.0 * WuI2Jm);
      }
      s = 0.0;
      for (i = 0; i < 80; i++) {
        WuI2Jm = aux2[i];
        s += WuI2Jm * (Su1[i] * WuI2Jm);
      }
      b_Kv = 0.0;
      for (i = 0; i < 21; i++) {
        WuI2Jm = 0.0;
        for (i1 = 0; i1 < 21; i1++) {
          WuI2Jm += H[i + 21 * i1] * aux[i1];
        }
        b_Kv += aux[i] * (WuI2Jm + 2.0 * varargin_1[i]);
      }
      *cost = (normH + s) + b_Kv;
    }
    normH = old_u + uoff;
    for (i = 0; i < 40; i++) {
      WuI2Jm = 0.0;
      for (i1 = 0; i1 < 20; i1++) {
        WuI2Jm += I2Jm[i + 40 * i1] * aux[i1];
      }
      useq[i] = WuI2Jm + normH;
    }
    useq[40] = useq[39];
  }
}

/*
 * File trailer for mpcblock_optimizer.c
 *
 * [EOF]
 */
