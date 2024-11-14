/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralPredictAudio2.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef NEURALPREDICTAUDIO2_H
#define NEURALPREDICTAUDIO2_H

/* Include Files */
#include "NeuralNgin_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void NeuralPredictAudio2(const double feature[14042],
                                categorical *predictResult, float *confidence);

void NeuralPredictAudio2_delete(void);

void NeuralPredictAudio2_init(void);

void NeuralPredictAudio2_new(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for NeuralPredictAudio2.h
 *
 * [EOF]
 */
