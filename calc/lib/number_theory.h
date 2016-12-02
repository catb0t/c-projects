#pragma once
#include "libcommon.h"

#ifdef GCC
#line __LINE__ "number_theory"
#endif

number_t* deg2rad (const number_t* const degrees) {
  MAKE_NUMBER_PI;

  number_t *halfCirc = number_new(180),
                *fin = degrad_conv_compose(degrees, halfCirc, pi);
  number_destruct_args(2, pi, halfCirc);
  return fin;
}

number_t* rad2deg (const number_t* const radians) {
  MAKE_NUMBER_PI;

  number_t *halfCirc = number_new(180),
                *fin = degrad_conv_compose(radians, pi, halfCirc);
  number_destruct_args(2, pi, halfCirc);
  return fin;
}

number_t* degrad_conv_compose (const number_t* const val, const number_t* const op_a, const number_t* const op_b) {
  number_t
    *imd = number_mul(val, op_a),
    *fin = number_divmod(imd, op_b, NULL);

  number_destruct(imd);
  return fin;
}
