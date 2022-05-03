/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2022 16:42:46
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "mpcmoveCodeGeneration.h"
#include "mpcmoveCodeGeneration_terminate.h"
#include "mpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_200x1_boolean_T(boolean_T result[200]);

static void argInit_2x1_real_T(double result[2]);

static void argInit_2x5_real_T(double result[10]);

static void argInit_40x2_real_T(double result[80]);

static void argInit_5x1_real_T(double result[5]);

static void argInit_5x5_real_T(double result[25]);

static void argInit_6x6_real_T(double result[36]);

static boolean_T argInit_boolean_T(void);

static double argInit_real_T(void);

static void argInit_struct10_T(struct10_T *result);

static void argInit_struct4_T(struct4_T *result);

static void argInit_struct5_T(struct5_T *result);

static void argInit_struct6_T(struct6_T *result);

static void main_mpcmoveCodeGeneration(void);

/* Function Definitions */
/*
 * Arguments    : boolean_T result[200]
 * Return Type  : void
 */
static void argInit_200x1_boolean_T(boolean_T result[200])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 200; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_boolean_T();
  }
}

/*
 * Arguments    : double result[2]
 * Return Type  : void
 */
static void argInit_2x1_real_T(double result[2])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[10]
 * Return Type  : void
 */
static void argInit_2x5_real_T(double result[10])
{
  int idx0;
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    for (idx1 = 0; idx1 < 5; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 1)] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[80]
 * Return Type  : void
 */
static void argInit_40x2_real_T(double result[80])
{
  int idx0;
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 40; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result[idx0 + 40 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[5]
 * Return Type  : void
 */
static void argInit_5x1_real_T(double result[5])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 5; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[25]
 * Return Type  : void
 */
static void argInit_5x5_real_T(double result[25])
{
  int idx0;
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 5; idx0++) {
    for (idx1 = 0; idx1 < 5; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result[idx0 + 5 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[36]
 * Return Type  : void
 */
static void argInit_6x6_real_T(double result[36])
{
  int idx0;
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result[idx0 + 6 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : boolean_T
 */
static boolean_T argInit_boolean_T(void)
{
  return false;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : struct10_T *result
 * Return Type  : void
 */
static void argInit_struct10_T(struct10_T *result)
{
  double d;
  int i;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  argInit_5x1_real_T(result->B);
  argInit_2x1_real_T(result->D);
  argInit_5x5_real_T(result->A);
  argInit_2x5_real_T(result->C);
  result->U = argInit_real_T();
  result->Y[0] = result->D[0];
  result->Y[1] = result->D[1];
  for (i = 0; i < 5; i++) {
    d = result->B[i];
    result->X[i] = d;
    result->DX[i] = d;
  }
}

/*
 * Arguments    : struct4_T *result
 * Return Type  : void
 */
static void argInit_struct4_T(struct4_T *result)
{
  double result_tmp;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result->LastMove = result_tmp;
  argInit_5x1_real_T(result->Plant);
  result->Disturbance = result_tmp;
  argInit_6x6_real_T(result->Covariance);
  argInit_200x1_boolean_T(result->iA);
}

/*
 * Arguments    : struct5_T *result
 * Return Type  : void
 */
static void argInit_struct5_T(struct5_T *result)
{
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  argInit_struct6_T(&result->signals);
  argInit_struct10_T(&result->model);
}

/*
 * Arguments    : struct6_T *result
 * Return Type  : void
 */
static void argInit_struct6_T(struct6_T *result)
{
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  argInit_2x1_real_T(result->ym);
  argInit_40x2_real_T(result->ref);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_mpcmoveCodeGeneration(void)
{
  struct11_T Info;
  struct4_T statedata;
  struct5_T r;
  double u;
  /* Initialize function 'mpcmoveCodeGeneration' input arguments. */
  /* Initialize function input argument 'statedata'. */
  /* Initialize function input argument 'onlinedata'. */
  /* Call the entry-point 'mpcmoveCodeGeneration'. */
  argInit_struct4_T(&statedata);
  argInit_struct5_T(&r);
  mpcmoveCodeGeneration(&statedata, &r, &u, &Info);
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_mpcmoveCodeGeneration();
  /* Terminate the application.
You do not need to do this more than one time. */
  mpcmoveCodeGeneration_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
