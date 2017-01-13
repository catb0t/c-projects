#include "calc/object/object.h"

define_assoc_new_fromctype(ssize_t);
int main (void) {

  ssize_t s[] = {1, 5};
  ssize_t s2[] = {5, 1};

  assoc_t* a = assoc_new_from_ssize_t_lit(s, s2, 2, t_realint, t_realint);

  assoc_t* b = assoc_clearv2(a);
  assoc_destruct(a);
  a = b;
  //assoc_clear(a);

  assoc_destruct(a);
  return 0;
}
