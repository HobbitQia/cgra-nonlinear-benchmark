#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

const float beta = 1.0;

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
        float softplus_x = (1.0 / beta) * log(1.0 + exp(beta * x));
        float exp_2x = exp(softplus_x * (-2.0));
        output[i] = x * (1.0 - exp_2x) / (1.0 + exp_2x);
    }
}