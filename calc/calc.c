#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (void) {
//  interpret();

  stack_t* stk = stack_new();

  for (size_t i = 1; i < 4; i++) {

    stack_push(stk, (number_t) i);

  }
  printf("len: %zu\n", stack_size(stk));

  for (size_t i = 0; i < stack_size(stk) + 2; i++) {
    printf("idx: %zu value: %LG\n", i, stack_get(stk, i));
  }

  //char* o = stack_see(stk);
  //printf("stk: %s\n", o);
  //safefree(o);

  stack_destruct(stk);

  return 0;
}
