#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
const DATA_TYPE alpha = 3, const1 = 0, const2 = 1;      // 0.1 0.0 1.0

void kernel(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE alpha);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(input, output, alpha);
    #else
        DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
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

void kernel(DATA_TYPE* __restrict input, DATA_TYPE* __restrict output, DATA_TYPE alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    // #pragma unroll 8 vectorize(disable)//vectorize_width(4)
    #pragma clang loop unroll_count(4) vectorize(enable)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = Convert(input[i]);
        if (x > (DATA_TYPE)(const1)) output[i] = Convert(x);
        else output[i] = Convert(alpha * (exp(x) - (DATA_TYPE)(const2)));
    }
}