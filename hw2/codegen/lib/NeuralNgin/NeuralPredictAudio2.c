/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralPredictAudio2.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "NeuralPredictAudio2.h"
#include "NeuralNgin_data.h"
#include "NeuralNgin_initialize.h"
#include "NeuralNgin_internal_types.h"
#include "NeuralNgin_types.h"
#include "minOrMax.h"
#include "predict.h"
#include "rt_nonfinite.h"
#include "scores2label.h"
#include <string.h>

/* Variable Definitions */
static c_coder_internal_ctarget_DeepLe net;

static bool net_not_empty;

static bool classNames_not_empty;

/* Function Definitions */
/*
 * Arguments    : const double feature[14042]
 *                categorical *predictResult
 *                float *confidence
 * Return Type  : void
 */
void NeuralPredictAudio2(const double feature[14042],
                         categorical *predictResult, float *confidence)
{
  static cell_wrap_30 r;
  static char classNames[3];
  float score[3];
  if (!isInitialized_NeuralNgin) {
    NeuralNgin_initialize();
  }
  if (!net_not_empty) {
    net.IsNetworkInitialized = false;
    net.matlabCodegenIsDeleted = false;
    net_not_empty = true;
    /*  Load network once */
  }
  if (!classNames_not_empty) {
    classNames[0] = 'F';
    classNames[1] = 'N';
    classNames[2] = 'X';
    classNames_not_empty = true;
  }
  memcpy(&r.f1[0], &feature[0], 14042U * sizeof(double));
  DeepLearningNetwork_predict(&net, &r, score);
  predictResult->codes =
      scores2label(score, classNames, predictResult->categoryNames);
  *confidence = maximum(score);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void NeuralPredictAudio2_delete(void)
{
  if (!net.matlabCodegenIsDeleted) {
    net.matlabCodegenIsDeleted = true;
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void NeuralPredictAudio2_init(void)
{
  classNames_not_empty = false;
  net_not_empty = false;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void NeuralPredictAudio2_new(void)
{
  net.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for NeuralPredictAudio2.c
 *
 * [EOF]
 */
