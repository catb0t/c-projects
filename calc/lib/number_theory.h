#pragma once
#include "libcommon.h"

#ifdef GCC
#line __LINE__ "number_theory"
#endif

number_t* deg2rad (const number_t* const degrees) {
  number_t *out = number_copy(degrees);

  out = number_pmul(MATH_PI, out);

  out = number_pdivmod(180, out, NULL);

  return out;
}

number_t* rad2deg (const number_t* const radians) {
  number_t* out = number_copy(radians);

  out = number_pmul(180, out);
}