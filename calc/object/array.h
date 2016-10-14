#ifdef GCC
#line 2 "array"
#endif

#include "objcommon.h"

array_t* array_new (const object_t* const * const objs, const ssize_t len) {
  array_t* array = safemalloc( sizeof (array_t) );
  array->data    = safemalloc( sizeof (object_t *) );

  if (-1 != len) {
    for (ssize_t i = 0; i < len; i++) {
      object_t* o = object_copy(objs[i]);
      array_append(array, o);
      object_destruct(o);
    }

  }
  array->idx = len;

  report_ctor(array);

  return array;
}

array_t* array_copy (const array_t* const a) {
  pfn();

  return array_new( (const object_t* const * const) a->data, a->idx);
}

void array_destruct (array_t* const array) {

  report_dtor(array);

  if ( ! array_isempty(array) ) {
    for (ssize_t i = 0; i < (array->idx + 1); i++) {
      // because array_get returns a copy, not a reference
      // so we need to destruct by address
      object_destruct( *array_get_ref(array, i, NULL) );
    }
  }
  if (NULL != array->data) {
    safefree(array->data);
  }

  safefree(array);
}

bool array_isempty (const array_t* const a) {
  pfn();

  return -1 == a->idx || (NULL == a->data);
}

void array_resize (array_t* const a, const ssize_t new_idx) {
  if ( -1 == new_idx ) {
    a->data = realloc(a->data, 0);
    a->idx = -1;
    return;
  }

  a->idx  = new_idx;
  a->data = realloc(a->data, sizeof (object_t*) * signed2un(new_idx));
}

void array_delete (array_t* const a, const ssize_t idx) {

  if (-1 == idx || idx == a->idx) {
    array_resize(a, idx);
    return;
  }

  ssize_t i;
  for (i = idx + 1; i < (a->idx); i++) {
    // a copy construction
    a->data[i - 1] = a->data[i];
  }

  array_resize(
    a,
    un2signed(udifference(
      signed2un(i),
      signed2un(idx)
    ))
  );

}

//void array_insert (array_t* const a, const object_t* const o, const ssize_t idx) {}

void array_append (array_t* const a, const object_t* const o) {

  dbg_prn("b4 idx: %zd\n", a->idx);

  ++(a->idx);
  a->data = realloc(a->data, (sizeof (object_t *) * signed2un(a->idx + 1)) + 2);

  dbg_prn("after idx: %zd\n", a->idx);

  (a->data) [a->idx] = object_copy(o);
}

// WARN: POINTER MATH INCOMING
// thankfully, without threatening aliasing or alignment
// because we are working only with char and size_t
char* array_see (const array_t* const a) {

  char *outbuf = safemalloc(10),
       *bufptr = outbuf;

  str_append(bufptr, 3, "%s ", "{");

  if ( array_isempty(a) ) {
    str_append(bufptr, 3, "%s\n", "}");
    return outbuf;
  }

  size_t total_len = safestrnlen(outbuf);

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    // but a reference
    object_t** this = array_get_ref(a, i, NULL);
    char*   strthis = object_repr(*this);
    size_t  tlen    = safestrnlen(strthis) + 2;

    outbuf = realloc(outbuf, total_len + tlen);
    bufptr = outbuf + total_len;

    str_append(bufptr, tlen, "%s ", strthis);
    total_len = safestrnlen(outbuf);

    safefree(strthis);
  }

  // for my own sanity
  total_len = safestrnlen(outbuf);

  outbuf  = realloc(outbuf, total_len + 3);

  bufptr  = outbuf + total_len;
  str_append(bufptr, 3, "%s\n", "}");

  return outbuf;
}

ssize_t array_find (const array_t* const a, const object_t* const obj) {

  for (ssize_t i = 0; i < a->idx; i++) {
    if ( object_equals(obj, array_get_copy(a, i, NULL) )) {
      return i;
    }
  }

  return -1;
}

object_t* array_get_copy (const array_t* const a, const ssize_t idx, bool* ok) {

  if (NULL != ok) { *ok = true; }

  if ( array_isempty(a) || idx > a->idx || -1 == idx ) {
    if (NULL != ok) { *ok = false; }
    return nothing_new();
  }

  size_t uidx = signed2un(idx);
  return object_copy( (a->data) [uidx] );
}

object_t** array_get_ref (const array_t* const a, const ssize_t idx, bool* ok) {

  if (NULL != ok) { *ok = true; }

  if ( array_isempty(a) || idx > a->idx || -1 == idx ) {
    if (NULL != ok) { *ok = false; }
    return NULL;
  }

  size_t uidx = signed2un(idx);
  return &( (a->data) [uidx] );
}

bool array_equals (const array_t* const a, const array_t* const b) {
  if ( array_isempty(a) && array_isempty(b) ) {
    return true;
  }

  if ( b->idx != a->idx ) {
    return false;
  }

  for (ssize_t i = 0; i < a->idx; i++) {
    object_t *oa = array_get_copy(a, i, NULL),
             *ob = array_get_copy(b, i, NULL);
    if ( ! object_equals(oa, ob) ) {
      object_destruct(oa), object_destruct(ob);
      return false;
    }
    object_destruct(oa), object_destruct(ob);
  }

  return true;
}
