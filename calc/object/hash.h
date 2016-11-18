#include "objcommon.h"

#ifdef GCC
#line __LINE__ "hash"
#endif

#include "../../fnv-hash/fnv.h"

typedef Fnv32_t hashkey_t;

hashkey_t hash_obj (const object_t* const obj);

/*
  make a new empty hash skeleton
*/
hash_t* hash_new_skele (void) {
  pfn();

  hash_t*  hash = (typeof(hash)) safemalloc( sizeof(hash_t) );

  hash->keys     = array_new(NULL, -1);
  hash->vals     = assoc_new(NULL, NULL);
  hash->idxs     = assoc_new(NULL, NULL);

  report_ctor(hash);

  return hash;
}

hash_t* hash_new_boa (
  const array_t* const keys,
  const array_t* const vals
) {
  pfn();

  size_t len = size_t_min( array_length(keys), array_length(vals) );

  printf("minsize: %zd\n", len);

  hash_t* hash = hash_new_skele(); // 1

  for (size_t i = 0; i < len; i++) {
    object_t
      **k = array_get_ref(keys, i, NULL),
      **v = array_get_ref(vals, i, NULL);

    // references are okay because thisp will copy them anyways
    if ( ! hash_add(hash, *k, *v) ) {
      break;
    }
  }

  // 1 alloc, 0 frees, last free is caller's problem
  return hash;
}

void  hash_destruct (hash_t* const hash) {
  pfn();

  report_dtor(hash);

  array_destruct(hash->keys);
  assoc_destruct(hash->vals);
  assoc_destruct(hash->idxs);
  safefree(hash);
}

define_objtype_dtor_args(hash);

hash_t*   hash_copy (const hash_t* const h) {
  pfn();

  object_failnull(h);

  array_t* values = hash_getvals(h); // 1

  // 2
  hash_t* copy = hash_new_boa(h->keys, values);

  array_destruct(values); // ~1
  return copy;
}

bool   hash_isempty (const hash_t* const h) {
  pfn();

  object_failnull(h);

  return 0 == hash_length(h);
}

size_t hash_length (const hash_t* const h) {
  pfn();

  object_failnull(h);

  return assoc_length(h->idxs);
}

/*
  hash an object's string representation using Fowler Noll Vo 32-bits
*/
hashkey_t hash_obj (const object_t* const obj) {
  pfn();

  object_failnull(obj);

  char* buf      = object_repr(obj);
  hashkey_t hval = fnv_32a_str(buf, FNV1_32A_INIT);
  safefree(buf);

  char* s = objtype_repr(obj->type);
  dbg_prn("hash of %s #%zu is %d", s, obj->uid, hval);
  safefree(s);

  return hval;
}

static inline object_t* hash_val_asobject (const object_t* const obj) {
  pfn();

  object_failnull(obj);

  hashkey_t kh = hash_obj(obj);
  object_t* khobj = object_new(t_realuint, &kh);

  return khobj;
}

