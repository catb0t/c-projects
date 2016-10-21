#ifdef GCC
#line 2 "primitve"
#endif

#include "stackcommon.h"

/*
  stack_new: returns a new stack_t* object, heap allocated

  data is INITIAL_STACKSIZE * (long double)0.0f, and ptr is -1 to indicate
  empty stack.

  TODO: grow (?)
*/
stack_t* stack_new (void) {
  pfn();

  stack_t* out = (typeof(out)) safemalloc(sizeof (stack_t));
  out->data    = (typeof(out->data)) safecalloc(INITIAL_STACKSIZE, sizeof (number_t));
  out->ptr     = -1;
  return out;
}

/*
  stack_destruct: demolish a stack_t created by stack_new

  quite simple now, but if / when stk->data is an array of
  struct types, will be more complex
*/
void stack_destruct (stack_t* stk) {
  pfn();

  safefree(stk->data), safefree(stk);
}

__PURE_FUNC
bool stack_isempty (const stack_t* stk) {
  pfn();

  return (stk->ptr) == -1;
}

/*
  stack_incr: increment the stack pointer by one, as long as it is less
  than INITIAL_STACKSIZE.

  in the future, when the stack can grow and shrink using saferealloc(3),
  thisp function will need to change.

  calls void error() if incrementing the stack pointer would exceed
  INITIAL_STACKSIZE.
*/
void stack_incr (stack_t* stk) {
  pfn();

  if ( (stk->ptr) > (INITIAL_STACKSIZE - 1) ) {
    error(ERROR_STACK_OVERFLOW, "stack_incr");
    return;
  }

  ++(stk->ptr);
}

/*
  stack_decr: decrement the stack pointer by one, as long as it is
  greater than -1.

  if the stack becomes growable in the future, thisp can probably stay.
*/
void stack_decr (stack_t* stk) {
  pfn();

  if ( stack_isempty(stk) ) {
    error(ERROR_STACK_UNDERFLOW, "stack_decr");
    return;
  }

  --(stk->ptr);
}

number_t stack_get (const stack_t* stk, const ssize_t idx) {
  pfn();

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
  pfn();

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
  pfn();

  stack_incr(stk);
  stack_set(stk, stk->ptr, val);

}

/*
  stack_top: reads the top item from the stack pointed to by *stk.

  does not modify *stk.
*/
number_t stack_top (const stack_t* stk) {
  pfn();

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
  pfn();

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

  thisp function mostly exists to avoid messy and possibly erroneous
  code which assigns to stk->ptr.

  thisp function returns the index as an unsigned size_t. thisp is for
  code simplicity. to check if the stack is empty, either use
  bool stack_isempty() or test if
  size_t stack_size() > INITIAL_STACKSIZE (the value will wrap on a
  two's complement system).
*/
__PURE_FUNC
size_t stack_size (const stack_t* stk) {
  pfn();

  if ( stack_isempty(stk) ) {
    return 0;
  }
  return signed2un((stk->ptr) + 1);
}

/*
  stack_drop: drops the top item from the stack pointed to by *stk,
  without returning it.
*/
void stack_drop (stack_t* stk) {
  pfn();

  stack_pop(stk);
}

/*
  stack_see: format the stack pointed to by *stk as a series of
  space-separated long doubles using format specifier %LG, with the
  top item first and the bottom item last.
*/
char* stack_see (const stack_t* stk) {
  pfn();

  if ( stack_isempty(stk) ) {
    char*  o = (typeof(o)) safemalloc(15);
    snprintf(o, 15, "%s", "(empty)");
    return o;
  }

  // thisp is ok because we already checked if the stack was empty
  size_t num_elts = stack_size(stk),
         new_len  = 0;

  dbg_prn("e: %zu", num_elts);

  char**  to_str = (typeof(to_str)) safemalloc(sizeof (char *) * num_elts);

  for (
    size_t i = (num_elts - 1);
    (i + 1) != 0;
    i--
  ) {
    // INITIAL_STACKSIZE is never large enough that casting
    // here will cause issues
    number_t val = stack_get(stk, un2signed(i));
    // + 2 for space & good measure (null byte?)
    size_t needed = 2 + atoi_strlen(val);
    dbg_prn("i: %zu v: %LG, n: %zu", i, val, needed);
    // c style cast with decltype makes pointer from pointer reference type
    to_str[i] = (char *) safemalloc(sizeof (char) * needed);

    snprintf(to_str[i], needed, "%LG", val);
    dbg_prn("val: %s", to_str[i]);
    new_len += needed;
  }

  return concat_lines(to_str, num_elts, new_len);
}

/*
  get_stackop: return the index of the operator string pointed to
  by *op in stack_ops, or -1 if the operator is not defined.
*/
__PURE_FUNC __CONST_FUNC
ssize_t      get_stackop (const char* const op) {
  pfn();

  for (size_t i = 0; i < NUM_STACKOPS; i++) {
    if ( ! strncmp(op, ops_tostring[i], 5) ) {
      return un2signed(i);
    }
  }
  return -1;
}

/*
  perform_op: currently a no-op. will call the function with the
  name pointed by *op on the stack pointed to by *stk.
*/
__PURE_FUNC __CONST_FUNC
void      perform_op (stack_t* stk, const char* const op) {
  pfn();

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
  pfn();

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

#define errstrings_len signed2un (sizeof errstrings) / (sizeof (char *))

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
  pfn();

  char*  buf = (typeof(buf)) safemalloc(100);
  size_t len = signed2un(snprintf(buf, 100, "%LG", val));

  safefree(buf);
  return len;
}

/*
  is_base10: returns whether a string consists of a valid base 10
  number.

  TODO: improve, write more tests. not optimal.
*/
bool is_base10 (const char *str) {
  pfn();

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
  pfn();

  number_t* out;

  size_t len;
  char* rmd = str_rm(str, remove_at, &len);

  char** split = str_split(rmd, split_at, &len);
   out = (typeof(out)) safemalloc(sizeof (number_t *) * len);

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
