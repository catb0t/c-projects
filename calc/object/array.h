#ifdef GCC
#line 2 "array"
#endif

#include "objcommon.h"

bool array_isempty (const array_t* const a) {
  pfn(__FILE__, __LINE__, __func__);
  return a->len == -1 || (NULL == a->data);
}

array_t* array_copy (const array_t* const a) {
  pfn(__FILE__, __LINE__, __func__);

  array_t* out = safemalloc(sizeof (array_t));

  if ( ! array_isempty(a) ) {
    out->data = safemalloc(sizeof (object_t *) * (size_t) a->len);
    out->len  = a->len;

    for (ssize_t i = 0; i < (out->len); i++) {
      out->data[i] = object_copy(a->data[i]);
    }
    return out;
  }

  out->data = NULL;
  out->len  = -1;

  return out;
}
