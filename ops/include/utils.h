#ifndef __UTILS_H__
#define __UTILS_H__

#define NTAPS 32

// #define exp(x) (1+(x)+((x)*(x)/2))
#define log(x) ((x)-((x)*(x)/2)+((x)*(x)*(x)/3))        // ln(1+x) = x - 1/2 x^2 + 1/3 x^3 + ... 
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define sin(x) ((x)-(x)*(x)*(x)/6)
#define cos(x) (1-(x)*(x)/4)
#define sigmoid(x) (1/(1+exp(-x)))
#define abs(x) (((x)<0)?(-x):(x))
#define invsqrt(x) (0x5f3759df - (*(unsigned int*)&(x) >> 1))

__attribute__((noinline)) float lut(float x) 
{
    if (x < 1.0) return 1.0;
    else return x;
}

__attribute__((noinline)) float fp2fx(float x) 
{
    return x + 1.0;    
}


inline float exp(float x) {
    float int_x = fp2fx(x);
    float exp_x = lut(int_x);
    float frac_x = int_x;
    float frac_x_square = frac_x * frac_x;
    float frac_x_cube = frac_x_square * frac_x;
    float exp2 = frac_x_square * (float)0.5;
    float exp3 = frac_x_cube * (float)(1.0/6.0);
    float exp_frac_x =  (float)(1.0) + frac_x + exp2 + exp3;
    return exp_x * exp_frac_x;
}

#endif