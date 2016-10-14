#ifdef GCC
#line 2 "objcommon"
#endif

#include <stdarg.h>
#pragma once
#include "../../common.h"
#include "../../points/points.h"

#define LD_EPSILON 0.001L // this is how to compare floating point, right??

typedef enum {
  t_F, // only false value
  t_number,
  t_fixwid,
  t_string,
  t_point,
  t_shape,
  t_func,
  t_array,
  t_hash,
  t_pair,
  t_realint,
  t_realchar,
  NUM_OBJTYPES
} objtype_t;

typedef enum {
  NOT_A_TYPE,
  KEYERROR,
} objerror_t;

// object object
typedef struct st_obj_t   object_t;
// false singleton compares false with everything except itself
typedef struct st_F_t     F_t;

// arithmetic types
//  arbitrary precision
typedef struct st_numb_t  number_t;
//  convenience:
typedef       long double numderlying_t;
//  fixed width signed integral type -- underlying uses ssize_t and size_t
typedef struct st_fxwd_t  fixwid_t;

// collections
//  string is mostly just a wrapper for char*, at least for now
typedef struct st_str_t   string_t;
//  array is little more than a list of objects
typedef struct st_array_t array_t;
//  hash is implemented using FNV-1A 32-bit
typedef struct st_hash_t  hash_t;
//  pair is just two things -- this can be used for a singly linked list
typedef struct st_pair_t  pair_t;

// function type
typedef struct st_fnc_t   func_t;

/*
  the point of having this as a struct is
  C compiler errors around void* casts and alignment
  if it were:
    typedef void* st_F_t
  then `f` would be transparently and silently castable
  to any other pointer (and thus object) type -- not desired behaviour
*/
struct st_F_t {
  void*  nothing;

  OBJ_UID_SLOT;
};

struct st_fnc_t {
  char*  code;
  char*  name;

  OBJ_UID_SLOT;
};

/*
  for now, data is null terminated and not wide
  and len is mostly for convenience
  a len of 0 indicates an empty string
*/
struct st_str_t {
  char*   data;
  size_t  len;

  OBJ_UID_SLOT;
};

/*
  idx is a direct index value to the last value in data
  -1 indicates an empty array, but use array_isempty instead
*/
struct st_array_t {
  object_t** data;
  ssize_t    idx;  // -1 for empty

  OBJ_UID_SLOT;
};

/*
  again, the point of having this primitive as a struct
  type is that it can be cast between void* and itself

  or void** in the case of struct pointers, which are primarily used
*/
struct st_numb_t {
  numderlying_t value;

  OBJ_UID_SLOT;
};

/*
  another wrapper for void*?* convenience
  note that sign_active only indicates which union member should be used
  and should not be correlated to the actual sign of the union's 'active' value

  if sign_active is true, refer to `svalue`, and value otherwise.
*/
struct st_fxwd_t {
  ssize_t value;

  OBJ_UID_SLOT;
};

/*
  a pair is a very simple concept -- a collection which holds at most two things

  especially useful for e.g a singly linked list, in which each node contains data
  and a pointer to the next node, or NULL / an object of objtype_t t_F for the end of the list.
*/
struct st_pair_t {
  object_t* car;
  object_t* cdr;

  OBJ_UID_SLOT;
};

/*
  a hashtable consists of:
    non-sparse list of keys: array_t
    non-sparse list of pairs of values and
    sparse list of which values map to which actual entries.

  in pythonish syntax (and inspired from python 3.6's ordered dictionaries):

  { 1: 'a', 2: 'b', 3: 'c' }

  is represented in this structure as:

  hash->keys = array{ 1, 2, 3 }
  hash->vals = array{
    pair{ 'a' 5 }
    pair{ 'b' 7 }
    pair{ 'c' 9 }
  }
  hash->idxs = { -1 -1 -1 -1 -1  0 -1  1 -1  2 }
                 0  1  2  3  4  5  6  7  8  9

  to get an value by key, we:
    hash the key
    return ( vals [ idxs [ hash_obj(key) ] ] ) [0]

  to set a value to a key, we:
    hash the key
    array_append( keys, key )
    array_append( vals, pair{ value, hash_obj(key) } )
    resize idxs to vals->idx + 1
    idxs [ hash_obj(key) ] = vals->idx

  to delete a value by key, we:
    hash the key
    array_delete( keys, array_find( keys, key ) )
    array_delete( vals, idxs [ hash_obj(key) ] )
    idxs[ hash_obj(key) ] = -1
    resize idxs to be as small as possible

  to find a key or value by value, we:
    binary search the list of pairs of values
    use the hash value from the search to get the value in idxs
    hash each value in keys until we find the one matching


*/
struct st_hash_t {
  array_t* keys;
  array_t* vals;

