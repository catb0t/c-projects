#ifdef GCC
#line 2 "array"
#endif

#include "objcommon.h"

array_t* array_new (const object_t* const * const objs, const ssize_t len) {
  array_t* array = safemalloc( sizeof (array_t) );
  array->data    = safemalloc( sizeof (object_t *) );

  if (-1 != len) {
    for (ssize_t i = 0; i < len; i++) {
      array->data[i] = object_copy(objs[i]);
    }

  }
  array->idx = len;

  report_ctor(array);

  return array;
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

  return out;
}

void array_destruct (array_t* const array) {

  report_dtor(array);

  if ( ! array_isempty(array) ) {
    for (ssize_t i = 0; i < array->idx; i++) {
      object_destruct( (array->data) [i]);
    }
  }
  if (NULL != array->data) {
    safefree(array->data);
  }
  safefree(array);
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

  object_t** back = safemalloc(sizeof (object_t *) * safe_usub( (size_t) idx, (size_t) a->idx));
  for (ssize_t i = idx + 1; i < (a->idx); i++) {
    // **NOT** a copy construction
    back[i] = a->data[i];
  }

}

//void array_append (array_t* const a, const object_t* const o, const ssize_t idx) {}
