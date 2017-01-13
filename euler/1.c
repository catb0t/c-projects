#include "../calc/object/object.h"
#include <stdio.h>

size_t f (const size_t max, const size_t a, const size_t b);
size_t f2 (const size_t max, const array_t* const divs);
size_t g (size_t max, array_t* divs);

define_array_new_fromctype(size_t);

int main(void) {
  printf("%zu\n", f(10, 3, 5));
  static const size_t a[] = {
    3, 5
  };
  array_t* b = array_new_from_size_t_lit(a, 2, t_realuint);
  printf("%zu\n", f2(10, b));
  printf("%zu\n", g(10, b));
  array_destruct(b);
  return 0;
}

size_t f (const size_t max, const size_t a, const size_t b) {
  size_t sum = 0;
  for (size_t i = 0; i < max; i++) {
    sum += (i % a * i % b) ? 0 : i;
  }
  return sum;
}

size_t f2 (const size_t max, const array_t* const divs) {
  size_t sum = 0;
  const size_t len = array_length(divs);

  for (size_t i = 0; i < max; i++) {
    size_t mul = 1;
    for (size_t j = 0; j < len; j++) {
      object_t** this = array_get_ref(divs, j, NULL);

      fixwid_t*   num = (*this)->fwi;

      mul *= i % (size_t) num->value;
    }
    sum += mul ? 0 : i;
  }
  return sum;
}

#define S size_t
S g(S m,array_t*d){S s,i,l,j;for(s=i=0;i<m;i++){for(l=1,j=0;j<d->idx+1;l*=i%(S)(*array_get_ref(d,j++,NULL))->fwi->value);s+=l?0:i;}return s;}
