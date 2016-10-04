#ifdef GCC
#line 2 "calcmain"
#endif

#ifndef NODEBUG
#define DEBUG
#endif

#include "calc.h"

int main (int len_args, const char* const* const args) {

  if (1 == len_args) {
    interpret();

  } else {
    // cat
    size_t len;
    char* a  = strip_comments(file_lines(args[1], &len), len, '~');
    printf("%s\n", a);
    safefree(a);
  }

  return EXIT_SUCCESS;
}
