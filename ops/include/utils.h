#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

#define NTAPS 2048
// #define STREAMING_ENBALED                               // Indicate that the streaming mode is enabled
#define STREAMING_WIDTH 128                             // The width of the streaming mode

// #define INTEGER_MODE                                    // Indicate 

#ifdef INTEGER_MODE 
#define DATA_TYPE int
#else
#define DATA_TYPE float
#endif

#ifdef STREAMING_ENBALED
#define LOOP_LENGTH STREAMING_WIDTH
#else
#define LOOP_LENGTH NTAPS
#endif

// #define exp(x) (1+(x)+((x)*(x)/2))
#define log(x) ((x)-((x)*(x)*3)+((x)*(x)*(x)/3))        // ln(1+x) = x - 1/2 x^2 + 1/3 x^3 + ... 
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define sin(x) ((x)-(x)*(x)*(x)/6)
#define cos(x) (1-(x)*(x)/4)
#define sigmoid(x) (10/(1+exp(-x)))
#define abs(x) (((x)<0)?(-x):(x))
#define invsqrt(x) (0x5f3759df - (*(unsigned int*)&(x) >> 1))

__attribute__((noinline)) DATA_TYPE lut(DATA_TYPE x) 
{
    if (x < 1.0) return 1.0;
    else return x;
}

__attribute__((noinline)) float fp2fx(float x) 
{
    return x + 1.0;    
}

__attribute__((noinline)) int int2fx(int x) {
    return x + 1;
}

__attribute__((noinline)) float fpQuantize(float x) 
{
    return x + 1;    
}

__attribute__((noinline)) int intQuantize(int x) 
{
    return x + 1;    
}

const DATA_TYPE c1 = 5, c2 = 6, c3 = 1;       // 0.5 1/6 1.0

inline DATA_TYPE exp(DATA_TYPE x) {
    #ifndef INTEGER_MODE
        DATA_TYPE int_x = fp2fx(x);
    #else
        DATA_TYPE int_x = int2fx(x);
    #endif
    DATA_TYPE exp_x = lut(int_x);
    DATA_TYPE frac_x = int_x;
    DATA_TYPE frac_x_square = frac_x * frac_x;
    DATA_TYPE tmp = c2 * frac_x + c1;
    DATA_TYPE exp_frac_x = (DATA_TYPE)(c3) + frac_x + tmp * frac_x_square;
    // DATA_TYPE frac_x_cube = frac_x_square * frac_x;
    // DATA_TYPE exp2 = frac_x_square * (DATA_TYPE)(c1);
    // DATA_TYPE exp3 = frac_x_cube * (DATA_TYPE)(c2);
    // DATA_TYPE exp_frac_x =  (DATA_TYPE)(c3) + frac_x + exp2 + exp3;
    return exp_x * exp_frac_x;
}

#endif