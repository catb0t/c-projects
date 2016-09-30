#ifdef GCC
#line 2 "stack"
#endif

#include <errno.h>
#include "../common.h"

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

// handy types
// may change number_t to object_t or so in the future
typedef long double number_t;
typedef struct s_stack stack_t;

// subject to change -- maybe to be an array of other things too
struct s_stack {
  // list of long doubles
  number_t* data;
  // points to the top
  ssize_t    ptr;
};

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
void (* stack_ops[]) (stack_t *) = {
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

/*
  stack_new: returns a new stack_t* object, heap allocated

  data is INITIAL_STACKSIZE * (long double)0.0f, and ptr is -1 to indicate
  empty stack.

  TODO: grow (?)
*/
stack_t* stack_new (void) {
  pfn(__FILE__, __LINE__, __func__);

  stack_t* out = safemalloc(sizeof (stack_t));
  out->data    = calloc(INITIAL_STACKSIZE, sizeof (number_t));
  out->ptr     = -1;
  return out;
}

/*
  stack_destruct: demolish a stack_t created by stack_new

  quite simple now, but if / when stk->data is an array of
  struct types, will be more complex
*/
void stack_destruct (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  safefree(stk->data), safefree(stk);
}

bool stack_isempty (const stack_t* stk) {
  return (stk->ptr) == -1;
}

/*
  stack_incr: increment the stack pointer by one, as long as it is less
  than INITIAL_STACKSIZE.

  in the future, when the stack can grow and shrink using realloc(3),
  this function will need to change.

  calls void error() if incrementing the stack pointer would exceed
  INITIAL_STACKSIZE.
*/
void stack_incr (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  ssize_t newval = (stk->ptr) + 1;

  if (newval >= INITIAL_STACKSIZE) {
    error(ERROR_STACK_OVERFLOW, "stack_incr");
    return;
  }

  ++(stk->ptr);
}

/*
  stack_decr: decrement the stack pointer by one, as long as it is
  greater than -1.

  if the stack becomes growable in the future, this can probably stay.
*/
void stack_decr (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if ( stack_isempty(stk) ) {
    error(ERROR_STACK_UNDERFLOW, "stack_decr");
    return;
  }

  --(stk->ptr);
}

number_t stack_get (const stack_t* stk, const ssize_t idx) {
  pfn(__FILE__, __LINE__, __func__);

  if ( stack_isempty(stk) ) {
    error(ERROR_STACK_UNDERFLOW, "stack_get");
    assert( ! stack_isempty(stk) );
    return 0.f;

  } else if ( idx < 0 ) {
    error(ERROR_BAD_INDEX, "stack_get");
    assert( idx > 0 );
    return 0.f;
  }


  assert(idx <= INITIAL_STACKSIZE);

  return stk->data[idx];
}

void stack_set (stack_t* stk, const ssize_t idx, const number_t val) {
  pfn(__FILE__, __LINE__, __func__);

  if ( idx < 0 ) {
    error(ERROR_BAD_INDEX, "stack_set");
    assert( idx > 0 );
    return;
  }

  assert(idx <= INITIAL_STACKSIZE);

  stk->data[idx] = val;
}


/*
  stack_push: appends a new object to the stack, and points to it.

  since the stack pointer always points to the top element, not past it,
  it is important the pointer is incremented before the new value is
  assigned except when ptr is 0.
*/
void stack_push (stack_t* stk, number_t val) {
  pfn(__FILE__, __LINE__, __func__);

  stack_incr(stk);
  stack_set(stk, stk->ptr, val);

}

/*
  stack_top: reads the top item from the stack pointed to by *stk.

  does not modify *stk.
*/
number_t stack_top (const stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if ( stack_isempty(stk) ) {
    return 0.f;
  }

  return stack_get(stk, stk->ptr);
}

/*
  stack_pop: pops the top item from the stack pointed to by *stk,
  returning it.

  unlike number_t stack_top(), modifies *stk.
*/
number_t stack_pop (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if ( stack_isempty(stk) ) {
    error(ERROR_EMPTY_STACK, "stack_pop (empty stack)");
    return 0.f;
  }

  number_t out = stack_top(stk);
  stack_set(stk, stk->ptr, 0);
  stack_decr(stk);
  return out;
}

/*
  stack_size: returns the number of elements currently on the
  stack pointed to by *stk.

  this function mostly exists to avoid messy and possibly erroneous
  code which assigns to stk->ptr.

  this function returns the index as an unsigned size_t. this is for
  code simplicity. to check if the stack is empty, either use
  bool stack_isempty() or test if
  size_t stack_size() > INITIAL_STACKSIZE (the value will wrap on a
  two's complement system).
*/
size_t stack_size (const stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  return (size_t) ((stk->ptr) + 1);
}

/*
  stack_drop: drops the top item from the stack pointed to by *stk,
  without returning it.
*/
void stack_drop (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_pop(stk);
}

/*
  stack_see: format the stack pointed to by *stk as a series of
  space-separated long doubles using format specifier %LG, with the
  top item first and the bottom item last.
*/
char* stack_see (const stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if ( stack_isempty(stk) ) {
    char* o = safemalloc(15);
    snprintf(o, 15, "%s", "(empty)");
    return o;
  }

  // this is ok because we already checked if the stack was empty
  size_t num_elts = stack_size(stk),
         new_len  = 0;

  char** to_str = safemalloc(sizeof (char *) * num_elts);

  for (
    size_t i = (num_elts - 1);
    (i + 1) != 0;
    i--
  ) {
    // INITIAL_STACKSIZE is never large enough that casting
    // here will cause issues
    number_t val = stack_get(stk, (ssize_t) i);
    // + 2 for space & good measure (null byte?)
    size_t needed = 2 + atoi_strlen(val);

    to_str[i] = safemalloc(sizeof (char) * needed);

    snprintf(to_str[i], needed, "%LG", val);

    new_len += needed;
  }

  char* output = safemalloc(sizeof (char) * new_len),
       *bufend = output;

  for (size_t i = 0; i < num_elts; i++) {
    // "normalise" to read in reverse order
    size_t nml_val = (num_elts - 1) - i;
    bufend += snprintf(bufend, 20, "%s ", to_str[nml_val]);
  }

  free_ptr_array((void **) to_str, num_elts);

  return output;
}


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
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b - a);
}
/*
  effect: ( x y -- pow(x,y) )
  operator pow: push the result of x raised to the y power.
*/
void    stack_op_pow (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, powl(a, b));
}
/*
  effect: ( x -- )
  operator drop: drop the top item off the stack pointed to by *stk.
*/
void    stack_op_drp (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_pop(stk);
}
/*
  effect: ( x y -- y x )
  operator swap: swap the top two operands.
*/
void    stack_op_swp (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

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
  const; this is because the operators must share a type.
*/
void    stack_op_prn (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%LG", stack_top(stk));
}
/*
  effect: ( x -- )
  operator prn_dispose: print the top item on the stack pointed to
  by *stk, discarding it in the process.

  unlike prn, modifies *stk.
*/
void    stack_op_prn_dispose (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%LG", stack_pop(stk));
}
/*
  effect: ( x -- )
  operator prc: print the top item on the stack as an ASCII character
  and discard it.

  applies no formatting whatsoever.
*/
void    stack_op_prc (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%c", (int) floorl( stack_pop(stk) ) );
}
/*
  effect: ( x -- x )
  operator see: call stack_see on the stack pointed to by *stk,
  without modifying it.
*/
void    stack_op_see (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_see(stk);
}

/* END OPERATORS */

/*
  get_stackop: return the index of the operator string pointed to
  by *op in stack_ops, or -1 if the operator is not defined.
*/
ssize_t      get_stackop (const char* const op) {
  pfn(__FILE__, __LINE__, __func__);

  for (size_t i = 0; i < NUM_STACKOPS; i++) {
    if ( ! strncmp(op, ops_tostring[i], 5) ) {
      return (ssize_t) i;
    }
  }
  return -1;
}

/*
  perform_op: currently a no-op. will call the function with the
  name pointed by *op on the stack pointed to by *stk.
*/
void      perform_op (stack_t* stk, const char* const op) {
  pfn(__FILE__, __LINE__, __func__);

  (void) stk, (void) op;
/*  ssize_t opidx;

  if ( ( opidx = get_stackop(op) ) != -1 ) {
    stack_ops[opidx](stk);

  } else {
    printf("%s: operator not defined\n", op);
  }
*/
}

/*
  error: writes an error message based on args and errno. neither
  optimal nor used, yet.
*/
void error (size_t err, const char* const info) {
  pfn(__FILE__, __LINE__, __func__);

  static const char* const errstrings[] = {
    "Data stack overflowed (too many values)",
    "Data stack underflowed (not enough values)",
    "Value overflows type 'long double' (value too large)",
    "Attempt to divide by zero leads to incomplete or inexpressable value (n / 0)",
    "Bad literal string for conversion (unexpected radix or non-digit)",
    "Input string cannot possibly be converted to a number",
    "Empty data stack (underflow)",
    "Attempt to access memory with a negative index leads to undefined behaviour",
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

/*
  atoi_strlen: return the number of bytes it would take to format
  val as a string with the %LG format specifier.

  uses snprintf(3), and the max is 100, which is way above the max
  ever used by %LG for any long double.
*/
size_t atoi_strlen (number_t val) {
  pfn(__FILE__, __LINE__, __func__);

  char* buf = safemalloc(100);
  size_t len = (size_t) snprintf(buf, 100, "%LG", val);

  safefree(buf);
  return len;
}

/*
  is_base10: returns whether a string consists of a valid base 10
  number.

  TODO: improve, write more tests. not optimal.
*/
bool is_base10 (const char *str) {
  pfn(__FILE__, __LINE__, __func__);

  // quickly invalidate str
  if ( (!str_count(str, DEC_DIGITS))
    || (str_count(str, "+-") > 1)
    || (str_count(str, ".") > 1)
  ) {
    return false;
  }

  size_t len = safestrnlen(str);

  static const char sign_chars[] = { '-', '.', '+' };

  for (size_t i = 0; i < len; i++) {
    char tmpbuf[2];
    snprintf(tmpbuf, 2, "%c", str[i]);

    bool ismisc   = false,
         isnum    = false,
         validch  = false,
         validpos = true;


    ismisc   = 1 == str_count(sign_chars, tmpbuf);

    isnum    = ( str[i] >= '0' ) && ( str[i] <= '9' );
    validch  = ismisc || isnum;

    if ( ( str[i] == '+' ) || ( str[i] == '-' ) ) {
      validpos = i == 0 ? true : false ;
    }

    //printf("%zu: %d valid: %d\n", i, str[i], validpos );

    if ( !validch || !validpos ) {
      return false;
    }
  }
  return true;
}

/*
  str_to_number_array: return a pointer to an array created by
  interpreting a string as a delimited list of number_ts.
*/
number_t* str_to_number_array (
  const char*   str,
  const char*   remove_at,
  const char    split_at,
        size_t* out_len
) {
  pfn(__FILE__, __LINE__, __func__);

  number_t* out;

  size_t len;
  char* rmd = str_rm(str, remove_at, &len);

  char** split = str_split(rmd, split_at, &len);
  out = safemalloc(sizeof (number_t *) * len);

  for (size_t i = 0; i < len; i++) {
    out[i] = strtold(split[i], NULL);
  }

  *out_len = len;
  return out;
}

void stack_dbgp (const stack_t* stk) {
  static unsigned long long count;
  ++count;
  char* s = stack_see(stk);
  dbg_prn("debug(%lld): %s\n", count, s);
  safefree(s);
}
