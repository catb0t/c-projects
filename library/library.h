#include "../calc/object/object.h"

void test (void);

void test (void) {

  char* buf     = readln(MAX_STR_LEN);
  long double a = strtold(buf, NULL);
  number_t* num = number_new(a);
  object_t* obj = object_new(t_number, (void *) num);

  char* repr = object_repr(obj);

  const Fnv32_t hval = fnv_32a_str(repr, FNV1_32A_INIT);

  printf("%u\n", hval);

  object_destruct(obj);
  number_destruct(num);
  safefree(buf);
  safefree(repr);
}
