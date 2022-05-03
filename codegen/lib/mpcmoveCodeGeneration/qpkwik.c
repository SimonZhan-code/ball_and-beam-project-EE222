/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qpkwik.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/* Include Files */
#include "qpkwik.h"
#include "mpcmoveCodeGeneration_rtwutil.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "xgerc.h"
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void DropConstraint(int kDrop, boolean_T iA[200], int *nA, int iC[200]);

static double KWIKfactor(const double Ac[4200], const int iC[200], int nA,
                         const double Linv[441], double RLinv[441],
                         double D[441], double H[441]);

static double rt_hypotd_snf(double u0, double u1);

static double rt_roundd_snf(double u);

/* Function Definitions */
/*
 * Arguments    : int kDrop
 *                boolean_T iA[200]
 *                int *nA
 *                int iC[200]
 * Return Type  : void
 */
static void DropConstraint(int kDrop, boolean_T iA[200], int *nA, int iC[200])
{
  int i;
  int q0;
  if (kDrop > 0) {
    iA[iC[kDrop - 1] - 1] = false;
    if (kDrop < *nA) {
      q0 = *nA;
      if (q0 < -2147483647) {
        q0 = MIN_int32_T;
      } else {
        q0--;
      }
      for (i = kDrop; i <= q0; i++) {
        iC[i - 1] = iC[i];
      }
    }
    iC[*nA - 1] = 0;
    q0 = *nA;
    if (q0 < -2147483647) {
      *nA = MIN_int32_T;
    } else {
      *nA = q0 - 1;
    }
  }
}

/*
 * Arguments    : const double Ac[4200]
 *                const int iC[200]
 *                int nA
 *                const double Linv[441]
 *                double RLinv[441]
 *                double D[441]
 *                double H[441]
 * Return Type  : double
 */
