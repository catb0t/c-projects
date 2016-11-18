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

    size_t idx = size_t_min(array_length(a), array_length(b));

    assoc->data = (typeof(assoc->data)) safemalloc( sizeof (pair_t*) * (idx + 1) );

    for (size_t i = 0; i < idx; i++) {
      object_t
        **car = array_get_ref(a, i, NULL),
        **cdr = array_get_ref(b, i, NULL);

      assoc_append_boa(assoc, *car, *cdr);
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

  object_failnull(asc);

  array_t *a, *b;
  assoc_unzip(asc, &a, &b);
  return assoc_new(a, b);
}

void assoc_destruct (assoc_t* const assoc) {
  pfn();

  object_failnull(assoc);

  report_dtor(assoc);

  if (NULL != assoc->data) {
    for (size_t i = 0; i < assoc_length(assoc); i++) {
      pair_destruct( *assoc_get_ref(assoc, i, NULL) );
    }

    safefree(assoc->data);
  }

  safefree(assoc);
}

define_objtype_dtor_args(assoc);

/*
  assoc_unzip: write the cars and cdrs of each pair to the respective pointers

  if assoc is null / empty, then car and cdr will be null.
*/
void assoc_unzip (const assoc_t* a, array_t** car, array_t** cdr) {
  pfn();

  *car = array_new(NULL, -1),
  *cdr = array_new(NULL, -1);

  for (size_t i = 0; i < assoc_length(a); i++) {
    pair_t** p = assoc_get_ref(a, i, NULL);
    array_append(*car, *pair_car_ref( *p ) ),
    array_append(*cdr, *pair_cdr_ref( *p ) );
  }

}

size_t assoc_length (const assoc_t* const a) {
  return signed2un(a->idx + 1);
}

define_isinbounds(assoc);

/*
  mutable reference to a pair at an index in the assoc.

  returns null and sets ok to false on error.
*/
pair_t** assoc_get_ref (const assoc_t* const a, const size_t idx, bool* ok) {
  pfn();

  object_failnull(a);

  if (NULL != ok) { *ok = true; }

  if (assoc_isempty(a) || un2signed(idx) > a->idx) {

    if (NULL != ok) { *ok = false; }

    object_error(
      ER_INDEXERROR,
      false,
      "get elt %zu from highest %zd%s",
      idx,
      a->idx,
      assoc_isempty(a)
        ? " (get from empty assoc)"
        : ""
    );
    return NULL;
  }

  return &( a->data [idx] );
}

/*
  copy a pair from an assoc, returning a new one with the same data
*/
pair_t* assoc_get_copy (const assoc_t* const a, const size_t idx, bool* ok) {
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
      pair_destruct( *assoc_get_ref(a, i, NULL) );
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
bool assoc_delete (assoc_t* const a, const size_t idx) {
  pfn();

  object_failnull(a);

  if ( idx > signed2un(a->idx) ) {
    char buf[200];
    snprintf(
      buf,
      199,
      "attempt to delete index %zu but the highest is %zd%s",
      idx, a->idx, assoc_length(a) ? "" : "(delete from empty assoc)"
    );
    object_error(
      ER_INDEXERROR,
      false,
      "attempt to delete index %zu but the highest is %zd%s",
      idx,
      a->idx,
      assoc_length(a)
        ? ""
        : " (delete from empty assoc)"
    );
    return false;
  }

  pair_destruct( *assoc_get_ref(a, idx, NULL));

  // if idx and a->idx are equal (that is, if it's the last element) we can just resize
  if ( idx != signed2un(a->idx) ) {
    for (size_t i = idx; i < signed2un(a->idx); i++) {
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
    pair_t** thisp  = assoc_get_ref(a, i, NULL);
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
    char* s = pair_see( *assoc_get_ref(a, i, NULL) );
    printf("\t%zu:%s\n", i, s);
    safefree(s);
  }

  puts("}\n");
}

bool assoc_equals (const assoc_t* const a, const assoc_t* const b) {
  pfn();

  object_failnull(a), object_failnull(b);



  if (assoc_length(a) != assoc_length(b)) {
    return false;
  }

  for (size_t i = 0; i < signed2un(a->idx); i++) {

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

ssize_t assoc_schreg_1st (
  const assoc_t*  const a,
  const object_t* const obj,
  object_t** (* reg_get_func) (pair_t* const p)
) {

  pfn();

  object_failnull(obj);

  size_t len = assoc_length(a);

  for (size_t i = 0; i < len; i++) {
    if ( object_equals( obj, *reg_get_func( *assoc_get_ref(a, i, NULL) ) ) ) {
      return un2signed(i);
    }
  }

  return -1;
}
