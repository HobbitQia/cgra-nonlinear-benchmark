#include "../include/utils.h"

float a[NTAPS];
float b[NTAPS];
float output[NTAPS];

void kernel(float a[], float b[], float output[]);

int main()
{

  kernel(a, b, output);

  return 0;
}

void kernel(float a[], float b[], float output[])
/*   input :           input sample array */
/*   output:           output sample array */
{
    #pragma clang loop unroll_count(1) vectorize(disable)//vectorize_width(4)
    for (int i = 0; i < NTAPS; i++) {
        float ai = a[i];
        float bi = b[i];
        output[i] = ai * sigmoid(bi);
    }
}