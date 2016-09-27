#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (void) {
  //interpret();

  stack_t* stk = stack_new();

  stack_push(stk, 34);

  stack_push(stk, 67);
  stack_dbgp(stk);

  printf("1 ptr: %zu\n", stk->ptr);

  printf("1 pop: %LG\n", stack_pop(stk));

  printf("2 ptr: %zu\n", stk->ptr);
  stack_dbgp(stk);

  printf("2 pop: %LG\n", stack_pop(stk));
  stack_dbgp(stk);


  return 0;
}
