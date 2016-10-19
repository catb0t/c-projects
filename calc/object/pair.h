#include "objcommon.h"

#ifdef GCC
#line __LINE__ "pair"
#endif

pair_t*   pair_new (const object_t* const car, const object_t* const cdr) {
  pair_t*  pair = (typeof(pair)) safemalloc( sizeof (pair_t) );

  pair->car = object_copy(car),
  pair->cdr = object_copy(cdr);

  report_ctor(pair);

  return pair;
}

pair_t*  pair_copy (const pair_t* const p) {
  return pair_new(p->car, p->cdr);
}

char* pair_see (const pair_t* const p) {
  char
    *scar = object_repr(p->car), // 1
    *scdr = object_repr(p->cdr), // 2
    *buf;

  size_t buflen = safestrnlen(scar) + safestrnlen(scdr) + 11;
   buf = (typeof(buf)) safemalloc(sizeof (char) * buflen);
  snprintf(buf, buflen, "{ %s . %s }", scar, scdr);

  safefree(scar), safefree(scdr);

  return buf;
}

object_t* pair_car_copy (const pair_t* const p) { return object_copy(p->car); }
object_t* pair_cdr_copy (const pair_t* const p) { return object_copy(p->cdr); }

object_t** pair_car_ref (pair_t* const p) { return &(p->car); }
object_t** pair_cdr_ref (pair_t* const p) { return &(p->cdr); }

bool   pair_equals (const pair_t* const a, const pair_t* const b) {
  return
       object_equals(a->car, b->car)
    && object_equals(a->cdr, b->cdr);
}

void pair_destruct (pair_t* const pair) {
  report_dtor(pair);

  object_dtor_args(2, pair->car, pair->cdr);
  safefree(pair);
}

// void pair_cons (pair_t* const p, const object_t* cdr) { }