/*
  return a copy of a value in a hash by key.

  to get a value by key, we:
    hash the key
    return ( vals [ idxs [ hash_obj(key) ] ] ) [0]
*/
object_t* hash_get_copy (const hash_t* const h, const object_t* const key, bool* ok) {
  pfn();

  object_failnull(h);

  if (NULL != ok) {
    *ok = true;
  }

  if ( ! hash_exists(h, key) ) {
    if (NULL != ok) {
      *ok = false;
    }
    char* s = object_repr(key);
    object_error(ER_KEYERROR, false, "no such key %s in hash #%zu", s, h->uid);
    safefree(s);
    return object_new(t_F, NULL);
  }

  object_t *finalval, *khobj;
  pair_t** valpair;

  // hash the key
  khobj = hash_val_asobject(key);
  // get the object by copy (accepts NULL)
  ssize_t proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);

  if ( -1 == proxy_idx ) {
    object_destruct(khobj);
    return object_new(t_F, NULL);
  }

  valpair = assoc_get_ref(h->vals, signed2un(proxy_idx), ok);

  object_destruct(khobj);

  if ( (NULL != ok) && (false == *ok) ) {
    char* s = object_repr(key);
    object_error(
      ER_PTRMATH_BUG,
      true,
      "getting key %s from hash #%zu",
      s,
      h->uid
    );
    safefree(s);
    return object_new(t_F, NULL);
  }

  // get the first item, which should be the value
  finalval = pair_car_copy(*valpair);     // 1

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

  object_failnull(h);

  if (NULL != ok) {
    *ok = true;
  }

  if ( ! hash_exists(h, key) ) {
    if (NULL != ok) {
      *ok = false;
    }
    char* s = object_repr(key);
    object_error(ER_KEYERROR, false, "no such key %s in hash #%zu", s, h->uid);;
    safefree(s);
    return NULL;
  }

  object_t* khobj;
  pair_t **valpair;

  // hash the key
  khobj = hash_val_asobject(key);
  // get the object by copy (accepts NULL)
  ssize_t proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);

  if ( -1 == proxy_idx ) {
    object_destruct(khobj);
    return NULL;
  }

  valpair = assoc_get_ref(h->vals, signed2un(proxy_idx), ok);

  object_destruct(khobj);

  if ( (NULL != ok) && (false == *ok) ) {
    char* s = object_repr(key);
    object_error(
      ER_PTRMATH_BUG,
      true,
      "getting key %s from hash #%zu",
      s,
      h->uid
    );
    safefree(s);
    return NULL;
  }

  // 0 allocs, 0 frees, the last free is up to the caller
  // get the first item, which should be the value
  return pair_car_ref( *valpair );     // 1
}

/*
  change a value at a key in a hash

  returns false and does nothing if an error occurs.

  does nothing successfully if the new and old keys compare equal.
*/
bool hash_change_at (hash_t* const h, const object_t* const obj, object_t* newval) {
  pfn();

  object_failnull(h);

  bool ok = true;

  object_t** ref = hash_get_ref(h, obj, &ok);

  if ( ! ok ) {
    return false;
  }

  if ( ! object_equals(*ref, newval) ) {
    object_destruct(*ref);
    *ref = object_copy(newval);
  }

  return true;
}

/*
  change the key oldkey to newkey, preserving the value.

  returns false if an error occurs.

  does nothing successfully if oldkey and newkey compare equal.
*/
bool hash_change_key (hash_t* const h, const object_t* const oldkey, const object_t* const newkey) {
  pfn();

  object_failnull(h);

  if ( object_equals(oldkey, newkey) ) {
    return true;
  }

  bool ok = true;

  object_t* val = hash_get_copy(h, oldkey, &ok); // 1

  if ( ! ok ) {
    object_destruct(val);
    return false;
  }

  ok = hash_add(h, newkey, val);

  object_destruct(val);

  if ( ok ) {
    hash_delete(h, oldkey);
    return true;
  }

  return false;
}

/*
  return the list of values, eg the car of every pair in hash->vals
*/
array_t* hash_getvals (const hash_t* const h) {
  pfn();

  object_failnull(h);

  // new empty value store
  array_t* vs = array_new(NULL, -1); // 1

  for (size_t i = 0; i < array_length(h->keys); i++) {
    // get a reference to thisp value's pair's first item
    object_t **car = pair_car_ref( ( *array_get_ref(vs, i, NULL) )->cel );

    // copy it to the end of the array
    array_append(vs, *car);
  }

  // 1 alloc, 0 frees, last is for caller
  return vs;
}

/*
  return the list of keys
*/
array_t* hash_getkeys (const hash_t* const h) {
  pfn();

  object_failnull(h);

  array_t* ks = array_new(NULL, -1);

  for (size_t i = 0; i < array_length(h->keys); i++) {
    array_append(ks, *array_get_ref(h->keys, i, NULL));
  }

  return ks;
}

