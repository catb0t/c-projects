#ifdef GCC
#line 2 "calcmain"
#endif

#include "calc.h"
//#include "lex.h"

int main (int len_args, const char* const* const args) {

  if (1 == len_args) {
    interpret();

  } else {
    (void) args;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