  ssize_t* idxs;
  size_t   idxs_len;

  OBJ_UID_SLOT;
};

struct st_obj_t {
  objtype_t type;
  union {
    F_t*      f;
    number_t* num;
    fixwid_t* fwi;
    string_t* str;
    point_t*  pt;
    shape_t*  sp;
    func_t*   fnc;
    array_t*  ary;
    hash_t*   hsh;
    pair_t*   cel;
  };

  OBJ_UID_SLOT;
};



void object_error (objerror_t, const char* const, const bool);

void object_error (objerror_t errt, const char* const info, const bool fatal) {
  pfn();

  if (NOT_A_TYPE == errt) {
    fprintf(stderr, "%s: NUM_OBJTYPES isn't a real type, dummy. Don't do that.\n"
      "Have you considered trying to match wits with a rutabaga?",
      info
    );
  } else {
    fprintf(stderr, "%s:%s\n", "some object-error occurred...", info);
  }

  if ( fatal ) {
    abort();
  }

}

// provided by object.h
object_t*  object_new (const objtype_t valtype, const void* const val);
object_t* object_copy (const object_t* const obj);
object_t* nothing_new (void);
void**  object_getval (const object_t* const obj);
char*     object_repr (const object_t* const obj);
char*    objtype_repr (const objtype_t t);
bool object_id_equals (const object_t* const a, const object_t* const b);
bool    object_equals (const object_t* const a, const object_t* const b);
void  object_destruct (object_t* obj);
void object_dtor_args (size_t args, ...);

// provided by array.h
array_t*       array_new (const object_t* const * const objs, const ssize_t len);
array_t*      array_copy (const array_t* const a);
char*          array_see (const array_t* const a);
object_t* array_get_copy (const array_t* const a, const ssize_t idx, bool* ok);
object_t** array_get_ref (const array_t* const a, const ssize_t idx, bool* ok);
ssize_t       array_find (const array_t* const a, const object_t* const obj);
bool        array_equals (const array_t* const a, const array_t* const b);
bool       array_isempty (const array_t* const a);
void        array_resize (array_t* const a, const ssize_t new_len);
void        array_delete (array_t* const a, const ssize_t idx);
void        array_append (array_t* const a, const object_t* const o);
void      array_destruct (array_t* const a);

// provided by string.h
string_t*  string_new (const char* const str);
string_t* string_copy (const string_t* const s);
bool   string_isempty (const string_t* const s);
void  string_destruct (string_t* const s);

// provided by hash.h
hash_t* hash_new_skele (void);
hash_t*   hash_new_boa (const array_t* const keys, const array_t* const vals, const size_t len);
hash_t*      hash_copy (const hash_t* const h);
char*         hash_see (const hash_t* const h);
object_t*     hash_get (const hash_t* const h, const object_t* const key, bool* ok);
array_t*  hash_getvals (const hash_t* const h);
bool       hash_equals (const hash_t* const a, const hash_t* const b);
bool      hash_isempty (const hash_t* const h);
bool          hash_add (hash_t* const h, const object_t* const key, const object_t* val);
bool    hash_keyexists (const hash_t* const h, const object_t* const key);
bool       hash_exists (const hash_t* const h, const object_t* const key);
void       hash_delete (hash_t* const h, const object_t* const key);
void       hash_resize (hash_t* const h, const size_t new_len);
void     hash_destruct (hash_t* const h);

// provided by pair.h
// yes, it's cons, but the idiomatic thing here is typename_new
pair_t*   pair_new (const object_t* const car, const object_t* const cdr);
pair_t*  pair_copy (const pair_t* const p);
char*     pair_see (const pair_t* const p);
object_t* pair_car (const pair_t* const p);
object_t* pair_cdr (const pair_t* const p);
bool   pair_equals (const pair_t* const a, const pair_t* const b);
void pair_destruct (pair_t* const p);

// provided by number.h
number_t*  number_new (const long double val);
number_t* number_copy (const number_t* const n);
char*      number_see (const number_t* const n);
bool        number_eq (const number_t* const a, const number_t* const b);
bool        number_gt (const number_t* const a, const number_t* const b);
bool        number_lt (const number_t* const a, const number_t* const b);
void  number_destruct (number_t* const n);

// provided by fixdsz.h
fixwid_t*  fixwid_new (const ssize_t n);
fixwid_t* fixwid_copy (const fixwid_t* const n);
char*      fixwid_see (const fixwid_t* const n);
void  fixwid_destruct (fixwid_t* const n);
bool    fixwid_eq (const fixwid_t* const a, const fixwid_t* const b);
bool    fixwid_gt (const fixwid_t* const a, const fixwid_t* const b);
bool    fixwid_lt (const fixwid_t* const a, const fixwid_t* const b);
