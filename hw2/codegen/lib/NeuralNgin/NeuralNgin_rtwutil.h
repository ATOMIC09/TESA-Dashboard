/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralNgin_rtwutil.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef NEURALNGIN_RTWUTIL_H
#define NEURALNGIN_RTWUTIL_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath);

extern int div_nde_s32_floor(int numerator);

extern int div_s32_floor(int numerator, int denominator);

extern char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath);

extern int getPositionOfLastFileSeparator(const char *filePath);

extern char *getRelativePathToParentFolder(const char *filePath);

extern char *getResolvedFilePath(const char *unresolvedFilePath);

extern void macroKernel1(int M, int K, int N, const float *A, int LDA,
                         const float *B, int LDB, float *C, int LDC);

extern void matrixMultiply1(int M, int K, int N, int blockSizeM, int blockSizeK,
                            int blockSizeN, const float *A, const float *B,
                            float *C);

extern void microKernel11(int K, const float *A, int LDA, const float *B,
                          float *C);

extern void microKernel12(int K, const float *A, int LDA, const float *B,
                          float *C);

extern void readDnnConstants(float *inputBufferPtr,
                             const char *unresolvedFilePath,
                             int numElementsToRead);

extern char *resolveBinaryFilePath(const char *unresolvedFilePath);

extern char *sanitizeFilePathForHSP(const char *unSanitizedFilePath);

extern void stringConcat(char *destinationString, const char *sourceString,
                         size_t destBufferSize);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for NeuralNgin_rtwutil.h
 *
 * [EOF]
 */
