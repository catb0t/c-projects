#include "fxpt.h"

int main (void) {
  /*
  fixed_point_t a  = fxpt_new(10, 0, 0, false);
  fixed_point_t b  = fxpt_new(5, 0, 0, false);
  fixed_point_t c  = fxpt_sub(a, b);

  fxpt_writedebug(a);
  fxpt_writedebug(b);
  fxpt_writedebug(c);

  */

  char *in, *f;

/*  while (true) {
    in = readln(SHORT_INSTR);
    if (!in) { printf("Bad input\n"); continue; }
    fixed_point_t a = fxpt_new_fromstring(in);
    fxpt_writedebug(a);
    safefree(in);
  }
*/
  while (true) {
    in = readln(SHORT_INSTR);
    if (!in) { printf("Bad input\n"); continue; }
    fixed_point_t a = fxpt_new_fromstring(in);

    in = readln(SHORT_INSTR);
    if (!in) { printf("Bad input\n"); continue; }
    fixed_point_t b = fxpt_new_fromstring(in);

    fixed_point_t c = fxpt_add(a, b);
    f = fxpt_tostring(c);
    printf("= %s\n", f);

    fxpt_writedebug(a);
    fxpt_writedebug(b);
    fxpt_writedebug(c);
    safefree(in);

  }

}
