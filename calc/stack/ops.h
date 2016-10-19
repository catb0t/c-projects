#ifdef GCC
#line 2 "ops"
#endif

#include "stackcommon.h"

/*
  OPERATORS
  TODO: tests. make sure operands are in correct order.
*/

/*
  effect: ( x y -- x+y )
  operator add: push the result of adding the top two numbers on the
  stack.
*/
void    stack_op_add (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b + a);
}
/*
  effect: ( x y -- x*y )
  operator multiply: push the result of multiplying the top two numbers
  on the stack pointed to by *stk.
*/
void    stack_op_mul (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b * a);
}
/*
  effect: ( x y -- x%y x/y )
  operator divmod: push the result of x modulo y, then the result of
  x divided by y.

  results for % may be off by a rounding error because of casting.
  TODO: floorl instead.
*/
void stack_op_divmod (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(
    stk,
    (number_t)
    (
      ( (signed long long) b ) % ( (signed long long) a )
    )
  );
  stack_push(stk, b / a);
}
/*
  effect: ( x y -- x-y )
  operator subtract: push the result of subtracting y from x.
*/
void    stack_op_sub (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b - a);
}
/*
  effect: ( x y -- pow(x,y) )
  operator pow: push the result of x raised to the y power.
*/
void    stack_op_pow (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, powl(a, b));
}
/*
  effect: ( x -- )
  operator drop: drop the top item off the stack pointed to by *stk.
*/
void    stack_op_drp (stack_t* stk) {
  pfn();

  stack_pop(stk);
}
/*
  effect: ( x y -- y x )
  operator swap: swap the top two operands.
*/
void    stack_op_swp (stack_t* stk) {
  pfn();

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, a);
  stack_push(stk, b);
}
/*
  effect: ( x -- x )
  operator prn: print the top item on the stack pointed to by *stk,
  with no formatting whatsoever.

  does not modify *stk, even though *stk is not marked
  const; thisp is because the operators must share a type.
*/
void    stack_op_prn (stack_t* stk) {
  pfn();

  printf("%LG", stack_top(stk));
}
/*
  effect: ( x -- )
  operator prn_dispose: print the top item on the stack pointed to
  by *stk, discarding it in the process.

  unlike prn, modifies *stk.
*/
void    stack_op_prn_dispose (stack_t* stk) {
  pfn();

  printf("%LG", stack_pop(stk));
}
/*
  effect: ( x -- )
  operator prc: print the top item on the stack as an ASCII character
  and discard it.

  applies no formatting whatsoever.
*/
void    stack_op_prc (stack_t* stk) {
  pfn();

  printf("%c", (int) floorl( stack_pop(stk) ) );
}
/*
  effect: ( x -- x )
  operator see: call stack_see on the stack pointed to by *stk,
  without modifying it.
*/
void    stack_op_see (stack_t* stk) {
  pfn();

  stack_see(stk);
}

/* END OPERATORS */
