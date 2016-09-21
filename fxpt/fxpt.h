#include "../common.h"

typedef uint32_t fxpt_atom_t;

struct s_fxpt_t {
  fxpt_atom_t igrl;
  fxpt_atom_t frac;
  uint8_t frac_place;
};

typedef struct s_fxpt_t fixed_point_t;

char*        fxpt_fmt (fixed_point_t val);
void  fxpt_writedebug (fixed_point_t val);
double floor_atleast1 (const double val);
double  fxpt_frac_tof (fixed_point_t val);

fixed_point_t fxpt_f_tofrac (const double val);

fixed_point_t fxpt_new (const fxpt_atom_t integral, const fxpt_atom_t fractional, const uint8_t frac_place);
fixed_point_t fxpt_add (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_sub (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_mul (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_div (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_pow (const fixed_point_t lhs, const fixed_point_t rhs);

fixed_point_t fxpt_new (const fxpt_atom_t integral, const fxpt_atom_t fractional, const uint8_t frac_place) {
  fixed_point_t new;
  new.igrl           = integral;
  new.frac           = fractional;
  new.frac_place = frac_place;
  return new;
}

// turn the fractional part into a decimal
double fxpt_frac_tof (const fixed_point_t val) {
  return val.frac * pow(10, -(val.frac_place) );
}

double floor_atleast1 (const double val) {
  double f = floor(val);
  return (f > 0 ? f : 1);
}

fixed_point_t fxpt_f_tofrac (double val) {

  fixed_point_t out;
  out.frac_place = 0;

  val -= out.igrl = (fxpt_atom_t) floor(val);


  while (floor(val) < 1) {
    val /= pow(10, -1);
    ++out.frac_place;
  }

  out.frac = (fxpt_atom_t) val;

  return out;
}


// add two fixed point numbers
fixed_point_t fxpt_add (const fixed_point_t lhs, const fixed_point_t rhs) {
  fixed_point_t out;
  fxpt_atom_t new_ig, new_fc;

  // add integral parts
  new_ig = lhs.igrl + rhs.igrl;

  // add fractional parts & wrap
  new_fc = (lhs.frac + rhs.frac) % INT32_MAX;
  new_ig += (new_fc / 10);
  new_fc %= 10;

  out.igrl = new_ig;
  out.frac = new_fc;
  return out;
}

/*fixed_point_t fxpt_mul (fixed_point_t lhs, fixed_point_t rhs) {
  fixed_point_t out;
  out.frac = 1;

  //fxpt_atom_t ixi = lhs.igrl * rhs.igrl;
  return out;
}*/

char* fxpt_fmt (fixed_point_t val) {
  size_t len;
  char *out        = malloc(sizeof (char) * 66),
       *zeroes_str = str_repeat("0", val.frac_place, &len);

  sprintf(out, "%d.%s%d", val.igrl, zeroes_str, val.frac);

  safefree(zeroes_str);
  return out;
}

void fxpt_writedebug (fixed_point_t val) {
  printf("\n\n\x1b[36;1migrl: %d\nfrac: %d\nfrac place: %d\x1b[0m\n\n", val.igrl, val.frac, val.frac_place);
}