#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

void kernel(float input[], float output[]);
const float x = 3.0;

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
    float max = 0.0;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        if (x0 > max) max = x0;
    }
    output[0] = max;
}