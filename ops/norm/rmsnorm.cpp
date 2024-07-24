#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
DATA_TYPE alpha = 3;         // 0.2

const DATA_TYPE eps = 1;    // 1e-5

void rmsnorm_loop1(DATA_TYPE input[], DATA_TYPE *variance);
void rmsnorm_loop2(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE *invsqrt, DATA_TYPE alpha);

int main()
{
    DATA_TYPE variance = 0;
    #ifndef __STREAMING_ENBALED__
        rmsnorm_loop1(input, &variance);
        variance /= NTAPS;
        DATA_TYPE var_eps = variance + eps;
        DATA_TYPE inv_stddev = invsqrt(var_eps);
        rmsnorm_loop2(input, output, &inv_stddev, alpha);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            rmsnorm_loop1(input_buf, &variance);
        }
        variance /= NTAPS;
        DATA_TYPE var_eps = variance + eps;
        DATA_TYPE inv_stddev = invsqrt(var_eps);
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            rmsnorm_loop2(input_buf, output_buf, &inv_stddev, alpha);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void rmsnorm_loop1(DATA_TYPE input[], DATA_TYPE *variance) 
{
    DATA_TYPE var = *variance;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        var += x * x;
    }
    *variance = var;
}

void rmsnorm_loop2(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE *invsqrt, DATA_TYPE alpha) 
{
    DATA_TYPE inv_stddev = *invsqrt;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        output[i] = (input[i]) * inv_stddev * alpha;
    }
}
