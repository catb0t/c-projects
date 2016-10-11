#ifdef GCC
#line 2 "hash"
#endif

#include "objcommon.h"

#include "../../fnv-hash/fnv.h"

Fnv64_t    hash_obj (const object_t* const obj);

hash_t* hash_new (const array_t* const keys, const array_t* const vals, size_t len) {
  pfn();

  ssize_t slen = un2signed(len);

  // all must be same length
  assert(
    (keys->idx == vals->idx)
    // hopefully works
    && (keys->idx == (slen > 0 ? slen + 1 : slen))
    && (vals->idx == (slen > 0 ? slen + 1 : slen))
  );


  hash_t* hash = safemalloc( sizeof(hash_t) );

  hash->keys   = array_copy(keys);
  hash->vals   = array_copy(keys);
  hash->len    = len;

  report_ctor(hash);

  return hash;
}

void  hash_destruct (hash_t* const hash) {
  pfn();

  report_dtor(hash);

  array_destruct(hash->keys);
  array_destruct(hash->vals);
  safefree(hash);
}

hash_t*   hash_copy (const hash_t* const h) {
  pfn();

  return hash_new(h->keys, h->vals, h->len);
}

bool   hash_isempty (const hash_t* const h) {
  pfn();

  return 0 == h->len;
}

Fnv64_t hash_obj (const object_t* const obj) {
  pfn();

  char* buf = object_repr(obj);
  Fnv64_t hval = fnv_64a_str(buf, FNV1A_64_INIT);
  safefree(buf);
  return hval;
}

object_t* hash_get (const hash_t* const h, const object_t* const key, bool* ok) {
  pfn();

  return array_get(h->keys, un2signed( hash_obj(key) ), ok);
}

void       hash_set (const hash_t* const h, const object_t* const key) {
  pfn();

  (void) h, (void) key;
}

void    hash_delete (const hash_t* const h, const object_t* const key) {
  pfn();

  ssize_t keyidx = array_find(h->keys, key);

  if ( -1 == keyidx ) {
    object_error(KEYERROR, "hash_delete", false);
    return;
  }

  array_delete(h->keys, keyidx);

  // this is BAD -- cast from unsigned to signed cuts the keyspace in half
  array_delete(h->vals, un2signed( hash_obj(key) ));
}

void    hash_resize (hash_t* h, const size_t len) {
  pfn();

  (void) h, (void) len;
}

char* hash_see (const hash_t* const h) {
  pfn();

  (void) h;
  char* buf = safemalloc(1);
  return buf;
}

bool hash_equals (const hash_t* const a, const hash_t* const b) {
  pfn();

  if ( hash_isempty(a) && hash_isempty(b) ) {
    return true;
  }

  if ( a->len != b->len ) {
    return false;
  }

  return array_equals(a->keys, b->keys) && array_equals(a->vals, b->vals);
}
