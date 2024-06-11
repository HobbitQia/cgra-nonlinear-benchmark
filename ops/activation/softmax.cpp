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
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        if (x > max) max = x;
    }
    float sum = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        float e = exp(x - max);
        output[i] = e;
        sum += e;
    }
    for (int i = 0; i < NTAPS; i++) {
        output[i] /= sum;
    }
}