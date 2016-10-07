#include "chemcalc.h"

void test (void);

void test (void) {

/*  char
    *in, *name, *symb;

  printf("Element name: ");
  name = readln(MAX_STR_LEN);

  printf("Element symbol: ");
  symb = readln(3);
*/

  isotope_t** isos = safemalloc( sizeof (isotope_t*) * 3);

  isos[0] = isotope_new(.365, .48);
  isos[1] = isotope_new(.123, .157);
  isos[2] = isotope_new(.438, .18);

  printf("%LG\n", amass_from_isos((const isotope_t* const * const) isos, 3));
}

int main(void) {

  test();

  return EXIT_SUCCESS;
}
