/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: designMelFilterBank.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 02:25:16
 */

/* Include Files */
#include "designMelFilterBank.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static void binary_expand_op(double in1_data[], int in1_size[2],
                             const double in2_data[], int in3, int in4,
                             int in5);

/* Function Definitions */
/*
 * Arguments    : double in1_data[]
 *                int in1_size[2]
 *                const double in2_data[]
 *                int in3
 *                int in4
 *                int in5
 * Return Type  : void
 */
static void binary_expand_op(double in1_data[], int in1_size[2],
                             const double in2_data[], int in3, int in4, int in5)
{
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1_size[0] = 1;
  i = (in4 - in3) + 1;
  if (in5 + 1 == 1) {
    loop_ub = i;
  } else {
    loop_ub = in5 + 1;
  }
  in1_size[1] = loop_ub;
  stride_0_1 = (i != 1);
  stride_1_1 = (in5 + 1 != 1);
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        (in2_data[in3 + i * stride_0_1] - in2_data[i * stride_1_1]) / 2.0;
  }
}

/*
 * Arguments    : double fs
 *                const double bandEdges_data[]
 *                const int bandEdges_size[2]
 *                double filterBank_data[]
 *                int filterBank_size[2]
 * Return Type  : void
 */
void designMelFilterBank(double fs, const double bandEdges_data[],
                         const int bandEdges_size[2], double filterBank_data[],
                         int filterBank_size[2])
{
  static const double a[86] = {0.0,
                               0.011627906976744186,
                               0.023255813953488372,
                               0.034883720930232558,
                               0.046511627906976744,
                               0.058139534883720929,
                               0.069767441860465115,
                               0.081395348837209308,
                               0.093023255813953487,
                               0.10465116279069768,
                               0.11627906976744186,
                               0.12790697674418605,
                               0.13953488372093023,
                               0.15116279069767441,
                               0.16279069767441862,
                               0.1744186046511628,
                               0.18604651162790697,
                               0.19767441860465115,
                               0.20930232558139536,
                               0.22093023255813954,
                               0.23255813953488372,
                               0.2441860465116279,
                               0.2558139534883721,
                               0.26744186046511625,
                               0.27906976744186046,
                               0.29069767441860467,
                               0.30232558139534882,
                               0.313953488372093,
                               0.32558139534883723,
                               0.33720930232558138,
                               0.34883720930232559,
                               0.36046511627906974,
                               0.37209302325581395,
                               0.38372093023255816,
                               0.39534883720930231,
                               0.40697674418604651,
                               0.41860465116279072,
                               0.43023255813953487,
                               0.44186046511627908,
                               0.45348837209302323,
                               0.46511627906976744,
                               0.47674418604651164,
                               0.48837209302325579,
                               0.5,
                               0.51162790697674421,
                               0.52325581395348841,
                               0.53488372093023251,
                               0.54651162790697672,
                               0.55813953488372092,
                               0.56976744186046513,
                               0.58139534883720934,
                               0.59302325581395354,
                               0.60465116279069764,
                               0.61627906976744184,
                               0.627906976744186,
                               0.63953488372093026,
                               0.65116279069767447,
                               0.66279069767441856,
                               0.67441860465116277,
                               0.686046511627907,
                               0.69767441860465118,
                               0.70930232558139539,
                               0.72093023255813948,
                               0.73255813953488369,
                               0.7441860465116279,
                               0.7558139534883721,
                               0.76744186046511631,
                               0.77906976744186052,
                               0.79069767441860461,
                               0.80232558139534882,
                               0.813953488372093,
                               0.82558139534883723,
                               0.83720930232558144,
                               0.84883720930232553,
                               0.86046511627906974,
                               0.872093023255814,
                               0.88372093023255816,
                               0.89534883720930236,
                               0.90697674418604646,
                               0.91860465116279066,
                               0.93023255813953487,
                               0.94186046511627908,
                               0.95348837209302328,
                               0.96511627906976749,
                               0.97674418604651159,
                               0.98837209302325579};
  double linFq[86];
  double weightPerBand_data[42];
  double y1_data[41];
  double work_data;
  int weightPerBand_size[2];
  int i;
  int i1;
  int j;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int nz;
  signed char p_data[42];
  bool x_data[42];
  loop_ub = bandEdges_size[1];
  work_data = fs / 2.0;
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = (bandEdges_data[i] - work_data < 1.4901161193847656E-8);
  }
  if (bandEdges_size[1] == 0) {
    nz = 0;
  } else {
    nz = x_data[0];
    for (k = 2; k <= loop_ub; k++) {
      nz += x_data[k - 1];
    }
  }
  filterBank_size[0] = 86;
  filterBank_size[1] = bandEdges_size[1] - 2;
  loop_ub_tmp = 86 * (bandEdges_size[1] - 2);
  if (loop_ub_tmp - 1 >= 0) {
    memset(&filterBank_data[0], 0, (unsigned int)loop_ub_tmp * sizeof(double));
  }
  for (i = 0; i < 86; i++) {
    linFq[i] = a[i] * fs;
  }
  for (k = 0; k < nz; k++) {
    bool exitg1;
    loop_ub_tmp = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub_tmp < 86)) {
      if (linFq[loop_ub_tmp] > bandEdges_data[k]) {
        p_data[k] = (signed char)(loop_ub_tmp + 1);
        exitg1 = true;
      } else {
        loop_ub_tmp++;
      }
    }
  }
  if (bandEdges_size[1] != 0) {
    loop_ub_tmp = bandEdges_size[1] - 1;
    if (loop_ub_tmp > 1) {
      loop_ub_tmp = 1;
    }
    if (loop_ub_tmp >= 1) {
      if (bandEdges_size[1] - 1 != 0) {
        work_data = bandEdges_data[0];
        for (loop_ub_tmp = 2; loop_ub_tmp <= loop_ub; loop_ub_tmp++) {
          double d;
          double tmp1;
          tmp1 = bandEdges_data[loop_ub_tmp - 1];
          d = tmp1;
          tmp1 -= work_data;
          work_data = d;
          y1_data[loop_ub_tmp - 2] = tmp1;
        }
      }
    }
  }
  for (k = 0; k <= nz - 3; k++) {
    i = p_data[k + 1];
    i1 = i - p_data[k];
    for (j = 0; j < i1; j++) {
      loop_ub_tmp = (p_data[k] + j) - 1;
      filterBank_data[loop_ub_tmp + 86 * k] =
          (linFq[loop_ub_tmp] - bandEdges_data[k]) / y1_data[k];
    }
    i1 = p_data[k + 2] - i;
    for (j = 0; j < i1; j++) {
      loop_ub_tmp = (i + j) - 1;
      filterBank_data[loop_ub_tmp + 86 * k] =
          (bandEdges_data[k + 2] - linFq[loop_ub_tmp]) / y1_data[k + 1];
    }
  }
  if (bandEdges_size[1] < 3) {
    i = 0;
    i1 = 0;
  } else {
    i = 2;
    i1 = bandEdges_size[1];
  }
  if (bandEdges_size[1] - 2 < 1) {
    loop_ub_tmp = 0;
  } else {
    loop_ub_tmp = bandEdges_size[1] - 2;
  }
  k = i1 - i;
  if (k == loop_ub_tmp) {
    for (i1 = 0; i1 < k; i1++) {
      weightPerBand_data[i1] =
          (bandEdges_data[i + i1] - bandEdges_data[i1]) / 2.0;
    }
  } else {
    binary_expand_op(weightPerBand_data, weightPerBand_size, bandEdges_data, i,
                     i1 - 1, loop_ub_tmp - 1);
  }
  for (k = 0; k <= loop_ub - 3; k++) {
    work_data = weightPerBand_data[k];
    for (i = 0; i < 86; i++) {
      loop_ub_tmp = i + 86 * k;
      filterBank_data[loop_ub_tmp] /= work_data;
    }
  }
}

/*
 * File trailer for designMelFilterBank.c
 *
 * [EOF]
 */
