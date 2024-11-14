/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralNgin_rtwutil.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "NeuralNgin_rtwutil.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath)
{
  char *resolvedFilePath;
  char *stringDuplicate;
  size_t filePathLen;
  size_t sizeOfChar;
  filePathLen = strlen((char *)unresolvedFilePath) + 1;
  sizeOfChar = 1;
  stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
  stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
#if defined(MW_RUNTIME_DL_DATA_PATH) != 0
  extern char *mwGetRuntimeDLDataPath(const char *);
  resolvedFilePath = mwGetRuntimeDLDataPath((char *)unresolvedFilePath);
#elif defined(MW_DL_DATA_PATH) != 0
  resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
#else
  char *coderDataPath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
  } else {
    resolvedFilePath = stringDuplicate;
  }
#endif
  return resolvedFilePath;
}

/*
 * Arguments    : int numerator
 * Return Type  : int
 */
int div_nde_s32_floor(int numerator)
{
  int quotient;
  if ((numerator < 0) && (numerator % 7 != 0)) {
    quotient = -1;
  } else {
    quotient = 0;
  }
  quotient += numerator / 7;
  return quotient;
}

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int absDenominator;
    unsigned int absNumerator;
    unsigned int tempAbsQuotient;
    bool quotientNeedsNegation;
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }
    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }
  return quotient;
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath)
{
  const char *fileName;
  char *coderDataPath;
  char *resolvedFilePath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    int posOfLastPathSeparator;
    size_t filePathLength;
    size_t sizeOfChar;
    posOfLastPathSeparator = getPositionOfLastFileSeparator(unresolvedFilePath);
    fileName = &unresolvedFilePath[posOfLastPathSeparator];
    filePathLength = (strlen(coderDataPath) + strlen((char *)fileName)) + 1;
    sizeOfChar = 1;
    resolvedFilePath = (char *)calloc(filePathLength, sizeOfChar);
    stringConcat(resolvedFilePath, coderDataPath, filePathLength);
    stringConcat(resolvedFilePath, fileName, filePathLength);
  } else {
    resolvedFilePath = NULL;
  }
  return resolvedFilePath;
}

/*
 * Arguments    : const char *filePath
 * Return Type  : int
 */
int getPositionOfLastFileSeparator(const char *filePath)
{
  int lastPathSeparatorUnix;
  int posOfLastPathSeparator;
  const char *ptrToLastPathSeparator;
  lastPathSeparatorUnix = '/';
  ptrToLastPathSeparator = strrchr((char *)filePath, lastPathSeparatorUnix);
  if (ptrToLastPathSeparator != NULL) {
    posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
  } else {
    int lastPathSeparatorWindows;
    lastPathSeparatorWindows = '\\';
    ptrToLastPathSeparator =
        strrchr((char *)filePath, lastPathSeparatorWindows);
    if (ptrToLastPathSeparator != NULL) {
      posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
    } else {
      posOfLastPathSeparator = -1;
    }
  }
  return posOfLastPathSeparator;
}

/*
 * Arguments    : const char *filePath
 * Return Type  : char *
 */
