#pragma once
#include "../object/object.h"

#ifdef GCC
#line __LINE__ "libcommon"
#endif

#define MATH_PI (long double)3.14159265358979323846264338327950288419716939937510582097494459230

// number theory
number_t* deg2rad (const number_t* const degrees);
number_t* rad2deg (const number_t* const radians);