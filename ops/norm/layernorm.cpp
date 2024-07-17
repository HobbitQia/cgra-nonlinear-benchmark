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
    // Original Verison
    /*
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        mean += x;
        mean_x2 += x * x;
    }
    */
    #pragma clang loop unroll(disable) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        // float x1 = input[i+1];
        // float x2 = input[i+2];
        // float x3 = input[i+3];
        mean += x0;
        mean_x2 += x0 * x0;
        // mean += (x0 + x1) + (x2 + x3);
        // mean_x2 += (x0 * x0 + x1 * x1) + (x2 * x2 + x3 * x3);
    }
    mean /= NTAPS;
    mean_x2 /= NTAPS;
    float variance = mean_x2 - mean * mean;

    float var_eps = variance + eps;
    float inv_stddev = invsqrt(var_eps);
    #pragma clang loop unroll(disable) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i] - mean;
        output[i] = x * inv_stddev * alpha + beta;
    }
}