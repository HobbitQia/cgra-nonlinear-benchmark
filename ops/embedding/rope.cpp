#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
DATA_TYPE theta = 3;
DATA_TYPE const0 = -2;

void kernel(DATA_TYPE* __restrict__ input, DATA_TYPE* __restrict__ output, DATA_TYPE position, int dim);

int main()
{
   #ifndef __STREAMING_ENBALED__
        for (int i = 0; i < 10; i++)
        kernel(input, output, i, NTAPS);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf, 1, NTAPS);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(DATA_TYPE* __restrict__ input, DATA_TYPE* __restrict__ output, DATA_TYPE position, int dim)
/*   input :           input sample array */
/*   output:           output sample array */
{
    // #pragma unroll 4 
    #pragma clang loop unroll_count(1) vectorize(disable)
    for (int i = 0; i < LOOP_LENGTH; i += 2) {
        DATA_TYPE theta = position * exp(const0 * i / dim);
        DATA_TYPE x = input[i];
        DATA_TYPE y = input[i + 1];
        DATA_TYPE cos_theta = cos(theta);
        DATA_TYPE sin_theta = sin(theta);
        output[i] = x * cos_theta - y * sin_theta;
        output[i + 1] = x * sin_theta + y * cos_theta;
    }
}