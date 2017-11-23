/*
 * filter.h
 *
 *  Created on: 2017年11月23日
 */

#ifndef INCLUDE_FILTER_H_
#define INCLUDE_FILTER_H_

#define FILTER_ORDER 2		//滤波器阶数定义

struct IIR_Filter_State{

    float x[FILTER_ORDER+1];
    float y[FILTER_ORDER+1];
};

float IIR_B[3] = {
8.765554958e-05,0.0001753110992,8.765554958e-05};

float IIR_A[3] = {
1,   -1.973344207,   0.9736948609};

float iir_filter(struct IIR_Filter_State *filter_state, float *a, float *b, float x_0);

#endif /* INCLUDE_FILTER_H_ */

