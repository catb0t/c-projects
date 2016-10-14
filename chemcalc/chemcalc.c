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

  size_t b = 2;
  isotope_t** isos = safemalloc( sizeof (isotope_t*) * b);

  isos[0] = isotope_new(.5069, 078.92);
  isos[1] = isotope_new(.4931, 80.92);


  printf("%LG\n", amass_from_isos((const isotope_t* const * const) isos, b));
}

int main(void) {

  test();

  return EXIT_SUCCESS;
}
