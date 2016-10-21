#include "objcommon.h"

#ifdef GCC
#line __LINE__ "number"
#endif

number_t* number_new (const numderlying_t val) {
  pfn();

  number_t*  number = (typeof(number)) safemalloc(sizeof (number_t));
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

  char*  buf = (typeof(buf)) safemalloc(30);
  snprintf(buf, 30, "%LG", num->value);
  buf = (typeof(buf)) saferealloc(buf, safestrnlen(buf));

  return buf;
}

bool number_eq (const number_t* const a, const number_t* const b) {
  pfn();

  numderlying_t
    an = a->value,
    bn = b->value;

  return fabsl(an - bn) < LD_EPSILON;
}

bool number_gt (const number_t* const a, const number_t* const b) {
  pfn();

  numderlying_t an = a->value, bn = b->value;
  return an > bn;
}

bool number_lt (const number_t* const a, const number_t* const b) {
  pfn();

  numderlying_t an = a->value, bn = b->value;
  return an > bn;
}
