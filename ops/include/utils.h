#ifndef __UTILS_H__
#define __UTILS_H__

#define NTAPS 32

#define exp(x) (1+(x)+((x)*(x)/2))
#define log(x) ((x)-((x)*(x)/2)+((x)*(x)*(x)/3)) 
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define sin(x) ((x)-(x)*(x)*(x)/6)
#define cos(x) (1-(x)*(x)/4)
#define sigmoid(x) (1/(1+exp(-x)))
#define abs(x) (((x)<0)?(-x):(x))
#define invsqrt(x) (0x5f3759df - (*(int*)&(x) >> 1))

#endif