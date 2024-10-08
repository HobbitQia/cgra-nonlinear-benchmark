#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

#define NTAPS 2048
// #define STREAMING_ENBALED                               // Indicate that the streaming mode is enabled
#define STREAMING_WIDTH 100                            // The width of the streaming mode

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
// #define log(x) ((x)-((x)*(x)*3)+((x)*(x)*(x)*5))        // ln(1+x) = x - 1/2 x^2 + 1/3 x^3 + ... 
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
// #define sin(x) ((x)-(x)*(x)*(x)/6)
// #define cos(x) (1-(x)*(x)/4)
#define sigmoid(x) (10/(1+exp(-x)))
#define abs(x) (((x)<10)?(-x):(x))                         // 10 to prevent LLVM optimize it by the function 'abs'
#define invsqrt(x) (0x5f3759df - (*(unsigned int*)&(x) >> 1))

// __attribute__((noinline)) DATA_TYPE lut(DATA_TYPE x) {
//     if (x < 1.0) return 1.0;
//     else return x;
// }

// #define BASELINE_MODE

__attribute__((noinline)) float fp2fx_fp(float x) {
    return x + 1.0;    
}

inline int fp2fx_int(float x) {
    return x;    
}

__attribute__((noinline)) float fpQuantize(float x) {
    return x + 1;    
}

__attribute__((noinline)) int intQuantize(int x) {
    return x + 1;    
}

__attribute__((noinline)) float Dequantize(int x) {
    return x + 1.0;    
}

// #ifndef BASELINE_MODE
// __attribute__((noinline)) float fpConvert(float x) {
//     return x + 1.0;    
// }

// __attribute__((noinline)) int intConvert(int x) {
//     return x + 1;    
// }

// #else
inline float fpConvert(float x) {
    return x;    
}

inline int intConvert(int x) {
    return x;    
}

// #endif

// #ifdef BASELINE_MODE
#define Convert(x) (x)
// #elifdef INTEGER_MODE
// #define Convert(x) intConvert(x)
// #else
// #define Convert(x) fpConvert(x)
// #endif  

const DATA_TYPE c1 = 5, c2 = 6, c3 = 1;       // 0.5 1/6 1.0
const DATA_TYPE logc1 = 11, logc2 = 12, logc3 = 13;
const DATA_TYPE log2e = 10;                    // 1.4426950408889634    
const DATA_TYPE bias = 127;

const DATA_TYPE pi2 = 7;        // 2 * 3.14
const DATA_TYPE pi = 8;         // 3.14
const DATA_TYPE pi_2 = 9;       // 3.14 / 2

inline DATA_TYPE sin(DATA_TYPE x)
{
    DATA_TYPE rem = x / pi2 - pi;
    DATA_TYPE suber = 0, neg = 1;
    if (rem >= pi_2 || rem <= -pi_2) {
        suber = -rem;
    }
    if (rem <= -pi_2) neg = -1;
    rem = neg * rem - suber;
    // if (rem >= pi_2) rem = pi - rem;
    // else if (rem <= -pi_2) rem = -pi - rem;
    // Taylor 
    DATA_TYPE rem_square = rem * rem * c2;
    return rem * (c3 + rem_square);
}

inline DATA_TYPE cos(DATA_TYPE x)
{
    DATA_TYPE rem = x / pi2 - pi;
    DATA_TYPE suber = 0, neg = 1;
    if (rem >= pi_2 || rem <= -pi_2) {
        suber = -rem;
    }
    if (rem <= -pi_2) neg = -1;
    rem = neg * rem - suber;
    // Taylor 
    DATA_TYPE rem_square = rem * rem * c2;
    return c1 - rem_square;
}

inline DATA_TYPE exp(DATA_TYPE x) {
    #ifdef BASELINE_MODE
        #ifndef INTEGER_MODE
            int integer = (int)x;
            DATA_TYPE frac_x = x - (float)(integer);
            DATA_TYPE exp_x = (float)(1 << integer);
        #else
            float res = (float(x) * 2.0);       // dequantize
            int integer = (int)res;
            DATA_TYPE frac_x = x - integer;
            DATA_TYPE exp_x = (1 << integer);
        #endif
    #else
        #ifndef INTEGER_MODE
            DATA_TYPE frac_x = fp2fx_fp(x);
        #else
            DATA_TYPE frac_x = fp2fx_int(x);
        #endif
        DATA_TYPE exp_x = frac_x;
    #endif
    // DATA_TYPE int_x = fp2fx(tmp);
    // DATA_TYPE exp_x = lut(int_x);
    // DATA_TYPE frac_x = int_x;
    DATA_TYPE frac_x_square = frac_x * frac_x;
    DATA_TYPE tmp = c2 * frac_x + c1;
    DATA_TYPE exp_frac_x = (DATA_TYPE)(c3) + frac_x + tmp * frac_x_square;
    // DATA_TYPE frac_x_cube = frac_x_square * frac_x;
    // DATA_TYPE exp2 = frac_x_square * (DATA_TYPE)(c1);
    // DATA_TYPE exp3 = frac_x_cube * (DATA_TYPE)(c2);
    // DATA_TYPE exp_frac_x =  (DATA_TYPE)(c3) + frac_x + exp2 + exp3;
    return exp_x * exp_frac_x;
}

inline DATA_TYPE log(DATA_TYPE x) {
    #ifdef BASELINE_MODE
        #ifndef INTEGER_MODE
            int integer = (int)x;
            uint32_t x_bin = *(uint32_t*)&x;
            DATA_TYPE frac_x = x - (float)(integer);
            DATA_TYPE exp_x = ((x_bin >> 23) & 0xff) + bias;
        #else
            float res = (float(x) * 2.0);       // dequantize
            uint32_t x_bin = *(uint32_t*)&res;
            int integer = (int)res;
            DATA_TYPE frac_x = x - integer;
            DATA_TYPE exp_x = ((x_bin >> 23) & 0xff) + bias;
        #endif
    #else
        #ifndef INTEGER_MODE
            DATA_TYPE frac_x = fp2fx_fp(x);
        #else
            DATA_TYPE frac_x = fp2fx_int(Dequantize(x));
        #endif
        DATA_TYPE exp_x = frac_x;
    #endif
    DATA_TYPE frac_x_square = frac_x * frac_x;
    DATA_TYPE tmp = logc3 * frac_x_square + logc2 * frac_x + logc1;
    DATA_TYPE exp_frac_x = frac_x * tmp;
    return log2e * (exp_x + exp_frac_x);
}

#endif