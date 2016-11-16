#include "objcommon.h"

#ifdef GCC
#line __LINE__ "string"
#endif

string_t* string_new (const char* const c) {
  pfn();

  string_t*  string = (typeof(string)) safemalloc(sizeof (string_t));
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
  safefree(string);
}

define_objtype_dtor_args(string);

char* string_see (const string_t* const s) {
  size_t buflen = sizeof (char) * (s->len + 3);

  char* buf = (typeof(buf)) safemalloc(buflen);
  snprintf(buf, buflen, "\"%s\"", s->data);
  return buf;
}

