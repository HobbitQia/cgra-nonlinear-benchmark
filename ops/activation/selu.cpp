#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
const DATA_TYPE alpha = 5, scale = 3, const1 = 1, const2 = 0;   // 1.67 1.05 1.0 0.0

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE scale, DATA_TYPE alpha);

int main()
{    
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, scale, alpha);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
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

void kernel(DATA_TYPE input[], DATA_TYPE output[], DATA_TYPE scale, DATA_TYPE alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = input[i];
        output[i] = scale * (max((DATA_TYPE)(const2), x)) + min((DATA_TYPE)(const2), alpha * (exp(x) - (DATA_TYPE)(const1)));
    }
}