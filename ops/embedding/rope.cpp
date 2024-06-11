#include "../include/utils.h"

float input[NTAPS];
float output[NTAPS];
float theta = 0.2;

void kernel(float input[], float output[], int postion, float theta);

int main()
{

  kernel(input, output, 0, theta);

  return 0;
}

void kernel(float input[], float output[], int postion, float theta)
/*   input :           input sample array */
/*   output:           output sample array */
{
    for (int i = 0; i < NTAPS; i += 2) {
        float x = input[i];
        float y = input[i + 1];
        output[i] = x * cos(theta) - y * sin(theta);
        output[i + 1] = x * sin(theta) + y * cos(theta);
    }
}