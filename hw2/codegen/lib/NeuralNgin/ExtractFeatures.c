/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ExtractFeatures.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "ExtractFeatures.h"
#include "NeuralNgin_data.h"
#include "NeuralNgin_initialize.h"
#include "mean.h"
#include "mfcc.h"
#include "rt_nonfinite.h"
#include "std.h"

/* Function Definitions */
/*
 * Arguments    : const double x[43200]
 *                double Fs
 *                double features[14042]
 * Return Type  : void
 */
void ExtractFeatures(const double x[43200], double Fs, double features[14042])
{
  double b_dv[14];
  double dv1[14];
  int i;
  int i1;
  if (!isInitialized_NeuralNgin) {
    NeuralNgin_initialize();
  }
  /*  50% overlap */
  mfcc(x, Fs, features);
  c_mean(features, b_dv);
  b_std(features, dv1);
  for (i = 0; i < 14; i++) {
    for (i1 = 0; i1 < 1003; i1++) {
      int features_tmp;
      features_tmp = i1 + 1003 * i;
      features[features_tmp] = (features[features_tmp] - b_dv[i]) / dv1[i];
    }
  }
  /*  Pack the extracted feature vector to a new row of the feature matrix X */
  /* coeffs = reshape(coeffs, 1, []); */
  /* c = modwt(x', 'db2', 15); */
}

/*
 * File trailer for ExtractFeatures.c
 *
 * [EOF]
 */
