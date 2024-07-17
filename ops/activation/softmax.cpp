#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

void kernel(float input[], float output[]);

int main()
{

  kernel(input, output);

  return 0;
}

void kernel(float input[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    float max = -10000.0;
    float sum = 0.0;
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        if (x0 > max) max = x0;
    }
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        // float x = input[i];
        float x0 = input[i];
        float e0 = exp(x0 - max);
        output[i] = e0;
        sum += e0;
    }
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        output[i] /= sum;
    }
}