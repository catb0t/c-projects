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
    char** fl = file_lines(args[1], &len);
    for (size_t i = 0; i < len; i++) {
      printf("%s\n", fl[i]);
    }
    free_ptr_array((void **) fl, len);
  }

  return EXIT_SUCCESS;
}
