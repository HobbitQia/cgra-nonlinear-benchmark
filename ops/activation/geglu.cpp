#include "../include/utils.h"

DATA_TYPE a[NTAPS], b[NTAPS], output[NTAPS];
const DATA_TYPE const1 = 5, const2 = 6, const3 = -2, const4 = 1, const5 = 3; 

void kernel(DATA_TYPE* __restrict__ a, DATA_TYPE* __restrict__ b, DATA_TYPE* __restrict__ output);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(a, b, output);
    #else
        DATA_TYPE a_buf[STREAMING_WIDTH], b_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
        for (int i = 0; i < NTAPS; i += STREAMING_WIDTH) {
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                a_buf[j] = a[i + j];
                b_buf[j] = b[i + j];
            }
            kernel(a, b, output_buf);
            for (int j = 0; j < STREAMING_WIDTH; j++) {
                output[i + j] = output_buf[j];
            }
        }
    #endif

    return 0;
}

void kernel(DATA_TYPE* __restrict__ a, DATA_TYPE* __restrict__ b, DATA_TYPE* __restrict__ output)
/*   input :           input sample array */
/*   output:           output sample array */
{
    // #pragma unroll 8 vectorize(disable)//vectorize_width(4)
    #pragma clang loop unroll_count(1) vectorize(enable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = Convert(a[i]);
        DATA_TYPE bi = Convert(b[i]);
        DATA_TYPE xx = (DATA_TYPE)(const1) * (x + (DATA_TYPE)(const2) * x * x * x);
        DATA_TYPE exp_2x = exp(xx);
        DATA_TYPE tanh_x = ((DATA_TYPE)(const4) - exp_2x) / ((DATA_TYPE)(const4) + exp_2x);
        DATA_TYPE gelu_ai = (DATA_TYPE)(const5) * x * ((DATA_TYPE)(const4) + tanh_x);
        output[i] = Convert(bi * gelu_ai);
    }
}