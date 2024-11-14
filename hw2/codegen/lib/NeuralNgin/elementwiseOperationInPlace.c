/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: elementwiseOperationInPlace.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "elementwiseOperationInPlace.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <math.h>

/* Function Declarations */
static void b_lambdaForColumnMajorGeneric(float *X);

static void d_lambdaForColumnMajorGeneric(float *X);

/* Function Definitions */
/*
 * Arguments    : float *X
 * Return Type  : void
 */
static void b_lambdaForColumnMajorGeneric(float *X)
{
  *X = 1.0F / (expf(-*X) + 1.0F);
}

/*
 * Arguments    : float *X
 * Return Type  : void
 */
static void d_lambdaForColumnMajorGeneric(float *X)
{
  *X = tanhf(*X);
}

/*
 * Arguments    : float X[500]
 * Return Type  : void
 */
void c_lambdaForColumnMajorGeneric(float X[500])
{
  int iElem;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (iElem = 0; iElem < 500; iElem++) {
    d_lambdaForColumnMajorGeneric(&X[iElem]);
  }
}

/*
 * Arguments    : float X[500]
 * Return Type  : void
 */
void e_lambdaForColumnMajorGeneric(float X[500])
{
  int iElem;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (iElem = 0; iElem < 500; iElem++) {
    X[iElem] = tanhf(X[iElem]);
  }
}

/*
 * Arguments    : float X[500]
 * Return Type  : void
 */
void f_lambdaForColumnMajorGeneric(float X[500])
{
  int iElem;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (iElem = 0; iElem < 500; iElem++) {
    X[iElem] = fmaxf(0.0F, X[iElem]);
  }
}

/*
 * Arguments    : float X[3]
 * Return Type  : void
 */
void g_lambdaForColumnMajorGeneric(float X[3])
{
  int iElem;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (iElem = 0; iElem < 3; iElem++) {
    X[iElem] = expf(X[iElem]);
  }
}

/*
 * Arguments    : float X[1500]
 * Return Type  : void
 */
void lambdaForColumnMajorGeneric(float X[1500])
{
  int iElem;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (iElem = 0; iElem < 1500; iElem++) {
    b_lambdaForColumnMajorGeneric(&X[iElem]);
  }
}

/*
 * File trailer for elementwiseOperationInPlace.c
 *
 * [EOF]
 */
