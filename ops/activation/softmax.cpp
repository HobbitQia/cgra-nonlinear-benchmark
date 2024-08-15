#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS], input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];

void softmax_loop1(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE* __restrict max);
void softmax_loop2(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE* __restrict max, DATA_TYPE* __restrict sum);
void softmax_loop3(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE *sum);

int main()
{
    
    DATA_TYPE sum = 0, max = -10000;
    DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];

    #ifndef __STREAMING_ENBALED__
        softmax_loop1(input, output, &max);
        softmax_loop2(input, output, &max, &sum);
        softmax_loop3(input, output, &sum);
    #else
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            softmax_loop1(input, output, &max);
        }
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            softmax_loop2(input, output, &max);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = output[i + j];
            }
            softmax_loop3(input, output, &sum);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void softmax_loop1(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE* __restrict max) 
{
    DATA_TYPE maxx = *max;
    #pragma clang loop unroll_count(4) vectorize(enable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        DATA_TYPE x0 = Convert(input[i]);
        if (x0 > maxx) maxx = x0;
    }
    *max = maxx;
}

void softmax_loop2(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE* __restrict max, DATA_TYPE* __restrict sum) 
{
    DATA_TYPE summ = *sum;
    DATA_TYPE maxx = *max;
    #pragma clang loop unroll_count(4) vectorize(enable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        DATA_TYPE x0 = Convert(input[i]);
        DATA_TYPE e0 = exp(x0 - maxx);
        output[i] = Convert(e0);
        summ += e0;
    }
    *sum = summ;
}

void softmax_loop3(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE *sum) 
{
    DATA_TYPE summ = *sum;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        output[i] = Convert(Convert(input[i]) / summ);
    }
}