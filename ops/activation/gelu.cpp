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
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        float xx = 0.79788456 * (x + 0.044715 * x * x * x);
        float exp_2x = exp(-(xx * 2));
        float tanh_x = (1 - exp_2x) / (1 + exp_2x);
        output[i] = 0.5 * x * (1 + tanh_x);
    }
}