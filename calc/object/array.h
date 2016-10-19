#include "objcommon.h"

#ifdef GCC
#line __LINE__ "array"
#endif

/*
  returns a newly constructed, unique array object.
  if objs is NULL or len is -1, an empty array will be returned, instead of building
  a new one by copying the objects from the first argument.
*/
array_t* array_new (const object_t* const * const objs, const ssize_t len) {
  pfn();

  array_t* array = (typeof(array)) safemalloc( sizeof (array_t) );
  array->data    = (typeof(array->data)) safemalloc( sizeof (object_t *) );

  if ( (-1 != len) && (NULL != objs) ) {
    for (ssize_t i = 0; i < len; i++) {
      array_append(array, objs[i]);
    }
  }
  array->idx = len;

  report_ctor(array);

  return array;
}

/*
  copies an array object, by constructing a new one with the argument's
  underlying object** array

  copy constructors are called all the way down, so the new object is unique
*/
array_t* array_copy (const array_t* const a) {
  pfn();

  return array_new( (const object_t* const * const) a->data, a->idx);
}

/*
  free, by reference, all of an array's items, then the object itself

  mutates its argument, because it will be in an invalid state hereafter
*/
void array_destruct (array_t* const array) {
  pfn();

  report_dtor(array);

  if ( ! array_isempty(array) ) {
    for (ssize_t i = 0; i < (array->idx + 1); i++) {
      // because array_get returns a copy, not a reference
      // so we need to destruct by address
      object_destruct( *array_get_ref(array, i, NULL) );
    }
  }

  if (NULL != array->data) {
    safefree( array->data );
  }

  safefree(array);
}

/*
  tests whether an array contains no elements (its index is -1),
  or if its data pointer is NULL

  effectively, there is little difference, except in referencing NULL pointers.
*/
bool array_isempty (const array_t* const a) {
  pfn();

  return -1 == a->idx || (NULL == a->data);
}

/*
  resize an array to the new size. implemented with realloc(2), so if new_idx is
  smaller than a->idx, the objects past will disappear and their destructors will
  not be called.
*/
void array_resize (array_t* const a, const ssize_t new_idx) {
  pfn();

  if ( -1 == new_idx ) {
    a->data = (typeof(a->data)) realloc(a->data, 0);
    a->idx  = -1;
    return;
  }

  if (new_idx < a->idx) {
    for (ssize_t i = new_idx + 1; i < a->idx; i++) {
      object_destruct( *array_get_ref(a, i, NULL) );
    }
  }

  a->idx  = new_idx;
  a->data = (typeof(a->data)) realloc(a->data, sizeof (object_t*) * signed2un(new_idx + 1));
}

/*
  remove an element from an array and shrink it by one.

  to remove an element from an array:
    if the array is empty, return
    if idx is the same as array->idx, return

    shift elements above the index left by one by changing the pointers, not by
      ...copying them
    resize the array by -1.
*/
void array_delete (array_t* const a, const ssize_t idx) {
  pfn();

  if ( ( idx > a->idx ) || ( array_isempty(a) ) || ( -1 == idx ) ) {
    object_error(INDEXERROR, __func__, false);
    return;
  }

  // if idx and a->idx are equal we can just resize
  if ( (idx != a->idx) ) {

    for (ssize_t i = idx + 1; i < (a->idx); i++) {
      // change pointer (?)
      (a->data) [i - 1] = (a->data) [i];
    }

  }

  array_resize(a, a->idx - 1);

}

/*
  insert an element anywhere into an array, growing it by one in the process.

  to insert an element into an array:
    if the array is empty, just append

    resize the array by one
    shift elements left by one
    put the new element at its index
*/
void array_insert (array_t* const a, const object_t* const o, const ssize_t idx) {
  pfn();

  array_resize(a, a->idx + 1);

  ssize_t i;
  for (i = a->idx; i > idx; i--) {
    // change pointer (?)
    (a->data) [i] = (a->data) [i - 1];
  }

  (a->data) [idx] = object_copy(o);
}

