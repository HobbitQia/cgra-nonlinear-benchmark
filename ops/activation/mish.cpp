#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
const DATA_TYPE beta1 = 3, beta2 = 5, const1 = 1, const2 = -3;     // 1.0 -2.0 beta1: 1/ beta beta2: beta

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
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        // const2 should be beta1 * -2
        DATA_TYPE softplus_x = (DATA_TYPE)(const2) * log(exp(beta2 * x));
        DATA_TYPE exp_2x = exp(softplus_x);
        output[i] = x * ((DATA_TYPE)(const1) - exp_2x) / ((DATA_TYPE)(const1) + exp_2x);
    }
}