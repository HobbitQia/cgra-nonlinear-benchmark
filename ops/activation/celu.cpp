#include "../include/utils.h"

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE alpha);

DATA_TYPE input[NTAPS], output[NTAPS], input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
const DATA_TYPE alpha = 3, const1 = 0, const2 = 1;      // 0.1 0.0 1.0

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, alpha);
    #else
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                input_buf[j] = input[i + j];
            }
            kernel(input_buf, output_buf, alpha);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        output[i] = max((DATA_TYPE)(const1), x) + min((DATA_TYPE)(const1), alpha * (exp(x / alpha) - (DATA_TYPE)(const2)));
    }
}