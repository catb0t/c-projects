#include <time.h>

#include "../calc/object/object.h"

clock_t start, diff, msec;

#ifndef NODEBUG
  #define clock_start() start = clock()
  #define clock_stop() diff = clock() - start; \
    msec = diff * 1000; \
    msec /= CLOCKS_PER_SEC; \
    msec %= 1000;
#else
  #define clock_start()
  #define clock_stop()
#endif

#define GETTER_LOOP_LENGTH 100

define_array_new_fromctype(ssize_t);
define_assoc_new_fromctype(ssize_t);

array_t *a, *b, *ra, *rb;

assoc_t *c, *d, *rc, *rd;

object_t *oa, *ob, **refa;

char *s, *s2, *s3, *s4;

size_t __LOOPCOUNT;

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
