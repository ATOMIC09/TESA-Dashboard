/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: std.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "std.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double x[14042]
 *                double y[14]
 * Return Type  : void
 */
void b_std(const double x[14042], double y[14])
{
  double xv[1003];
  int p;
  int workspace_ixfirst;
  for (p = 0; p < 14; p++) {
    double scale;
    double xbar;
    double yv;
    workspace_ixfirst = p * 1003;
    memcpy(&xv[0], &x[workspace_ixfirst], 1003U * sizeof(double));
    xbar = xv[0];
    for (workspace_ixfirst = 0; workspace_ixfirst < 1002; workspace_ixfirst++) {
      xbar += xv[workspace_ixfirst + 1];
    }
    xbar /= 1003.0;
    yv = 0.0;
    scale = 3.3121686421112381E-170;
    for (workspace_ixfirst = 0; workspace_ixfirst < 1003; workspace_ixfirst++) {
      double d;
      d = fabs(xv[workspace_ixfirst] - xbar);
      if (d > scale) {
        double t;
        t = scale / d;
        yv = yv * t * t + 1.0;
        scale = d;
      } else {
        double t;
        t = d / scale;
        yv += t * t;
      }
    }
    yv = scale * sqrt(yv);
    y[p] = yv / 31.654383582688826;
  }
}

/*
 * File trailer for std.c
 *
 * [EOF]
 */
