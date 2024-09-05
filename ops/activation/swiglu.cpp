#include "../include/utils.h"

DATA_TYPE a[NTAPS], b[NTAPS], output[NTAPS];

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
    // #pragma unroll 4 vectorize(disable)//vectorize_width(4)
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE ai = Convert(a[i]);
        DATA_TYPE bi = Convert(b[i]);
        DATA_TYPE silu_ai = ai * sigmoid(ai);
        output[i] = Convert(bi * sigmoid(silu_ai));
    }
}