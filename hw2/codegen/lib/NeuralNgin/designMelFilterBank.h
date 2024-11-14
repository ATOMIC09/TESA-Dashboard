/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: designMelFilterBank.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef DESIGNMELFILTERBANK_H
#define DESIGNMELFILTERBANK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void designMelFilterBank(double fs, const double bandEdges_data[],
                         const int bandEdges_size[2], double filterBank_data[],
                         int filterBank_size[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for designMelFilterBank.h
 *
 * [EOF]
 */
