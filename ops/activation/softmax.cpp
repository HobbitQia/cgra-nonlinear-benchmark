#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];

void kernel(float input[], float output[]);

int main()
{

  kernel(input, output);

  return 0;
}

void kernel(float input[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    float max = -10000.0;
    float sum = 0.0;
    // Original Verison
    /*
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        if (x > max) max = x;
    }
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        float e = exp(x - max);
        output[i] = e;
        sum += e;
    }
    */
    #pragma clang loop unroll(disable) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        float x0 = input[i];
        // float x1 = input[i+1];
        // float x2 = input[i+2];
        // float x3 = input[i+3];
        // float maxx = max(max(x0, x1), max(x2, x3));
        // if (maxx > max) max = maxx;
        if (x0 > max) max = x0;
    }
    #pragma clang loop unroll(disable) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        // float x = input[i];
        float x0 = input[i];
        // float x1 = input[i+1];
        // float x2 = input[i+2];
        // float x3 = input[i+3];
        float e0 = exp(x0 - max);
        // float e1 = exp(x1 - max);
        // float e2 = exp(x2 - max);
        // float e3 = exp(x3 - max);
        output[i] = e0;
        // output[i+1] = e1;
        // output[i+2] = e2;
        // output[i+3] = e3;
        sum += e0;
        // sum += (e0 + e1) + (e2 + e3);
    }
    #pragma clang loop unroll(disable) vectorize(disable)
    for (int i = 0; i < NTAPS; i++) {
        output[i] /= sum;
    }
}