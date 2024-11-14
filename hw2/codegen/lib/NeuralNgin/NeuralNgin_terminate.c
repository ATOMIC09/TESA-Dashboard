/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralNgin_terminate.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "NeuralNgin_terminate.h"
#include "NeuralNgin_data.h"
#include "NeuralPredictAudio2.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void NeuralNgin_terminate(void)
{
  NeuralPredictAudio2_delete();
  omp_destroy_nest_lock(&NeuralNgin_nestLockGlobal);
  isInitialized_NeuralNgin = false;
}

/*
 * File trailer for NeuralNgin_terminate.c
 *
 * [EOF]
 */
