#ifdef GCC
#line 2 "objcommon"
#endif

#pragma once
#include "../../points/points.h"

typedef enum {
  t_F, // only false value
  t_number,
  t_string,
  t_point,
  t_shape,
  t_func,
  t_array,
  t_realchar,
  NUM_OBJTYPES
} objtype_t;

typedef struct st_obj_t   object_t;
typedef struct st_F_t     F_t;

typedef struct st_numb_t  number_t;
typedef struct st_fnc_t   func_t;
typedef struct st_str_t   string_t;
typedef struct st_array_t array_t;

// false singleton
struct st_F_t {
  void* nothing;
  size_t uid;
};

struct st_fnc_t {
  char* code;
  char* name;
  size_t uid;
};

struct st_str_t {
  char* data;
  ssize_t len;
  size_t uid;
};

struct st_array_t {
  object_t** data;
  ssize_t    idx;  // -1 for empty
  size_t uid;
};

struct st_numb_t {
  long double value;
  size_t uid;
};

struct st_obj_t {
  objtype_t type;
  union {
    F_t*       f;
    number_t*  num;
    string_t*  str;
    point_t*   pt;
    shape_t*   sp;
    func_t*    fnc;
    array_t*   ary;
  };
  size_t uid;
};

object_t*  object_new (const objtype_t valtype, const void* const val);
object_t* object_copy (const object_t* const obj);

void object_destruct (object_t* obj);
void** object_getval (const object_t* const obj);
char*   objtype_repr (const objtype_t t);

array_t*    array_new (const object_t* const * const objs, const ssize_t len);
void   array_destruct (array_t* const a);
array_t*   array_copy (const array_t* const a);
bool    array_isempty (const array_t* const a);
void     array_resize (array_t* const a, const ssize_t new_len);
void     array_delete (array_t* const a, const ssize_t idx);
void     array_append (array_t* const a, const object_t* const o, const ssize_t idx);

string_t*  string_new (const char* const str);
void  string_destruct (string_t* s);
string_t* string_copy (const string_t* const s);
bool   string_isempty (const string_t* const s);
