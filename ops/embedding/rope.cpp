#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
DATA_TYPE theta = 3;

void kernel(DATA_TYPE input[], DATA_TYPE output[], int postion, DATA_TYPE theta);

int main()
{
   #ifndef __STREAMING_ENBALED__
        kernel(input, output, 1, theta);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf, 1, theta);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif
    kernel(input, output, 0, theta);

    return 0;
}

void kernel(DATA_TYPE input[], DATA_TYPE output[], int postion, DATA_TYPE theta)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < NTAPS; i += 2) {
        DATA_TYPE x = input[i];
        DATA_TYPE y = input[i + 1];
        output[i] = x * cos(theta) - y * sin(theta);
        output[i + 1] = x * sin(theta) + y * cos(theta);
    }
}