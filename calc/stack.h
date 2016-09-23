#include "../common.h"

#define INITIAL_STACKSIZE 512


enum errortypes {
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
  VALUE_OVERFLOW,
  ZERO_DIVISION,
  MATH_EXCEPT
};

typedef long double number_t;
typedef struct stack stack_t;

struct stack {
  number_t* data;
  size_t    stack_ptr;
};


void   run (void);
void error (size_t err, const char* const info);

stack_t* stack_new (void);

void stack_incr (stack_t* stk);
void stack_decr (stack_t* stk);
void stack_push (stack_t* stk, number_t val);
void stack_drop (stack_t* stk);

number_t stack_top (stack_t* stk);
number_t stack_pop (stack_t* stk);


stack_t* stack_new (void) {
  stack_t* out   = safemalloc(sizeof (stack_t));
  out->data      = calloc(INITIAL_STACKSIZE, sizeof (number_t *));
  out->stack_ptr = 0;
  return out;
}

void stack_incr (stack_t* stk) {
  if (( stk->stack_ptr + 1 ) >= INITIAL_STACKSIZE) {
    error(STACK_OVERFLOW, "stack_incr");
    return;
  }

  ++stk->stack_ptr;
}

void stack_decr (stack_t* stk) {
  if (( ( (ssize_t) stk->stack_ptr) - 1 ) < 0) {
    error(STACK_UNDERFLOW, "stack_decr");
    return;
  }

  --stk->stack_ptr;
}

void stack_push (stack_t* stk, number_t val) {
  stack_incr(stk);
  stk->data[stk->stack_ptr] = val;
}

number_t stack_top (stack_t* stk) {
  return stk->data[stk->stack_ptr];
}

number_t stack_pop (stack_t* stk) {
  number_t out = stk->data[stk->stack_ptr];
  stack_decr(stk);
  return out;
}

void stack_drop (stack_t* stk) {
  stack_pop(stk);
}


void error (size_t err, const char* const info) {
  static const char* const errstrings[] = {
    "Data stack overflowed (too many values)",
    "Data stack underflowed (not enough values)",
    "Value overflows type 'long double' (value too large)",
    "Attempt to divide by zero leads to incomplete or inexpressable value (n / 0)",
  };

#define errstrings_len (size_t) (sizeof errstrings) / (sizeof (char *))

  if (err > errstrings_len) {
    fprintf(stderr, "Attempted to access value out of bounds of error string array\n");
  }
  fprintf(stderr, "%s: %s\n", info, errstrings[err]);
}
