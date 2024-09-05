#include "../include/utils.h"

DATA_TYPE input[NTAPS], output[NTAPS];
//  0.79788456 0.044715  -2.0 1.0 0.5 
DATA_TYPE const0 = 0; 

void kernel(DATA_TYPE input[], DATA_TYPE output[]);

int main()
{
    DATA_TYPE input_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
    #ifndef __STREAMING_ENBALED__
        kernel(input, output);
    #else
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
    // #pragma unroll 6 vectorize(disable)//vectorize_width(4)
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < LOOP_LENGTH; i++) {
        DATA_TYPE x = Convert(input[i]);
        // const1 should be 2/sqrt pi * (-2)
        output[i] = Convert(max(x, const0));
    }
}