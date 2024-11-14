/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CheckEvent.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "CheckEvent.h"
#include "NeuralNgin_data.h"
#include "NeuralNgin_initialize.h"
#include "filter.h"
#include "mean.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * fil = designfilt('lowpassfir', ...
 *     'PassbandFrequency',10000,'StopbandFrequency',11000, ...
 *     'PassbandRipple',1,'StopbandAttenuation',60, ...
 *     'SampleRate',Fs,'DesignMethod','kaiserwin');
 *
 * Arguments    : const double b_signal[43200]
 *                double *m
 *                bool *isCandidate
 * Return Type  : void
 */
void CheckEvent(const double b_signal[43200], double *m, bool *isCandidate)
{
  static double s[43200];
  static double y[43200];
  int k;
  if (!isInitialized_NeuralNgin) {
    NeuralNgin_initialize();
  }
  /*  Example sample rate, replace with your actual Fs */
  /*  Passband frequency */
  /*  Stopband frequency */
  /*  Passband ripple in dB */
  /*  Stopband attenuation in dB */
  /*  Normalized frequencies (0 to 1) */
  /*  Normalized passband frequency */
  /*  Normalized stopband frequency */
  /*  Calculate the order of the filter */
  /*  Minimum attenuation needed in dB */
  /*  Estimate filter order */
  /*  Design the FIR filter using a Kaiser window */
  *isCandidate = false;
  filter(b_signal, s);
  for (k = 0; k < 43200; k++) {
    y[k] = fabs(s[k]);
  }
  *m = mean(y);
  if (*m > 0.33) {
    double b_y[100];
    for (k = 0; k < 100; k++) {
      b_y[k] = fabs(b_signal[k]);
    }
    if (b_mean(b_y) > 0.7) {
      *isCandidate = true;
    }
  }
}

/*
 * File trailer for CheckEvent.c
 *
 * [EOF]
 */
