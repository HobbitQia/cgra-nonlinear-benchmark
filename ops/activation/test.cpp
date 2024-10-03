#include "../include/utils.h"

alignas(4) float input[NTAPS];
alignas(4) float output[NTAPS];

void kernel(float* __restrict input, float* __restrict output, float s_in);
float x;

int main()
{
    x = rand();
    // #ifndef __STREAMING_ENBALED__
        kernel(input, output, x);
    // #else
    //     float input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
    //     for (float i = 0; i < NTAPS; i += STREAMING_WIDTH) {
    //         for (float j = 0; j < STREAMING_WIDTH; j++) {
    //             input_buf[j] = input[i + j];
    //         }
    //         kernel(input_buf, output_buf);
    //         for (float j = 0; j < STREAMING_WIDTH; j++) {
    //             output[i + j] = output_buf[j];
    //         }
    //     }
    // #endif

    return 0;
}

void kernel(float* __restrict input, float* __restrict output, float s_in)
/*   input :           input sample array */
/*   output:           output sample array */
{   
    // float* input = __builtin_assume_aligned(inputt, 4);
    // float* output = __builtin_assume_aligned(outputt,4);
    // s_in 会被优化掉
    #pragma clang loop vectorize(disable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        float x  = input[i];
        output[i] = x / s_in;
    }
}