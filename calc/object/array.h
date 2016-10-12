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
    for (ssize_t i = 0; i < array->idx; i++) {
      object_destruct( array_get(array, i, NULL) );
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

char* array_see (const array_t* const a) {

  size_t total_len = 0;
  char *outbuf = safemalloc(4),
       *bufptr = outbuf;

  bufptr += snprintf(bufptr, 3, "%s", "{ ");

  if ( array_isempty(a) ) {
    bufptr += snprintf(bufptr, 3, "%s", "}\n");
    return outbuf;
  }

  for (ssize_t i = 0; i < a->idx; i++) {
    object_t* this = array_get(a, i, NULL);
    char*  strthis = object_repr(this);
    size_t thislen = safestrnlen(strthis);

    outbuf     = realloc(outbuf, total_len + thislen);
    bufptr     = outbuf + total_len;

    bufptr    += snprintf(bufptr, thislen, "%s ", strthis);
    total_len += thislen;
  }

  bufptr += snprintf(bufptr, 3, "%s", "}\n");

  return outbuf;
}

ssize_t array_find (const array_t* const a, const object_t* const obj) {

  for (ssize_t i = 0; i < a->idx; i++) {
    if ( object_equals(obj, array_get(a, i, NULL) )) {
      return i;
    }
  }

  return -1;
}

object_t* array_get (const array_t* const a, const ssize_t idx, bool* ok) {

  *ok = true;

  if ( array_isempty(a) || idx > a->idx || -1 == idx ) {
    *ok = false;
    return object_new(t_F, NULL);
  }

  size_t uidx = signed2un(idx);
  return object_copy( (a->data) [uidx] );
}

bool array_equals (const array_t* const a, const array_t* const b) {
  if ( array_isempty(a) && array_isempty(b) ) {
    return true;
  }

  if ( b->idx != a->idx ) {
    return false;
  }

  for (ssize_t i = 0; i < a->idx; i++) {
    object_t *oa = array_get(a, i, NULL),
             *ob = array_get(b, i, NULL);
    if ( ! object_equals(oa, ob) ) {
      object_destruct(oa), object_destruct(ob);
      return false;
    }
    object_destruct(oa), object_destruct(ob);
  }

  return true;
}
