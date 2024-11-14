/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cepstralCoefficients.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "cepstralCoefficients.h"
#include "NeuralNgin_emxutil.h"
#include "NeuralNgin_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *S
 *                double coeffs[13039]
 * Return Type  : void
 */
void cepstralCoefficients(emxArray_real_T *S, double coeffs[13039])
{
  emxArray_uint16_T *ii;
  double b_coeffs[13039];
  double DCTmatrix_data[520];
  double A;
  double B;
  double piCCast;
  double *S_data;
  int aoffset;
  int coeffs_tmp;
  int coffset;
  int i;
  int idx;
  int j;
  int k;
  int loop_ub;
  unsigned short *ii_data;
  bool x_data[40120];
  bool exitg1;
  S_data = S->data;
  loop_ub = S->size[0];
  aoffset = S->size[0] * 1003;
  for (coeffs_tmp = 0; coeffs_tmp < aoffset; coeffs_tmp++) {
    x_data[coeffs_tmp] = (S_data[coeffs_tmp] == 0.0);
  }
  idx = 0;
  emxInit_uint16_T(&ii);
  coeffs_tmp = ii->size[0];
  ii->size[0] = aoffset;
  emxEnsureCapacity_uint16_T(ii, coeffs_tmp);
  ii_data = ii->data;
  coffset = 0;
  exitg1 = false;
  while ((!exitg1) && (coffset <= aoffset - 1)) {
    if (x_data[coffset]) {
      idx++;
      ii_data[idx - 1] = (unsigned short)(coffset + 1);
      if (idx >= aoffset) {
        exitg1 = true;
      } else {
        coffset++;
      }
    } else {
      coffset++;
    }
  }
  if (aoffset == 1) {
    if (idx == 0) {
      ii->size[0] = 0;
    }
  } else {
    coeffs_tmp = ii->size[0];
    if (idx < 1) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }
    emxEnsureCapacity_uint16_T(ii, coeffs_tmp);
    ii_data = ii->data;
  }
  if (ii->size[0] != 0) {
    coffset = ii->size[0] - 1;
    for (coeffs_tmp = 0; coeffs_tmp <= coffset; coeffs_tmp++) {
      S_data[ii_data[coeffs_tmp] - 1] = 2.2250738585072014E-308;
    }
  }
  emxFree_uint16_T(&ii);
  for (k = 0; k < aoffset; k++) {
    S_data[k] = log10(S_data[k]);
  }
  aoffset = 13 * S->size[0];
  if (aoffset - 1 >= 0) {
    memset(&DCTmatrix_data[0], 0, (unsigned int)aoffset * sizeof(double));
  }
  A = sqrt(1.0 / (double)S->size[0]);
  B = sqrt(2.0 / (double)S->size[0]);
  piCCast = 6.2831853071795862 / (2.0 * (double)S->size[0]);
  for (k = 0; k < loop_ub; k++) {
    DCTmatrix_data[13 * k] = A;
    for (coffset = 0; coffset < 12; coffset++) {
      DCTmatrix_data[(coffset + 13 * k) + 1] =
          B * cos(piCCast * (((double)coffset + 2.0) - 1.0) *
                  (((double)k + 1.0) - 0.5));
    }
  }
  for (j = 0; j < 1003; j++) {
    coffset = j * 13;
    idx = j * S->size[0];
    memset(&b_coeffs[coffset], 0, 13U * sizeof(double));
    for (k = 0; k < loop_ub; k++) {
      aoffset = k * 13;
      A = S_data[idx + k];
      for (i = 0; i < 13; i++) {
        coeffs_tmp = coffset + i;
        b_coeffs[coeffs_tmp] += DCTmatrix_data[aoffset + i] * A;
      }
    }
  }
  for (k = 0; k < 1003; k++) {
    for (coffset = 0; coffset < 13; coffset++) {
      coeffs[k + 1003 * coffset] = b_coeffs[coffset + 13 * k];
    }
  }
}

/*
 * File trailer for cepstralCoefficients.c
 *
 * [EOF]
 */
