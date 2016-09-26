#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (void) {
  interpret();
/*
  while (true) {
    printf("> ");
    char* in = readln(MAX_STR_LEN);
    number_t told = strtold(in, NULL);
    printf(
       "%s is %zu length\n"
      "%LG is %zu length\nlengths match: %s\n",
      in, safestrnlen(in),
      told, atoi_strlen(told),
      atoi_strlen(told) == safestrnlen(in) ? "yes" : "no"
    );
  }

  char* in = readln(MAX_STR_LEN);
  printf("%d\n", in[safestrnlen(in)-1]);
  number_t x = strtold(in, NULL);
  printf("%Lf\n", x);
*/
  return 0;
}
