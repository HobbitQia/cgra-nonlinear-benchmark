#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float negative_slope = -0.1;

void kernel(float input[], float output[], float negative_slope);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, negative_slope);
    #else
        float input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf, negative_slope);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(float input[], float output[], float negative_slope)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop vectorize(disable) unroll_count(1)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        if (x >= (float)(0.0)) output[i] = x;
        else output[i] = negative_slope * x;
    }
}