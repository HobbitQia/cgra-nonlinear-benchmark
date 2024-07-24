#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
const DATA_TYPE const1 = 1, const2 = -2;           // 1.0 -2.0

void kernel(DATA_TYPE input[], DATA_TYPE output[]);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
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

void kernel(DATA_TYPE input[], DATA_TYPE output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        DATA_TYPE exp_2x = exp(x * (DATA_TYPE)(const2));
        output[i] = ((DATA_TYPE)(const1) - exp_2x) / ((DATA_TYPE)(const1) + exp_2x);
    }
}