/*
  append an element to an array, growing it by one in the process

  to append:
    increment idx
    realloc by one
    put the new object at the end.
*/
void array_append (array_t* const a, const object_t* const o) {
  pfn();

  ++(a->idx);
  a->data = (typeof(a->data)) realloc(a->data, (sizeof (object_t *)) * signed2un(a->idx + 1) );

  (a->data) [a->idx] = object_copy(o);
}


/*
  return a string representation of the given array object

  hopefully, roundtrips.
*/
// WARN: POINTER MATH INCOMING
// thankfully, without threatening aliasing or alignment
// because we are working only with char and size_t
char* array_see (const array_t* const a) {
  pfn();

  char *outbuf = (typeof(outbuf)) safemalloc(10),
       *bufptr = outbuf;

  str_append(bufptr, 3, "%s ", "{");

  if ( array_isempty(a) ) {
    str_append(bufptr, 3, "%s\n", "}");
    return outbuf;
  }

  size_t total_len = safestrnlen(outbuf);

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    // 'tis but a reference
    object_t** thisp = array_get_ref(a, i, NULL);
    char*   strthis = object_repr(*thisp);
    size_t  tlen    = safestrnlen(strthis) + 2;

    outbuf = (typeof(outbuf)) realloc(outbuf, total_len + tlen);
    bufptr = outbuf + total_len;

    str_append(bufptr, tlen, "%s ", strthis);
    total_len = safestrnlen(outbuf);

    safefree(strthis);
  }

  // for my own sanity
  total_len = safestrnlen(outbuf);

  outbuf  = (typeof(outbuf)) realloc(outbuf, total_len + 3);

  bufptr  = outbuf + total_len;
  str_append(bufptr, 3, "%s\n", "}");

  return outbuf;
}

void array_inspect (const array_t* const a) {

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    char* x = object_repr(*array_get_ref(a, i, NULL));
    printf("%zu: %s\n", i, x);
    safefree(x);
  }

}

/*
  find an object in an array, by simply checking each for equality
  not a binary search.
*/
ssize_t array_find (const array_t* const a, const object_t* const obj) {
  pfn();

  for (ssize_t i = 0; i < a->idx; i++) {
    if ( object_equals(obj, *array_get_ref(a, i, NULL) )) {
      return i;
    }
  }

  return -1;
}

/*
  copy an element from an array and return it.

  if the array is empty or some error occurred, ok will be false and a new false object will be returned.

  otherwise, ok will be true and a new object is copy constructed and returned.

  if ok is NULL, it will be ignored (useful in loops when it is known that the
  index will never go out of bounds).
*/
object_t* array_get_copy (const array_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  if (NULL != ok) { *ok = true; }

  if ( array_isempty(a) || idx > a->idx || -1 == idx ) {
    if (NULL != ok) { *ok = false; }
    return nothing_new();
  }

  return object_copy( *array_get_ref(a, idx, ok) );
}

/*
  return a reference to an object in an array.

  realistically thisp does little more than add the array's data address to the
  element's offset.

  if some error occurred, ok will be false and NULL is returned.
  otherwise, ok is true and a reference to the original object is given.

  if ok is NULL, then it will be ignored (useful in loops when it is known that the
  index will never go out of bounds).
*/
object_t** array_get_ref (const array_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  if (NULL != ok) { *ok = true; }

  if ( array_isempty(a) || idx > a->idx || -1 == idx ) {
    if (NULL != ok) { *ok = false; }
    return NULL;
  }

  size_t uidx = signed2un(idx);
  return &( (a->data) [uidx] );
}

/*
  test if two arrays are equal by value.

  thisp is done by comparing each element in one with each element in another, and
  returning when a difference is found.

  arrays of disparate length cannot be equal.

  references to each object from the arrays are given to object_equals.
*/
bool array_equals (const array_t* const a, const array_t* const b) {
  pfn();

  if ( array_isempty(a) && array_isempty(b) ) {
    return true;
  }

  if ( b->idx != a->idx ) {
    return false;
  }

  for (ssize_t i = 0; i < a->idx; i++) {
    // 'tis but a reference
    object_t **oa = array_get_ref(a, i, NULL),
             **ob = array_get_ref(b, i, NULL);
    if ( ! object_equals(*oa, *ob) ) {
      return false;
    }
  }

  return true;
}