/*
  write the keys and values to pointers supplied by caller
*/
void hash_unzip (const hash_t* const h, array_t** keys, array_t** vals) {
  pfn();

  object_failnull(h);

  *keys = hash_getkeys(h),
  *vals = hash_getvals(h);
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
bool hash_add (hash_t* h, const object_t* const key, const object_t* const val) {
  pfn();

  object_failnull(h);

  // fail if it exists
  if ( hash_exists(h, key) || hash_keyexists(h, key) ) {
    return false;
  }
  // add the key to the list
  array_append(h->keys, key);

  // objectify the key hash
  object_t *khobj = hash_val_asobject(key), // 1
           *newidx;

  // add the value and keyhash obj to values
  assoc_append_boa(h->vals, val, khobj);

  newidx = object_new(t_realint, &( h->vals->idx )); // 2

  assoc_append_boa(h->idxs, khobj, newidx);

  object_destruct_args(2, newidx, khobj); // ~1, ~2

  // looks like everything went ok
  // 1 alloc, 1 free
  return true;
}

/*
  test, by simple search, whether thisp key is in the list of keys
*/
bool hash_keyexists (const hash_t* const h, const object_t* const key) {
  pfn();

  return object_failnull(h)
    ? -1 != array_find(h->keys, key)
    : false;
}

/*
  test if the hash of the key is in the hash.
*/
bool hash_exists (const hash_t* const h, const object_t* const key) {
  pfn();

  object_failnull(h);

  object_t* khobj = hash_val_asobject(key);

  bool found = -1 != assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);

  object_destruct(khobj);

  return found;
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
bool hash_delete (hash_t* const h, const object_t* const key) {
  pfn();

  object_failnull(h);

  // hash the key
  object_t* khobj = hash_val_asobject(key);

  ssize_t keyidx = array_find(h->keys, key),
          proxy_idx = assoc_schreg_1st(h->idxs, khobj, &pair_car_ref);

  if ( ! hash_exists(h, key) || ( -1 == keyidx ) || ( -1 == proxy_idx ) ) {
    char* s = object_repr(key);
    object_error(ER_KEYERROR, false, "no such key %s in hash #%zu", s, h->uid);
    safefree(s);
    return false;
  }

  // delete the key
  array_delete(h->keys, signed2un(keyidx));

  // delete the value
  assoc_delete(h->vals,
    (size_t) *object_getval(
      *pair_cdr_ref(
        *assoc_get_ref(h->idxs, signed2un(proxy_idx), NULL)
      )
    )
  );

  // invalidate its position in the index list
  assoc_delete(h->idxs, signed2un(proxy_idx));

  return true;
}

/*
  recompute the hash of every key and value.

  the simple way to do thisp is to change h to point to a new hash with the data of the
  old one.

  useful if you modified a key in place. you're dumb in that case.

  =====
  recompute base encryption hash key sequence
  this may take forever. do not interrupt the hash recompute or you may be required
  to relicense all your products. don't believe us? try it.

  -- The Website is Down Episode #4: Sales Demolition
*/
void hash_recompute (hash_t** const h) {
  pfn();

  *h = hash_copy(*h);
}

char* hash_see (const hash_t* const h) {
  pfn();

  object_failnull(h);

  (void) h;
  char*  buf = (typeof(buf)) safemalloc(1);
  return buf;
}

void hash_inspect (const hash_t* const h) {
  pfn();

  printf("hash uid:%zu idxs_len:%zu {\n", h->uid, assoc_length(h->idxs));

  printf("\tkeys: %zd\n\t", h->keys->idx + 1);
  char* s = array_see(h->keys);
  dealloc_printf( s );

  printf("\tvals: %zd\n\t", h->vals->idx + 1);
  s = assoc_see(h->vals);
  dealloc_printf( s );

  printf("\n\tidxs: %zu\n", assoc_length(h->idxs));

  puts("\n}");

}

bool hash_equals (const hash_t* const a, const hash_t* const b) {
  pfn();

  object_failnull(a);

  if ( hash_isempty(a) && hash_isempty(b) ) {
    return true;
  }

  return
    array_equals(a->keys, b->keys)
    && assoc_equals(a->vals, b->vals)
    && assoc_equals(a->idxs, b->idxs);
}
