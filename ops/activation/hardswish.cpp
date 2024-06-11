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
    for (int i = 0; i < NTAPS; i++) {
        float x = input[i];
        if (x <= -3) output[i] = 0;
        else if (x >= 3) output[i] = x;
        else output[i] = x * (x + 3) / 6;
    }
}