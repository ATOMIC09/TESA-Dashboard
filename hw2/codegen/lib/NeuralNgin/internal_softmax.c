/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: internal_softmax.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "internal_softmax.h"
#include "elementwiseOperationInPlace.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const float xdata[3]
 *                float ydata[3]
 * Return Type  : void
 */
void iComputeSoftmaxForCpu(const float xdata[3], float ydata[3])
{
  int k;
  int nonChannelDimsProductIdx;
  for (nonChannelDimsProductIdx = 0; nonChannelDimsProductIdx < 1;
       nonChannelDimsProductIdx++) {
    float maxVal;
    float sumX;
    int idx;
    if (!rtIsNaNF(xdata[0])) {
      idx = 1;
    } else {
      bool exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 4)) {
        if (!rtIsNaNF(xdata[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      maxVal = xdata[0];
    } else {
      maxVal = xdata[idx - 1];
      idx++;
      for (k = idx; k < 4; k++) {
        sumX = xdata[k - 1];
        if (maxVal < sumX) {
          maxVal = sumX;
        }
      }
    }
    ydata[0] = xdata[0] - maxVal;
    ydata[1] = xdata[1] - maxVal;
    ydata[2] = xdata[2] - maxVal;
    g_lambdaForColumnMajorGeneric(ydata);
    sumX = (ydata[0] + ydata[1]) + ydata[2];
    ydata[0] /= sumX;
    ydata[1] /= sumX;
    ydata[2] /= sumX;
  }
}

/*
 * File trailer for internal_softmax.c
 *
 * [EOF]
 */
