#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

void kernel(float input[], float output[]);
const float x = 3.0;

int main()
{

  kernel(input, output);

  return 0;
}

void kernel(float input[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    float max = 0.0;
    #pragma clang loop unroll_count(4) vectorize(disable)//vectorize_width(1)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        if (x0 > max) max = x0;
    }
    output[0] = max;
}