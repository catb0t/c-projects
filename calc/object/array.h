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
  array->data    = NULL;
  array->idx     = -1;

  if ( (-1 != len) && (NULL != objs) ) {
    array->data = (typeof(array->data)) safemalloc( sizeof (object_t *) );

    for (ssize_t i = 0; i < len; i++) {
      array_append(array, objs[i]);
    }
  }

  report_ctor(array);

  return array;
}

/*
  makes a function which makes a new array from a heap-alloced C array
*/
#define define_array_new_fromctype(type) \
  array_t* array_new_from_ ## type ## _lit (const type * const ptr, const size_t len, const objtype_t conv_to); \
  \
  array_t* array_new_from_ ## type ## _lit (const type * const ptr, const size_t len, const objtype_t conv_to) { \
    \
    object_t** UNSHADOW_OBJS = (typeof(UNSHADOW_OBJS)) safemalloc( sizeof(object_t *) * len ); \
    \
    for (size_t i = 0; i < len; i++) { UNSHADOW_OBJS[i] = object_new(conv_to, (const void* const) &( ptr[i] ) ); } \
    \
    array_t* UNSHADOW_ARRAY = array_new( (const object_t* const * const) UNSHADOW_OBJS, un2signed(len)); \
    \
    object_dtorn(UNSHADOW_OBJS, len); \
    \
    return UNSHADOW_ARRAY; \
  } \
  int DONT_FIND_THIS_NAME ## funcname

//array_t* a = array_new( (const object_t * const * const) objs, un2signed(len));object_dtorn(objs, len);
/*
  makes a new array from an array of pointers to raw C types.
*/
array_t* array_new_fromcptr (const void* const * const ptr, const size_t len, const objtype_t conv_to) {

  object_t** objs = (typeof(objs)) safemalloc( sizeof(object_t *) * len);

  for (size_t i = 0; i < len; i++) {
    objs[i] = object_new(conv_to, ptr[i] );
  }

  array_t* a = array_new( (const object_t * const * const) objs, un2signed(len));

  object_dtorn(objs, len);

  return a;
}


/*
  copies an array object, by constructing a new one with the argument's
  underlying object** array

  copy constructors are called all the way down, so the new object is unique
*/
array_t* array_copy (const array_t* const a) {
  pfn();

  object_failnull(a);

  return array_new( (const object_t* const * const) a->data, un2signed(array_length(a)) );
}

/*
  free, by reference, all of an array's items, then the object itself

  mutates its argument, because it will be in an invalid state hereafter
*/
void array_destruct (array_t* const array) {
  pfn();

  report_dtor(array);

  object_dtorn(array->data, array_length(array));

  safefree(array);
}

void array_destruct_args (const size_t argc, ...) {
  pfn();

  va_list vl;
  va_start(vl, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully thisp just takes the address
    array_t** v = (typeof(v)) safemalloc( sizeof (array_t *) );
    *v = va_arg(vl, array_t*);

    // 0 allocs, 1 free, but not double free
    array_destruct( *v );
    safefree(v);
  }

  va_end(vl);
}

/*
  tests whether an array contains no elements (its index is -1),
  or if its data pointer is NULL

  effectively, there is little difference, except in referencing NULL pointers.
*/
bool array_isempty (const array_t* const a) {
  pfn();

  object_failnull(a);

  return ( ! array_length(a) ) || (NULL == a->data);
}

size_t array_length (const array_t* const a) {
  return signed2un(a->idx + 1);
}

/*
  resize an array to the new size. implemented with saferealloc(2), so if new_idx is
  smaller than a->idx, the objects past will disappear and their destructors will
  be called.
*/
void array_resize (array_t* const a, const size_t new_len) {
  pfn();

  object_failnull(a);

  if ( ! new_len ) {
    a->data = (typeof(a->data)) saferealloc(a->data, 0);
    a->idx  = -1;
    return;
  }

  if (new_len < array_length(a)) {
    for (size_t i = new_len + 1; i < array_length(a); i++) {
      object_destruct( *array_get_ref(a, un2signed(i), NULL) );
    }
  }

  a->data = (typeof(a->data)) saferealloc(
    a->data, sizeof (object_t*) * new_len
  );

  a->idx  = un2signed(new_len) - 1;
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

  object_failnull(a);

  if ( ( idx > a->idx ) || ( array_isempty(a) ) || ( -1 == idx ) ) {
    char* er = (typeof(er)) safemalloc(100);
    snprintf(er, 99, "%s: delete index %zd but the highest is %zd", __func__, idx, a->idx);
    object_error(INDEXERROR, er, false);
    safefree(er);
    return;
  }

  object_destruct( *array_get_ref(a, idx, NULL));

  // if idx and a->idx (that is, if it's the last element) are equal we can just resize
  if ( idx != a->idx ) {
    printf("not equal\n" );
    for (ssize_t i = idx; i < (a->idx); i++) {
      // change pointer (?)
      (a->data) [i] = (a->data) [i + 1];
    }

  }

  array_resize(a, array_length(a) - 1);
}

