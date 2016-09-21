#include "fxpt.h"

int main (void) {
/*  fixed_point_t a  = fxpt_new(10, 5, 0);
  fixed_point_t b  = fxpt_new(5, 5, 0);
  fixed_point_t c  = fxpt_add(a, b);

  char* fmt = fxpt_fmt(c);

  printf("%s\n", fmt);

  safefree(fmt);
*/

  //fixed_point_t a = fxpt_new(4, 5, 1); fxpt_writedebug(a);

  double b = 5.5;
  fixed_point_t c = fxpt_f_tofrac(b);
  fxpt_writedebug(c);
  double f = fxpt_frac_tof(c) + c.igrl;
  printf("%f == %f : %d\n", b, f, b == f);
}
