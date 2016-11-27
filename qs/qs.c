#include "qs.h"

int main(const int argc, const char* const * argv) {

  if ( argc - 1 ) {
    unsigned long index = strtoul(argv[1], NULL, DEC_BASE);

    if ( (index > NUM_QUESTIONS) || !index ) {
      printf("wrong index (argument 1): %ld: expected 1-%d\n", index, NUM_QUESTIONS);
      return EXIT_FAILURE;
    }

    ( q_funcs [index - 1] ) ();

  } else {

    for (size_t i = 0; i < NUM_QUESTIONS; i++) {
      printf("\n=== QUESTION %zd ===\n\n", i + 1);
      (q_funcs [i] ) ();
    }

  }

  return EXIT_SUCCESS;
}
