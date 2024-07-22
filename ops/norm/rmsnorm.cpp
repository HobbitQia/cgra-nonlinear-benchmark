#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 0.2;

const float eps = 1e-5;

void rmsnorm_loop1(float input[], float *variance);
void rmsnorm_loop2(float input[], float output[], float *invsqrt, float alpha);

int main()
{
    float variance = 0.0;
    rmsnorm_loop1(input, &variance);
    variance /= NTAPS;
    float var_eps = variance + eps;
    float inv_stddev = invsqrt(var_eps);
    rmsnorm_loop2(input, output, &inv_stddev, alpha);

    return 0;
}

void rmsnorm_loop1(float input[], float *variance) 
{
    float var = *variance;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        var += x * x;
    }
    *variance = var;
}

void rmsnorm_loop2(float input[], float output[], float *invsqrt, float alpha) 
{
    float inv_stddev = *invsqrt;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        output[i] = (input[i]) * inv_stddev * alpha;
    }
}
