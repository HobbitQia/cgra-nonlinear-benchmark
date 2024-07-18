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
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        float xx = (float)(0.79788456) * (x + (float)(0.044715) * x * x * x);
        float exp_2x = exp(xx * (float)(-2.0));
        float tanh_x = ((float)(1.0) - exp_2x) / ((float)(1.0) + exp_2x);
        output[i] = (float)(0.5) * x * ((float)(1.0) + tanh_x);
    }
}