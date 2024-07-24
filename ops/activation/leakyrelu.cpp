#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
const DATA_TYPE negative_slope = -3, const1 = 0;    // 0.0

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE negative_slope);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, negative_slope);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
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

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE negative_slope)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        if (x >= (DATA_TYPE)(const1)) output[i] = x;
        else output[i] = negative_slope * x;
    }
}