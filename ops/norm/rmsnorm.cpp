#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 0.2;

const float eps = 1e-5;

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
    float variance = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        variance += x * x;
    }
    variance /= NTAPS;;
    float inv_stddev = invsqrt(variance);
    for (int i = 0; i < NTAPS; i++) {
        output[i] = (input[i]) * inv_stddev * alpha;
    }
}