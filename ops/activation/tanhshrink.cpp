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
        float exp_2x = exp(x * (float)(-2.0));
        output[i] = x - ((float)(1.0) - exp_2x) / ((float)(1.0) + exp_2x);
    }
}