char *getRelativePathToParentFolder(const char *filePath)
{
  int posOfLastPathSeparator;
  const char *fileName;
  const char *parentDir;
  char *resolvedFilePath;
  size_t filePathLength;
  size_t sizeOfChar;
  parentDir = "..";
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  fileName = &filePath[posOfLastPathSeparator];
  filePathLength = (strlen((char *)parentDir) + strlen((char *)fileName)) + 1;
  sizeOfChar = 1;
  resolvedFilePath = (char *)calloc(filePathLength, sizeOfChar);
  stringConcat(resolvedFilePath, parentDir, filePathLength);
  stringConcat(resolvedFilePath, fileName, filePathLength);
  return resolvedFilePath;
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *getResolvedFilePath(const char *unresolvedFilePath)
{
  const char *fileOpenMode;
  char *computedPathUsingEnvVars;
  char *pathUsingEnvVarAndSanitizedPath;
  char *relativePathToParent;
  char *resolvedFilePath;
  char *sanitizedFilePath;
  char *stringDuplicate;
  FILE *filePtr;
  resolvedFilePath = NULL;
  fileOpenMode = "rb";
  filePtr = fopen((char *)unresolvedFilePath, (char *)fileOpenMode);
  if (filePtr) {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen((char *)unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
    fclose(filePtr);
  } else {
    computedPathUsingEnvVars =
        computeFilePathUsingEnvVariable(unresolvedFilePath);
    filePtr = fopen(computedPathUsingEnvVars, (char *)fileOpenMode);
    if (filePtr) {
      resolvedFilePath = computedPathUsingEnvVars;
      fclose(filePtr);
    } else {
      free(computedPathUsingEnvVars);
      sanitizedFilePath = sanitizeFilePathForHSP(unresolvedFilePath);
      filePtr = fopen(sanitizedFilePath, (char *)fileOpenMode);
      if (filePtr) {
        resolvedFilePath = sanitizedFilePath;
        fclose(filePtr);
      } else {
        relativePathToParent =
            getRelativePathToParentFolder(unresolvedFilePath);
        filePtr = fopen(relativePathToParent, (char *)fileOpenMode);
        if (filePtr) {
          resolvedFilePath = relativePathToParent;
          fclose(filePtr);
        } else {
          free(relativePathToParent);
          pathUsingEnvVarAndSanitizedPath =
              computeFilePathUsingEnvVariable(sanitizedFilePath);
          filePtr =
              fopen(pathUsingEnvVarAndSanitizedPath, (char *)fileOpenMode);
          if (filePtr) {
            resolvedFilePath = pathUsingEnvVarAndSanitizedPath;
            fclose(filePtr);
          } else {
            free(pathUsingEnvVarAndSanitizedPath);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  return resolvedFilePath;
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
void macroKernel1(int M, int K, int N, const float *A, int LDA, const float *B,
                  int LDB, float *C, int LDC)
{
  int idxB;
  int j;
  j = 0;
  idxB = 0;
  while (j <= N - 1) {
    int i;
    int idxA;
    int idxC;
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 7) {
      microKernel11(K, &A[idxA], LDA, &B[idxB], &C[idxC]);
      idxA += 7;
      idxC += 7;
      i += 7;
    }
    while (i <= M - 1) {
      microKernel12(K, &A[idxA], LDA, &B[idxB], &C[idxC]);
      idxA++;
      idxC++;
      i++;
    }
    idxB += LDB;
    j++;
  }
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                int blockSizeM
 *                int blockSizeK
 *                int blockSizeN
 *                const float *A
 *                const float *B
 *                float *C
 * Return Type  : void
 */
void matrixMultiply1(int M, int K, int N, int blockSizeM, int blockSizeK,
                     int blockSizeN, const float *A, const float *B, float *C)
{
  const float *ptrB;
  int b_i;
  int b_j1;
  int i;
  int i0;
  int i0_ub;
  int k0;
  int k0_ub;
  memset(C, 0, (unsigned int)((M * N) << 2));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = div_nde_s32_floor(blockSizeM) * 7;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }
  if (blockSizeN >= N) {
    blockSizeN = N;
  } else if (blockSizeN <= 0) {
    blockSizeN = 1;
  }
  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (b_j1 = 0; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }
    for (k0 = 1; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }
      ptrB = &B[k + K * b_j1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i, b_i)

      for (i0 = 1; i0 <= i0_ub; i0++) {
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }
        macroKernel1(b_i, K2, N2, &A[i + M * k], M, ptrB, K, &C[i + M * b_j1],
                     M);
      }
    }
  }
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                float *C
 * Return Type  : void
 */
void microKernel11(int K, const float *A, int LDA, const float *B, float *C)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  float e_c;
  float f_c;
  float g_c;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[2];
  d_c = C[3];
  e_c = C[4];
  f_c = C[5];
  g_c = C[6];
  for (k = 0; k < K; k++) {
    float b;
    b = B[idxB];
    c += A[idxA] * b;
    b_c += A[idxA + 1] * b;
    c_c += A[idxA + 2] * b;
    d_c += A[idxA + 3] * b;
    e_c += A[idxA + 4] * b;
    f_c += A[idxA + 5] * b;
    g_c += A[idxA + 6] * b;
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
  C[1] = b_c;
  C[2] = c_c;
  C[3] = d_c;
  C[4] = e_c;
  C[5] = f_c;
  C[6] = g_c;
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                float *C
 * Return Type  : void
 */
void microKernel12(int K, const float *A, int LDA, const float *B, float *C)
{
  float c;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (k = 0; k < K; k++) {
    c += A[idxA] * B[idxB];
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
}

/*
 * Arguments    : float *inputBufferPtr
 *                const char *unresolvedFilePath
 *                int numElementsToRead
 * Return Type  : void
 */
void readDnnConstants(float *inputBufferPtr, const char *unresolvedFilePath,
                      int numElementsToRead)
{
  int elementSizeInBytes;
  const char *fileOpenMode;
  char *resolvedFilePath;
  FILE *filePtr;
  void *dataBufferPtr;
  resolvedFilePath = getResolvedFilePath(unresolvedFilePath);
  fileOpenMode = "rb";
  filePtr = fopen(resolvedFilePath, (char *)fileOpenMode);
  dataBufferPtr = &inputBufferPtr[0];
  elementSizeInBytes = 4;
  fread(dataBufferPtr, elementSizeInBytes, numElementsToRead, filePtr);
  fclose(filePtr);
  free(resolvedFilePath);
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *resolveBinaryFilePath(const char *unresolvedFilePath)
{
  const char *c_filePathAfterSlicingRelativeP;
  const char *c_leadingPathSeparatorUnixAndWi;
  const char *codegenDirStrInMWDLDataPath;
  const char *d_filePathAfterSlicingRelativeP;
  const char *mwDLDataPath;
  char *codegenDir;
  char *coderDataPath;
  char *resolvedFilePath;
  char *updatedStartDir;
  size_t sizeOfChar;
#define XSTR(x) #x
#define STR(x) XSTR(x)
  coderDataPath = getenv("CODER_DATA_PATH");
  sizeOfChar = 1;
  if (coderDataPath != NULL) {
    resolvedFilePath = getCustomUserDataPathEnvVar(unresolvedFilePath);
  } else {
    size_t filePathLen;
    size_t posOfCodegenDir;
    size_t posOfLeadingPathSeparator;
    mwDLDataPath = STR(MW_DL_DATA_PATH);
    c_filePathAfterSlicingRelativeP = &unresolvedFilePath[2];
    c_leadingPathSeparatorUnixAndWi = "/\\";
    posOfLeadingPathSeparator =
        strcspn((char *)c_filePathAfterSlicingRelativeP,
                (char *)c_leadingPathSeparatorUnixAndWi);
    filePathLen = posOfLeadingPathSeparator + 1;
    codegenDir = (char *)calloc(filePathLen, sizeOfChar);
    strncpy(codegenDir, (char *)c_filePathAfterSlicingRelativeP,
            posOfLeadingPathSeparator);
    codegenDirStrInMWDLDataPath = strstr((char *)mwDLDataPath, codegenDir);
    if (codegenDirStrInMWDLDataPath == NULL) {
      posOfCodegenDir = strlen((char *)mwDLDataPath);
    } else {
      posOfCodegenDir = codegenDirStrInMWDLDataPath - mwDLDataPath;
    }
    if (posOfCodegenDir == strlen((char *)mwDLDataPath)) {
      size_t b_filePathLen;
      d_filePathAfterSlicingRelativeP = &unresolvedFilePath[1];
      b_filePathLen = (strlen((char *)mwDLDataPath) +
                       strlen((char *)d_filePathAfterSlicingRelativeP)) +
                      1;
      resolvedFilePath = (char *)calloc(b_filePathLen, sizeOfChar);
      stringConcat(resolvedFilePath, mwDLDataPath, b_filePathLen);
      stringConcat(resolvedFilePath, d_filePathAfterSlicingRelativeP,
                   b_filePathLen);
    } else {
      size_t c_filePathLen;
      c_filePathLen = posOfCodegenDir + 1;
      updatedStartDir = (char *)calloc(c_filePathLen, sizeOfChar);
      strncpy(updatedStartDir, (char *)mwDLDataPath, posOfCodegenDir);
      c_filePathLen = (strlen(updatedStartDir) +
                       strlen((char *)c_filePathAfterSlicingRelativeP)) +
                      1;
      resolvedFilePath = (char *)calloc(c_filePathLen, sizeOfChar);
      stringConcat(resolvedFilePath, updatedStartDir, c_filePathLen);
      stringConcat(resolvedFilePath, c_filePathAfterSlicingRelativeP,
                   c_filePathLen);
      free(updatedStartDir);
    }
    free(codegenDir);
  }
#undef XSTR
#undef STR
  return resolvedFilePath;
}

/*
 * Arguments    : const char *unSanitizedFilePath
 * Return Type  : char *
 */
char *sanitizeFilePathForHSP(const char *unSanitizedFilePath)
{
  char *sanitizedFilePath;
  char *stringDuplicate;
  size_t charIdx;
  size_t filePathLen;
  size_t sizeOfChar;
  filePathLen = strlen((char *)unSanitizedFilePath) + 1;
  sizeOfChar = 1;
  stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
  stringConcat(stringDuplicate, unSanitizedFilePath, filePathLen);
  sanitizedFilePath = stringDuplicate;
  for (charIdx = 0; charIdx < strlen((char *)unSanitizedFilePath); charIdx++) {
    char charToCheckFor;
    charToCheckFor = unSanitizedFilePath[charIdx];
    if (isspace(charToCheckFor)) {
      sanitizedFilePath[charIdx] = '_';
    }
  }
  return sanitizedFilePath;
}

/*
 * Arguments    : char *destinationString
 *                const char *sourceString
 *                size_t destBufferSize
 * Return Type  : void
 */
void stringConcat(char *destinationString, const char *sourceString,
                  size_t destBufferSize)
{
  size_t dstStringLen;
  size_t srcBuffIdx;
  dstStringLen = strlen(destinationString);
  srcBuffIdx = 0;
  while ((sourceString[srcBuffIdx] != '\x00') &&
         (dstStringLen < destBufferSize - 1)) {
    destinationString[dstStringLen] = sourceString[srcBuffIdx];
    dstStringLen++;
    srcBuffIdx++;
  }
  destinationString[dstStringLen] = '\x00';
}

/*
 * File trailer for NeuralNgin_rtwutil.c
 *
 * [EOF]
 */
