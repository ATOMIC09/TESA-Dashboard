/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: scores2label.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "scores2label.h"
#include "NeuralNgin_types.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const float scores[3]
 *                const char classes[3]
 *                cell_wrap_29 label_categoryNames[3]
 * Return Type  : unsigned char
 */
unsigned char scores2label(const float scores[3], const char classes[3],
                           cell_wrap_29 label_categoryNames[3])
{
  static const bool bv[128] = {
      false, false, false, false, false, false, false, false, false, true,
      true,  true,  true,  true,  false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, true,  true,
      true,  true,  true,  false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false};
  float ex;
  int unusedExpr[3];
  int b_j1;
  int j2;
  int k;
  signed char unnamed_idx_0;
  bool exitg1;
  if (!rtIsNaNF(scores[0])) {
    b_j1 = 1;
  } else {
    b_j1 = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!rtIsNaNF(scores[k - 1])) {
        b_j1 = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (b_j1 == 0) {
    ex = scores[0];
    b_j1 = 1;
  } else {
    ex = scores[b_j1 - 1];
    j2 = b_j1 + 1;
    for (k = j2; k < 4; k++) {
      float f;
      f = scores[k - 1];
      if (ex < f) {
        ex = f;
        b_j1 = k;
      }
    }
  }
  unnamed_idx_0 = (signed char)b_j1;
  if (rtIsNaNF(ex)) {
    unnamed_idx_0 = 0;
  }
  for (k = 0; k < 3; k++) {
    char c;
    bool b;
    b_j1 = 1;
    c = classes[k];
    b = bv[(int)c];
    if (b) {
      b_j1 = 2;
    }
    j2 = 1;
    if (b) {
      j2 = 0;
    }
    b_j1 = (b_j1 <= j2);
    label_categoryNames[k].f1.size[0] = 1;
    label_categoryNames[k].f1.size[1] = b_j1;
    if (b_j1 - 1 >= 0) {
      label_categoryNames[k].f1.data[0] = c;
    }
  }
  introsort(label_categoryNames, unusedExpr);
  b_j1 = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    if (unnamed_idx_0 == k + 1) {
      b_j1 = k + 1;
      exitg1 = true;
    } else {
      k++;
    }
  }
  return (unsigned char)b_j1;
}

/*
 * File trailer for scores2label.c
 *
 * [EOF]
 */
