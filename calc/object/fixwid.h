#ifdef GCC
#line 2 "fixwid"
#endif

#include "objcommon.h"

fixwid_t* fixwid_new (const ssize_t n) {
  pfn();

  fixwid_t* fixwid = safemalloc( sizeof(fixwid_t) );

  fixwid->value = n;

  report_ctor(fixwid);

  return fixwid;
}

void  fixwid_destruct (fixwid_t* const fixwid) {
  pfn();

  report_dtor(fixwid);
  safefree(fixwid);
}

fixwid_t* fixwid_copy (const fixwid_t* const n) {
  pfn();

  return fixwid_new(n->value);
}

char* fixwid_see (const fixwid_t* const n) {
  pfn();

  char* buf = safemalloc( sizeof(char) * ULL_DIGITS );
  snprintf( buf, ULL_DIGITS, "%zd", n->value );

  buf = realloc(buf, sizeof (char) * safestrnlen(buf));
  return buf;
}

bool fixwid_eq (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  return a->value == b->value;
}

bool    fixwid_gt (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  return a->value > b->value;
}

bool    fixwid_lt (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  return a->value < b->value;
}
