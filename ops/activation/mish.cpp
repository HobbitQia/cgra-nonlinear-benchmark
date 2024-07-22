#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

const float beta = 1.0;

void kernel(float input[], float output[]);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output);
    #else
        float input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(float input[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        float softplus_x = ((float)(1.0) / beta) * log(exp(beta * x));
        float exp_2x = exp(softplus_x * (float)(-2.0));
        output[i] = x * ((float)(1.0) - exp_2x) / ((float)(1.0) + exp_2x);
    }
}