#ifdef GCC
#line 2 "number"
#endif

#include "objcommon.h"

number_t* number_new (const long double val) {
  pfn();

  number_t* number = safemalloc(sizeof (number_t));
  number->value = val;

  report_ctor(number);
  return number;
}

number_t* number_copy (const number_t* const num) {
  pfn();

  return number_new(num->value);
}

void number_destruct (number_t* const number) {
  pfn();

  report_dtor(number);
  safefree(number);
}

char* number_see (const number_t* const num) {
  pfn();

  char* buf = safemalloc(30);
  snprintf(buf, 30, "%LG", num->value);
  buf = realloc(buf, safestrnlen(buf));

  return buf;
}
