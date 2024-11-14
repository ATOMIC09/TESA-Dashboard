/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SoftmaxLayer.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "SoftmaxLayer.h"
#include "internal_softmax.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const float X1_Data[3]
 *                float Z1_Data[3]
 * Return Type  : void
 */
void SoftmaxLayer_predict(const float X1_Data[3], float Z1_Data[3])
{
  iComputeSoftmaxForCpu(X1_Data, Z1_Data);
}

/*
 * File trailer for SoftmaxLayer.c
 *
 * [EOF]
 */
