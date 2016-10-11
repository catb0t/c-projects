#ifdef GCC
#line 2 "objcommon"
#endif

#pragma once
#include "../../common.h"
#include "../../points/points.h"

typedef enum {
  t_F, // only false value
  t_number,
  t_string,
  t_point,
  t_shape,
  t_func,
  t_array,
  t_hash,
  t_realchar,
  NUM_OBJTYPES
} objtype_t;

typedef enum {
  NOT_A_TYPE,
  KEYERROR,
} objerror_t;

typedef struct st_obj_t   object_t;
typedef struct st_F_t     F_t;
typedef struct st_numb_t  number_t;
typedef struct st_fnc_t   func_t;
typedef struct st_str_t   string_t;
typedef struct st_array_t array_t;
typedef struct st_hash_t  hash_t;

// false singleton
struct st_F_t {
  void*  nothing;
  size_t uid;
};

struct st_fnc_t {
  char*  code;
  char*  name;
  size_t uid;
};

struct st_str_t {
  char*   data;
  size_t len;
  size_t  uid;
};

struct st_array_t {
  object_t** data;
  ssize_t    idx;  // -1 for empty
  size_t     uid;
};

struct st_numb_t {
  long double value;
  size_t      uid;
};

struct st_hash_t {
  array_t* keys;
  array_t* vals;
  size_t   len;

  size_t   uid;
};

struct st_obj_t {
  objtype_t type;
  union {
    F_t*      f;
    number_t* num;
    string_t* str;
    point_t*  pt;
    shape_t*  sp;
    func_t*   fnc;
    array_t*  ary;
    hash_t*   hsh;
  };
  size_t uid;
};



void object_error (objerror_t errt, const char* const info, const bool fatal);

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

// provided by array.h
array_t*    array_new (const object_t* const * const objs, const ssize_t len);
array_t*   array_copy (const array_t* const a);
char*       array_see (const array_t* const a);
object_t*   array_get (const array_t* const a, const ssize_t idx, bool* ok);
ssize_t    array_find (const array_t* const a, const object_t* const obj);
bool     array_equals (const array_t* const a, const array_t* const b);
bool    array_isempty (const array_t* const a);
void     array_resize (array_t* const a, const ssize_t new_len);
void     array_delete (array_t* const a, const ssize_t idx);
void     array_append (array_t* const a, const object_t* const o, const ssize_t idx);
void   array_destruct (array_t* const a);

// provided by string.h
string_t*  string_new (const char* const str);
string_t* string_copy (const string_t* const s);
void  string_destruct (string_t* s);
bool   string_isempty (const string_t* const s);

// provided by hash.h
hash_t*    hash_new (const array_t* const keys, const array_t* const vals, const size_t len);
hash_t*   hash_copy (const hash_t* const h);
char*      hash_see (const hash_t* const h);
object_t*  hash_get (const hash_t* const h, const object_t* const key, bool* ok);
bool    hash_equals (const hash_t* const a, const hash_t* const b);
bool   hash_isempty (const hash_t* const h);
void       hash_set (const hash_t* const h, const object_t* const key);
void    hash_delete (const hash_t* const h, const object_t* const key);
void    hash_resize (hash_t* h, const size_t );
void  hash_destruct (hash_t* h);

// provided by number.h
number_t*  number_new (const long double val);
number_t* number_copy (const number_t* const n);
char*      number_see (const number_t* const n);
bool        number_eq (const number_t* const n);
bool        number_gt (const number_t* const n);
bool        number_lt (const number_t* const n);
void  number_destruct (number_t* n);

