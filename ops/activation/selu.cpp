#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 1.67;
float scale = 1.05;

void kernel(float input[], float output[], float scale, float alpha);

int main()
{    
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, scale, alpha);
    #else
        float input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf, scale, alpha);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(float input[], float output[], float scale, float alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        output[i] = scale * (max((float)(0.0), x)) + min((float)(0.0), alpha * (exp(x) - (float)(1.0)));
    }
}