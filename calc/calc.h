#ifdef GCC
#line 2 "calc"
#endif

#include "stack.h"

void interpret (void);
void    run_str(const char* const, stack_t* stk);

void interpret (void) {
  pfn(__FILE__, __LINE__, __func__);

  printf(
    "Stack-based calculator\n"
    "Enter a list of commands to run.\n\n"
  );

  stack_t* stk = stack_new();

  while (true) {

    printf("> ");

    char* in = readln(MAX_STR_LEN);

    if (!safestrnlen(in)) {
      safefree(in);
      continue;
    } else if (in[0] == 4) {
      safefree(in);
      break;
    } else {
      run_str(in, stk);
      safefree(in);
    }
  }

  char* o = stack_see(stk);
  printf("data stack: %s\n", o);
  safefree(o);
  stack_destruct(stk);
}

void run_str (const char* const prog, stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if (prog == NULL) {
    return;
  }

  for (size_t i = 0; i < safestrnlen(prog); i++) {
    dbg_prn("%d ", prog[i]);
  }

  size_t len;
  number_t tmp = 0;

  char *val,
       *error = NULL,
       **spl_prog = str_split(prog, ' ', &len);

  for (size_t i = 0; i < len; i++) {
    val = spl_prog[i];

    for (size_t z = 0; z < safestrnlen(val); z++) {
      dbg_prn("chr %zu: %d\n", z, val[z]);
    }

    tmp = strtold(val, &error);

    if ( !safestrnlen(error) ) {
      stack_push(stk, tmp);

    } else {
      //perform_op(stk, val);
      ssize_t opidx = get_stackop(val);

      if ( opidx > -1 ) {
        stack_ops[opidx](stk);

      } else {
        printf("%s: operator not defined\n", val);
      }

    }

  }

  for (size_t i = 0; i < len; i++) {
    safefree(spl_prog[i]);
  }

  safefree(spl_prog);

  char* o = stack_see(stk);
  printf("\nstack: %s\n", o);
  safefree(o);
}
