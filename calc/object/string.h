#ifdef GCC
#line 2 "string"
#endif

#include "objcommon.h"

string_t* string_new (const char* const c) {
  pfn();

  string_t* s = safemalloc(sizeof (string_t));
  size_t  len = safestrnlen(c);

  s->len  = len;
  s->data = strndup(c, len);

  return s;
}

string_t* string_copy (const string_t* const s) {
  pfn();

  return string_new(s->data);
}

bool string_isempty (const string_t* const s) {
  pfn();

  return s->len == 0;
}

void string_destruct (string_t* const string) {
  pfn();

  report_dtor(string);

  safefree(string->data);
}
