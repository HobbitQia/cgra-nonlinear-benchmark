#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
DATA_TYPE alpha = 3, beta = 5;       // 0.2 0.1

const DATA_TYPE eps = 1;    // 1e-5

void layernorm_loop1(DATA_TYPE* __restrict input, DATA_TYPE* __restrict mean, DATA_TYPE* __restrict mean_x2);
void layernorm_loop2(DATA_TYPE* __restrict input, DATA_TYPE* __restrict mean, DATA_TYPE* __restrict invsqrt, DATA_TYPE alpha, DATA_TYPE beta);
int main()
{   
    DATA_TYPE mean = 0, mean_x2 = 0;
    #ifndef __STREAMING_ENBALED__
        layernorm_loop1(input, &mean, &mean_x2);
        mean /= NTAPS;
        mean_x2 /= NTAPS;
        DATA_TYPE variance = mean_x2 - mean * mean;
        DATA_TYPE var_eps = variance + eps;
        DATA_TYPE inv_stddev = invsqrt(var_eps);
        layernorm_loop2(input, &mean, &inv_stddev, alpha, beta);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            layernorm_loop1(input_buf, &mean, &mean_x2);
        }
        mean /= NTAPS;
        mean_x2 /= NTAPS;
        DATA_TYPE variance = mean_x2 - mean * mean;
        DATA_TYPE var_eps = variance + eps;
        DATA_TYPE inv_stddev = invsqrt(var_eps);
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            layernorm_loop2(input_buf, &mean, &inv_stddev, alpha, beta);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void layernorm_loop1(DATA_TYPE* __restrict input, DATA_TYPE* __restrict mean, DATA_TYPE* __restrict mean_x2) 
{
    DATA_TYPE meann = *mean;
    DATA_TYPE meann_x2 = *mean_x2;
    #pragma clang loop unroll_count(4) vectorize(enable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x0 = input[i];
        meann += x0;
        meann_x2 += x0 * x0;
    }
    *mean = meann;
    *mean_x2 = meann_x2;
}

void layernorm_loop2(DATA_TYPE* __restrict input, DATA_TYPE* __restrict mean, DATA_TYPE* __restrict invsqrt, DATA_TYPE alpha, DATA_TYPE beta) 
{
    DATA_TYPE meann = *mean;
    DATA_TYPE inv_stddev = *invsqrt;
    #pragma clang loop unroll_count(4) vectorize(enable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i] - meann;
        output[i] = x * inv_stddev * alpha + beta;
    }
}