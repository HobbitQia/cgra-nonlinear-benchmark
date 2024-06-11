#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 0.2;
float beta = 0.1;

const float eps = 1e-5;

void kernel(float input[], float output[], float alpha, float beta);

int main()
{

  kernel(input, output, alpha, beta);

  return 0;
}

void kernel(float input[], float output[], float alpha, float beta)
/*   input :           input sample array */
/*   output:           output sample array */
{
    float mean = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        mean += input[i];
    }
    mean /= NTAPS;
    float variance = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i] - mean;
        variance += x * x;
    }
    variance /= NTAPS;
    float var_eps = variance + eps;
    float inv_stddev = invsqrt(var_eps);
    for (int i = 0; i < NTAPS; i++) {
        output[i] = (input[i] - mean) * inv_stddev * alpha + beta;
    }
}