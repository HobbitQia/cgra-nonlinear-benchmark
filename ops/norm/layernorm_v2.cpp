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
    float mean_x2 = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        mean += x;
        mean_x2 += x * x;
    }
    mean /= NTAPS;
    mean_x2 /= NTAPS;
    float variance = mean_x2 - mean * mean;

    float var_eps = variance + eps;
    float inv_stddev = invsqrt(var_eps);
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i] - mean;
        output[i] = x * inv_stddev * alpha + beta;
    }
}