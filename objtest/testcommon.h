#include "../calc/object/object.h"

define_array_new_fromctype(ssize_t);

array_t *a, *b, *ra, *rb;

assoc_t *c, *d;

char *s, *s2;

bool ok;

const ssize_t anums[] = {
  1, -3, 5, -7, 9, -11
};

const ssize_t bnums[] = {
  -2, 4, -6, 8, -10, 12
};

const char* const literal[] = {
  "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz"
};
