#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float negative_slope = -0.1;

void kernel(float input[], float output[], float negative_slope);

int main()
{

  kernel(input, output, negative_slope);

  return 0;
}

void kernel(float input[], float output[], float negative_slope)
/*   input :           input sample array */
/*   output:           output sample array */
{
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        if (x >= 0) output[i] = x;
        else output[i] = negative_slope * x;
    }
}