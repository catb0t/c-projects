#include "../common.h"

typedef uint64_t fxpt_atom_t;
typedef int64_t fxpt_satom_t;

struct s_fxpt_t {
  fxpt_atom_t igrl;
  fxpt_atom_t frac;
  uint8_t     frac_place;
  bool        sign;
};

typedef struct s_fxpt_t fixed_point_t;

bool            dbl_eq (const double lhs, const double rhs, const double eps);
double  floor_atleast1 (const double val);
void   fxpt_writedebug (const fixed_point_t val);
char*    fxpt_tostring (const fixed_point_t val);
double   fxpt_frac_tof (const fixed_point_t val);
uint8_t leading_zeroes (const char* const str);
ssize_t    str_indexof (const char* const str, char findme);

fixed_point_t fxpt_new_fromstring (char* str);
fixed_point_t fxpt_new (
  const fxpt_atom_t integral,
  const fxpt_atom_t fractional,
  const uint8_t frac_place,
  const bool    sign
);
fixed_point_t fxpt_add (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_mul (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_sub (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_div (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_pow (const fixed_point_t lhs, const fixed_point_t rhs);
fixed_point_t fxpt_abs (const fixed_point_t lhs, const fixed_point_t rhs);

uint8_t fxpt_cmp (const fixed_point_t lhs, const fixed_point_t rhs);
bool     fxpt_eq (const fixed_point_t lhs, const fixed_point_t rhs);
bool     fxpt_gt (const fixed_point_t lhs, const fixed_point_t rhs);
bool     fxpt_lt (const fixed_point_t lhs, const fixed_point_t rhs);
bool    fxpt_gte (const fixed_point_t lhs, const fixed_point_t rhs);
bool    fxpt_lte (const fixed_point_t lhs, const fixed_point_t rhs);

fixed_point_t fxpt_f_tofxpt (const double val);
fixed_point_t    fxpt_floor (const fixed_point_t val);
fixed_point_t     fxpt_ceil (const fixed_point_t val);

fxpt_satom_t fxpt_itosigned (const fixed_point_t val);
fxpt_satom_t fxpt_ftosigned (const fixed_point_t val);

fixed_point_t fxpt_new (
  const fxpt_atom_t integral,
  const fxpt_atom_t fractional,
  const uint8_t frac_place,
  const bool    sign
) {
  fixed_point_t new;
  new.igrl       = integral;
  new.frac       = fractional;
  new.frac_place = frac_place;
  new.sign       = sign;
  return new;
}

fxpt_satom_t fxpt_itosigned (const fixed_point_t val) {
  return ((fxpt_satom_t) val.igrl) * (val.sign ? -1 : 1);
}

fxpt_satom_t fxpt_ftosigned (const fixed_point_t val) {
  return ((fxpt_satom_t) val.frac) * (val.sign ? -1 : 1);
}

bool dbl_eq (const double lhs, const double rhs, const double eps) {
  return fabs(lhs - rhs) < eps;
}

double floor_atleast1 (const double val) {
  double f = floor(val);
  return (f > 0 ? f : 1);
}

uint8_t leading_zeroes (const char* const str) {
  size_t len = safestrnlen(str);
  uint8_t i;
  for (
    i = 0;
    (i < len) && (str[i] == '0');
    i++
  );

  return i;
}

ssize_t str_indexof (const char* const str, char findme) {
  size_t len = safestrnlen(str), i;
  bool found;
  for (
    i = 0;
    (i < len) && (found = str[i] != findme);
    i++
  );
  if ( (i == len) && found) {
    return -1;
  }
  return (ssize_t) i;
}

fixed_point_t fxpt_new_fromstring (char* str) {

  ssize_t dec_loc;
  fixed_point_t out = fxpt_new(0, 0, 0, true);
  char **spl_str,
       *s_igrl,
       *s_frac;

  out.sign = str[0] == '-';
  dec_loc  = str_indexof(str, '.');

  if (
      ( dec_loc == 0 )
      || ( out.sign && ( dec_loc == 1 ) )
  ) {
    printf("startswith\n" );

    // skip leading decimal
    s_frac   = (char *) &(str[dec_loc + 1]);

    out.frac = strtoull(s_frac, NULL, DEC_BASE);
    out.igrl = 0;
    out.frac_place = leading_zeroes(s_frac);

  } else if (dec_loc == -1) {
    printf("notfound\n" );

    // skip the sign
    s_igrl   = (char *) &(str[out.sign]);

    out.igrl = strtoull(s_igrl, NULL, DEC_BASE);
    out.frac = 0;
    out.frac_place = 0;

  } else if ( ( (size_t) dec_loc ) == ( safestrnlen(str) - 1) ) {
    printf("atend\n" );

    // skip the sign & end decimal
    s_igrl   = (char *) &(str[out.sign]);
    s_igrl[dec_loc] = '\0';

    out.igrl = strtoull(s_igrl, NULL, DEC_BASE);
    out.frac = 0;
    out.frac_place = 0;

  } else {
    printf("else\n" );

    size_t len;
    spl_str = str_split(str, '.', &len);
    s_igrl = spl_str[0],
    s_frac = spl_str[1];
    //printf("%s %s\n", s_igrl, s_frac);

    out.igrl = strtoull(s_igrl, NULL, DEC_BASE);
    out.frac = strtoull(s_frac, NULL, DEC_BASE);
    out.frac_place = leading_zeroes(s_frac);

    safefree(spl_str);
  }

  return out;
}


// turn ONLY the fractional part into a decimal
double fxpt_frac_tof (const fixed_point_t val) {
  return (double) val.frac * pow(10, -(val.frac_place));
}

// turn the whole value to fixed
fixed_point_t fxpt_f_tofxpt (double val) {

  fixed_point_t out;
  out.sign = val < 0;
  out.frac_place = 0;

  out.igrl = (fxpt_atom_t) floor(val);
  val -= (double) out.igrl;

  while ((floor(val) < 1)) {
    if (dbl_eq(val, 0, 0)) { break; }
    val /= pow(10, -1);
    ++out.frac_place;
  }

  out.frac = (fxpt_atom_t) val;

  return out;
}


// add two fixed point numbers
fixed_point_t fxpt_add (const fixed_point_t lhs, const fixed_point_t rhs) {
  fixed_point_t out;
  fxpt_satom_t lhs_isigned, rhs_isigned,
               lhs_fsigned, rhs_fsigned,
               new_ig, new_fc;
  out.sign = false;
  out.frac_place = 0;
  out.frac = 0;

  // add integral parts
  lhs_isigned = fxpt_itosigned(lhs),
  rhs_isigned = fxpt_itosigned(rhs);
  new_ig = lhs_isigned + rhs_isigned;

  // add fractional parts & wrap
  lhs_fsigned = fxpt_ftosigned(lhs),
  rhs_fsigned = fxpt_ftosigned(rhs);
  new_fc = (lhs_fsigned + rhs_fsigned) % INT32_MAX;
  new_ig += (new_fc / 10);
  new_fc %= 10;


  // set the sign
  if (new_ig < 0) {
    new_ig = -new_ig;
    out.sign = true;
  }

  out.igrl = (fxpt_atom_t) new_ig;
  return out;
}

fixed_point_t fxpt_mul (const fixed_point_t lhs, const fixed_point_t rhs) {
  double lhs_frac, rhs_frac, ixi, fxf, ixf, fxi, final;

  lhs_frac = fxpt_frac_tof(lhs), rhs_frac = fxpt_frac_tof(rhs);

  ixi = (double) lhs.igrl * (double) rhs.igrl;
  fxf = lhs_frac * rhs_frac;
  ixf = (double) lhs.igrl * rhs_frac;
  fxi = lhs_frac * (double) rhs.igrl;

  final = ixi + fxf + ixf + fxi;

  if (lhs.sign ^ rhs.sign) {
    final = -final;
  }

  return fxpt_f_tofxpt(final);
}

fixed_point_t fxpt_sub (const fixed_point_t lhs, const fixed_point_t rhs) {
  fixed_point_t new_r = rhs;

  new_r.sign = !new_r.sign;

  return fxpt_add(lhs, new_r);
}

char* fxpt_tostring (fixed_point_t val) {
  size_t len, fp = val.frac_place ? (size_t) val.frac_place - 1 : val.frac_place;

  char *out        = safemalloc(sizeof (char) * 66),
       *zeroes_str = str_repeat("0", fp, &len);



  sprintf(out, "%s%ld.%s%ld",
    val.sign ? "-" : "",
    val.igrl,
    zeroes_str,
    val.frac
  );

  safefree(zeroes_str);
  return out;
}

void fxpt_writedebug (fixed_point_t val) {
  printf("\n\n\x1b[36;1migrl: %ld\nfrac: %ld\nfrac place: %d\nsign: %s\x1b[0m\n\n",
    val.igrl,
    val.frac,
    val.frac_place,
    val.sign ? "yes" : "no");
}
