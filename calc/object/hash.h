#include "objcommon.h"

#ifdef GCC
#line __LINE__ "hash"
#endif

#include "../../fnv-hash/fnv.h"

typedef Fnv32_t hashkey_t;

hashkey_t hash_obj (const object_t* const obj);

hash_t* hash_new_skele (void) {
  pfn();

  hash_t*  hash = (typeof(hash)) safemalloc( sizeof(hash_t) );

  hash->keys     = array_new(NULL, -1);
  hash->vals     = array_new(NULL, -1);
  hash->idxs     = (typeof(hash->idxs)) safemalloc( sizeof (size_t) * 1 );
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
    klen = signed2un(keys->idx + 1); // ,
    //vlen = signed2un(vals->idx + 1);

  (void) len;

  /*
  assert(
    (klen == vlen)
    && (klen == len)
    && (vlen == len)
  );*/

  hash_t* hash = hash_new_skele(); // 1

  for (size_t i = 0; i < klen; i++) {
    object_t
      **k = &( (keys->data) [i] ),
      **v = &( (vals->data) [i] );

    // references are okay because thisp will copy them anyways
    hash_add(hash, *k, *v);
  }

  // 1 alloc, 0 frees, last free is caller's problem
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

/*
  return a copy of a value in a hash by key.

  to get a value by key, we:
    hash the key
    return ( vals [ idxs [ hash_obj(key) ] ] ) [0]
*/
object_t* hash_get_copy (const hash_t* const h, const object_t* const key, bool* ok) {
  pfn();

  if (NULL != ok) {
    *ok = true;
  }

  if ( ! hash_exists(h, key) ) {
    if (NULL != ok) {
      *ok = false;
    }
    object_error(KEYERROR, __func__, false);
    return object_new(t_F, NULL);
  }

  hashkey_t kh;
  object_t **valpair, *finalval;

  // hash the key
  kh      = hash_obj(key);
  // get the object by copy (accepts NULL)
  valpair = array_get_ref(h->vals, (h->idxs) [kh], ok);
  if ( (false == *ok) && (ok != NULL) ) {
    object_error(PTRMATH_BUG, __func__, true);
    return object_new(t_F, NULL);
  }

  // get the first item, which should be the value
  finalval = pair_car_copy( (*valpair)->cel );     // 1

  // 1 alloc, 0 frees, the last free is up to the caller

  return finalval;
}

/*
  return a reference to a value by key.

  implemented with the same semantics as hash_get_copy.

  it's not provided to change members of the keys array, because thisp
  would cause the hashtable to be in an invalid state, in which the keys no longer
  hash to the hashes stored. recomputing just one hash of the entire table could result
  in a hash collision.
*/
object_t** hash_get_ref (const hash_t* const h, const object_t* const key, bool* ok) {
  pfn();

  if (NULL != ok) {
    *ok = true;
  }

  if ( ! hash_exists(h, key) ) {
    if (NULL != ok) {
      *ok = false;
    }
    object_error(KEYERROR, __func__, false);
    return NULL;
  }

  hashkey_t kh;
  object_t **valpair;

  // hash the key
  kh      = hash_obj(key);
  // get the object by copy (accepts NULL)
  valpair = array_get_ref(h->vals, (h->idxs) [kh], ok);
  if (false == *ok && ok != NULL) {
    object_error(PTRMATH_BUG, __func__, true);
    return NULL;
  }

  // 0 allocs, 0 frees, the last free is up to the caller
  // get the first item, which should be the value
  return pair_car_ref( (*valpair)->cel );     // 1
}

/*
  change a value at a key in a hash

  returns false and does nothing if an error occurs.

  does nothing successfully if the new and old keys compare equal.
*/
bool hash_change_at (hash_t* const h, const object_t* const obj, object_t* newval) {

  bool ok = true;

  object_t** ref = hash_get_ref(h, obj, &ok);

  if ( false == ok ) {
    return false;
  }

  if ( object_equals(*ref, newval) ) {
    return true;
  }

  *ref = newval;

  return ok;
}

/*
  change the key oldkey to newkey, preserving the value.

  returns false if an error occurs.

  does nothing successfully if oldkey and newkey compare equal.
*/
bool hash_change_key (hash_t* const h, const object_t* const oldkey, const object_t* const newkey) {

  if ( object_equals(oldkey, newkey) ) {
    return true;
  }

  bool ok = true;

  object_t
    *val = hash_get_copy(h, oldkey, &ok);

  if ( false == ok ) {
    return false;
  }

  ok = hash_add(h, newkey, val);

  if ( false == ok ) {
    return false;
  }

  hash_delete(h, oldkey);

  object_destruct(val);

  return ok;
}

/*
  return the list of values, eg the car of every pair in hash->vals
*/
array_t* hash_getvals (const hash_t* h) {
  pfn();

  // new empty value store
  array_t* vs = array_new(NULL, -1); // 1

  size_t vlen = signed2un(h->vals->idx);

  for (size_t i = 0; i < vlen; i++) {
    object_t
      // get a reference to thisp value's pair
      **p   = array_get_ref(vs, un2signed(i), NULL),
      // get a reference to its first item
      **car = pair_car_ref( (*p)->cel );

    // copy it to the end of the array
    array_append(vs, *car);
  }

  // 1 alloc, 0 frees, last is for caller
  return vs;
}

/*
  add a value with its key to a hash.

  to set a value to a key, we:
    hash the key
    array_append( keys, key )
    array_append( vals, pair{ value, hash_obj(key) } )
    resize idxs to vals->idx + 1
    idxs [ hash_obj(key) ] = vals->idx
*/
bool hash_add (hash_t* const h, const object_t* const key, const object_t* const val) {
  pfn();

  pair_t* newp;
  object_t *pairobj, *khobj;

  // hash the key
  const hashkey_t kh = hash_obj(key);


  // fail if it exists
  if ( hash_exists(h, key) || hash_keyexists(h, key) ) {
    return false;
  }

  // add the key to the list
  array_append(h->keys, key);

  // objectify the key hash
  khobj = object_new(t_realuint, &kh); // 1
  // make a pair out of the value and keyhash obj
  newp  = pair_new(val, khobj); // 2


  // objectify the pair
  pairobj = object_new(t_pair, (const void * const) newp); // 3

  object_destruct(khobj); // ~1
  pair_destruct(newp); // ~2

  // add the pair to values
  array_append(h->vals, pairobj);
  // resize the idxs array by the needed amount
  h->idxs = (typeof(h->idxs)) saferealloc(h->idxs, sizeof (size_t) * kh + 1);
  // increment the pointer
  ++(h->idxs_len);
  // assign the index of the pair in values to idxs
  (h->idxs) [kh] = h->vals->idx;
  // looks like everything went ok
  return true;
}

/*
  test, by simple search, whether thisp key is in the list of keys
*/
bool hash_keyexists (const hash_t* const h, const object_t* const key) {
  pfn();

  return -1 != array_find(h->keys, key);
}

/*
  test if the hash of the key is in the hash.
*/
bool hash_exists (const hash_t* const h, const object_t* const key) {
  pfn();

  hashkey_t kh = hash_obj(key);

  if (kh > h->idxs_len) {
    return false;
  }

  return -1 != h->idxs[kh];
}

inline static ssize_t findlast (
  const ssize_t* const array,
  const size_t         len,
  const ssize_t        n,
  const bool           invert_cmp
) {

  for (size_t i = len; i != 0; i--) {

    if ( invert_cmp ) {

      if ( array[i] != n ) {
        return un2signed(i);
      }
    } else {
      if ( array[i] == n ) {
        return un2signed(i);
      }
    }
  }

  return -1;
}

/*
  remove a key and value from a hash by key.

  to delete a value by key, we:
    hash the key
    array_delete( keys, array_find( keys, key ) )
    array_delete( vals, idxs [ hash_obj(key) ] )
    idxs[ hash_obj(key) ] = -1
    resize idxs to be as small as possible

*/
void hash_delete (hash_t* const h, const object_t* const key) {
  pfn();

  // hash the key
  hashkey_t kh = hash_obj(key);

  ssize_t keyidx = array_find(h->keys, key);

  if ( -1 == keyidx ) {
    object_error(KEYERROR, __func__, false);
    return;
  }
  // delete the key
  array_delete(h->keys, keyidx);

  // delete the value
  array_delete(h->vals, h->idxs[kh]);

  // invalidate its position in the index list
  (h->idxs) [kh] = -1;

  // find the last occurence of something that isn't -1
  size_t lastval = signed2un( findlast(h->idxs, h->idxs_len, -1, true) );

  // resize to be as small as possible
  h->idxs = (typeof(h->idxs)) saferealloc(h->idxs, sizeof(size_t *) * lastval);

}

/*
  recompute the hash of every key and value.

  the simple way to do thisp is to change h to point to a new hash with the data of the
  old one.

  useful if you modified a key in place. you're dumb in that case.

  =====
  recompute base encryption hash key sequence
  thisp may take forever. do not interrupt the hash recompute or you may be required
  to relicense all your products. don't believe us? try it.

  -- The Website is Down Episode #4: Sales Demolition
*/
void hash_recompute (const hash_t* h) {
  h = hash_copy(h);
}

char* hash_see (const hash_t* const h) {
  pfn();

  (void) h;
  char*  buf = (typeof(buf)) safemalloc(1);
  return buf;
}

void hash_inspect (const hash_t* const h) {
  printf("WARN: LONG OUTPUT\n");

  printf("hash #%zu\n", h->uid);

  printf("%zu keys:\n", h->keys->idx);
  dealloc_printf( array_see(h->keys) );

  printf("%zu vals:\n", h->vals->idx);
  dealloc_printf( array_see(h->vals) );

  printf("%zu idxs:\n", h->idxs_len);
  for (size_t i = 0; i < h->idxs_len; i++) {
    printf("i:%zu d:%zu ", i, h->idxs[i]);
  }

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
