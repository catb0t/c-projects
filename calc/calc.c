#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (void) {
  interpret();

  //stack_t* s = stack_new();
  //stack_push(s, 7);
  //stack_push(s, 2);
  //stack_op_divmod(s);
  
  return 0;
}
