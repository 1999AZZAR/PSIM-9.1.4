/* Copyright (c) 2001-2009 by SoftIntegration, Inc. All Rights Reserved */
/************************************************************
* File name: math.h
************************************************************/
#ifndef _MATH_H_
#define	_MATH_H_

#define HUGE_VAL 1.797693134862315E+308 /* DBL_MAX */
#define HUGE     1.797693134862315E+308 /* DBL_MAX */

#define INFINITY Inf
#define NAN NaN 

#define FP_ILOGB0   _INT_MIN
#define FP_ILOGBNAN _INT_MAX

/* SVID & X/Open */
#define	M_E		2.7182818284590452354
#define	M_LOG2E		1.4426950408889634074
#define	M_LOG10E	0.43429448190325182765
#define	M_LN2		0.69314718055994530942
#define	M_LN10		2.30258509299404568402
#define	M_PI		3.14159265358979323846
#define	M_PI_2		1.57079632679489661923
#define	M_PI_4		0.78539816339744830962
#define	M_1_PI		0.31830988618379067154
#define	M_2_PI		0.63661977236758134308
#define	M_2_SQRTPI	1.12837916709551257390
#define	M_SQRT2		1.41421356237309504880
#define	M_SQRT1_2	0.70710678118654752440

/* the last 5 digits are to be verified, HHC */
#define	M_PI_180	0.01745329251994329547  /* PI/180 */
#define	M_180_PI        57.29577951308232286465 /* 180/PI */

#define FP_NAN          0
#define FP_INFINITE     1
#define FP_ZERO         2
#define FP_SUBNORMAL    3
#define FP_NORMAL       4

extern double log2(double x);

//extern int fpclassify(float);
//extern int isfinite(float);
//extern int isinf(float);
extern int isnan(float);
//extern int isnormal(float);
//extern int signbit(float);

extern double fmax(double x, double y);
extern double fmin(double x, double y);

extern double erf(double);
extern double erfc(double);
extern double gamma(double);
extern double hypot(double, double);
extern double j0(double);
extern double j1(double);
extern double jn(int, double);
extern double lgamma(double);
extern double y0(double);
extern double y1(double);
extern double yn(int, double);

extern double cbrt(double);
extern double logb(double);
extern double nextafter(double, double);
extern double remainder(double, double);
extern double scalb(double, double);
extern double copysign(double, double);
extern int ilogb(double);
extern double rint(double);
extern double scalbn(double, int);
extern int fpclassify(double);
extern int isfinite(double);
extern int isinf(double);
extern int isnormal(double);
extern int signbit(double);
 
extern double gamma_r(double, int *);
extern double lgamma_r(double, int *);

extern double round(double);


/* float type */
/*
extern float acosf(float x);
extern float asinf(float x);
extern float atanf(float x);
extern float atan2f(float y, float x);
extern float cosf(float x);
extern float sinf(float x);
extern float tanf(float x);
extern float acoshf(float x);
extern float asinhf(float x);
extern float atanhf(float x);
extern float coshf(float x);
extern float sinhf(float x);
extern float tanhf(float x);
extern float expf(float x);
extern float frexpf(float value, int *exp);
extern float ldexpf(float x, int exp);
extern float logf(float x);
extern float log10f(float x);
extern float logbf(float x);
extern float modff(float value, float *iptr);
extern float scalbnf(float x, int n);
extern float scalblnf(float x, long int n);
extern float cbrtf(float x);
extern float fabsf(float x);
extern float hypotf(float x, float y);
extern float powf(float x, float y);
extern float sqrtf(float x);
extern float erff(float x);
extern float erfcf(float x);
extern float lgammaf(float x);
extern float tgammaf(float x);
extern float ceilf(float x);
extern float floorf(float x);
extern float fmodf(float x, float y);
extern float remainderf(float x, float y);
extern float copysignf(float x, float y);
extern float fmaxf(float x, float y);
extern float fminf(float x, float y);
*/

#define isgreater(x, y) ((x)>(y))
#define isgreaterequal(x, y) ((x)>=(y))
#define isless(x, y) ((x)<(y))
#define islessequal(x, y) ((x)<=(y))
//#define islessgreater(x, y) ((x)<=(y) || (x)>=(y))
#define isequal(x, y) ((x)==<(y))
#define lround(X) ((long int) round(X))        // doesn't handle errno
#define llround(X) ((long long int) round(X))  // doesn't handle errno
#define islessgreater (x, y) ((x) != (y))      // incorrect for NaNs
#define isunordered (x, y) (isnan(x) || isnan(y))

/* generic functions  */
extern double acos(double x);
extern double asin(double x);
extern double atan(double x);
extern double atan2(double y, double x);
extern double cos(double x);
extern double sin(double x);
extern double tan(double x);
extern double acosh(double x);
extern double asinh(double x);
extern double atanh(double x);
extern double cosh(double x);
extern double sinh(double x);
extern double tanh(double x);
extern double exp(double x);
extern double frexp(double value, int *exp);
extern double ldexp(double x, int exp);
extern double log(double x);
extern double log10(double x);
extern double modf(double value, double *iptr);
extern double pow(double x, double y);
extern double sqrt(double x);
extern double ceil(double x);
extern double floor(double x);
extern double fmod(double x, double y);
extern double fabs(double xy);

#if defined(_CHDLL_)
#include <dlfcn.h>
extern void *_Chmath_handle = dlopen("libmath.dl", RTLD_LAZY);
#pragma exec _Chmath_handle?0:                           \
   fprintf(_stderr, "Error: dlopen(): %s\n", dlerror()), \
   fprintf(_stderr, "       cannot get _Chmath_handle in math.h\n");
void _dlclose_math(void) {
   dlclose(_Chmath_handle);
}
atexit(_dlclose_math);
#endif


#endif /* _MATH_H_ */
