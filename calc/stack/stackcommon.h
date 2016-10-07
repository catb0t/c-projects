#ifdef GCC
#line 2
#endif

#pragma once
#define STACK
#include "../object/object.h"

// maybe it will grow in the future
#define INITIAL_STACKSIZE 50

// pretty useless for now, we'll see
enum errortypes {
  ERROR_STACK_OVERFLOW,  // 0
  ERROR_STACK_UNDERFLOW, // 1
  ERROR_VALUE_OVERFLOW,  // 2
  ERROR_ZERO_DIVISION,   // 3
  ERROR_LITERAL_JUNK,    // 4
  ERROR_NOT_A_NUMBER,    // 5
  ERROR_EMPTY_STACK,     // 6
  ERROR_BAD_INDEX,       // 7
};

// subject to change -- maybe to be an array of other things too
typedef struct {
  // list of long doubles
  number_t* data;
  // points to the top
  ssize_t    ptr;
} stack_t;

size_t       stack_size (const stack_t* stk);
size_t      atoi_strlen (const number_t val);
void              error (const size_t err, const char* const info);
bool          is_base10 (const char *nptr);
bool      stack_isempty (const stack_t* stk);

char* stack_see (const stack_t* stk);
void stack_dbgp (const stack_t* stk);
void stack_incr (stack_t* stk);
void stack_decr (stack_t* stk);
void stack_push (stack_t* stk, const number_t val);
void stack_drop (stack_t* stk);

stack_t* stack_new (void);
number_t stack_top (const stack_t* stk);
number_t stack_pop (stack_t* stk);
number_t stack_get (const stack_t* skt, const ssize_t idx);
void     stack_set (stack_t* stk, const ssize_t idx, const number_t val);
void stack_op_divmod (stack_t* stk);
void  stack_destruct (stack_t* stk);
void    stack_op_add (stack_t* stk);
void    stack_op_mul (stack_t* stk);
void    stack_op_sub (stack_t* stk);
void    stack_op_pow (stack_t* stk);
void    stack_op_swp (stack_t* stk);
void    stack_op_drp (stack_t* stk);
void    stack_op_prn (stack_t* stk);
void    stack_op_prn_dispose (stack_t* stk);
void    stack_op_prc (stack_t* stk);
void    stack_op_see (stack_t* stk);

ssize_t get_stackop (const char* const op);
void     perform_op (stack_t* stk, const char* const op);

number_t* str_to_number_array (
  const char*   str,
  const char*   remove_at,
  const char    split_at,
        size_t* out_len
);

// for converting input. must stay synched
void (* const stack_ops[]) (stack_t *)  = {
  stack_op_add,
  stack_op_mul,
  stack_op_divmod,
  stack_op_sub,
  stack_op_pow,
  stack_op_swp,
  stack_op_drp,
  stack_op_prn,
  stack_op_see,
  stack_op_prc,
};

const char* ops_tostring[] = {
  // # is arith related
  "#+", // add
  "#*", // mul
  "#/", // divmod
  "#-", // sub
  "#^", // pow

  // $ is stack related
  "$%", // swap
  "$,", // drop

  // ! is io related
  "!!", // prn
  "!.", // see
  "!,", // prc
};

#define NUM_STACKOPS (size_t) (sizeof ops_tostring) / (sizeof (char *))
