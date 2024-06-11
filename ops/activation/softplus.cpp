#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float beta = 0.1;

void kernel(float input[], float output[], float beta);

int main()
{

  kernel(input, output, beta);

  return 0;
}

void kernel(float input[], float output[], float beta)
/*   input :           input sample array */
/*   output:           output sample array */
{
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        output[i] = (1.0 / beta) * log(exp(beta * x));
    }
}