#ifdef GCC
#line 2 "hash"
#endif

#include "objcommon.h"

#include "../../fnv-hash/fnv.h"

typedef Fnv32_t hashkey_t;

hashkey_t hash_obj (const object_t* const obj);

hash_t* hash_new_skele (void) {
  pfn();

  hash_t* hash = safemalloc( sizeof(hash_t) );

  hash->keys     = array_new(NULL, -1);
  hash->vals     = array_new(NULL, -1);
  hash->idxs     = safemalloc( sizeof (size_t) * 1 );
  hash->idxs_len = 0;

  report_ctor(hash);

  return hash;
}

hash_t* hash_new_boa (
  const array_t* const keys,
  const array_t* const vals,
  const size_t         len
) {
  pfn();

  size_t
    klen = signed2un(keys->idx + 1),
    vlen = signed2un(vals->idx + 1);

  printf("%zu %zu %zu\n", klen, vlen, len);

  assert(
    (klen == vlen)
    && (klen == len)
    && (vlen == len)
  );

  hash_t* hash = hash_new_skele(); // 1

  for (size_t i = 0; i < klen; i++) {
    object_t
      *k = object_copy((keys->data) [i]), // 2
      *v = object_copy((vals->data) [i]); // 3

    hash_add(hash, k, v);
    object_dtor_args(2, k, v); // ~2, ~3
  }

  // 3 allocs, 2 frees, last free is caller's problem
  return hash;
}

void  hash_destruct (hash_t* const hash) {
  pfn();

  report_dtor(hash);

  array_destruct(hash->keys);
  array_destruct(hash->vals);
  safefree(hash->idxs);
  safefree(hash);
}

hash_t*   hash_copy (const hash_t* const h) {
  pfn();

  array_t* values = hash_getvals(h); // 1

  // 2
  hash_t* cp = hash_new_boa(h->keys, values, signed2un(h->keys->idx));

  array_destruct(values); // ~1
  return cp;
}

bool   hash_isempty (const hash_t* const h) {
  pfn();

  return 0 == h->idxs_len;
}

hashkey_t hash_obj (const object_t* const obj) {
  pfn();

  char* buf      = object_repr(obj);
  hashkey_t hval = fnv_32a_str(buf, FNV1_32A_INIT);
  safefree(buf);

  return hval;
}

object_t* hash_get (const hash_t* const h, const object_t* const key, bool* ok) {
  pfn();

  pair_t* vals;
  hashkey_t kh;
  object_t *valpair, *finalval;

  kh       = hash_obj(key);
  valpair  = array_get_copy(h->vals, (h->idxs) [kh], ok); // 1
  if (! ok) {
    object_destruct(valpair); // ~1
    return object_new(t_F, NULL);
  }
  vals     = pair_copy(valpair->cel); // 2
  finalval = pair_car(vals);          // 3

  object_destruct(valpair); // ~1
  pair_destruct(vals);      // ~2

  // 3 allocs, 2 frees, the last free is up to the caller

  return finalval;
}

array_t* hash_getvals (const hash_t* h) {
  pfn();

  array_t* vs = array_new(NULL, -1); // 1

  size_t vlen = signed2un(h->vals->idx);

  for (size_t i = 0; i < vlen; i++) {
    object_t
      *p   = array_get_copy(vs, un2signed(i), NULL), // 2
      *car = pair_car( p->cel );                // 3

    array_append(vs, car);
    object_destruct(car), object_destruct(p); // ~2, ~3
  }

  // 3 allocs, 2 frees, last is for caller
  return vs;
}

bool hash_add (hash_t* const h, const object_t* const key, const object_t* const val) {
  pfn();

  pair_t* newp;
  object_t *pairobj, *khobj;
  hashkey_t kh;

  // hash the key
  kh = hash_obj(key);
  // fail if it exists
  if ( hash_exists(h, key) || hash_keyexists(h, key) ) {
    return false;
  }

  // add the key to the list
  array_append(h->keys, key);

  // objectify the key hash
  khobj = object_new(t_realint, &kh); // 1
  // make a pair out of the value and keyhash obj
  newp  = pair_new(val, khobj); // 2


  // objectify the pair
  pairobj = object_new(t_pair, (const void * const) newp); // 3

  object_destruct(khobj); // ~1
  pair_destruct(newp); // ~2

  // add the pair to values
  array_append(h->vals, pairobj);
  // resize the idxs array by the needed amount
  h->idxs = realloc(h->idxs, sizeof (size_t) * kh + 1);
  // increment the pointer
  ++(h->idxs_len);
  // assign the index of the pair in values to idxs
  (h->idxs) [kh] = h->vals->idx;
  // looks like everything went ok
  return true;
}

bool hash_keyexists (const hash_t* const h, const object_t* const key) {
  pfn();

  return -1 != array_find(h->keys, key);
}

bool hash_exists (const hash_t* const h, const object_t* const key) {
  pfn();

  hashkey_t kh = hash_obj(key);

  if (kh > h->idxs_len) {
    return false;
  }

  return -1 != h->idxs[kh];
}

void hash_delete (hash_t* const h, const object_t* const key) {
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

  if ( a->idxs_len != b->idxs_len ) {
    return false;
  }

  return array_equals(a->keys, b->keys) && array_equals(a->vals, b->vals);
}
