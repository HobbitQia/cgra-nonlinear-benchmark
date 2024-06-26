#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 1.67;
float scale = 1.05;

void kernel(float input[], float output[], float scale, float alpha);

int main()
{

  kernel(input, output, scale, alpha);

  return 0;
}

void kernel(float input[], float output[], float scale, float alpha)
/*   input :           input sample array */
/*   output:           output sample array */
{
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        output[i] = scale * (max(0, x)) + min(0, alpha * (exp(x) - 1));
    }
}