static double KWIKfactor(const double Ac[4200], const int iC[200], int nA,
                         const double Linv[441], double RLinv[441],
                         double D[441], double H[441])
{
  double Q[441];
  double R[441];
  double TL[441];
  double tau[21];
  double work[21];
  double Status;
  double atmp;
  double beta1;
  double c;
  double d;
  int b_i;
  int exitg1;
  int i;
  int i1;
  int ia;
  int iac;
  int ii;
  int ix0;
  int knt;
  int lastc;
  int lastv;
  boolean_T exitg2;
  Status = 1.0;
  memset(&RLinv[0], 0, 441U * sizeof(double));
  for (i = 0; i < nA; i++) {
    for (b_i = 0; b_i < 21; b_i++) {
      i1 = b_i + 21 * i;
      RLinv[i1] = 0.0;
      for (knt = 0; knt < 21; knt++) {
        RLinv[i1] += Linv[b_i + 21 * knt] * Ac[(iC[i] + 200 * knt) - 1];
      }
    }
  }
  memcpy(&TL[0], &RLinv[0], 441U * sizeof(double));
  memset(&tau[0], 0, 21U * sizeof(double));
  memset(&work[0], 0, 21U * sizeof(double));
  for (i = 0; i < 21; i++) {
    ii = i * 21 + i;
    if (i + 1 < 21) {
      atmp = TL[ii];
      ix0 = ii + 2;
      tau[i] = 0.0;
      c = xnrm2(20 - i, TL, ii + 2);
      if (c != 0.0) {
        d = TL[ii];
        beta1 = rt_hypotd_snf(d, c);
        if (d >= 0.0) {
          beta1 = -beta1;
        }
        if (fabs(beta1) < 1.0020841800044864E-292) {
          knt = 0;
          b_i = (ii - i) + 21;
          do {
            knt++;
            for (lastc = ix0; lastc <= b_i; lastc++) {
              TL[lastc - 1] *= 9.9792015476736E+291;
            }
            beta1 *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
          beta1 = rt_hypotd_snf(atmp, xnrm2(20 - i, TL, ii + 2));
          if (atmp >= 0.0) {
            beta1 = -beta1;
          }
          tau[i] = (beta1 - atmp) / beta1;
          c = 1.0 / (atmp - beta1);
          for (lastc = ix0; lastc <= b_i; lastc++) {
            TL[lastc - 1] *= c;
          }
          for (lastc = 0; lastc < knt; lastc++) {
            beta1 *= 1.0020841800044864E-292;
          }
          atmp = beta1;
        } else {
          tau[i] = (beta1 - d) / beta1;
          c = 1.0 / (d - beta1);
          b_i = (ii - i) + 21;
          for (lastc = ix0; lastc <= b_i; lastc++) {
            TL[lastc - 1] *= c;
          }
          atmp = beta1;
        }
      }
      TL[ii] = 1.0;
      if (tau[i] != 0.0) {
        lastv = 21 - i;
        knt = (ii - i) + 20;
        while ((lastv > 0) && (TL[knt] == 0.0)) {
          lastv--;
          knt--;
        }
        lastc = 20 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          knt = (ii + (lastc - 1) * 21) + 21;
          ia = knt;
          do {
            exitg1 = 0;
            if (ia + 1 <= knt + lastv) {
              if (TL[ia] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }
      if (lastv > 0) {
        ix0 = ii + 22;
        if (lastc != 0) {
          memset(&work[0], 0, lastc * sizeof(double));
          b_i = (ii + 21 * (lastc - 1)) + 22;
          for (iac = ix0; iac <= b_i; iac += 21) {
            c = 0.0;
            i1 = (iac + lastv) - 1;
            for (ia = iac; ia <= i1; ia++) {
              c += TL[ia - 1] * TL[(ii + ia) - iac];
            }
            knt = div_nde_s32_floor((iac - ii) - 22);
            work[knt] += c;
          }
        }
        xgerc(lastv, lastc, -tau[i], ii + 1, work, TL, ii + 22);
      }
      TL[ii] = atmp;
    } else {
      tau[20] = 0.0;
    }
  }
  for (ix0 = 0; ix0 < 21; ix0++) {
    for (i = 0; i <= ix0; i++) {
      knt = i + 21 * ix0;
      R[knt] = TL[knt];
    }
    b_i = ix0 + 2;
    if (b_i <= 21) {
      memset(&R[(ix0 * 21 + b_i) + -1], 0, (-b_i + 22) * sizeof(double));
    }
    work[ix0] = 0.0;
  }
  for (i = 20; i >= 0; i--) {
    ii = (i + i * 21) + 22;
    if (i + 1 < 21) {
      TL[ii - 22] = 1.0;
      if (tau[i] != 0.0) {
        lastv = 21 - i;
        knt = ii - i;
        while ((lastv > 0) && (TL[knt - 2] == 0.0)) {
          lastv--;
          knt--;
        }
        lastc = 20 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          knt = ii + (lastc - 1) * 21;
          ia = knt;
          do {
            exitg1 = 0;
            if (ia <= (knt + lastv) - 1) {
              if (TL[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }
      if (lastv > 0) {
        if (lastc != 0) {
          memset(&work[0], 0, lastc * sizeof(double));
          b_i = ii + 21 * (lastc - 1);
          for (iac = ii; iac <= b_i; iac += 21) {
            c = 0.0;
            i1 = (iac + lastv) - 1;
            for (ia = iac; ia <= i1; ia++) {
              c += TL[ia - 1] * TL[((ii + ia) - iac) - 22];
            }
            knt = div_nde_s32_floor(iac - ii);
            work[knt] += c;
          }
        }
        xgerc(lastv, lastc, -tau[i], ii - 21, work, TL, ii);
      }
      ix0 = ii - 20;
      b_i = (ii - i) - 1;
      for (lastc = ix0; lastc <= b_i; lastc++) {
        TL[lastc - 1] *= -tau[i];
      }
    }
    TL[ii - 22] = 1.0 - tau[i];
    for (ix0 = 0; ix0 < i; ix0++) {
      TL[(ii - ix0) - 23] = 0.0;
    }
  }
  for (ix0 = 0; ix0 < 21; ix0++) {
    memcpy(&Q[ix0 * 21], &TL[ix0 * 21], 21U * sizeof(double));
  }
  i = 0;
  do {
    exitg1 = 0;
    if (i <= nA - 1) {
      if (fabs(R[i + 21 * i]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      for (i = 0; i < 21; i++) {
        for (ix0 = 0; ix0 < 21; ix0++) {
          c = 0.0;
          for (b_i = 0; b_i < 21; b_i++) {
            c += Linv[b_i + 21 * i] * Q[b_i + 21 * ix0];
          }
          TL[i + 21 * ix0] = c;
        }
      }
      memset(&RLinv[0], 0, 441U * sizeof(double));
      for (ix0 = nA; ix0 >= 1; ix0--) {
        b_i = 21 * (ix0 - 1);
        i1 = (ix0 + b_i) - 1;
        RLinv[i1] = 1.0;
        for (lastc = ix0; lastc <= nA; lastc++) {
          knt = (ix0 + 21 * (lastc - 1)) - 1;
          RLinv[knt] /= R[i1];
        }
        if (ix0 > 1) {
          for (i = 0; i <= ix0 - 2; i++) {
            for (lastc = ix0; lastc <= nA; lastc++) {
              i1 = 21 * (lastc - 1);
              knt = i + i1;
              RLinv[knt] -= R[i + b_i] * RLinv[(ix0 + i1) - 1];
            }
          }
        }
      }
      if (nA > 2147483646) {
        knt = MAX_int32_T;
      } else {
        knt = nA + 1;
      }
      for (i = 0; i < 21; i++) {
        for (ix0 = i + 1; ix0 < 22; ix0++) {
          b_i = i + 21 * (ix0 - 1);
          H[b_i] = 0.0;
          for (lastc = knt; lastc < 22; lastc++) {
            i1 = 21 * (lastc - 1);
            H[b_i] -= TL[i + i1] * TL[(ix0 + i1) - 1];
          }
          H[(ix0 + 21 * i) - 1] = H[b_i];
        }
      }
      for (ix0 = 0; ix0 < nA; ix0++) {
        for (i = 0; i < 21; i++) {
          b_i = i + 21 * ix0;
          D[b_i] = 0.0;
          for (lastc = ix0 + 1; lastc <= nA; lastc++) {
            i1 = 21 * (lastc - 1);
            D[b_i] += TL[i + i1] * RLinv[ix0 + i1];
          }
        }
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return Status;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * sqrt(y * y + 1.0);
  } else if (!rtIsNaN(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

/*
 * Arguments    : const double Linv[441]
 *                const double Hinv[441]
 *                const double f[21]
 *                const double Ac[4200]
 *                const double b[200]
 *                boolean_T iA[200]
 *                double x[21]
 *                double lambda[200]
 *                int *status
 * Return Type  : void
 */
void qpkwik(const double Linv[441], const double Hinv[441], const double f[21],
            const double Ac[4200], const double b[200], boolean_T iA[200],
            double x[21], double lambda[200], int *status)
{
  double D[441];
  double H[441];
  double RLinv[441];
  double U[441];
  double cTol[200];
  double Opt[42];
  double Rhs[42];
  double r[21];
  double z[21];
  double Xnorm0;
  double cMin;
  double cVal;
  double rMin;
  double t;
  int iC[200];
  int b_exponent;
  int b_i;
  int exitg1;
  int exitg3;
  int exponent;
  int i;
  int idx;
  int k;
  int kDrop;
  int nA;
  int tmp;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  memset(&x[0], 0, 21U * sizeof(double));
  memset(&lambda[0], 0, 200U * sizeof(double));
  *status = 1;
  memset(&r[0], 0, 21U * sizeof(double));
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 200; i++) {
    cTol[i] = 1.0;
    iC[i] = 0;
  }
  nA = 0;
  for (i = 0; i < 200; i++) {
    if (iA[i]) {
      nA++;
      iC[nA - 1] = i + 1;
    }
  }
  guard1 = false;
  if (nA > 0) {
    memset(&Opt[0], 0, 42U * sizeof(double));
    for (i = 0; i < 21; i++) {
      Rhs[i] = f[i];
      Rhs[i + 21] = 0.0;
    }
    DualFeasible = false;
    tmp = (int)rt_roundd_snf(0.3 * (double)nA);
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && (*status <= 884)) {
        cVal = KWIKfactor(Ac, iC, nA, Linv, RLinv, D, H);
        if (cVal < 0.0) {
          if (ColdReset) {
            *status = -2;
            exitg3 = 2;
          } else {
            nA = 0;
            memset(&iA[0], 0, 200U * sizeof(boolean_T));
            memset(&iC[0], 0, 200U * sizeof(int));
            ColdReset = true;
          }
        } else {
          for (kDrop = 0; kDrop < nA; kDrop++) {
            if (kDrop + 1 > 2147483626) {
              idx = MAX_int32_T;
            } else {
              idx = kDrop + 22;
            }
            Rhs[idx - 1] = b[iC[kDrop] - 1];
            for (i = kDrop + 1; i <= nA; i++) {
              idx = (i + 21 * kDrop) - 1;
              U[idx] = 0.0;
              for (k = 0; k < nA; k++) {
                U[idx] += RLinv[(i + 21 * k) - 1] * RLinv[kDrop + 21 * k];
              }
              U[kDrop + 21 * (i - 1)] = U[idx];
            }
          }
          for (i = 0; i < 21; i++) {
            cVal = 0.0;
            for (b_i = 0; b_i < 21; b_i++) {
              cVal += H[i + 21 * b_i] * Rhs[b_i];
            }
            Opt[i] = cVal;
            for (k = 0; k < nA; k++) {
              Opt[i] += D[i + 21 * k] * Rhs[k + 21];
            }
          }
          for (i = 0; i < nA; i++) {
            cVal = 0.0;
            for (b_i = 0; b_i < 21; b_i++) {
              cVal += D[b_i + 21 * i] * Rhs[b_i];
            }
            Opt[i + 21] = cVal;
            for (k = 0; k < nA; k++) {
              Opt[i + 21] += U[i + 21 * k] * Rhs[k + 21];
            }
          }
          cVal = -1.0E-12;
          kDrop = 0;
          for (i = 0; i < nA; i++) {
            if (i + 1 > 2147483626) {
              idx = MAX_int32_T;
            } else {
              idx = i + 22;
            }
            lambda[iC[i] - 1] = Opt[idx - 1];
            if (i + 1 > 2147483626) {
              idx = MAX_int32_T;
            } else {
              idx = i + 22;
            }
            if ((Opt[idx - 1] < cVal) && (i + 1 <= nA)) {
              kDrop = i + 1;
              if (i + 1 > 2147483626) {
                idx = MAX_int32_T;
              } else {
                idx = i + 22;
              }
              cVal = Opt[idx - 1];
            }
          }
          if (kDrop <= 0) {
            DualFeasible = true;
            memcpy(&x[0], &Opt[0], 21U * sizeof(double));
          } else {
            (*status)++;
            if (tmp <= 5) {
              i = 5;
            } else {
              i = tmp;
            }
            if (*status > i) {
              nA = 0;
              memset(&iA[0], 0, 200U * sizeof(boolean_T));
              memset(&iC[0], 0, 200U * sizeof(int));
              ColdReset = true;
            } else {
              lambda[iC[kDrop - 1] - 1] = 0.0;
              DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          memset(&lambda[0], 0, 200U * sizeof(double));
          for (i = 0; i < 21; i++) {
            cVal = 0.0;
            for (b_i = 0; b_i < 21; b_i++) {
              cVal += -Hinv[i + 21 * b_i] * f[b_i];
            }
            x[i] = cVal;
          }
        }
        exitg3 = 1;
      }
    } while (exitg3 == 0);
    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    for (i = 0; i < 21; i++) {
      cVal = 0.0;
      for (b_i = 0; b_i < 21; b_i++) {
        cVal += -Hinv[i + 21 * b_i] * f[b_i];
      }
      x[i] = cVal;
    }
    guard1 = true;
  }
  if (guard1) {
    Xnorm0 = b_norm(x);
    exitg2 = false;
    while ((!exitg2) && (*status <= 884)) {
      cMin = -1.0E-6;
      tmp = -1;
      for (i = 0; i < 200; i++) {
        if (!cTolComputed) {
          for (k = 0; k < 21; k++) {
            z[k] = fabs(Ac[i + 200 * k] * x[k]);
          }
          if (!rtIsNaN(z[0])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg4 = false;
            while ((!exitg4) && (k < 22)) {
              if (!rtIsNaN(z[k - 1])) {
                idx = k;
                exitg4 = true;
              } else {
                k++;
              }
            }
          }
          if (idx == 0) {
            cVal = z[0];
          } else {
            cVal = z[idx - 1];
            b_i = idx + 1;
            for (k = b_i; k < 22; k++) {
              t = z[k - 1];
              if (cVal < t) {
                cVal = t;
              }
            }
          }
          if ((!(cTol[i] >= cVal)) && (!rtIsNaN(cVal))) {
            cTol[i] = cVal;
          }
        }
        if (!iA[i]) {
          t = 0.0;
          for (b_i = 0; b_i < 21; b_i++) {
            t += Ac[i + 200 * b_i] * x[b_i];
          }
          cVal = (t - b[i]) / cTol[i];
          if (cVal < cMin) {
            cMin = cVal;
            tmp = i;
          }
        }
      }
      cTolComputed = true;
      if (tmp + 1 <= 0) {
        exitg2 = true;
      } else if (*status == 884) {
        *status = 0;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((tmp + 1 > 0) && (*status <= 884)) {
            guard2 = false;
            if (nA == 0) {
              for (b_i = 0; b_i < 21; b_i++) {
                t = 0.0;
                for (idx = 0; idx < 21; idx++) {
                  t += Hinv[b_i + 21 * idx] * Ac[tmp + 200 * idx];
                }
                z[b_i] = t;
              }
              guard2 = true;
            } else {
              cVal = KWIKfactor(Ac, iC, nA, Linv, RLinv, D, H);
              if (cVal <= 0.0) {
                *status = -2;
                exitg1 = 1;
              } else {
                for (b_i = 0; b_i < 441; b_i++) {
                  U[b_i] = -H[b_i];
                }
                for (b_i = 0; b_i < 21; b_i++) {
                  t = 0.0;
                  for (idx = 0; idx < 21; idx++) {
                    t += U[b_i + 21 * idx] * Ac[tmp + 200 * idx];
                  }
                  z[b_i] = t;
                }
                for (i = 0; i < nA; i++) {
                  t = 0.0;
                  for (b_i = 0; b_i < 21; b_i++) {
                    t += Ac[tmp + 200 * b_i] * D[b_i + 21 * i];
                  }
                  r[i] = t;
                }
                guard2 = true;
              }
            }
            if (guard2) {
              kDrop = 0;
              cMin = 0.0;
              ColdReset = true;
              DualFeasible = true;
              if (nA > 0) {
                idx = 0;
                exitg4 = false;
                while ((!exitg4) && (idx <= nA - 1)) {
                  if (r[idx] >= 1.0E-12) {
                    DualFeasible = false;
                    exitg4 = true;
                  } else {
                    idx++;
                  }
                }
              }
              if ((nA != 0) && (!DualFeasible)) {
                for (i = 0; i < nA; i++) {
                  t = r[i];
                  if (t > 1.0E-12) {
                    cVal = lambda[iC[i] - 1] / t;
                    if ((kDrop == 0) || (cVal < rMin)) {
                      rMin = cVal;
                      kDrop = i + 1;
                    }
                  }
                }
                if (kDrop > 0) {
                  cMin = rMin;
                  ColdReset = false;
                }
              }
              cVal = 0.0;
              for (k = 0; k < 21; k++) {
                cVal += z[k] * Ac[tmp + 200 * k];
              }
              if (cVal <= 0.0) {
                cVal = 0.0;
                DualFeasible = true;
              } else {
                t = 0.0;
                for (b_i = 0; b_i < 21; b_i++) {
                  t += Ac[tmp + 200 * b_i] * x[b_i];
                }
                cVal = (b[tmp] - t) / cVal;
                DualFeasible = false;
              }
              if (ColdReset && DualFeasible) {
                *status = -1;
                exitg1 = 1;
              } else {
                if (DualFeasible) {
                  t = cMin;
                } else if (ColdReset) {
                  t = cVal;
                } else if (cMin < cVal) {
                  t = cMin;
                } else {
                  t = cVal;
                }
                for (i = 0; i < nA; i++) {
                  lambda[iC[i] - 1] -= t * r[i];
                  if (lambda[iC[i] - 1] < 0.0) {
                    lambda[iC[i] - 1] = 0.0;
                  }
                }
                lambda[tmp] += t;
                frexp(1.0, &exponent);
                if (fabs(t - cMin) < 2.2204460492503131E-16) {
                  DropConstraint(kDrop, iA, &nA, iC);
                }
                if (!DualFeasible) {
                  for (b_i = 0; b_i < 21; b_i++) {
                    x[b_i] += t * z[b_i];
                  }
                  frexp(1.0, &b_exponent);
                  if (fabs(t - cVal) < 2.2204460492503131E-16) {
                    if (nA == 21) {
                      *status = -1;
                      exitg1 = 1;
                    } else {
                      if (nA > 2147483646) {
                        nA = MAX_int32_T;
                      } else {
                        nA++;
                      }
                      iC[nA - 1] = tmp + 1;
                      i = nA - 1;
                      exitg4 = false;
                      while ((!exitg4) && (i + 1 > 1)) {
                        b_i = iC[i - 1];
                        if (iC[i] > b_i) {
                          exitg4 = true;
                        } else {
                          idx = iC[i];
                          iC[i] = b_i;
                          iC[i - 1] = idx;
                          i--;
                        }
                      }
                      iA[tmp] = true;
                      tmp = -1;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            cVal = b_norm(x);
            if (fabs(cVal - Xnorm0) > 0.001) {
              Xnorm0 = cVal;
              for (k = 0; k < 200; k++) {
                t = fabs(b[k]);
                if (t >= 1.0) {
                  cTol[k] = t;
                } else {
                  cTol[k] = 1.0;
                }
              }
              cTolComputed = false;
            }
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/*
 * File trailer for qpkwik.c
 *
 * [EOF]
 */
