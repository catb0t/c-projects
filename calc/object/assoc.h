#include "objcommon.h"

#ifdef GCC
#line __LINE__ "assoc"
#endif

assoc_t* assoc_new (const array_t* const a, const array_t* const b) {
  pfn();

  assoc_t* assoc = (typeof(assoc)) safemalloc(sizeof (assoc_t) );

  assoc->idx  = -1;
  assoc->data = NULL;

  if ( (NULL != a) && (NULL != b) ) {

    ssize_t idx = ssize_min(a->idx, b->idx);
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

assoc_t* assoc_copy (const assoc_t* const asc) {
  pfn();

  array_t *a, *b;
  assoc_unzip(asc, &a, &b);
  return assoc_new(a, b);
}

void assoc_destruct (assoc_t* const assoc) {
  pfn();

  for (ssize_t i = 0; i < assoc->idx; i++) {
    pair_destruct( *assoc_get_ref(assoc, i, NULL) );
  }

  safefree(assoc->data), safefree(assoc);
  report_dtor(assoc);
}

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

pair_t** assoc_get_ref (const assoc_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  if ( (NULL == a) || (-1 == idx) || (idx > a->idx) ) {

    if (NULL != ok) {
      *ok = false;
    }

    if ( (-1 == idx) || (idx > a->idx) ) {
      object_error(INDEXERROR, __func__, false);
    }

    return NULL;
  }

  return &( a->data [idx] );
}

pair_t* assoc_get_copy (const assoc_t* const a, const ssize_t idx, bool* ok) {
  pfn();

  return pair_copy( *assoc_get_ref(a, idx, ok) );
}

void assoc_append_boa (assoc_t* const a, const object_t* const car, const object_t* const cdr) {
  pfn();

  pair_t* p = pair_new(car, cdr);

  assoc_append(a, p);

  pair_destruct(p);
}

void assoc_append (assoc_t* const a, const pair_t* const b) {
  pfn();

  assoc_resize(a, signed2un(a->idx) + 1);
  (a->data) [a->idx] = pair_copy(b);
}

void assoc_resize (assoc_t* const a, const size_t newsize) {
  pfn();

  a->data = saferealloc(a->data, sizeof (pair_t*) * (newsize));
  a->idx  = un2signed(newsize) - 1;
}

void assoc_delete (assoc_t* const a, const ssize_t idx) {
  pfn();

  if ( NULL == a ) {
    return;
  } else if ( (idx > a->idx) || (-1 == idx) ) {
    object_error(INDEXERROR, __func__, false);
    return;
  }

  pair_destruct( *assoc_get_ref(a, idx, NULL));

  // if idx and a->idx (that is, if it's the last element) are equal we can just resize
  if ( (idx != a->idx) ) {
    printf("not equal\n" );
    for (ssize_t i = idx; i < (a->idx); i++) {
      // change pointer (?)
      (a->data) [i] = (a->data) [i + 1];
    }

  }

  assoc_resize(a, signed2un(a->idx - 1));
}

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

  for (ssize_t i = 0; i < (a->idx + 1); i++) {
    // 'tis but a reference
    pair_t** thisp = assoc_get_ref(a, i, NULL);
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

void assoc_inspect (const assoc_t* const a) {
  pfn();

  printf("assoc uid:%zu idx:%zd sz:%zu {\n", a->uid, a->idx, sizeof a);

  for (ssize_t i = 0; i < a->idx; i++) {
    char* s = pair_see( *assoc_get_ref(a, i, NULL) );
    printf("\t%zd:%s\n", i, s);
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
