#ifdef GCC
#line 2 "array"
#endif

#include "objcommon.h"

array_t* array_new (const object_t* const * const objs, const ssize_t len) {
  array_t* out = safemalloc( sizeof (array_t) );
  out->data    = safemalloc( sizeof (object_t *) );

  if (-1 != len) {
    for (ssize_t i = 0; i < len; i++) {
      out->data[i] = object_copy(objs[i]);
    }

  }
  out->idx = len;

  report_ctor("array", out);

  return out;
}

array_t* array_copy (const array_t* const a) {
  pfn(__FILE__, __LINE__, __func__);

  array_t* out = safemalloc(sizeof (array_t));

  if ( ! array_isempty(a) ) {
    out->data = safemalloc(sizeof (object_t *) * (size_t) a->idx);
    out->idx  = a->idx;

    for (ssize_t i = 0; i < (out->idx); i++) {
      out->data[i] = object_copy(a->data[i]);
    }
    return out;
  }

  out->data = NULL;
  out->idx  = -1;

  report_ctor("array", out);

  return out;
}

void array_destruct (array_t* const a) {

  report_dtor("array", a);

  if ( ! array_isempty(a) ) {
    for (ssize_t i = 0; i < a->idx; i++) {
      object_destruct( (a->data) [i]);
    }
  }
  if (NULL != a->data) {
    safefree(a->data);
  }
  safefree(a);
}

bool array_isempty (const array_t* const a) {
  pfn(__FILE__, __LINE__, __func__);
  return -1 == a->idx || (NULL == a->data);
}

void array_resize (array_t* const a, const ssize_t new_idx) {
  if ( -1 == new_idx ) {
    a->data = realloc(a->data, 0);
    a->idx = -1;
    return;
  }
  a->idx  = (ssize_t) new_idx;
  a->data = realloc(a->data, sizeof (object_t*) * (size_t) new_idx);
}

void array_delete (array_t* const a, const ssize_t idx) {
  if (-1 == idx || idx == a->idx) {
    array_resize(a, idx);
    return;
  }

  size_t uidx = (size_t) idx - 1 > -1 ? idx : 0;

  object_t** front = safemalloc(sizeof (object_t *) * uidx);
  for (size_t i = 0; i < uidx; i++) {
    // **NOT** a copy construction
    front[i] = a->data[i];
  }

}

void array_append (array_t* const a, const object_t* const o, const ssize_t idx) {

}