void array_clear (array_t* const a) {
  pfn();

  object_failnull(a);

  array_resize(a, 0);
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

  object_failnull(a);

  array_resize(a, array_length(a) + 1);

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

  object_failnull(a);

  array_resize(a, array_length(a) + 1);

  (a->data) [a->idx] = object_copy(o);
}

/*
  variadic version of array_append
*/
void array_vappend (array_t* const a, const size_t argc, ...) {
  pfn();

  object_failnull(a);

  va_list vl;
  va_start(vl, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully thisp just takes the address
    object_t** v = (typeof(v)) safemalloc( sizeof (object_t *) );
    *v = va_arg(vl, object_t*);

    array_append(a, *v);
    safefree(v);
  }

  va_end(vl);
}

/*
  concatenate two array_ts
*/
void array_concat (array_t** const a, const array_t* const b) {
  pfn();

  object_failnull(a);

  if ( array_isempty(*a) && array_isempty(b) ) {
    return;
  }

  else if ( array_isempty(*a) || array_isempty(b) ) {

    if ( array_isempty(*a) ) {
      *a = array_copy(b);
    }

    return;
  }

  size_t alen = array_length(*a),
         total_len = alen + array_length(b);

  array_resize(*a, total_len);

  for (size_t i = alen; i < total_len; i++) {
    (*a)->data[i] = array_get_copy(b, un2signed( udifference(i, alen) ), NULL);
  }
}

/*
  variadic version of array_cat
*/
void array_vconcat (array_t** const a, const size_t argc, ...) {
  pfn();

  object_failnull(a);

  va_list vl;
  va_start(vl, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully thisp just takes the address
    array_t** v = (typeof(v)) safemalloc( sizeof (array_t *) );
    *v = va_arg(vl, array_t*);

    array_concat(a, *v);
    safefree(v);
  }

  va_end(vl);
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

  object_failnull(a);

  char *outbuf = (typeof(outbuf)) safemalloc(6),
       *bufptr = outbuf;

  str_append(bufptr, 3, "%s ", "{");

  if ( array_isempty(a) ) {
    str_append(bufptr, 2, "%s", "}");
    return outbuf;
  }

  size_t total_len = safestrnlen(outbuf);

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    // 'tis but a reference
    object_t** thisp = array_get_ref(a, i, NULL);
    char*   strthis = object_repr(*thisp);
    size_t  tlen    = safestrnlen(strthis) + 2;

    outbuf = (typeof(outbuf)) saferealloc(outbuf, total_len + tlen);
    bufptr = outbuf + total_len;

    str_append(bufptr, tlen, "%s ", strthis);
    total_len = safestrnlen(outbuf);

    safefree(strthis);
  }

  // for my own sanity
  total_len = safestrnlen(outbuf);

  outbuf  = (typeof(outbuf)) saferealloc(outbuf, total_len + 3);

  bufptr  = outbuf + total_len;
  str_append(bufptr, 3, "%s", "}");

  return outbuf;
}

void array_inspect (const array_t* const a) {
  pfn();

  object_failnull(a);

  printf("array uid:%zu idx:%zd {\n", a->uid, a->idx);

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    char* x = object_repr(*array_get_ref(a, i, NULL));
    printf("\t%zd: %s\n", i, x);
    safefree(x);
  }
  puts("}\n");

}

/*
  find an object in an array, by simply checking each for equality
  not a binary search.
*/
ssize_t array_find (const array_t* const a, const object_t* const obj) {
  pfn();

  object_failnull(a);

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

  object_failnull(a);

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

  object_failnull(a);

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

  object_failnull(a);

  if ( array_isempty(a) && array_isempty(b) ) {
    return true;
  }

  if ( array_length(a) != array_length(b) ) {
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
