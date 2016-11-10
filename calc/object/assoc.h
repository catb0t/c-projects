#include "objcommon.h"

#ifdef GCC
#line __LINE__ "assoc"
#endif

/*
  new assoc object from two arrays (zip)
*/
assoc_t* assoc_new (const array_t* const a, const array_t* const b) {
  pfn();

  assoc_t* assoc = (typeof(assoc)) safemalloc(sizeof (assoc_t) );

  assoc->idx  = -1;
  assoc->data = NULL;

  if ( (NULL != a) && (NULL != b) ) {

    ssize_t idx = un2signed( size_t_min(array_length(a), array_length(b)) );
    assoc->idx  = idx;
    assoc->data = (typeof(assoc->data)) safemalloc( sizeof (pair_t*) * (signed2un(idx) + 1) );

    for (ssize_t i = 0; i < idx; i++) {
      object_t
        **car = array_get_ref(a, i, NULL),
        **cdr = array_get_ref(b, i, NULL);

      pair_t* p = pair_new(*car, *cdr);
      assoc_append(assoc, p);
      pair_destruct(p);
    }

  }

  report_ctor(assoc);

  return assoc;
}

/*
  copies one assoc's data to a new one's; does not copy identity
*/
assoc_t* assoc_copy (const assoc_t* const asc) {
  pfn();

  array_t *a, *b;
  assoc_unzip(asc, &a, &b);
  return assoc_new(a, b);
}

void assoc_destruct (assoc_t* const assoc) {
  pfn();

  report_dtor(assoc);

  for (size_t i = 0; i < assoc_length(assoc); i++) {
    pair_destruct( *assoc_get_ref(assoc, un2signed(i), NULL) );
  }

  safefree(assoc->data), safefree(assoc);
}

/*
  assoc_unzip: write the cars and cdrs of each pair to the respective pointers

  if assoc is null / empty, then car and cdr will be null.
*/
void assoc_unzip (const assoc_t* a, array_t** car, array_t** cdr) {
  pfn();

  *car = array_new(NULL, -1),
  *cdr = array_new(NULL, -1);

  for (ssize_t i = 0; i < a->idx; i++) {
    pair_t** p = assoc_get_ref(a, i, NULL);
    array_append(*car, *pair_car_ref( *p ) ),
    array_append(*cdr, *pair_cdr_ref( *p ) );
  }

}

size_t assoc_length (const assoc_t* const a) {
  return signed2un(a->idx + 1);
}

/*
  mutable reference to a pair at an index in the assoc.

  returns null and sets ok to false on error.
*/
pair_t** assoc_get_ref (const assoc_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  object_failnull(a);

  if ( (-1 == idx) || (idx > a->idx) ) {

    if (NULL != ok) {
      *ok = false;
    }

    if ( (-1 == idx) || (idx > a->idx) ) {
      object_error(ER_INDEXERROR, __func__, false);
    }

    return NULL;
  }

  return &( a->data [idx] );
}

/*
  copy a pair from an assoc, returning a new one with the same data
*/
pair_t* assoc_get_copy (const assoc_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  return pair_copy( *assoc_get_ref(a, idx, ok) );
}

/*
  append a new pair with the given car and cdr to the assoc
*/
void assoc_append_boa (assoc_t* const a, const object_t* const car, const object_t* const cdr) {
  pfn();

  pair_t* p = pair_new(car, cdr);

  assoc_append(a, p);

  pair_destruct(p);

}

/*
  append a pair object to assoc.
*/
void assoc_append (assoc_t* const a, const pair_t* const b) {
  pfn();

  object_failnull(a);

  assoc_resize(a, assoc_length(a) + 1);
  (a->data) [a->idx] = pair_copy(b);
}

/*
  resize an assoc to the new size. implemented with saferealloc(2), so if new_idx is
  smaller than a->idx, the pairs past will disappear and their destructors will
  be called.
*/
void assoc_resize (assoc_t* const a, const size_t new_len) {
  pfn();

  object_failnull(a);

  if ( ! new_len ) {
    // points to a region of memory of size zero aligned to pair_t* (aka pointer)
    a->data = (typeof(a->data)) saferealloc(a->data, 0);
    a->idx  = -1;
    return;
  }

  if (new_len < assoc_length(a)) {
    for (size_t i = new_len + 1; i < assoc_length(a); i++) {
      pair_destruct( *assoc_get_ref(a, un2signed(i), NULL) );
    }
  }

  a->data = (typeof(a->data)) saferealloc(
    a->data, sizeof (pair_t*) * new_len
  );

  a->idx = un2signed(new_len) - 1;
}

/*
  delete a pair from an assoc by index
*/
bool assoc_delete (assoc_t* const a, const ssize_t idx) {
  pfn();

  if ( NULL == a ) {
    return false;
  } else if ( (idx > a->idx) || (-1 == idx) ) {
    object_error(ER_INDEXERROR, __func__, false);
    return false;
  }

  pair_destruct( *assoc_get_ref(a, idx, NULL));

  // if idx and a->idx are equal (that is, if it's the last element) we can just resize
  if ( (idx != a->idx) ) {
    printf("not equal\n" );
    for (ssize_t i = idx; i < (a->idx); i++) {
      // change pointer (?)
      (a->data) [i] = (a->data) [i + 1];
    }

  }

  assoc_resize(a, assoc_length(a) - 1);

  return true;
}

/*
  get the string representation of an assoc object. round-trips.
*/
char* assoc_see (const assoc_t* const a) {
  pfn();

  object_failnull(a);

  char *outbuf = (typeof(outbuf)) safemalloc(7),
       *bufptr = outbuf;

  str_append(bufptr, 4, "%s ", "a{");

  if ( assoc_isempty(a) ) {
    str_append(bufptr, 2, "%s", "}");
    return outbuf;
  }

  size_t total_len = safestrnlen(outbuf);

  for (size_t i = 0; i < assoc_length(a); i++) {
    // 'tis but a reference
    pair_t** thisp = assoc_get_ref(a, un2signed(i), NULL);
    char*   strthis = pair_see(*thisp);
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

/*
  directly writes debug data about the assoc to stdout.
*/
void assoc_inspect (const assoc_t* const a) {
  pfn();

  printf("assoc uid:%zu idx:%zd sz:%zu {\n", a->uid, a->idx, sizeof a);

  for (size_t i = 0; i < assoc_length(a); i++) {
    char* s = pair_see( *assoc_get_ref(a, un2signed(i), NULL) );
    printf("\t%zu:%s\n", i, s);
    safefree(s);
  }

  puts("}\n");
}

bool assoc_equals (const assoc_t* const a, const assoc_t* const b) {
  pfn();

  if ( (NULL == a) || (NULL == b) ) {
    if ((!a) && (!b)) {
      return true;
    }
    return false;
  }

  if (a->idx != b->idx) {
    return false;
  }

  for (ssize_t i = 0; i < a->idx; i++) {

    bool same = pair_equals(
      *assoc_get_ref(a, i, NULL),
      *assoc_get_ref(b, i, NULL)
    );

    if (! same) {
      return false;
    }
  }

  return true;
}

bool assoc_isempty (const assoc_t* const a) {
  pfn();

  object_failnull(a);

  return -1 == a->idx || NULL == a->data;
}
