/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: LSTMLayer.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef LSTMLAYER_H
#define LSTMLAYER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void LSTMLayer_predict(const float X_data[], const float hiddenState[500],
                       const float cellState[500], float Y[500]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for LSTMLayer.h
 *
 * [EOF]
 */
