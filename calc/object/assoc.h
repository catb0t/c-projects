#include "objcommon.h"

#ifdef GCC
#line __LINE__ "assoc"
#endif

static inline __PURE_FUNC __CONST_FUNC ssize_t ssize_min (ssize_t a, ssize_t b) {
  pfn();

  return a < b ? a : b;
}

assoc_t* assoc_new (const array_t* const a, const array_t* const b) {
  pfn();

  assoc_t* assoc = (typeof(assoc)) safemalloc(sizeof (assoc_t) );

  if ( ! ( (NULL == a) || (NULL == b) ) ) {

    ssize_t idx = ssize_min(a->idx, b->idx);

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

void assoc_unzip (const assoc_t* a, array_t** keys, array_t** vals) {
  pfn();

  *keys = array_new(NULL, -1),
  *vals = array_new(NULL, -1);

  for (ssize_t i = 0; i < a->idx; i++) {
    array_append(*keys, *pair_car_ref( (a->data) [i] ) ),
    array_append(*vals, *pair_cdr_ref( (a->data) [i] ) );
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

void assoc_append (assoc_t* a, const pair_t* const b) {
  pfn();

  ++(a->idx);
  assoc_resize(a, signed2un(a->idx));
  (a->data) [a->idx] = pair_copy(b);
}

void assoc_resize (assoc_t* a, const size_t newsize) {
  pfn();

  a = saferealloc(a, sizeof (pair_t*) * (newsize));
  a->idx = un2signed(newsize) - 1;
}

void assoc_delete (assoc_t* const a, const ssize_t idx) {
  pfn();

  if ( (NULL == a) ) {
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

  (void) a;
  char*  buf = (typeof(buf)) safemalloc(1);
  return buf;
}

void assoc_inspect (const assoc_t* const a) {
  pfn();

  printf("WARN: LONG OUTPUT\n");

  printf("data: ");

  for (ssize_t i = 0; i < a->idx; i++) {
    char* s = pair_see( *assoc_get_ref(a, i, NULL) );
    printf("%s ", s);
    safefree(s);
  }

  printf("\nidx: %zd\n", a->idx);
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

    bool same = pair_equals( *assoc_get_ref(a, i, NULL), *assoc_get_ref(b, i, NULL) );

    if (! same ) {
      return false;
    }
  }

  return true;
}
