#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float alpha = 0.2;
float beta = 0.1;

const float eps = 1e-5;

void layernorm_loop1(float input[], float *mean, float *mean_x2);
void layernorm_loop2(float input[], float *mean, float *invsqrt, float alpha, float beta);

int main()
{
    float mean = 0.0, mean_x2 = 0.0;
    layernorm_loop1(input, &mean, &mean_x2);
    mean /= NTAPS;
    mean_x2 /= NTAPS;
    float variance = mean_x2 - mean * mean;
    float var_eps = variance + eps;
    float inv_stddev = invsqrt(var_eps);
    layernorm_loop2(input, &mean, &inv_stddev, alpha, beta);

    return 0;
}

void layernorm_loop1(float input[], float *mean, float *mean_x2) 
{
    float meann = *mean;
    float meann_x2 = *mean_x2;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        meann += x0;
        meann_x2 += x0 * x0;
    }
    *mean = meann;
    *mean_x2 = meann_x2;
}

void layernorm_loop2(float input[], float *mean, float *invsqrt, float alpha, float beta) 
{
    float meann = *mean;
    float inv_stddev = *invsqrt;
    #pragma clang loop unroll_count(4) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i] - meann;
        output[i] = x * inv_stddev * alpha + beta;
    }
}