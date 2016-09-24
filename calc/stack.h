#include <errno.h>
#include "../common.h"


#define INITIAL_STACKSIZE 512

enum errortypes {
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
  VALUE_OVERFLOW,
  ZERO_DIVISION,
};

typedef long double number_t;
typedef struct stack stack_t;

struct stack {
  number_t* data;
  size_t    ptr;
};

void   run (void);
void error (size_t err, const char* const info);


char* stack_see (stack_t* stk);
void stack_incr (stack_t* stk);
void stack_decr (stack_t* stk);
void stack_push (stack_t* stk, number_t val);
void stack_drop (stack_t* stk);

stack_t* stack_new (void);
number_t stack_top (stack_t* stk);
number_t stack_pop (stack_t* stk);

void stack_op_divmod (stack_t* stk);
void  stack_destruct (stack_t* stk);
void    stack_op_add (stack_t* stk);
void    stack_op_mul (stack_t* stk);
void    stack_op_sub (stack_t* stk);
void    stack_op_pow (stack_t* stk);
void    stack_op_prn (stack_t* stk);
void    stack_op_swp (stack_t* stk);
void    stack_op_drp (stack_t* stk);
void    stack_op_see (stack_t* stk);

ssize_t get_stackop (const char* const op);
void     perform_op (stack_t* stk, const char* const op);

number_t* str_to_number_array (
  const char*   str,
  const char*   remove_at,
  const char    split_at,
        size_t* out_len
);

void (* stack_ops[]) (stack_t *) = {
  stack_op_add,
  stack_op_mul,
  stack_op_divmod,
  stack_op_sub,
  stack_op_pow,
};

const char* ops_tostring[] = {
  "+",
  "*",
  "/",
  "-",
  "**",
};

#define NUM_STACKOPS (size_t) (sizeof ops_tostring) / (sizeof (char *))

stack_t* stack_new (void) {
  stack_t* out = safemalloc(sizeof (stack_t));
  out->data    = calloc(INITIAL_STACKSIZE, sizeof (number_t *));
  out->ptr     = 0;
  return out;
}

void stack_destruct (stack_t* stk) {
  safefree(stk->data), safefree(stk);
}

void stack_incr (stack_t* stk) {
  if (( stk->ptr + 1 ) >= INITIAL_STACKSIZE) {
    error(STACK_OVERFLOW, "stack_incr");
    return;
  }

  ++stk->ptr;
}

void stack_decr (stack_t* stk) {
  if (( ( (ssize_t) stk->ptr ) - 1 ) < 0) {
    error(STACK_UNDERFLOW, "stack_decr");
    return;
  }

  --stk->ptr;
}

void stack_push (stack_t* stk, number_t val) {
  stk->data[stk->ptr] = val;
  stack_incr(stk);
}

number_t stack_top (stack_t* stk) {
  return stk->data[stk->ptr];
}

number_t stack_pop (stack_t* stk) {
  number_t out = stk->data[stk->ptr];
  stack_decr(stk);
  return out;
}

void stack_drop (stack_t* stk) {
  stack_pop(stk);
}

char* stack_see (stack_t* stk) {

  size_t num_elts = stk->ptr,
         new_len = 0;//  !!= (num_elts / 2) + (num_elts % 2);

  char **str_list = safemalloc(1 + sizeof (char *) * (num_elts)),
       *output;


  for (size_t i = 0; i < num_elts; i++) {
    str_list[i] = safemalloc(21);
    snprintf(str_list[i], 20, "%1.1Lf", (stk->data)[i]);
    new_len += safestrnlen(str_list[i]);
  }

  output = safemalloc(new_len + 5);
  char* bufptr = output;

  for (size_t i = 0; i < num_elts; i++) {
    bufptr += sprintf(bufptr, "%s ", str_list[i]);
    safefree(str_list[i]);
  }

  safefree(str_list);

  return output;
}

void    stack_op_add (stack_t* stk) {
  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b + a);
}
void    stack_op_mul (stack_t* stk) {
  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b * a);
}
void stack_op_divmod (stack_t* stk) {
  number_t a = (long double) stack_pop(stk);
  number_t b = (long double) stack_pop(stk);

  stack_push(stk, (number_t) ( ( (signed long long) b ) % ( (signed long long) a ) ));
  stack_push(stk, b / a);
}
void    stack_op_sub (stack_t* stk) {
  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b - a);
}
void    stack_op_pow (stack_t* stk) {
  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, powl(a, b));
}
void    stack_op_prn (stack_t* stk) {
  printf("%Lf\n", stack_pop(stk));
}
void    stack_op_swp (stack_t* stk) {
  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, a);
  stack_push(stk, b);
}
void    stack_op_drp (stack_t* stk) {
  stack_pop(stk);
}
void    stack_op_see (stack_t* stk) {
  stack_see(stk);
}


ssize_t      get_stackop (const char* const op) {
  for (size_t i = 0; i < NUM_STACKOPS; i++) {
    if ( strncmp(op, ops_tostring[i], 5) ) {
      return (ssize_t) i;
    }
  }
  return -1;
}

void      perform_op (stack_t* stk, const char* const op) {
  (void) stk, (void) op;
/*  ssize_t opidx;

  if ( ( opidx = get_stackop(op) ) != -1 ) {
    stack_ops[opidx](stk);

  } else {
    printf("%s: operator not defined\n", op);
  }
*/
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
    return;
  }

  if (errno) {
    perror(info);
  }
  fprintf(stderr, "%s: %s\n", info, errstrings[err]);
}

number_t* str_to_number_array (
  const char*   str,
  const char*   remove_at,
  const char    split_at,
        size_t* out_len
) {
  number_t* out;

  size_t len;
  char* rmd = str_rm(str, remove_at, &len);

  char** split = str_split(rmd, split_at, &len);
  out = safemalloc(sizeof (number_t *) * len);

  for (size_t i = 0; i < len; i++) {
    out[i] = strtod(split[i], NULL);
  }

  *out_len = len;
  return out;
}