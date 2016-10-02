#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (void) {
  interpret();

  //char* a = safemalloc(5);
  //snprintf(a, 5, "%s\n", "Hi!");
  //object_t* o = object_new(string, (void *) a);
  //object_destruct(o);

  return 0;
}
