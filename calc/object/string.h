#ifdef GCC
#line 2 "string"
#endif

#include "objcommon.h"

string_t* string_new (const char* const c) {
  pfn();

  string_t* string = safemalloc(sizeof (string_t));
  size_t       len = safestrnlen(c);

  string->len  = len;
  string->data = strndup(c, len);

  report_ctor(string);

  return string;
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
