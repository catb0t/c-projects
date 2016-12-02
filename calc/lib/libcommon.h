#pragma once
#include "../object/object.h"

#ifdef GCC
#line __LINE__ "libcommon"
#endif

#define MATH_PI (long double)3.14159265358979323846264338327950288419716939937510582097494459230
#define MAKE_NUMBER_PI number_t* pi = number_new(MATH_PI)

// number theory
number_t* deg2rad (const number_t* const degrees);
number_t* rad2deg (const number_t* const radians);
number_t* degrad_conv_compose (const number_t* const val, const number_t* const op_a, const number_t* const op_b);
