#include "../include/utils.h"

int input[NTAPS];
int output[NTAPS];

void kernel(int input[], int output[], float s_in);
float x;

int main()
{
    x = rand();
    // #ifndef __STREAMING_ENBALED__
        kernel(input, output, x);
    // #else
    //     float input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
    //     for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
    //         for (int j = 0; j < STREAMING_WIDTH; j++) {
    //             input_buf[j] = input[i + j];
    //         }
    //         kernel(input_buf, output_buf);
    //         for (int j = 0; j < STREAMING_WIDTH; j++) {
    //             output[i + j] = output_buf[j];
    //         }
    //     }
    // #endif

    return 0;
}

void kernel(int input[], int output[], float s_in)
/*   input :           input sample array */
/*   output:           output sample array */
{   
    // s_in 会被优化掉
    for (int i = 0; i < LOOP_LENGTH; i++) {
        float s = intExp_s(s_in);
        float x = intExp(input[i], s_in);
        output[i]  = s * x;
        
    }
    // float max = 0.0;
    // #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    // for (int i = 0; i < NTAPS; i++) {
    //     float x0 = input[i];
    //     if (x0 > max) max = x0;
    // }
    // output[0] = max;
}