/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: scores2label.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef SCORES2LABEL_H
#define SCORES2LABEL_H

/* Include Files */
#include "NeuralNgin_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
unsigned char scores2label(const float scores[3], const char classes[3],
                           cell_wrap_29 label_categoryNames[3]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for scores2label.h
 *
 * [EOF]
 */
