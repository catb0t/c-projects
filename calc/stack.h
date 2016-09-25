#ifdef GCC
#line 2 "stack"
#endif
#include <errno.h>
#include "../common.h"

#define INITIAL_STACKSIZE 512

enum errortypes {
  ERROR_STACK_OVERFLOW,  // 0
  ERROR_STACK_UNDERFLOW, // 1
  ERROR_VALUE_OVERFLOW,  // 2
  ERROR_ZERO_DIVISION,   // 3
  ERROR_LITERAL_JUNK,    // 4
  ERROR_NOT_A_NUMBER,    // 5
};

typedef long double number_t;
typedef struct stack stack_t;

struct stack {
  number_t* data;
  size_t    ptr;
};

size_t count_igrlplaces (number_t val);
size_t count_fracplaces (number_t val);
size_t      atoi_strlen (number_t val);
void              error (size_t err, const char* const info);
bool          is_base10 (const char *nptr);

char* stack_see (const stack_t* stk);
void stack_incr (stack_t* stk);
void stack_decr (stack_t* stk);
void stack_push (stack_t* stk, number_t val);
void stack_drop (stack_t* stk);

stack_t* stack_new (void);
number_t stack_top (const stack_t* stk);
number_t stack_pop (stack_t* stk);

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
  "#+", // add
  "#*", // mul
  "#/", // divmod
  "#-", // sub
  "#^", // pow
  "$%", // swap
  "$,", // drop
  "!!", // prn
  "!.", // see
  "!,", // prc
};

#define NUM_STACKOPS (size_t) (sizeof ops_tostring) / (sizeof (char *))

stack_t* stack_new (void) {
  pfn(__FILE__, __LINE__, __func__);

  stack_t* out = safemalloc(sizeof (stack_t));
  out->data    = calloc(INITIAL_STACKSIZE, sizeof (number_t));
  out->ptr     = 0;
  return out;
}

void stack_destruct (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  safefree(stk->data), safefree(stk);
}

void stack_incr (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if (( stk->ptr + 1 ) >= INITIAL_STACKSIZE) {
    error(ERROR_STACK_OVERFLOW, "stack_incr");
    return;
  }

  ++stk->ptr;
}

void stack_decr (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if (( ( (ssize_t) stk->ptr ) - 1 ) < 0) {
    error(ERROR_STACK_UNDERFLOW, "stack_decr");
    return;
  }

  --(stk->ptr);
}

void stack_push (stack_t* stk, number_t val) {
  pfn(__FILE__, __LINE__, __func__);

  stk->data[stk->ptr] = val;
  stack_incr(stk);
}

number_t stack_top (const stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  return stk->data[stk->ptr];
}

number_t stack_pop (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t out = stk->data[stk->ptr];
  stack_decr(stk);
  return out;
}

void stack_drop (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_pop(stk);
}

char* stack_see (const stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  size_t num_elts = stk->ptr,
         new_len = 0;

  if (!num_elts) {
    char* output = safemalloc(1);
    snprintf(output, 1, "%s", "");
    return output;
  }

  char **str_list = safemalloc(sizeof (char *) * (num_elts)),
       *output;

  for (size_t i = 0; i < num_elts; i++) {
    number_t curdata = (stk->data)[i];
    size_t needed    = atoi_strlen(curdata);
    str_list[i]      = safemalloc(sizeof (char) * needed);

    snprintf(str_list[i], needed, "%LG", curdata);

    new_len += needed;
  }

  printf("new_len: %zu\n", new_len);  
  output = safemalloc(sizeof (char) * new_len);
  char* bufptr = output;

  for (size_t i = 0; i < num_elts; i++) {
    bufptr += snprintf(bufptr, 20, "%s ", str_list[i]);
    safefree(str_list[i]);
  }

  safefree(str_list);

  return output;
}

void    stack_op_add (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b + a);
}
void    stack_op_mul (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b * a);
}
void stack_op_divmod (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = (long double) stack_pop(stk);
  number_t b = (long double) stack_pop(stk);

  stack_push(stk, (number_t) ( ( (signed long long) b ) % ( (signed long long) a ) ));
  stack_push(stk, b / a);
}
void    stack_op_sub (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, b - a);
}
void    stack_op_pow (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, powl(a, b));
}
void    stack_op_drp (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_pop(stk);
}
void    stack_op_swp (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  number_t a = stack_pop(stk);
  number_t b = stack_pop(stk);

  stack_push(stk, a);
  stack_push(stk, b);
}
void    stack_op_prn (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%Lf\n", stack_top(stk));
}
void    stack_op_prn_dispose (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%Lf", stack_pop(stk));
}
void    stack_op_prc (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  printf("%c", (int) floorl( stack_pop(stk) ) );
}
void    stack_op_see (stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  stack_see(stk);
}


ssize_t      get_stackop (const char* const op) {
  pfn(__FILE__, __LINE__, __func__);

  for (size_t i = 0; i < NUM_STACKOPS; i++) {
    if ( strncmp(op, ops_tostring[i], 5) ) {
      return (ssize_t) i;
    }
  }
  return -1;
}

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


void error (size_t err, const char* const info) {
  pfn(__FILE__, __LINE__, __func__);

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

size_t atoi_strlen (number_t val) {
  pfn(__FILE__, __LINE__, __func__);

  char* buf = safemalloc(100);
  size_t len = (size_t) snprintf(buf, 99, "%LG", val);

  // safestrnlen(buf);

  safefree(buf);
  return len;
}

bool is_base10 (const char *str) {
  pfn(__FILE__, __LINE__, __func__);

  // quickly invalidate str
  if (
    (!str_count(str, "0123456789"))
    || (str_count(str, "+-") > 1)
    || (str_count(str, ".") > 1)
  ) {
    return false;
  }

  size_t len = safestrnlen(str);

  //
  static const char misc_numeric_chars[] = { '-', '.', '+' };

  char tmpbuf[2];

  for (size_t i = 0; i < len; i++) {
    sprintf(tmpbuf, "%c", str[i]);

    bool ismisc   = false,
         isnum    = false,
         validch  = false,
         validpos = true;


    ismisc   = 1 == str_count(misc_numeric_chars, tmpbuf);
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
    out[i] = strtod(split[i], NULL);
  }

  *out_len = len;
  return out;
}
