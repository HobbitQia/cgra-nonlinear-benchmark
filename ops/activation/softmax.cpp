#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

void softmax_loop1(float input[], float output[], float *max);
void softmax_loop2(float input[], float output[], float *max, float *sum);
void softmax_loop3(float input[], float output[], float *sum);

int main()
{
    float sum = 0.0, max = -10000.0;
    softmax_loop1(input, output, &max);
    softmax_loop2(input, output, &max, &sum);
    softmax_loop3(input, output, &sum);

    return 0;
}

void softmax_loop1(float input[], float output[], float *max) 
{
    float maxx = *max;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        if (x0 > maxx) maxx = x0;
    }
    *max = maxx;
}

void softmax_loop2(float input[], float output[], float *max, float *sum) 
{
    float summ = *sum;
    float maxx = *max;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        float e0 = exp(x0 - maxx);
        output[i] = e0;
        summ += e0;
    }
    *sum = summ;
}

void softmax_loop3(float input[], float output[], float *sum) 
{
    float summ = *sum;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        output[i] /= summ;
    }
}