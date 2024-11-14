/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: predict.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "predict.h"
#include "NeuralNgin_internal_types.h"
#include "predictForRNN.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : c_coder_internal_ctarget_DeepLe *obj
 *                const cell_wrap_30 *varargin_1
 *                float varargout_1[3]
 * Return Type  : void
 */
void DeepLearningNetwork_predict(c_coder_internal_ctarget_DeepLe *obj,
                                 const cell_wrap_30 *varargin_1,
                                 float varargout_1[3])
{
  static cell_wrap_31 r;
  r.f1[0] = *varargin_1;
  c_DeepLearningNetwork_predictFo(obj, &r, varargout_1);
}

/*
 * File trailer for predict.c
 *
 * [EOF]
 */
