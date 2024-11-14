/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: introsort.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "introsort.h"
#include "NeuralNgin_types.h"
#include "insertionsort.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const cell_wrap_29 cmp_workspace_c[3]
 *                int x[3]
 * Return Type  : void
 */
void introsort(const cell_wrap_29 cmp_workspace_c[3], int x[3])
{
  x[0] = 1;
  x[1] = 2;
  x[2] = 3;
  insertionsort(x, cmp_workspace_c);
}

/*
 * File trailer for introsort.c
 *
 * [EOF]
 */
