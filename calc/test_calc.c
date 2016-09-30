#include <criterion/criterion.h>

#undef DEBUG
#include "./calc.h"

Test(stack, base10) {
  cr_assert_eq( is_base10("+0123.4567890"), true, "numeric string is base 10");
  cr_assert_eq( is_base10("-01234567A890."), false, "non-base 10 string");
}

Test(stack, atoi_strlen) {
  cr_assert_eq( atoi_strlen(-200.003), 8, "signed fractional thou place");
  cr_assert_eq( atoi_strlen(-200.3), 6, "signed 10s place dec");
  cr_assert_eq( atoi_strlen(-200), 4, "signed int");
}

// add
Test(stack, op_add) {
  stack_t* stk = stack_new();
  stack_push(stk, 2);
  stack_push(stk, 2);

  stack_op_add(stk);
  cr_assert_eq( floorl(stack_top(stk) - 4), 0 , "addition" );

  stack_destruct(stk);
}

// sub
Test(stack, op_sub) {
  stack_t* stk = stack_new();
  stack_push(stk, 2);
  stack_push(stk, 1);

  stack_op_sub(stk);
  cr_assert_eq( floorl(stack_top(stk)), 1 , "subtraction" );

  stack_destruct(stk);
}

// mul
Test(stack, op_mul) {
  stack_t* stk = stack_new();
  stack_push(stk, 2);
  stack_push(stk, 7);

  stack_op_mul(stk);
  cr_assert_eq( floorl(stack_top(stk)), 14 , "multiplication" );

  stack_destruct(stk);
}

// div
Test(stack, op_div) {
  stack_t* stk = stack_new();
  stack_push(stk, 12);
  stack_push(stk, 4);

  stack_op_divmod(stk);
  cr_assert_eq( floorl(stack_top(stk)), 3 , "division" );

  stack_destruct(stk);
}
Test(stack, op_div_frac) {
  stack_t* stk = stack_new();
  stack_push(stk, 7);
  stack_push(stk, 2);

  stack_op_divmod(stk);
  cr_assert_eq( floorl(stack_top(stk)), 3.5 , "fractional division" );

  stack_destruct(stk);
}
