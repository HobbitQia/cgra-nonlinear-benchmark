#include "../include/utils.h"

float a[NTAPS];
float b[NTAPS];
float output[NTAPS];

void kernel(float a[], float b[], float output[]);

int main()
{
    #ifndef __STREAMING_ENBALED__
        kernel(a, b, output);
    #else
        float a_buf[STREAMING_WIDTH], b_buf[STREAMING_WIDTH], output_buf[STREAMING_WIDTH];
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

void kernel(float a[], float b[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < NTAPS; i++) {
        float ai = a[i];
        float bi = b[i];
        output[i] = ai * sigmoid(bi);
    }
}