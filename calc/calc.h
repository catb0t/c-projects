#include "stack.h"

void interpret (void);
void    run_str(const char* const, stack_t* stk);

void interpret (void) {
  printf(
    "Stack-based calculator\n"
    "Enter a list of commands to run.\n\n"
  );

  char* in;
  stack_t* stk = stack_new();

  while (true) {
    printf("> ");
    in = readln(MAX_STR_LEN);
    if (!in) { break; }
    run_str(in, stk);
    safefree(in);
  }

  char* o = stack_see(stk);
  printf("data stack: %s\n", o);
  safefree(o);
  stack_destruct(stk);
}

void run_str(const char* const prog, stack_t* stk) {
  size_t len;
  number_t tmp;

  char *val,
       **spl_prog = str_split(prog, ' ', &len);

  for (size_t i = 0; i < len; i++) {
    val = spl_prog[i];

    if ( sscanf(val, "%Lf", &tmp), !errno ) {
      stack_push(stk, tmp);

    } else {
      //perform_op(stk, val);
      ssize_t opidx;
      
      if ( ( opidx = get_stackop(val) ) != -1 ) {
        stack_ops[opidx](stk);

      } else {
        printf("%s: operator not defined\n", val);
      }

    }

  }

  char* o = stack_see(stk);
  printf("stack: %s\n", o);
  safefree(o);
}
