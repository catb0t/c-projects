typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
       
       

extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern char *program_invocation_name, *program_invocation_short_name;

typedef int error_t;
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
typedef int __gwchar_t;

typedef struct
  {
    long int quot;
    long int rem;
  } imaxdiv_t;
extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));
extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));
extern intmax_t wcstoimax (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));
extern uintmax_t wcstoumax (const __gwchar_t *__restrict __nptr,
       __gwchar_t ** __restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


typedef float float_t;
typedef double double_t;

extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern void sincos (double __x, double *__sinx, double *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincos (double __x, double *__sinx, double *__cosx) __attribute__ ((__nothrow__ , __leaf__));

extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern double exp10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp10 (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double pow10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow10 (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));

extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));


extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));

extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));

extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double nextdown (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextdown (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double nextup (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextup (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));

extern int __issignaling (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));

extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern void sincosf (float __x, float *__sinx, float *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf (float __x, float *__sinx, float *__cosx) __attribute__ ((__nothrow__ , __leaf__));

extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern float exp10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp10f (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float pow10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __pow10f (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));

extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));


extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));

extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));

extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float nextdownf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextdownf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float nextupf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextupf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));

extern int __issignalingf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));

extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern void sincosl (long double __x, long double *__sinx, long double *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosl (long double __x, long double *__sinx, long double *__cosx) __attribute__ ((__nothrow__ , __leaf__));

extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern long double exp10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double pow10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __pow10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));

extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));


extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));

extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));

extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double nextdownl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextdownl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double nextupl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextupl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));

extern int __issignalingl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
extern int signgam;
enum
  {
    FP_NAN =
      0,
    FP_INFINITE =
      1,
    FP_ZERO =
      2,
    FP_SUBNORMAL =
      3,
    FP_NORMAL =
      4
  };
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;
extern _LIB_VERSION_TYPE _LIB_VERSION;
struct exception
  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };
extern int matherr (struct exception *__exc);


typedef long unsigned int size_t;
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
struct _IO_FILE;

typedef struct _IO_FILE FILE;


typedef struct _IO_FILE __FILE;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
struct _IO_jump_t; struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
};
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE {
  int _flags;
  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);
typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);
typedef int __io_close_fn (void *__cookie);
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef struct
{
  __io_read_fn *read;
  __io_write_fn *write;
  __io_seek_fn *seek;
  __io_close_fn *close;
} _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
struct _IO_cookie_file;
extern void _IO_cookie_init (struct _IO_cookie_file *__cfile, int __read_write,
        void *__cookie, _IO_cookie_io_functions_t __fns);
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_peekc_locked (_IO_FILE *__fp);
extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
typedef __off_t off_t;
typedef __off64_t off64_t;
typedef __ssize_t ssize_t;

typedef _G_fpos_t fpos_t;

typedef _G_fpos64_t fpos64_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;

extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern FILE *tmpfile (void) ;
extern FILE *tmpfile64 (void) ;
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;

extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);

extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;
extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;

extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));
extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));


extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));

extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));


extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));


extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);

extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);

extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);

extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);

extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;
extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;

extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);

extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) ;

extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);

extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);

extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void perror (const char *__s);

extern int sys_nerr;
extern const char *const sys_errlist[];
extern int _sys_nerr;
extern const char *const _sys_errlist[];
extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *popen (const char *__command, const char *__modes) ;
extern int pclose (FILE *__stream);
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
extern char *cuserid (char *__s);
struct obstack;
extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0)));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

typedef int wchar_t;

typedef enum
{
  P_ALL,
  P_PID,
  P_PGID
} idtype_t;

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;


__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;

extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;

extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

typedef struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
} *__locale_t;
typedef __locale_t locale_t;
extern long int strtol_l (const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
extern unsigned long int strtoul_l (const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
extern double strtod_l (const char *__restrict __nptr,
   char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern float strtof_l (const char *__restrict __nptr,
         char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern long double strtold_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;
extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;

typedef __clock_t clock_t;



typedef __time_t time_t;


typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
typedef int __sig_atomic_t;
typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
typedef __sigset_t sigset_t;
struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
union pthread_attr_t
{
  char __size[56];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    unsigned int __nusers;
    int __kind;
    short __spins;
    short __elision;
    __pthread_list_t __list;
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    signed char __rwelision;
    unsigned char __pad1[7];
    unsigned long int __pad2;
    unsigned int __flags;
  } __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;

extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));

extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));
extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;


extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

extern void cfree (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));

extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;

extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern char *secure_getenv (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) ;
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;

extern int system (const char *__command) ;

extern char *canonicalize_file_name (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;
typedef int (*__compar_fn_t) (const void *, const void *);
typedef __compar_fn_t comparison_fn_t;
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);

extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));

extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern void setkey (const char *__key) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int posix_openpt (int __oflag) ;
extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int getpt (void);
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern void *rawmemchr (const void *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern void *memrchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));
extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcasecmp_l (const char *__s1, const char *__s2,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strverscmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strfry (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void *memfrob (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *basename (const char *__filename) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

         
char* strchr_c (const char* const str, const char c);
char* strncat_c (const char* const a, const char* const b, const size_t maxlen);
char* vstrncat (const size_t argc, ...);
char* vstrncat_c (const size_t argc, ...);
char* make_empty_str (void);
void str_chomp (char* str);
char* readln (const size_t len);
char* input_prompt (const char* const prompt, const size_t len, const char* const other);
char* str_reverse (const char* const str);
char* str_copy (const char* const str);
char* str_repeat (const char* const str, const size_t times, size_t* out_len);
char** str_split (const char* const str, const char delim, size_t* out_len);
char* str_rm (const char* const str, const char* const omit, size_t* out_len);
char* concat_lines (char** string_lines, const size_t lines_len, const size_t total_len);
_Bool isEOL (const char* const str);
_Bool getint64 (int64_t* dest);
_Bool getuint64 (uint64_t* dest);
uint64_t pow_uint64 (uint64_t in, uint64_t power);
uint64_t* str_to_ull_array (
  const char* const str,
  const size_t len,
  const char* const remove_at,
  const char split_at,
        size_t* out_len
);
size_t str_count (const char* const haystack, const char* const needle);
size_t safestrnlen (const char* const str);
size_t udifference (const size_t x, const size_t y);
size_t usub (const size_t a, const size_t b);
size_t signed2un (const ssize_t val);
ssize_t un2signed (const size_t val);
ssize_t str_issubstring (const char* const a, const char* const b);
void free_ptr_array (void** array, const size_t len);
void _safefree (void* ptr, const uint64_t lineno, const char* const fname);
void _safefree_args (const uint64_t lineno, const char* const fname, const size_t argc, ...);
void* _safemalloc (const size_t len, const uint64_t lineno, const char* const fname);
void* _saferealloc (void* ptr, const size_t len, uint64_t lineno, const char* const fname);
void* _safecalloc (const size_t nmemb, const size_t len, uint64_t lineno, const char* const fname);
__attribute__ ((__pure__)) __attribute__ ((__const__))
size_t signed2un (const ssize_t val) {
  return val < 0 ? 0 : (size_t) val;
}
__attribute__ ((__pure__)) __attribute__ ((__const__))
ssize_t un2signed (const size_t val) {
  return (ssize_t) (val > ((18446744073709551615UL) / 2) ? (18446744073709551615UL) / 2 : val);
}
__attribute__ ((__pure__)) __attribute__ ((__const__))
size_t usub (const size_t a, const size_t b) {
  return signed2un(un2signed(a) - un2signed(b));
}
__attribute__ ((__pure__)) __attribute__ ((__const__))
size_t udifference (const size_t x, const size_t y) {
  return (x < y ? y - x : x - y);
}
void _safefree (void* ptr, const uint64_t lineno, const char* const fname) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 226, __func__);
  if (((void *)0) == ptr) {
    printf("You fool! You have tried to free() a null pointer! (line %" "l" "u" " func %s)\n", lineno, fname);
    ((((void *)0) != ptr) ? (void) (0) : __assert_fail ("NULL != ptr", "common", 230, __PRETTY_FUNCTION__));
  } else {
    free(ptr);
  }
}
void _safefree_args (const uint64_t lineno, const char* const fname, const size_t argc, ...) {
  va_list vl;
  __builtin_va_start(vl,argc);
  for (size_t i = 0; i < argc; i++) {
    void* ptr = __builtin_va_arg(vl,void*);
    if (((void *)0) == ptr) {
      printf(
        "You fool! You have tried to free() a null pointer!"
        " (line %" "l" "u" " func %s, arg #%zu to safefree_args)\n",
        lineno, fname, i
      );
      ((((void *)0) != ptr) ? (void) (0) : __assert_fail ("NULL != ptr", "common", 249, __PRETTY_FUNCTION__));
    } else {
      free(ptr);
    }
  }
  __builtin_va_end(vl);
}
void* _safemalloc (const size_t len, const uint64_t lineno, const char* const fname) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 261, __func__);
  void* mem = malloc(len);
  if (!mem) {
    printf("Couldn't malloc() %zu bytes (perhaps you have run out of memory?) (line %" "l" "u" " func %s)\n", len, lineno, fname);
    ((mem) ? (void) (0) : __assert_fail ("mem", "common", 266, __PRETTY_FUNCTION__));
  }
  if (12 == (*__errno_location ())) {
    perror("safefree");
    abort();
  }
  return mem;
}
void* _saferealloc (void* ptr, const size_t len, uint64_t lineno, const char* const fname) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 276, __func__);
  (void) fname, (void) lineno;
  void* mem = realloc(ptr, len);
  if (12 == (*__errno_location ())) {
    perror("saferealloc");
    abort();
  }
  return mem;
}
void* _safecalloc (const size_t nmemb, const size_t len, uint64_t lineno, const char* const fname) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 289, __func__);
  (void) fname, (void) lineno;
  void* mem = calloc(nmemb, len);
  if (12 == (*__errno_location ())) {
    perror("safecalloc");
    abort();
  }
  return mem;
}
void free_ptr_array (void** ptr, const size_t len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 301, __func__);
  for (size_t i = 0; i < len; i++) {
    _safefree((ptr[i]), 304, __func__);
  }
  _safefree((ptr), 306, __func__);
}
char* strchr_c (const char* const str, const char c) {
  char* nw = strndup(str, safestrnlen(str));
  while ( (++*nw) != c);
  return nw;
}
char* strncat_c (const char* const a, const char* const b, const size_t maxlen) {
  size_t tlen = safestrnlen(a) + safestrnlen(b),
         outlen = (tlen > maxlen ? maxlen : tlen) - 1;
  char* outbuf = (char *) _safemalloc((sizeof (char) * outlen), 319, __func__);
  snprintf(outbuf, outlen, "%s%s", a, b);
  return outbuf;
}
char* vstrncat (const size_t argc, ...) {
  va_list vl;
  __builtin_va_start(vl,argc);
  size_t tlen = 0;
  char** outbuf = (char * *) _safemalloc((sizeof (char *) * argc), 334, __func__);
  for (size_t i = 0; i < argc; i++) {
    char** v = (char * *) _safemalloc((sizeof (char *) * 1), 338, __func__);
    *v = __builtin_va_arg(vl,char*);
    size_t l = safestrnlen(*v);
    outbuf[i] = strndup(*v, l);
    tlen += l;
    _safefree((*v), 345, __func__), _safefree((v), 345, __func__);
  }
  __builtin_va_end(vl);
  return concat_lines(outbuf, argc, tlen);
}
char* vstrncat_c (const size_t argc, ...) {
  va_list vl;
  __builtin_va_start(vl,argc);
  size_t tlen = 0;
  char** outbuf = (char * *) _safemalloc((sizeof (char *) * argc), 361, __func__);
  for (size_t i = 0; i < argc; i++) {
    char* v = __builtin_va_arg(vl,char*);
    size_t l = safestrnlen(v);
    outbuf[i] = strndup(v, l);
    tlen += l;
    _safefree((v), 371, __func__);
  }
  __builtin_va_end(vl);
  return concat_lines(outbuf, argc, tlen);
}
ssize_t str_issubstring (const char* const a, const char* const b) {
  if ( ((void *)0) == a ) {
    if ( ((void *)0) == b ) {
      return 0;
    }
    return -1;
  }
  size_t lena = safestrnlen(a),
         lenb = safestrnlen(b);
  if ( ( !str_count(a, "\0") ) || (!str_count(b, "\0")) ) {
    (*__errno_location ()) = 22;
    perror(__func__);
    ((0) ? (void) (0) : __assert_fail ("false", "common", 393, __PRETTY_FUNCTION__));
  }
  ssize_t begin = -1, end;
  char *ca = strndup(a, lena),
       *cb = strndup(b, lenb);
  while ( (*++ca) != *cb ) {
    ++begin;
  }
  end = begin;
  while ( *ca == *cb ) {
    ++ca, ++cb, ++end;
  }
  if ( signed2un(end) != lenb ) {
    begin = -1;
  }
  _safefree((ca), 414, __func__), _safefree((cb), 414, __func__);
  return begin;
}
char* str_reverse (const char* const str) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 420, __func__);
  if (!str) { return ((void *)0); }
  size_t len = safestrnlen(str);
  char* newp = (typeof(newp)) _safemalloc((sizeof(char) * len), 425, __func__);
  size_t i;
  for (i = 0; i < len; i++) {
    newp[i] = str[ udifference(i + 1, len) ];
  }
  return newp;
}
void str_chomp (char* str) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 437, __func__);
  if (str && (strchr(str, '\n') != ((void *)0)) ) {
    str[ strcspn(str, "\n") ] = 0;
  }
}
char* readln (const size_t len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 446, __func__);
  char
    *buf = (typeof(buf)) _safemalloc((sizeof(char) * len), 449, __func__),
    *ret = fgets(buf, len > 0x7fffffff ? 0x7fffffff : (int) len, stdin);
  if ( ((void *)0) == ret ) {
    _safefree((buf), 453, __func__);
    buf = (char *) _safemalloc((sizeof (char) * 2), 454, __func__);
    snprintf(buf, 2, "%c", '\4');
  } else {
    str_chomp(buf);
  }
  ((((void *)0) != buf) ? (void) (0) : __assert_fail ("NULL != buf", "common", 461, __PRETTY_FUNCTION__));
  return buf;
}
char* input_prompt (const char* const prompt, const size_t len, char const* const retry_prt) {
  printf("%s", prompt);
  char* buf;
  const char* const retry = ((void *)0) == retry_prt ? "Retry (bad input): " : retry_prt;
  while ( 1 ) {
    buf = readln(len);
    if (4 == buf[0]) { _safefree((buf), 477, __func__); return make_empty_str(); }
    if ( buf[0] ) { return buf; }
    _safefree((buf), 480, __func__);
    printf("%s", retry);
  }
}
char* str_copy (const char* const str) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 488, __func__);
  size_t len = safestrnlen(str);
  char* newp = (char *) _safemalloc((sizeof (char) * len), 491, __func__);
  for (size_t i = 0; i < len; i++) {
    newp[i] = str[i];
  }
  return newp;
}
char** str_split (
  const char* str,
  const char delim,
        size_t* out_len
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 504, __func__);
  if (! str[0]) {
    (*__errno_location ()) = 22;
    return ((void *)0);
  }
  char delim_str[2],
       *scopy = strndup(str, 4096);
  snprintf(delim_str, 2, "%c", delim);
  size_t len = safestrnlen(str);
  size_t num_delim = str_count(str, delim_str);
  char** newp;
  if (0 == num_delim) {
    newp = (char * *) _safemalloc((sizeof (char *) * 1), 524, __func__);
    newp[0] = scopy;
    *out_len = 1;
  } else if (1 == num_delim) {
     newp = (typeof(newp)) _safemalloc((sizeof (char *) * 2), 531, __func__);
    size_t i;
    for (
      i = 0;
      (i < len) && str[i] != delim;
      i++
    );
    scopy[i] = '\0';
    newp[0] = scopy;
    newp[1] = &(scopy[i + 1]);
    *out_len = 2;
  } else {
    size_t num_pieces = num_delim + 1;
     newp = (char * *) _safemalloc((sizeof (char *) * num_pieces), 547, __func__);
    size_t i;
    char* token;
    for (
      i = 0;
      (token = strsep(&scopy, delim_str)) != ((void *)0);
      i++
    ) {
      fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "i: %zu, token: %s\n", i, token);
      newp[i] = token;
    }
    *out_len = i;
  }
  return newp;
}
char* str_rm (
  const char* str,
  const char* omit,
        size_t* out_len
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 577, __func__);
  size_t len_str = safestrnlen(str);
  const size_t len_newp = ( ( ( sizeof(char) * len_str ) - str_count(str, omit) ) );
  char* newp = (char *) _safemalloc((sizeof (char) * len_newp + 1), 582, __func__);
  char c[3];
  size_t i, j;
  for (i = 0, j = 0; j < len_newp; i++) {
    snprintf(c, 3, "%c%c", str[i], 0);
    if (!str_count(omit, c)) {
      newp[j] = str[i];
      j++;
    }
  }
  newp[j] = 0;
  *out_len = len_newp;
  return newp;
}
__attribute__ ((__pure__))
size_t str_count (
  const char* haystack,
  const char* needles
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 604, __func__);
  size_t s = 0;
  size_t len_haystack = safestrnlen(haystack),
         len_needles = safestrnlen(needles);
  for (size_t i = 0; i < len_haystack; i++) {
    for (size_t h = 0; h < len_needles; h++) {
      if (haystack[i] == needles[h]) {
         s++;
       }
    }
  }
  return s;
}
char* str_repeat (
  const char* const in_str,
  const size_t times,
  size_t* out_len
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 625, __func__);
  size_t in_len = safestrnlen(in_str);
  *out_len = in_len * times;
  char *out = (char *) _safemalloc((sizeof (char) * 1 + *out_len), 630, __func__),
    *bufptr = out;
  for (size_t i = 0; i < *out_len; i++) {
    (bufptr) += snprintf((bufptr), (in_len + 1), ("%s"), (in_str));;
  }
  return out;
}
__attribute__ ((__pure__))
size_t safestrnlen (const char* const str) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 643, __func__);
  return str != ((void *)0)? strnlen(str, 256) : 0;
}
__attribute__ ((__pure__))
_Bool isEOL (const char* str) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 651, __func__);
  return !str || !safestrnlen(str) || str[0] == '\n';
}
_Bool getint64 (int64_t* dest) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 657, __func__);
  char* in = readln(20);
  if (!in) {
    return 0;
  }
  *dest = strtoll(in, ((void *)0), 10);
  _safefree((in), 664, __func__);
  return 1;
}
_Bool getuint64 (uint64_t* dest) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 669, __func__);
  char* in = readln(20);
  if (!in) {
    return 0;
  }
  *dest = strtoull(in, ((void *)0), 10);
  _safefree((in), 676, __func__);
  return 1;
}
__attribute__ ((__const__)) __attribute__ ((__pure__))
uint64_t pow_uint64 (const uint64_t in, const uint64_t power) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 682, __func__);
  uint64_t out = 1;
  for (uint64_t i = 0; i < power; i++) {
    out *= in;
  }
  return out;
}
char* concat_lines (char** string_lines, const size_t lines_len, const size_t total_len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 692, __func__);
  char *output = (char *) _safemalloc((sizeof (char) * total_len + 1), 694, __func__),
       *bufptr = output;
  for (size_t i = 0; i < lines_len; i++) {
    char* tl = string_lines[i];
    fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "tl: %s len: %zu", tl, safestrnlen(tl));
    (bufptr) += snprintf((bufptr), (safestrnlen(tl) + 2), ("%s "), (tl));;
  }
  printf("o: %s total_len: %zu\n", output, total_len);
  free_ptr_array( (void **) string_lines, lines_len);
  return output;
}
char* make_empty_str (void) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "common", 711, __func__);
  char* out = (char *) _safemalloc((sizeof (char) * 1), 713, __func__);
  snprintf(out, 1, "%s", "");
  return out;
}
typedef enum {
  t_F,
  t_T,
  t_number,
  t_fixwid,
  t_string,
  t_func,
  t_array,
  t_assoc,
  t_hash,
  t_pair,
  t_realint,
  t_realuint,
  t_realchar,
  NUM_OBJTYPES
} objtype_t;
typedef enum {
  ER_NOT_A_TYPE,
  ER_KEYERROR,
  ER_INDEXERROR,
  ER_PTRMATH_BUG,
  ER_NULL_OBJECT,
  ER_NUM_ERRTYPES
} objerror_t;
typedef struct st_obj_t object_t;
typedef struct st_F_t F_t;
typedef struct st_T_t T_t;
typedef struct st_numb_t number_t;
typedef long double numderlying_t;
typedef struct st_fxwd_t fixwid_t;
typedef struct st_str_t string_t;
typedef struct st_array_t array_t;
typedef struct st_hash_t hash_t;
typedef struct st_pair_t pair_t;
typedef struct st_assoc_t assoc_t;
typedef struct st_fnc_t func_t;
struct st_F_t {
  void* nothing;
  size_t uid;
};
struct st_T_t {
  void* something;
  size_t uid;
};
struct st_fnc_t {
  char* code;
  char* name;
  size_t uid;
};
struct st_str_t {
  char* data;
  size_t len;
  size_t uid;
};
struct st_array_t {
  object_t** data;
  ssize_t idx;
  size_t uid;
};
struct st_numb_t {
  numderlying_t value;
  size_t uid;
};
struct st_fxwd_t {
  union {
    ssize_t value;
    size_t uvalue;
  };
  _Bool signed_active;
  size_t uid;
};
struct st_pair_t {
  object_t* car;
  object_t* cdr;
  size_t uid;
};
struct st_assoc_t {
  pair_t** data;
  ssize_t idx;
  size_t uid;
};
struct st_hash_t {
  array_t* keys;
  assoc_t* vals;
  assoc_t* idxs;
  size_t uid;
};
struct st_obj_t {
  objtype_t type;
  union {
    F_t* f;
    T_t* t;
    number_t* num;
    fixwid_t* fwi;
    string_t* str;
    func_t* fnc;
    array_t* ary;
    assoc_t* asc;
    hash_t* hsh;
    pair_t* cel;
  };
  size_t uid;
};
static const char* const OBJTYPE_2STRING [] = {
  "(False)",
  "(True)",
  "number_t",
  "fixwid_t",
  "string_t",
  "func_t",
  "array_t",
  "assoc_t",
  "hash_t",
  "pair_t",
  "ssize_t (fixwid_t.value)",
  "size_t (fixwid_t.uvalue)",
  "char* (string_t.data)"
};
_Static_assert(
  ( (sizeof OBJTYPE_2STRING) / (sizeof (char *)) == NUM_OBJTYPES),
  "OBJTYPE_2STRING has too few or too many values"
);
extern void _object_error (objerror_t error, const _Bool fatal, const char* const file, const uint64_t line, const char* const func, const char* fmt, ...);
extern _Bool _obj_failnull (const void* const o, const char* const file, const uint64_t line, const char* const func);
static inline __attribute__((warn_unused_result)) __attribute__ ((__pure__)) __attribute__ ((__const__)) size_t size_t_min (size_t a, size_t b) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "objcommon", 276, __func__); return a < b ? a : b; } int NOTHING_MINsize_t;
object_t* object_new (const objtype_t valtype, const void* const val);
object_t* object_copy (const object_t* const obj);
void** object_getval (const object_t* const obj);
char* object_repr (const object_t* const obj);
char* objtype_repr (const objtype_t t);
_Bool object_isinstance (const objtype_t t, const object_t* const o);
_Bool object_id_equals (const object_t* const a, const object_t* const b);
_Bool object_equals (const object_t* const a, const object_t* const b);
void object_destruct (object_t* obj);
void object_dtorn (object_t** const obj, const size_t len);
void object_destruct_args (size_t args, ...);
object_t* nothing_new (void);
object_t* something_new (void);
char* F_see (const F_t* const f);
char* T_see (const T_t* const t);
array_t* array_new_fromcptr (const void* const * const ptr, const size_t len, const objtype_t outtype);
array_t* array_new (const object_t* const * const objs, const size_t len);
array_t* array_copy (const array_t* const a);
array_t* array_concat (const array_t* const a, const array_t* const b);
array_t* array_vconcat (const array_t* const a, const size_t argc, ...);
char* array_see (const array_t* const a);
object_t* array_get_copy (const array_t* const a, const size_t idx, _Bool* ok);
object_t** array_get_ref (const array_t* const a, const size_t idx, _Bool* ok);
size_t array_length (const array_t* const a);
ssize_t array_find (const array_t* const a, const object_t* const obj);
_Bool array_isinbounds (const array_t* const a, const size_t idx);
_Bool array_equals (const array_t* const a, const array_t* const b);
_Bool array_isempty (const array_t* const a);
_Bool array_delete (array_t* const a, const size_t idx);
_Bool array_insert (array_t* const a, const object_t* const o, const size_t idx);
void array_append (array_t* const a, const object_t* const o);
void array_resize (array_t* const a, const size_t new_len);
void array_vappend (array_t* const a, const size_t argc, ...);
void array_inspect (const array_t* const a);
void array_destruct (array_t* const a);
void array_destruct_args (const size_t argc, ...);
void array_clear (array_t* const a);
string_t* string_new (const char* const str);
string_t* string_copy (const string_t* const s);
size_t string_length (const string_t* const s);
_Bool string_isinbounds (const string_t* const a, const size_t idx);
_Bool string_isempty (const string_t* const s);
void string_destruct (string_t* const s);
char* string_see (const string_t* const s);
void string_destruct_args (const size_t argc, ...);
hash_t* hash_new_skele (void);
hash_t* hash_new_boa (const array_t* const keys, const array_t* const vals);
hash_t* hash_copy (const hash_t* const h);
char* hash_see (const hash_t* const h);
object_t* hash_get_copy (const hash_t* const h, const object_t* const key, _Bool* ok);
object_t** hash_get_ref (const hash_t* const h, const object_t* const key, _Bool* ok);
array_t* hash_getvals (const hash_t* const h);
array_t* hash_getkeys (const hash_t* const h);
size_t hash_length (const hash_t* const h);
_Bool hash_add (hash_t* const h, const object_t* const key, const object_t* val);
_Bool hash_change_key (hash_t* const h, const object_t* const oldkey, const object_t* const newkey);
_Bool hash_change_at (hash_t* const h, const object_t* const obj, object_t* newval);
_Bool hash_equals (const hash_t* const a, const hash_t* const b);
_Bool hash_isempty (const hash_t* const h);
_Bool hash_keyexists (const hash_t* const h, const object_t* const key);
_Bool hash_exists (const hash_t* const h, const object_t* const key);
_Bool hash_delete (hash_t* const h, const object_t* const key);
void hash_destruct (hash_t* const h);
void hash_destruct_args (const size_t argc, ...);
void hash_inspect (const hash_t* const h);
void hash_unzip (const hash_t* const h, array_t** keys, array_t** vals);
pair_t* pair_new (const object_t* const car, const object_t* const cdr);
pair_t* pair_copy (const pair_t* const p);
char* pair_see (const pair_t* const p);
object_t* pair_car_copy (const pair_t* const p);
object_t* pair_cdr_copy (const pair_t* const p);
object_t** pair_car_ref (pair_t* const p);
object_t** pair_cdr_ref (pair_t* const p);
_Bool pair_equals (const pair_t* const a, const pair_t* const b);
void pair_destruct (pair_t* const p);
void pair_destruct_args (const size_t argc, ...);
void pair_cons (pair_t* const p, const object_t* cdr);
assoc_t* assoc_new (const array_t* const a, const array_t* const b);
assoc_t* assoc_new_fromcptr (const void * const * const ct_car, const void * const * const ct_cdr, const size_t len, const objtype_t car_conv_to, const objtype_t cdr_conv_to);
assoc_t* assoc_copy (const assoc_t* const a);
assoc_t* assoc_concat (const assoc_t* const a, const assoc_t* const b);
assoc_t* assoc_vconcat (const assoc_t* const a, const size_t argc, ...);
char* assoc_see (const assoc_t* const a);
pair_t* assoc_get_copy (const assoc_t* const a, const size_t idx, _Bool* ok);
pair_t** assoc_get_ref (const assoc_t* const a, const size_t idx, _Bool* ok);
size_t assoc_length (const assoc_t* const a);
ssize_t assoc_schreg (const assoc_t* const a, const object_t* const obj, object_t** (* reg_get_func) (pair_t* const p));
ssize_t assoc_schreg_1st (const assoc_t* const a, const object_t* const obj, object_t** (* reg_get_func) (pair_t* const p));
_Bool assoc_equals (const assoc_t* const a, const assoc_t* const b);
_Bool assoc_isinbounds (const assoc_t* const a, const size_t idx);
_Bool assoc_isempty (const assoc_t* const a);
_Bool assoc_delete (assoc_t* const a, const size_t idx);
_Bool assoc_insert (assoc_t* const a, const pair_t* const p, const size_t idx);
_Bool assoc_insert_boa (assoc_t* const a, const object_t* const c, const object_t* const b, const size_t idx);
void assoc_append (assoc_t* const a, const pair_t* const o);
void assoc_unzip (const assoc_t* const a, array_t** keys, array_t** vals);
void assoc_resize (assoc_t* a, const size_t new_idx);
void assoc_append_boa (assoc_t* const a, const object_t* const car, const object_t* const cdr);
void assoc_vappend (assoc_t* const a, const size_t argc, ...);
void assoc_inspect (const assoc_t* const a);
void assoc_destruct (assoc_t* const a);
void assoc_destruct_args (const size_t argc, ...);
void assoc_clear (assoc_t* const a);
number_t* number_new (const long double val);
number_t* number_copy (const number_t* const n);
number_t* number_mul (const number_t* const a, const number_t* const b);
number_t* number_add (const number_t* const a, const number_t* const b);
number_t* number_sub (const number_t* const a, const number_t* const b);
number_t* number_divmod (const number_t* const a, const number_t* const b, number_t** mod_out);
number_t* number_pow (const number_t* const n, const number_t* const exp);
number_t* number_pmul (const numderlying_t a, const number_t* const b);
number_t* number_padd (const numderlying_t a, const number_t* const b);
number_t* number_psub (const numderlying_t a, const number_t* const b);
number_t* number_pdivmod (const numderlying_t a, const number_t* const b, number_t** mod_out);
number_t* number_ppow (const numderlying_t n, const number_t* const exp);
number_t* number_powp (const number_t* const n, const numderlying_t* const exp);
number_t* number_abs (const number_t* const n);
char* number_see (const number_t* const n);
_Bool number_eq (const number_t* const a, const number_t* const b);
_Bool number_gt (const number_t* const a, const number_t* const b);
_Bool number_lt (const number_t* const a, const number_t* const b);
void number_destruct (number_t* const n);
void number_destruct_args (const size_t argc, ...);
fixwid_t* fixwid_new (const ssize_t v, const size_t u, const _Bool sign);
fixwid_t* fixwid_copy (const fixwid_t* const n);
char* fixwid_see (const fixwid_t* const n);
void fixwid_destruct (fixwid_t* const n);
void fixwid_destruct_args (const size_t argc, ...);
_Bool fixwid_eq (const fixwid_t* const a, const fixwid_t* const b);
_Bool fixwid_gt (const fixwid_t* const a, const fixwid_t* const b);
_Bool fixwid_lt (const fixwid_t* const a, const fixwid_t* const b);
func_t* func_new (const char* const code, const char* const name);
func_t* func_copy (const func_t* const f);
char* func_see (const func_t* const f);
void func_destruct (func_t* const f);
void func_inspect (const func_t* const f);
_Bool func_equals (const func_t* const f);
void func_destruct_args (const size_t argc, ...);
__attribute__((warn_unused_result))
array_t* array_new (const object_t* const * const objs, const size_t len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 13, __func__);
  array_t* array = (array_t *) _safemalloc((sizeof (array_t) * 1), 15, __func__);
  array->data = ((void *)0);
  array->idx = -1;
  if ( len && objs ) {
    array->data = (object_t * *) _safemalloc((sizeof (object_t *) * 1), 20, __func__);
    for (size_t i = 0; i < len; i++) {
      array_append(array, objs[i]);
    }
  }
  static size_t uid = 0; ++uid; (array)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "array", uid);
  return array;
}
__attribute__((warn_unused_result))
array_t* array_new_fromcptr (const void* const * const ptr, const size_t len, const objtype_t conv_to) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 52, __func__);
  object_t** objs = (typeof(objs)) _safemalloc((sizeof(object_t *) * len), 54, __func__);
  for (size_t i = 0; i < len; i++) {
    objs[i] = object_new(conv_to, ptr[i] );
  }
  array_t* a = array_new( (const object_t * const * const) objs, len);
  object_dtorn(objs, len);
  return a;
}
__attribute__((warn_unused_result))
array_t* array_copy (const array_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 76, __func__);
  _obj_failnull((a), "array", 78, __func__);
  if (array_isempty(a)) { return array_new(((void *)0), 0); }
  return array_new(
    (const object_t* const * const) a->data,
    array_length(a)
  );
}
void array_destruct (array_t* const array) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 94, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "array", array->uid);
  if (((void *)0) != array->data) {
    object_dtorn(array->data, array_length(array));
  }
  _safefree((array), 102, __func__);
}
void array_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 105, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { array_t ** v = (typeof(v)) _safemalloc((sizeof ( array_t *)), 105, __func__); *v = __builtin_va_arg(vl,array_t*); array_destruct( *v ); _safefree((v), 105, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3array;
__attribute__ ((__pure__)) __attribute__ ((__const__)) __attribute__((warn_unused_result))
_Bool array_isempty (const array_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 115, __func__);
  _obj_failnull((a), "array", 117, __func__);
  return ( -1 == a->idx ) || (((void *)0) == a->data);
}
__attribute__ ((__pure__)) __attribute__ ((__const__)) __attribute__((warn_unused_result))
size_t array_length (const array_t* const a) {
  return signed2un(a->idx + 1);
}
_Bool array_isinbounds (const array_t * const iter, const size_t idx) { return idx <= signed2un((iter)->idx); } int ____DONT_FIND_THIS_NAME44array;
void array_resize (array_t* const a, const size_t new_len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 136, __func__);
  _obj_failnull((a), "array", 138, __func__);
  if ( ! new_len ) {
    object_dtorn(a->data, array_length(a));
    a->data = ((void *)0);
    a->idx = -1;
    return;
  }
  if (new_len < array_length(a)) {
    for (size_t i = new_len + 1; i < array_length(a); i++) {
      object_destruct( *array_get_ref(a, i, ((void *)0)) );
    }
  }
  a->data = (typeof(a->data)) _saferealloc((a->data), (sizeof (object_t*) * new_len), 155, __func__);
  a->idx = un2signed(new_len) - 1;
}
__attribute__((warn_unused_result))
_Bool array_delete (array_t* const a, const size_t idx) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 173, __func__);
  _obj_failnull((a), "array", 175, __func__);
  ssize_t sidx = un2signed(idx);
  if ( idx > array_length(a) || array_isempty(a) ) {
    _object_error ((ER_INDEXERROR), (0), "array", 189, __func__, "delete index %zd but the highest is %zd%s", idx, a->idx, array_isempty(a) ? " (delete from empty array)" : "");
    return 0;
  }
  object_destruct( *array_get_ref(a, idx, ((void *)0)));
  if ( sidx != a->idx ) {
    for (ssize_t i = sidx; i < (a->idx); i++) {
      (a->data) [i] = (a->data) [i + 1];
    }
  }
  array_resize(a, array_length(a) - 1);
  return 1;
}
void array_clear (array_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 211, __func__);
  _obj_failnull((a), "array", 213, __func__);
  array_resize(a, 0);
}
__attribute__((warn_unused_result))
_Bool array_insert (array_t* const a, const object_t* const o, const size_t idx) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 230, __func__);
  _obj_failnull((a), "array", 232, __func__);
  const size_t len = array_length(a);
  if ( idx > len ) {
    _object_error ((ER_INDEXERROR), (0), "array", 243, __func__, "insert to index %zu above highest %zu", idx, len);
    return 0;
  }
  array_resize(a, len + 1);
  for (size_t i = usub(array_length(a), 1); i > idx; i--) {
    (a->data) [i] = (a->data) [i - 1];
  }
  (a->data) [idx] = object_copy(o);
  return 1;
}
void array_append (array_t* const a, const object_t* const o) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 267, __func__);
  _obj_failnull((a), "array", 269, __func__);
  array_resize(a, array_length(a) + 1);
  (a->data) [a->idx] = object_copy(o);
}
void array_vappend (array_t* const a, const size_t argc, ...) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 279, __func__);
  _obj_failnull((a), "array", 281, __func__);
  va_list vl;
  __builtin_va_start(vl,argc);
  for (size_t i = 0; i < argc; i++) {
    object_t** v = (typeof(v)) _safemalloc((sizeof (object_t *)), 288, __func__);
    *v = __builtin_va_arg(vl,object_t*);
    array_append(a, *v);
    _safefree((v), 292, __func__);
  }
  __builtin_va_end(vl);
}
__attribute__((warn_unused_result))
array_t* array_concat (const array_t* const a, const array_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 303, __func__);
  _obj_failnull((a), "array", 305, __func__);
  _obj_failnull((b), "array", 306, __func__);
  if ( array_isempty(a) && array_isempty(b) ) {
    return array_new(((void *)0), 0);
  }
  else if ( array_isempty(a) || array_isempty(b) ) {
    if ( array_isempty(a) ) {
      return array_copy(b);
    }
    return array_copy(a);
  }
  array_t* c = array_copy(a);
  for (size_t i = 0; i < array_length(b); i++) {
    array_append(c, *array_get_ref(b, i, ((void *)0)) );
  }
  return c;
}
__attribute__((warn_unused_result))
array_t* array_vconcat (const array_t* const a, const size_t argc, ...) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 335, __func__);
  _obj_failnull((a), "array", 337, __func__);
  va_list vl;
  __builtin_va_start(vl,argc);
  array_t* c = array_copy(a);
  for (size_t i = 0; i < argc; i++) {
    array_t** v = (typeof(v)) _safemalloc((sizeof (array_t *)), 346, __func__);
    *v = __builtin_va_arg(vl,array_t*);
    c = array_concat(c, *v);
    _safefree((v), 350, __func__);
  }
  __builtin_va_end(vl);
  return c;
}
__attribute__((warn_unused_result)) __attribute__ ((__pure__)) __attribute__ ((__const__))
char* array_see (const array_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 368, __func__);
  _obj_failnull((a), "array", 370, __func__);
  char *outbuf = (typeof(outbuf)) _safemalloc((6), 372, __func__),
       *bufptr = outbuf;
  (bufptr) += snprintf((bufptr), (3), ("%s "), ("{"));;
  if ( array_isempty(a) ) {
    (bufptr) += snprintf((bufptr), (2), ("%s"), ("}"));;
    return outbuf;
  }
  size_t total_len = safestrnlen(outbuf);
  for (size_t i = 0; i < array_length(a); i++) {
    object_t** thisp = array_get_ref(a, i, ((void *)0));
    char* strthis = object_repr(*thisp);
    size_t tlen = safestrnlen(strthis) + 2;
    outbuf = (typeof(outbuf)) _saferealloc((outbuf), (total_len + tlen), 390, __func__);
    bufptr = outbuf + total_len;
    (bufptr) += snprintf((bufptr), (tlen), ("%s "), (strthis));;
    total_len = safestrnlen(outbuf);
    _safefree((strthis), 396, __func__);
  }
  total_len = safestrnlen(outbuf);
  outbuf = (typeof(outbuf)) _saferealloc((outbuf), (total_len + 3), 402, __func__);
  bufptr = outbuf + total_len;
  (bufptr) += snprintf((bufptr), (3), ("%s"), ("}"));;
  return outbuf;
}
void array_inspect (const array_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 411, __func__);
  _obj_failnull((a), "array", 413, __func__);
  printf("array uid:%zu idx:%zd {\n", a->uid, a->idx);
  for (size_t i = 0; i < array_length(a); i++) {
    char* x = object_repr( *array_get_ref(a, i, ((void *)0)) );
    printf("\t%zu: %s\n", i, x);
    _safefree((x), 420, __func__);
  }
  puts("}\n");
}
__attribute__((warn_unused_result)) __attribute__ ((__pure__)) __attribute__ ((__const__))
ssize_t array_find (const array_t* const a, const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 432, __func__);
  _obj_failnull((a), "array", 434, __func__);
  for (size_t i = 0; i < array_length(a); i++) {
    if ( object_equals(obj, *array_get_ref(a, i, ((void *)0)) )) {
      return un2signed(i);
    }
  }
  return -1;
}
__attribute__((warn_unused_result))
object_t* array_get_copy (const array_t* const a, const size_t idx, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 458, __func__);
  _obj_failnull((a), "array", 460, __func__);
  if (((void *)0) != ok) { *ok = 1; }
  if ( array_isempty(a) || ( un2signed(idx) > a->idx ) ) {
    if (((void *)0) != ok) { *ok = 0; }
    return nothing_new();
  }
  return object_copy( *array_get_ref(a, idx, ok) );
}
__attribute__((warn_unused_result)) __attribute__ ((__const__))
object_t** array_get_ref (const array_t* const a, const size_t idx, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 484, __func__);
  _obj_failnull((a), "array", 486, __func__);
  if (((void *)0) != ok) { *ok = 1; }
  if ( array_isempty(a) || un2signed(idx) > a->idx ) {
    if (((void *)0) != ok) { *ok = 0; }
    _object_error ((ER_INDEXERROR), (0), "array", 502, __func__, "get elt %zu from highest %zd%s", idx, a->idx, array_isempty(a) ? " (get from empty array)" : "");
    return ((void *)0);
  }
  return &( (a->data) [idx] );
}
__attribute__((warn_unused_result)) __attribute__ ((__pure__)) __attribute__ ((__const__))
_Bool array_equals (const array_t* const a, const array_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "array", 521, __func__);
  _obj_failnull((a), "array", 523, __func__);
  if ( array_isempty(a) && array_isempty(b) ) {
    return 1;
  }
  if ( array_length(a) != array_length(b) ) {
    return 0;
  }
  for (size_t i = 0; i < array_length(a); i++) {
    object_t **oa = array_get_ref(a, i, ((void *)0)),
             **ob = array_get_ref(b, i, ((void *)0));
    if ( ! object_equals(*oa, *ob) ) {
      return 0;
    }
  }
  return 1;
}
assoc_t* assoc_new (const array_t* const a, const array_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 10, __func__);
  assoc_t* assoc = (assoc_t *) _safemalloc((sizeof (assoc_t) * 1), 12, __func__);
  assoc->idx = -1;
  assoc->data = ((void *)0);
  if ( a && b ) {
    size_t idx = size_t_min(array_length(a), array_length(b));
    assoc->data = (pair_t* *) _safemalloc((sizeof (pair_t*) * idx + 1), 21, __func__);
    for (size_t i = 0; i < idx; i++) {
      object_t
        **car = array_get_ref(a, i, ((void *)0)),
        **cdr = array_get_ref(b, i, ((void *)0));
      assoc_append_boa(assoc, *car, *cdr);
    }
  }
  static size_t uid = 0; ++uid; (assoc)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "assoc", uid);
  return assoc;
}
assoc_t* assoc_new_fromcptr (const void * const * const ct_car, const void * const * const ct_cdr, const size_t len, const objtype_t car_conv_to, const objtype_t cdr_conv_to) {
  assoc_t* out = assoc_new(((void *)0), ((void *)0));
  for (size_t i = 0; i < len; i++) {
    object_t *a = object_new(car_conv_to, ct_car[i]), *b = object_new(cdr_conv_to, ct_cdr[i]);
    assoc_append_boa(out, a, b);
    object_destruct_args(2, a, b);
  }
  return out;
}
assoc_t* assoc_copy (const assoc_t* const asc) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 69, __func__);
  _obj_failnull((asc), "assoc", 71, __func__);
  array_t *a, *b;
  assoc_unzip(asc, &a, &b);
  assoc_t* c = assoc_new(a, b);
  array_destruct_args(2, a, b);
  return c;
}
void assoc_destruct (assoc_t* const assoc) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 82, __func__);
  _obj_failnull((assoc), "assoc", 84, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "assoc", assoc->uid);
  if (((void *)0) != assoc->data) {
    for (size_t i = 0; i < assoc_length(assoc); i++) {
      pair_destruct( *assoc_get_ref(assoc, i, ((void *)0)) );
    }
    _safefree((assoc->data), 93, __func__);
  }
  _safefree((assoc), 96, __func__);
}
void assoc_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 99, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { assoc_t ** v = (typeof(v)) _safemalloc((sizeof ( assoc_t *)), 99, __func__); *v = __builtin_va_arg(vl,assoc_t*); assoc_destruct( *v ); _safefree((v), 99, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3assoc;
void assoc_unzip (const assoc_t* a, array_t** car, array_t** cdr) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 107, __func__);
  _obj_failnull((a), "assoc", 109, __func__);
  if ( car && cdr ) {
    *car = array_new(((void *)0), 0),
    *cdr = array_copy(*car);
    for (size_t i = 0; i < assoc_length(a); i++) {
      pair_t** p = assoc_get_ref(a, i, ((void *)0));
      array_append(*car, *pair_car_ref( *p ) ),
      array_append(*cdr, *pair_cdr_ref( *p ) );
    }
  }
}
size_t assoc_length (const assoc_t* const a) {
  return signed2un(a->idx + 1);
}
_Bool assoc_isinbounds (const assoc_t * const iter, const size_t idx) { return idx <= signed2un((iter)->idx); } int ____DONT_FIND_THIS_NAME44assoc;
pair_t** assoc_get_ref (const assoc_t* const a, const size_t idx, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 137, __func__);
  _obj_failnull((a), "assoc", 139, __func__);
  if (ok) { *ok = 1; }
  if (assoc_isempty(a) || un2signed(idx) > a->idx) {
    if (ok) { *ok = 0; }
    _object_error ((ER_INDEXERROR), (0), "assoc", 156, __func__, "get elt %zu from highest %zd%s", idx, a->idx, assoc_isempty(a) ? " (get from empty assoc)" : "");
    return ((void *)0);
  }
  return &( a->data [idx] );
}
pair_t* assoc_get_copy (const assoc_t* const a, const size_t idx, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 167, __func__);
  pair_t** p = assoc_get_ref(a, idx, ok);
  if (((void *)0) == p || ( ! ok )) {
    return pair_new(((void *)0), ((void *)0));
  }
  return pair_copy( *p );
}
void assoc_append_boa (assoc_t* const a, const object_t* const car, const object_t* const cdr) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 182, __func__);
  pair_t* p = pair_new(car, cdr);
  assoc_append(a, p);
  pair_destruct(p);
}
void assoc_append (assoc_t* const a, const pair_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 196, __func__);
  _obj_failnull((a), "assoc", 198, __func__);
  assoc_resize(a, assoc_length(a) + 1);
  (a->data) [a->idx] = pair_copy(b);
}
__attribute__((warn_unused_result))
_Bool assoc_insert (assoc_t* const a, const pair_t* const p, const size_t idx) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 206, __func__);
  _obj_failnull((a), "assoc", 208, __func__), _obj_failnull((p), "assoc", 208, __func__);
  const size_t len = assoc_length(a);
  if (idx > len) {
    _object_error ((ER_INDEXERROR), (0), "assoc", 220, __func__, "insert to index %zu above highest %zu%s", idx, len, len ? " (insert to empty assoc)" : "");
    return 0;
  }
  assoc_resize(a, len + 1);
  for (size_t i = usub(assoc_length(a), 1); i > idx; i--) {
    (a->data) [i] = (a->data) [i - 1];
  }
  (a->data) [idx] = pair_copy(p);
  return 1;
}
__attribute__((warn_unused_result))
_Bool assoc_insert_boa (assoc_t* const a, const object_t* const car, const object_t* const cdr, const size_t idx) {
  pair_t* const p = pair_new(car, cdr);
  _Bool res = assoc_insert(a, p, idx);
  pair_destruct(p);
  return res;
}
void assoc_clear (assoc_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 247, __func__);
  _obj_failnull((a), "assoc", 249, __func__);
  assoc_resize(a, 0);
}
void assoc_resize (assoc_t* const a, const size_t new_len) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 260, __func__);
  _obj_failnull((a), "assoc", 262, __func__);
  if ( ! new_len ) {
    a->data = (typeof(a->data)) _saferealloc((a->data), (0), 266, __func__);
    a->idx = -1;
    return;
  }
  if (new_len < assoc_length(a)) {
    for (size_t i = new_len + 1; i < assoc_length(a); i++) {
      pair_destruct( *assoc_get_ref(a, i, ((void *)0)) );
    }
  }
  a->data = (typeof(a->data)) _saferealloc((a->data), (sizeof (pair_t*) * new_len), 279, __func__);
  a->idx = un2signed(new_len) - 1;
}
assoc_t* assoc_concat (const assoc_t* const a, const assoc_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 288, __func__);
  _obj_failnull((a), "assoc", 290, __func__);
  _obj_failnull((b), "assoc", 291, __func__);
  if ( assoc_isempty(a) && assoc_isempty(b) ) {
    return assoc_new(((void *)0), ((void *)0));
  }
  else if ( assoc_isempty(a) || assoc_isempty(b) ) {
    if ( assoc_isempty(a) ) {
      return assoc_copy(b);
    }
    return assoc_copy(a);
  }
  assoc_t* c = assoc_copy(a);
  for (size_t i = 0; i < assoc_length(b); i++) {
    assoc_append(c, *assoc_get_ref(b, i, ((void *)0)) );
  }
  return c;
}
_Bool assoc_delete (assoc_t* const a, const size_t idx) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 320, __func__);
  _obj_failnull((a), "assoc", 322, __func__);
  const size_t olen = assoc_length(a), nlen = udifference(olen, 1);
  if (
    assoc_isempty(a)
    || idx > olen
  ) {
    _object_error ((ER_INDEXERROR), (0), "assoc", 339, __func__, "attempt to delete index %zu but the highest is %zd%s", idx, a->idx, olen ? "" : " (delete from empty assoc)");
    return 0;
  }
  pair_destruct( *assoc_get_ref(a, idx, ((void *)0)));
  if (idx != signed2un((a)->idx)) {
    for (size_t i = idx; i < nlen; i++) {
      (a->data) [i] = (a->data) [i + 1];
    }
  }
  assoc_resize(a, assoc_length(a) - 1);
  return 1;
}
char* assoc_see (const assoc_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 362, __func__);
  _obj_failnull((a), "assoc", 364, __func__);
  char *outbuf = (char *) _safemalloc((sizeof (char) * 7), 366, __func__),
       *bufptr = outbuf;
  (bufptr) += snprintf((bufptr), (4), ("%s "), ("a{"));;
  if ( assoc_isempty(a) ) {
    (bufptr) += snprintf((bufptr), (2), ("%s"), ("}"));;
    return outbuf;
  }
  size_t total_len = safestrnlen(outbuf);
  for (size_t i = 0; i < assoc_length(a); i++) {
    pair_t** thisp = assoc_get_ref(a, i, ((void *)0));
    char* strthis = pair_see(*thisp);
    size_t tlen = safestrnlen(strthis) + 2;
    outbuf = (typeof(outbuf)) _saferealloc((outbuf), (total_len + tlen), 384, __func__);
    bufptr = outbuf + total_len;
    (bufptr) += snprintf((bufptr), (tlen), ("%s "), (strthis));;
    total_len = safestrnlen(outbuf);
    _safefree((strthis), 390, __func__);
  }
  total_len = safestrnlen(outbuf);
  outbuf = (typeof(outbuf)) _saferealloc((outbuf), (total_len + 3), 396, __func__);
  bufptr = outbuf + total_len;
  (bufptr) += snprintf((bufptr), (3), ("%s"), ("}"));;
  return outbuf;
}
void assoc_inspect (const assoc_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 408, __func__);
  printf("assoc uid:%zu idx:%zd sz:%zu {\n", a->uid, a->idx, sizeof a);
  for (size_t i = 0; i < assoc_length(a); i++) {
    char* s = pair_see( *assoc_get_ref(a, i, ((void *)0)) );
    printf("\t%zu:%s\n", i, s);
    _safefree((s), 415, __func__);
  }
  puts("}\n");
}
_Bool assoc_equals (const assoc_t* const a, const assoc_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 422, __func__);
  _obj_failnull((a), "assoc", 424, __func__), _obj_failnull((b), "assoc", 424, __func__);
  if (assoc_length(a) != assoc_length(b)) {
    return 0;
  }
  for (size_t i = 0; i < signed2un(a->idx); i++) {
    _Bool same = pair_equals(
      *assoc_get_ref(a, i, ((void *)0)),
      *assoc_get_ref(b, i, ((void *)0))
    );
    if (! same) {
      return 0;
    }
  }
  return 1;
}
_Bool assoc_isempty (const assoc_t* const a) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 448, __func__);
  _obj_failnull((a), "assoc", 450, __func__);
  return -1 == a->idx || ((void *)0) == a->data;
}
ssize_t assoc_schreg_1st (
  const assoc_t* const a,
  const object_t* const obj,
  object_t** (* reg_get_func) (pair_t* const p)
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "assoc", 461, __func__);
  _obj_failnull((obj), "assoc", 463, __func__);
  size_t len = assoc_length(a);
  for (size_t i = 0; i < len; i++) {
    if ( object_equals( obj, *reg_get_func( *assoc_get_ref(a, i, ((void *)0)) ) ) ) {
      return un2signed(i);
    }
  }
  return -1;
}
fixwid_t* fixwid_new (const ssize_t v, const size_t u, const _Bool signed_active) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 7, __func__);
  fixwid_t* fixwid = (typeof(fixwid)) _safemalloc((sizeof(fixwid_t)), 9, __func__);
  if (signed_active) {
    fixwid->value = v;
  } else {
    fixwid->uvalue = u;
  }
  fixwid->signed_active = signed_active;
  static size_t uid = 0; ++uid; (fixwid)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "fixwid", uid);
  return fixwid;
}
void fixwid_destruct (fixwid_t* const fixwid) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 25, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "fixwid", fixwid->uid);
  _safefree((fixwid), 28, __func__);
}
void fixwid_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 31, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { fixwid_t ** v = (typeof(v)) _safemalloc((sizeof ( fixwid_t *)), 31, __func__); *v = __builtin_va_arg(vl,fixwid_t*); fixwid_destruct( *v ); _safefree((v), 31, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3fixwid;
fixwid_t* fixwid_copy (const fixwid_t* const n) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 34, __func__);
  _obj_failnull((n), "fixwid", 36, __func__);
  ssize_t a = -1;
  size_t b = 0;
  if (n->signed_active) {
    a = n->value;
  } else {
    b = n->uvalue;
  }
  return fixwid_new(a, b, n->signed_active);
}
char* fixwid_see (const fixwid_t* const n) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 51, __func__);
  _obj_failnull((n), "fixwid", 53, __func__);
  char* buf = (typeof(buf)) _safemalloc((20 + 1), 55, __func__);
  if (n->signed_active) {
    snprintf( buf, 20 + 1, "%zd", n->value );
  } else {
    snprintf( buf, 20, "%zu", n->uvalue );
  }
  buf = (typeof(buf)) _saferealloc((buf), (safestrnlen(buf) + 1), 63, __func__);
  return buf;
}
_Bool fixwid_eq (const fixwid_t* const a, const fixwid_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 68, __func__);
  _obj_failnull((a), "fixwid", 70, __func__);
  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) == b->uvalue;
    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) == a->uvalue;
    }
    return 0;
  }
  return a->signed_active
    ? a->value == b->value
    : a->uvalue == b->uvalue;
}
_Bool fixwid_gt (const fixwid_t* const a, const fixwid_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 88, __func__);
  _obj_failnull((a), "fixwid", 90, __func__);
  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) > b->uvalue;
    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) < a->uvalue;
    }
    return 0;
  }
  return a->signed_active
    ? a->value > b->value
    : a->uvalue > b->uvalue;
}
_Bool fixwid_lt (const fixwid_t* const a, const fixwid_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "fixwid", 109, __func__);
  _obj_failnull((a), "fixwid", 111, __func__);
  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) < b->uvalue;
    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) > a->uvalue;
    }
    return 0;
  }
  return a->signed_active
    ? a->value < b->value
    : a->uvalue < b->uvalue;
}
func_t* func_new (const char* const code, const char* const name) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "func", 7, __func__);
  func_t* func = (typeof(func)) _safemalloc((sizeof (func_t)), 9, __func__);
  func->code = strndup(code, safestrnlen(code));
  func->name = strndup(name, safestrnlen(name));
  static size_t uid = 0; ++uid; (func)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "func", uid);
  return func;
}
func_t* func_copy (const func_t* const f) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "func", 19, __func__);
  _obj_failnull((f), "func", 21, __func__);
  return func_new(f->code, f->name);
}
void func_destruct (func_t* const func) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "func", 27, __func__);
  _obj_failnull((func), "func", 29, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "func", func->uid);
  _safefree((func->code), 33, __func__);
  _safefree((func->name), 34, __func__);
  _safefree((func), 35, __func__);
}
void func_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "func", 38, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { func_t ** v = (typeof(v)) _safemalloc((sizeof ( func_t *)), 38, __func__); *v = __builtin_va_arg(vl,func_t*); func_destruct( *v ); _safefree((v), 38, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3func;
char* func_see (const func_t* const f) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "func", 41, __func__);
  _obj_failnull((f), "func", 43, __func__);
  char *code = f->code,
       *name = f->name, *buf;
  size_t len = safestrnlen(code) + safestrnlen(name) + 2;
  buf = (typeof(buf)) _safemalloc((sizeof (char) * len), 49, __func__);
  snprintf(buf, len, "%s = [ %s ]", name, code);
  _safefree((code), 53, __func__), _safefree((name), 53, __func__);
  return buf;
}
typedef uint32_t Fnv32_t;
typedef uint64_t Fnv64_t;
enum fnv_type {
    FNV_NONE = 0,
    FNV0_32 = 1,
    FNV1_32 = 2,
    FNV1a_32 = 3,
    FNV0_64 = 4,
    FNV1_64 = 5,
    FNV1a_64 = 6,
};
struct test_vector {
    void *buf;
    int len;
};
struct fnv0_32_test_vector {
    struct test_vector *test;
    Fnv32_t fnv0_32;
};
struct fnv1_32_test_vector {
    struct test_vector *test;
    Fnv32_t fnv1_32;
};
struct fnv1a_32_test_vector {
    struct test_vector *test;
    Fnv32_t fnv1a_32;
};
struct fnv0_64_test_vector {
    struct test_vector *test;
    Fnv64_t fnv0_64;
};
struct fnv1_64_test_vector {
    struct test_vector *test;
    Fnv64_t fnv1_64;
};
struct fnv1a_64_test_vector {
    struct test_vector *test;
    Fnv64_t fnv1a_64;
};
extern Fnv32_t fnv_32_buf(void *buf, size_t len, Fnv32_t hashval);
extern Fnv32_t fnv_32_str(char *buf, Fnv32_t hashval);
extern Fnv32_t fnv_32a_buf(void *buf, size_t len, Fnv32_t hashval);
extern Fnv32_t fnv_32a_str(char *buf, Fnv32_t hashval);
extern Fnv64_t fnv_64_buf(void *buf, size_t len, Fnv64_t hashval);
extern Fnv64_t fnv_64_str(char *buf, Fnv64_t hashval);
extern Fnv64_t fnv_64a_buf(void *buf, size_t len, Fnv64_t hashval);
extern Fnv64_t fnv_64a_str(char *buf, Fnv64_t hashval);
extern struct test_vector fnv_test_str[];
extern struct fnv0_32_test_vector fnv0_32_vector[];
extern struct fnv1_32_test_vector fnv1_32_vector[];
extern struct fnv1a_32_test_vector fnv1a_32_vector[];
extern struct fnv0_64_test_vector fnv0_64_vector[];
extern struct fnv1_64_test_vector fnv1_64_vector[];
extern struct fnv1a_64_test_vector fnv1a_64_vector[];
extern void unknown_hash_type(char *prog, enum fnv_type type, int code);
extern void print_fnv32(Fnv32_t hval, Fnv32_t mask, int verbose, char *arg);
extern void print_fnv64(Fnv64_t hval, Fnv64_t mask, int verbose, char *arg);
typedef Fnv32_t hashkey_t;
hashkey_t hash_obj (const object_t* const obj);
hash_t* hash_new_skele (void) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 16, __func__);
  hash_t* hash = (typeof(hash)) _safemalloc((sizeof(hash_t)), 18, __func__);
  hash->keys = array_new(((void *)0), 0);
  hash->vals = assoc_new(((void *)0), ((void *)0));
  hash->idxs = assoc_new(((void *)0), ((void *)0));
  static size_t uid = 0; ++uid; (hash)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "hash", uid);
  return hash;
}
hash_t* hash_new_boa (
  const array_t* const keys,
  const array_t* const vals
) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 33, __func__);
  size_t len = size_t_min( array_length(keys), array_length(vals) );
  printf("minsize: %zd\n", len);
  hash_t* hash = hash_new_skele();
  for (size_t i = 0; i < len; i++) {
    object_t
      **k = array_get_ref(keys, i, ((void *)0)),
      **v = array_get_ref(vals, i, ((void *)0));
    if ( ! hash_add(hash, *k, *v) ) {
      break;
    }
  }
  return hash;
}
void hash_destruct (hash_t* const hash) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 57, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "hash", hash->uid);
  array_destruct(hash->keys);
  assoc_destruct(hash->vals);
  assoc_destruct(hash->idxs);
  _safefree((hash), 64, __func__);
}
void hash_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 67, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { hash_t ** v = (typeof(v)) _safemalloc((sizeof ( hash_t *)), 67, __func__); *v = __builtin_va_arg(vl,hash_t*); hash_destruct( *v ); _safefree((v), 67, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3hash;
hash_t* hash_copy (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 70, __func__);
  _obj_failnull((h), "hash", 72, __func__);
  array_t* values = hash_getvals(h);
  hash_t* copy = hash_new_boa(h->keys, values);
  array_destruct(values);
  return copy;
}
_Bool hash_isempty (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 84, __func__);
  _obj_failnull((h), "hash", 86, __func__);
  return ! hash_length(h);
}
__attribute__ ((__pure__)) __attribute__ ((__const__))
size_t hash_length (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 93, __func__);
  _obj_failnull((h), "hash", 95, __func__);
  return assoc_length(h->idxs);
}
hashkey_t hash_obj (const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 104, __func__);
  _obj_failnull((obj), "hash", 106, __func__);
  char* buf = object_repr(obj);
  hashkey_t hval = fnv_32a_str(buf, ((Fnv32_t)0x811c9dc5));
  _safefree((buf), 110, __func__);
  char* s = objtype_repr(obj->type);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "hash of %s #%zu is %d", s, obj->uid, hval);
  _safefree((s), 114, __func__);
  return hval;
}
static object_t* hash_val_asobject (const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 120, __func__);
  _obj_failnull((obj), "hash", 122, __func__);
  hashkey_t kh = hash_obj(obj);
  object_t* khobj = object_new(t_realuint, &kh);
  return khobj;
}
object_t* hash_get_copy (const hash_t* const h, const object_t* const key, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 138, __func__);
  _obj_failnull((h), "hash", 140, __func__);
  if (((void *)0) != ok) {
    *ok = 1;
  }
  if ( ! hash_exists(h, key) ) {
    if (((void *)0) != ok) {
      *ok = 0;
    }
    char* s = object_repr(key);
    _object_error ((ER_KEYERROR), (0), "hash", 151, __func__, "no such key %s in hash #%zu", s, h->uid);
    _safefree((s), 152, __func__);
    return object_new(t_F, ((void *)0));
  }
  object_t *finalval, *khobj;
  pair_t** valpair;
  khobj = hash_val_asobject(key);
  ssize_t proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);
  if ( -1 == proxy_idx ) {
    object_destruct(khobj);
    return object_new(t_F, ((void *)0));
  }
  valpair = assoc_get_ref(h->vals, signed2un(proxy_idx), ok);
  object_destruct(khobj);
  if ( (((void *)0) != ok) && (0 == *ok) ) {
    char* s = object_repr(key);
    _object_error ((ER_PTRMATH_BUG), (1), "hash", 181, __func__, "getting key %s from hash #%zu", s, h->uid);
    _safefree((s), 182, __func__);
    return object_new(t_F, ((void *)0));
  }
  finalval = pair_car_copy(*valpair);
  return finalval;
}
object_t** hash_get_ref (const hash_t* const h, const object_t* const key, _Bool* ok) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 205, __func__);
  _obj_failnull((h), "hash", 207, __func__);
  if (((void *)0) != ok) {
    *ok = 1;
  }
  if ( ! hash_exists(h, key) ) {
    if (((void *)0) != ok) {
      *ok = 0;
    }
    char* s = object_repr(key);
    _object_error ((ER_KEYERROR), (0), "hash", 218, __func__, "no such key %s in hash #%zu", s, h->uid);;
    _safefree((s), 219, __func__);
    return ((void *)0);
  }
  object_t* khobj;
  pair_t **valpair;
  khobj = hash_val_asobject(key);
  ssize_t proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);
  if ( -1 == proxy_idx ) {
    object_destruct(khobj);
    return ((void *)0);
  }
  valpair = assoc_get_ref(h->vals, signed2un(proxy_idx), ok);
  object_destruct(khobj);
  if ( (((void *)0) != ok) && (0 == *ok) ) {
    char* s = object_repr(key);
    _object_error ((ER_PTRMATH_BUG), (1), "hash", 248, __func__, "getting key %s from hash #%zu", s, h->uid);
    _safefree((s), 249, __func__);
    return ((void *)0);
  }
  return pair_car_ref( *valpair );
}
_Bool hash_change_at (hash_t* const h, const object_t* const obj, object_t* newval) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 266, __func__);
  _obj_failnull((h), "hash", 268, __func__);
  _Bool ok = 1;
  object_t** ref = hash_get_ref(h, obj, &ok);
  if ( ! ok ) {
    return 0;
  }
  if ( ! object_equals(*ref, newval) ) {
    object_destruct(*ref);
    *ref = object_copy(newval);
  }
  return 1;
}
_Bool hash_change_key (hash_t* const h, const object_t* const oldkey, const object_t* const newkey) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 294, __func__);
  _obj_failnull((h), "hash", 296, __func__);
  if ( object_equals(oldkey, newkey) ) {
    return 1;
  }
  _Bool ok = 1;
  object_t* val = hash_get_copy(h, oldkey, &ok);
  if ( ! ok ) {
    object_destruct(val);
    return 0;
  }
  ok = hash_add(h, newkey, val);
  object_destruct(val);
  if ( ok ) {
    hash_delete(h, oldkey);
    return 1;
  }
  return 0;
}
array_t* hash_getvals (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 327, __func__);
  _obj_failnull((h), "hash", 329, __func__);
  array_t* vs = array_new(((void *)0), 0);
  for (size_t i = 0; i < array_length(h->keys); i++) {
    object_t **car = pair_car_ref( ( *array_get_ref(vs, i, ((void *)0)) )->cel );
    array_append(vs, *car);
  }
  return vs;
}
array_t* hash_getkeys (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 350, __func__);
  _obj_failnull((h), "hash", 352, __func__);
  array_t* ks = array_new(((void *)0), 0);
  for (size_t i = 0; i < array_length(h->keys); i++) {
    array_append(ks, *array_get_ref(h->keys, i, ((void *)0)));
  }
  return ks;
}
void hash_unzip (const hash_t* const h, array_t** keys, array_t** vals) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 367, __func__);
  _obj_failnull((h), "hash", 369, __func__);
  *keys = hash_getkeys(h),
  *vals = hash_getvals(h);
}
_Bool hash_add (hash_t* h, const object_t* const key, const object_t* const val) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 386, __func__);
  _obj_failnull((h), "hash", 388, __func__);
  if ( hash_exists(h, key) || hash_keyexists(h, key) ) {
    return 0;
  }
  array_append(h->keys, key);
  object_t *khobj = hash_val_asobject(key),
           *newidx;
  assoc_append_boa(h->vals, val, khobj);
  newidx = object_new(t_realint, &( h->vals->idx ));
  assoc_append_boa(h->idxs, khobj, newidx);
  object_destruct_args(2, newidx, khobj);
  return 1;
}
_Bool hash_keyexists (const hash_t* const h, const object_t* const key) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 419, __func__);
  return _obj_failnull((h), "hash", 421, __func__)
    ? -1 != array_find(h->keys, key)
    : 0;
}
_Bool hash_exists (const hash_t* const h, const object_t* const key) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 430, __func__);
  _obj_failnull((h), "hash", 432, __func__);
  object_t* khobj = hash_val_asobject(key);
  _Bool found = -1 != assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);
  object_destruct(khobj);
  return found;
}
_Bool hash_delete (hash_t* const h, const object_t* const key) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 455, __func__);
  _obj_failnull((h), "hash", 457, __func__);
  object_t* khobj = hash_val_asobject(key);
  ssize_t keyidx = array_find(h->keys, key),
          proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);
  if ( ! hash_exists(h, key) || ( -1 == keyidx ) || ( -1 == proxy_idx ) ) {
    char* s = object_repr(key);
    _object_error ((ER_KEYERROR), (0), "hash", 467, __func__, "no such key %s in hash #%zu", s, h->uid);
    _safefree((s), 468, __func__);
    return 0;
  }
  _Bool ok = array_delete(h->keys, signed2un(keyidx));
  ((ok) ? (void) (0) : __assert_fail ("ok", "hash", 475, __PRETTY_FUNCTION__));
  assoc_delete(h->vals,
    (size_t) *object_getval(
      *pair_cdr_ref(
        *assoc_get_ref(h->idxs, signed2un(proxy_idx), ((void *)0))
      )
    )
  );
  assoc_delete(h->idxs, signed2un(proxy_idx));
  return 1;
}
char* hash_see (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 493, __func__);
  _obj_failnull((h), "hash", 495, __func__);
  (void) h;
  char* buf = (typeof(buf)) _safemalloc((1), 498, __func__);
  return buf;
}
void hash_inspect (const hash_t* const h) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 503, __func__);
  printf("hash uid:%zu idxs_len:%zu {\n", h->uid, assoc_length(h->idxs));
  printf("\tkeys: %zd\n\t", h->keys->idx + 1);
  char* s = array_see(h->keys);
  do { printf("%s\n", (s)); _safefree(((s)), 509, __func__); } while (0);;
  printf("\tvals: %zd\n\t", h->vals->idx + 1);
  s = assoc_see(h->vals);
  do { printf("%s\n", (s)); _safefree(((s)), 513, __func__); } while (0);;
  printf("\n\tidxs: %zu\n", assoc_length(h->idxs));
  puts("\n}");
}
_Bool hash_equals (const hash_t* const a, const hash_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "hash", 522, __func__);
  _obj_failnull((a), "hash", 524, __func__);
  if ( hash_isempty(a) && hash_isempty(b) ) {
    return 1;
  }
  return
    array_equals(a->keys, b->keys)
    && assoc_equals(a->vals, b->vals)
    && assoc_equals(a->idxs, b->idxs);
}
number_t* number_new (const numderlying_t val) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 7, __func__);
  number_t* number = (typeof(number)) _safemalloc((sizeof (number_t)), 9, __func__);
  number->value = val;
  static size_t uid = 0; ++uid; (number)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "number", uid);
  return number;
}
number_t* number_copy (const number_t* const num) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 17, __func__);
  return number_new(num->value);
}
void number_destruct (number_t* const number) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 23, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "number", number->uid);
  _safefree((number), 26, __func__);
}
void number_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 29, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { number_t ** v = (typeof(v)) _safemalloc((sizeof ( number_t *)), 29, __func__); *v = __builtin_va_arg(vl,number_t*); number_destruct( *v ); _safefree((v), 29, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3number;
char* number_see (const number_t* const num) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 32, __func__);
  char* buf = (typeof(buf)) _safemalloc((30), 34, __func__);
  snprintf(buf, 30, "%LG", num->value);
  buf = (typeof(buf)) _saferealloc((buf), (safestrnlen(buf)), 36, __func__);
  return buf;
}
_Bool number_eq (const number_t* const a, const number_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 42, __func__);
  numderlying_t
    an = a->value,
    bn = b->value;
  return fabsl(an - bn) < 0.001L;
}
_Bool number_gt (const number_t* const a, const number_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 52, __func__);
  numderlying_t an = a->value, bn = b->value;
  return an > bn;
}
_Bool number_lt (const number_t* const a, const number_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "number", 59, __func__);
  numderlying_t an = a->value, bn = b->value;
  return an > bn;
}
pair_t* pair_new (const object_t* const car, const object_t* const cdr) {
  pair_t* pair = (typeof(pair)) _safemalloc((sizeof (pair_t)), 7, __func__);
  pair->car = object_copy(car),
  pair->cdr = object_copy(cdr);
  static size_t uid = 0; ++uid; (pair)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "pair", uid);
  return pair;
}
pair_t* pair_copy (const pair_t* const p) {
  return pair_new(p->car, p->cdr);
}
char* pair_see (const pair_t* const p) {
  char
    *scar = object_repr(p->car),
    *scdr = object_repr(p->cdr),
    *buf;
  size_t buflen = safestrnlen(scar) + safestrnlen(scdr) + 11;
  buf = (typeof(buf)) _safemalloc((sizeof (char) * buflen), 28, __func__);
  snprintf(buf, buflen, "{ %s . %s }", scar, scdr);
  _safefree((scar), 31, __func__), _safefree((scdr), 31, __func__);
  return buf;
}
object_t* pair_car_copy (const pair_t* const p) { return object_copy(p->car); }
object_t* pair_cdr_copy (const pair_t* const p) { return object_copy(p->cdr); }
object_t** pair_car_ref (pair_t* const p) { return &(p->car); }
object_t** pair_cdr_ref (pair_t* const p) { return &(p->cdr); }
_Bool pair_equals (const pair_t* const a, const pair_t* const b) {
  return
       object_equals(a->car, b->car)
    && object_equals(a->cdr, b->cdr);
}
void pair_destruct (pair_t* const pair) {
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "pair", pair->uid);
  object_destruct_args(2, pair->car, pair->cdr);
  _safefree((pair), 52, __func__);
}
void pair_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "pair", 55, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { pair_t ** v = (typeof(v)) _safemalloc((sizeof ( pair_t *)), 55, __func__); *v = __builtin_va_arg(vl,pair_t*); pair_destruct( *v ); _safefree((v), 55, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3pair;
string_t* string_new (const char* const c) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "string", 7, __func__);
  string_t* string = (typeof(string)) _safemalloc((sizeof (string_t)), 9, __func__);
  size_t len = safestrnlen(c);
  string->len = len;
  string->data = strndup(c, len);
  static size_t uid = 0; ++uid; (string)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "string", uid);
  return string;
}
string_t* string_copy (const string_t* const s) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "string", 21, __func__);
  return string_new(s->data);
}
_Bool string_isempty (const string_t* const s) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "string", 27, __func__);
  return s->len == 0;
}
void string_destruct (string_t* const string) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "string", 33, __func__);
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "string", string->uid);
  _safefree((string->data), 37, __func__);
  _safefree((string), 38, __func__);
}
void string_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "string", 41, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { string_t ** v = (typeof(v)) _safemalloc((sizeof ( string_t *)), 41, __func__); *v = __builtin_va_arg(vl,string_t*); string_destruct( *v ); _safefree((v), 41, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3string;
char* string_see (const string_t* const s) {
  size_t buflen = sizeof (char) * (s->len + 3);
  char* buf = (typeof(buf)) _safemalloc((buflen), 46, __func__);
  snprintf(buf, buflen, "\"%s\"", s->data);
  return buf;
}
_Bool _obj_failnull (const void* const obj, const char* const file, uint64_t line, const char* const func) {
  if ( (__builtin_expect(!!(((void *)0) == obj), 0)) ) {
    _object_error ((ER_NULL_OBJECT), (1), "object", 32, __func__, "%s:%" "l" "u" ": %s", file, line, func);
    return 0;
  }
  return 1;
}
object_t* nothing_new (void) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 45, __func__);
  object_t* False = object_new(t_F, ((void *)0));
  static size_t uid = 0; ++uid; (False)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "False", uid);
  return False;
}
object_t* something_new (void) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 58, __func__);
  object_t* True = object_new(t_T, ((void *)0));
  static size_t uid = 0; ++uid; (True)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "True", uid);
  return True;
}
object_t* object_new (const objtype_t valtype, const void* const val) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 73, __func__);
  object_t* obj = (typeof(obj)) _safemalloc((sizeof (object_t)), 75, __func__);
  obj->type = valtype;
  if ( ((void *)0) == val ) {
    obj->type = t_F;
  }
  switch (obj->type) {
    case NUM_OBJTYPES: {
      _object_error ((ER_NOT_A_TYPE), (1), "object", 85, __func__, "", ((void *)0));
      break;
    }
    case t_F: {
      obj->f = (typeof(obj->f)) _safemalloc((sizeof (F_t)), 89, __func__);
      break;
    }
    case t_T: {
      obj->t = (typeof(obj->t)) _safemalloc((sizeof (T_t)), 93, __func__);
      break;
    }
    case t_number: {
      obj->num = number_copy( (const number_t * const) val);
      break;
    }
    case t_realuint: {
      obj->fwi = fixwid_new(-1, *(const size_t* const) val, 0);
      obj->type = t_fixwid;
      break;
    }
    case t_realint: {
      obj->fwi = fixwid_new( *(const ssize_t* const) val, 0, 1);
      obj->type = t_fixwid;
      break;
    }
    case t_fixwid: {
      obj->fwi = fixwid_copy( (const fixwid_t* const) val);
      break;
    }
    case t_string: {
      obj->str = string_copy( (const string_t * const) val);
      break;
    }
    case t_realchar: {
      obj->str = string_new( (const char * const) val);
      obj->type = t_string;
      break;
    }
    case t_func: {
      obj->fnc = func_copy( (const func_t* const) val);
      break;
    }
    case t_array: {
      obj->ary = array_copy( (const array_t * const) val);
      break;
    }
    case t_assoc: {
      obj->asc = assoc_copy( (const assoc_t* const) val);
      break;
    }
    case t_hash: {
      obj->hsh = hash_copy( (const hash_t * const) val);
      break;
    }
    case t_pair: {
      obj->cel = pair_copy( (const pair_t * const) val);
      break;
    }
  }
  static size_t uid = 0; ++uid; (obj)->uid = uid; fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", "obj", uid);
  return obj;
}
object_t* object_copy (const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 158, __func__);
  if (((void *)0) == obj) {
    return object_new(t_F, ((void *)0));
  }
  return object_new(obj->type, object_getval(obj));
}
void** object_getval (const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 172, __func__);
  if (((void *)0) == obj) {
    return ((void *)0);
  }
  void** types[] = {
    [t_F] = (void **) (obj->f),
    [t_T] = (void **) (obj->t),
    [t_number] = (void **) (obj->num),
    [t_fixwid] = (void **) (obj->fwi),
    [t_string] = (void **) (obj->str),
    [t_func] = (void **) (obj->fnc),
    [t_array] = (void **) (obj->ary),
    [t_assoc] = (void **) (obj->asc),
    [t_hash] = (void **) (obj->hsh),
    [t_pair] = (void **) (obj->cel),
    [t_realint] = (void **) (obj->fwi),
    [t_realuint] = (void **) (obj->fwi),
    [t_realchar] = (void **) (obj->str)
  };
  _Static_assert(
    ( (sizeof types) / (sizeof (void **)) == NUM_OBJTYPES),
    "getval types[] has too few or too many values"
  );
  return types[obj->type];
}
void object_destruct (object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 212, __func__);
  if (((void *)0) == obj) {
    return;
  }
  fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" "\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", "obj", obj->uid);
  switch (obj->type) {
    case t_array: {
      array_destruct(obj->ary);
      break;
    }
    case t_func: {
      func_destruct(obj->fnc);
      break;
    }
    case t_realchar:
    case t_string: {
      string_destruct(obj->str);
      break;
    }
    case t_hash: {
      hash_destruct(obj->hsh);
      break;
    }
    case t_pair: {
      pair_destruct(obj->cel);
      break;
    }
    case t_assoc: {
      assoc_destruct(obj->asc);
      break;
    }
    case t_realint:
    case t_realuint:
    case t_fixwid: {
      fixwid_destruct(obj->fwi);
      break;
    }
    case t_F:
    case t_T:
    case t_number: {
      _safefree((object_getval(obj)), 260, __func__);
      break;
    }
    case NUM_OBJTYPES: {
      _object_error ((ER_NOT_A_TYPE), (1), "object", 265, __func__, "", ((void *)0));
      break;
    }
  }
  _safefree((obj), 270, __func__);
}
void object_dtorn (object_t** const objs, const size_t len) {
  for (size_t i = 0; i < len; i++) {
    object_destruct(objs[i]);
  }
  if ( ((void *)0) != objs ) {
    _safefree((objs), 280, __func__);
  }
}
void object_destruct_args (const size_t argc, ...) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 289, __func__); va_list vl; __builtin_va_start(vl,argc); for (size_t i = 0; i < argc; i++) { object_t ** v = (typeof(v)) _safemalloc((sizeof ( object_t *)), 289, __func__); *v = __builtin_va_arg(vl,object_t*); object_destruct( *v ); _safefree((v), 289, __func__); } __builtin_va_end(vl); } int _IDONOTEXIST_3object;
char* objtype_repr (const objtype_t t) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 295, __func__);
  const char* const thisp = OBJTYPE_2STRING[t];
  const size_t len = safestrnlen(thisp) + 1;
  char* out = (typeof(out)) _safemalloc((sizeof (char) * len), 300, __func__);
  snprintf(out, len, "%s", thisp);
  return out;
}
void _object_error (objerror_t errt, const _Bool fatal, const char* const file, const uint64_t line, const char* const func, const char* fmt, ...) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 310, __func__);
  va_list vl;
  __builtin_va_start(vl,fmt);
  size_t fmtlen = safestrnlen(fmt) * 2;
  char* buf = (typeof(buf)) _safemalloc((sizeof (char) * fmtlen), 318, __func__);
  vsnprintf(buf, fmtlen, fmt, vl);
  __builtin_va_end(vl);
  static const char* const errmsgs[] = {
    [ER_NOT_A_TYPE] = "NUM_OBJTYPES isn't a real type, dummy. Don't do that.\n"
                       "Have you considered trying to match wits with a rutabaga?",
    [ER_KEYERROR] = "no such key",
    [ER_INDEXERROR] = "index out of bounds",
    [ER_PTRMATH_BUG] = "pointer math error (invalid read or write) -- probably a bug",
    [ER_NULL_OBJECT] = "null pointer encountered where a structure or union was expected"
  };
  _Static_assert(
    (sizeof (errmsgs) / sizeof (char*) ) == ER_NUM_ERRTYPES,
    "too many or too few error strings in object_error"
  );
  if (((void *)0) == stderr) {
    if (((void *)0) == stdout) {
      return;
    }
    stderr = freopen("/dev/stdout", "w", stderr);
  }
  fprintf(stderr, "|\033[31m%s\033[0m|\033[31;1m \b%s:%" "l" "u" ": %s: %s: %s\033[0m\n",
    fatal ? "FATAL" : "ERROR", file, line, func, buf, errmsgs[errt]);
  _safefree((buf), 351, __func__);
  if ( fatal ) {
    fprintf(
      stderr,
      "\033[31m\nThat error was fatal, aborting.\n\n"
      "I'm melting!\033[0m\n"
    );
    abort();
  }
}
char* object_repr (const object_t* const obj) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 369, __func__);
  _obj_failnull((obj), "object", 371, __func__);
  char* buf = ((void *)0);
  switch (obj->type) {
    case NUM_OBJTYPES: {
      _object_error ((ER_NOT_A_TYPE), (1), "object", 377, __func__, "", ((void *)0));
      break;
    }
    case t_F: {
      buf = (typeof(buf)) _safemalloc((2), 381, __func__);
      snprintf(buf, 1, "%s", "f");
      break;
    }
    case t_T: {
      buf = (typeof(buf)) _safemalloc((2), 387, __func__);
      snprintf(buf, 1, "%s", "t");
      break;
    }
    case t_number: {
      buf = number_see(obj->num);
      break;
    }
    case t_realint:
    case t_realuint:
    case t_fixwid: {
      buf = fixwid_see(obj->fwi);
      break;
    }
    case t_realchar:
    case t_string: {
      buf = string_see(obj->str);
      break;
    }
    case t_func: {
      buf = func_see(obj->fnc);
      break;
    }
    case t_array: {
      buf = array_see(obj->ary);
      break;
    }
    case t_assoc: {
      buf = assoc_see(obj->asc);
      break;
    }
    case t_hash: {
      buf = hash_see(obj->hsh);
      break;
    }
    case t_pair: {
      buf = pair_see(obj->cel);
      break;
    }
  }
  return buf;
}
_Bool object_equals (const object_t* const a, const object_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 444, __func__);
  if ( t_F == a->type + b->type ) {
    return 1;
  } else if (
       ( !a->type && b->type )
    || ( !b->type && a->type )
  ) {
    return 0;
  }
  if (a->type != b->type) {
    if (
         ( a->type == t_realchar || a->type == t_string )
      && ( b->type == t_realchar || b->type == t_string )
    ) {
      return strcmp(a->str->data, b->str->data) == 0;
    } else if (
         ( a->type == t_realint || a->type == t_fixwid )
      && ( b->type == t_realint || b->type == t_fixwid )
    ) {
      return a->fwi->value == b->fwi->value;
    } else if ( (a->type == t_T) || (b->type == t_T) ) {
      return 1;
    } else if (
         (a->type == t_realuint && b->type == t_fixwid)
      || (b->type == t_realuint && a->type == t_fixwid)
      ) {
      return fixwid_eq(a->fwi, b->fwi);
    } else {
      return 0;
    }
  }
  _Bool same = 0;
  switch (a->type) {
    case NUM_OBJTYPES: {
      _object_error ((ER_NOT_A_TYPE), (1), "object", 496, __func__, "", ((void *)0));
      return 0;
    }
    case t_T: same = 1; break;
    case t_fixwid: same = fixwid_eq(a->fwi, b->fwi); break;
    case t_number: same = number_eq(a->num, b->num); break;
    case t_array: same = array_equals(a->ary, b->ary); break;
    case t_assoc: same = assoc_equals(a->asc, b->asc); break;
    case t_hash: same = hash_equals(a->hsh, b->hsh); break;
    case t_pair: same = pair_equals(a->cel, b->cel); break;
    case t_func: {
      char *fa = object_repr(a),
           *fb = object_repr(b);
      same = strcmp(fa, fb) == 0;
      _safefree((fa), 514, __func__), _safefree((fa), 514, __func__);
      break;
    }
    case t_realuint:
    case t_realint:
    case t_string:
    case t_realchar:
    case t_F: {
      same = 1;
      break;
    }
  }
  return same;
}
_Bool object_id_equals (const object_t* const a, const object_t* const b) {
  printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "object", 542, __func__);
  return (a->type == b->type) && (a->uid == b->uid);
}
_Bool object_isinstance(const objtype_t t, const object_t* const o) {
  return ((void *)0) == o ? 0 : o->type == t;
}
assoc_t* assoc_new_from_ssize_t_lit (const ssize_t * const, const ssize_t * const, const size_t, const objtype_t, const objtype_t); assoc_t* assoc_new_from_ssize_t_lit (const ssize_t * const ct_cars, const ssize_t * const ct_cdrs, const size_t len, const objtype_t car_to, const objtype_t cdr_to) { printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", "test_clear.c", 3, __func__); assoc_t* out = assoc_new(((void *)0), ((void *)0)); for (size_t i = 0; i < len; i++) { object_t *a = object_new(car_to, &( ct_cars[i] )), *b = object_new(cdr_to, &( ct_cdrs[i] )); assoc_append_boa(out, a, b); object_destruct_args(2, a, b); } return out; } int ____DONT_FIND_THIS_NAME_ASSOCssize_t;
int main (void) {
  ssize_t s[] = {1, 5};
  ssize_t s2[] = {5, 1};
  assoc_t* a = assoc_new_from_ssize_t_lit(s, s2, 2, t_realint, t_realint);
  assoc_clear(a);
  assoc_destruct(a);
  return 0;
}
