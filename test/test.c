#include "test.h"

int main (void) {
  size_t l;
  char* a = str_repeat("'", 3, &l);
  printf("%s\n", a);
  safefree(a);
  return 0;
}
