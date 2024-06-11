#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 0.1;

void kernel(float input[], float output[], float alpha);

int main()
{

  kernel(input, output, alpha);

  return 0;
}

void kernel(float input[], float output[], float alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        output[i] = max(0, x) + min(0, alpha * (exp(x / alpha) - 1));
    }
}