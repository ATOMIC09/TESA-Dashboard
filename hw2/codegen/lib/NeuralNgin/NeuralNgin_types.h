/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NeuralNgin_types.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

#ifndef NEURALNGIN_TYPES_H
#define NEURALNGIN_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef struct_emxArray_uint16_T
#define struct_emxArray_uint16_T
struct emxArray_uint16_T {
  unsigned short *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_uint16_T */
#ifndef typedef_emxArray_uint16_T
#define typedef_emxArray_uint16_T
typedef struct emxArray_uint16_T emxArray_uint16_T;
#endif /* typedef_emxArray_uint16_T */

#ifndef struct_emxArray_char_T_1x1
#define struct_emxArray_char_T_1x1
struct emxArray_char_T_1x1 {
  char data[1];
  int size[2];
};
#endif /* struct_emxArray_char_T_1x1 */
#ifndef typedef_emxArray_char_T_1x1
#define typedef_emxArray_char_T_1x1
typedef struct emxArray_char_T_1x1 emxArray_char_T_1x1;
#endif /* typedef_emxArray_char_T_1x1 */

#ifndef typedef_cell_wrap_29
#define typedef_cell_wrap_29
typedef struct {
  emxArray_char_T_1x1 f1;
} cell_wrap_29;
#endif /* typedef_cell_wrap_29 */

#ifndef typedef_categorical
#define typedef_categorical
typedef struct {
  unsigned char codes;
  cell_wrap_29 categoryNames[3];
} categorical;
#endif /* typedef_categorical */

#endif
/*
 * File trailer for NeuralNgin_types.h
 *
 * [EOF]
 */
