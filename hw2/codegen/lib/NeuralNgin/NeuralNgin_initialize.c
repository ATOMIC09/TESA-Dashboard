/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralNgin_initialize.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "NeuralNgin_initialize.h"
#include "NeuralNgin_data.h"
#include "NeuralPredictAudio2.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void NeuralNgin_initialize(void)
{
  omp_init_nest_lock(&NeuralNgin_nestLockGlobal);
  NeuralPredictAudio2_new();
  NeuralPredictAudio2_init();
  isInitialized_NeuralNgin = true;
}

/*
 * File trailer for NeuralNgin_initialize.c
 *
 * [EOF]
 */
