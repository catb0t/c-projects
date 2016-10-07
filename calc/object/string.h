#ifdef GCC
#line 2 "string"
#endif

#include "objcommon.h"

string_t* string_new (const char* const c) {
  pfn(__FILE__, __LINE__, __func__);

  string_t* s = safemalloc(sizeof (string_t));
  size_t len = safestrnlen(c);

  s->len  = len ? (ssize_t) len : -1 ;
  s->data = strndup(c, len);

  return s;
}

string_t* string_copy (const string_t* const s) {
  pfn(__FILE__, __LINE__, __func__);
  return string_new(s->data);
}
