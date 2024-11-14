/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mean.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "mean.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double x[100]
 * Return Type  : double
 */
double b_mean(const double x[100])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 99; k++) {
    y += x[k + 1];
  }
  y /= 100.0;
  return y;
}

/*
 * Arguments    : const double x[14042]
 *                double y[14]
 * Return Type  : void
 */
void c_mean(const double x[14042], double y[14])
{
  int k;
  int xi;
  for (xi = 0; xi < 14; xi++) {
    double d;
    int xpageoffset;
    xpageoffset = xi * 1003;
    d = x[xpageoffset];
    for (k = 0; k < 1002; k++) {
      d += x[(xpageoffset + k) + 1];
    }
    y[xi] = d / 1003.0;
  }
}

/*
 * Arguments    : const double x[43200]
 * Return Type  : double
 */
double mean(const double x[43200])
{
  double accumulatedData;
  double y;
  int ib;
  int k;
  accumulatedData = x[0];
  for (k = 0; k < 1023; k++) {
    accumulatedData += x[k + 1];
  }
  for (ib = 0; ib < 42; ib++) {
    int hi;
    int xblockoffset;
    xblockoffset = (ib + 1) << 10;
    y = x[xblockoffset];
    if (ib + 2 == 43) {
      hi = 192;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      y += x[(xblockoffset + k) - 1];
    }
    accumulatedData += y;
  }
  return accumulatedData / 43200.0;
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
