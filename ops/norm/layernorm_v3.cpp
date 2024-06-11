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
    int welford_count = 0;
    float welford_mean = 0.0;
    float welford_m2 = 0.0;
    for (int i = 0; i < NTAPS; i++) {
        welford_count++;
        float x = input[i];
        float delta = x - welford_mean;
        welford_mean += delta / welford_count;
        float delta2 = x - welford_mean;
        welford_m2 += delta * delta2;
    }
    float var_eps = welford_m2 / welford_count + eps;      // div can be shift
    float inv_stddev = invsqrt(var_eps);
    for (int i = 0; i < NTAPS; i++) {
        output[i] = (input[i] - welford_mean) * inv_stddev * alpha + beta;
    }
}