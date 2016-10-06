#ifdef GCC
#line 2 "object"
#endif

#pragma once
#include "../points/points.h"

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
#ifdef STACK
typedef long double number_t;
#else
typedef struct st_numb_t  number_t;
#endif
typedef struct st_fnc_t   func_t;
typedef struct st_str_t   string_t;
typedef struct st_array_t array_t;

// false singleton
struct st_F_t {
  void* nothing;

  void (* destruct) (F_t*);
};

struct st_fnc_t {
  char* code;
  char* name;
};

struct st_str_t {
  char* data;
  ssize_t len;
};

struct st_array_t {
  object_t** data;
  ssize_t    len;  // -1 for empty
};

struct st_numb_t {
  long double value;
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
};

object_t*  object_new (const objtype_t valtype, const void* const val);
object_t* object_copy (const object_t* const obj);

void object_destruct (object_t* obj);
void** object_getval (const object_t* const obj);
char*   objtype_repr (const objtype_t t);

array_t*    array_new (object_t** objs);
void   array_destruct (array_t* a);
array_t*   array_copy (const array_t* const a);
bool    array_isempty (const array_t* const a);

string_t*  string_new (const char* const str);
void  string_destruct (string_t* s);
string_t* string_copy (const string_t* const s);
bool   string_isempty (const string_t* const s);

object_t* object_new (const objtype_t valtype, const void* const val) {

  object_t* obj = safemalloc(sizeof (object_t));
  obj->type     = valtype;

  if (NULL == val) {
    obj->type = t_F;
  }

  switch (obj->type) {
    case NUM_OBJTYPES: {
      fprintf(stderr, "NUM_OBJTYPES isn't a real type, dummy. Don't do that.\n"
        "Have you considered trying to match wits with a rutabaga?"
      );
      abort();
    }
    case t_F: {
      obj->f = safemalloc(sizeof (F_t));
      break;
    }
    case t_number: {
      obj->num        = safemalloc(sizeof (number_t));
      obj->num->value = ((const number_t *) val)->value;
      break;
    }
    case t_string: {
      obj->str = string_copy( (const string_t *) val);
      break;
    }
    case t_realchar: {
      obj->str  = string_new( (const char *) val);
      obj->type = t_string;
      break;
    }
    case t_point: {
      obj->pt  = point_copy( (const point_t *) val);
      break;
    }
    case t_shape: {
      obj->sp  = shape_copy( (const shape_t *) val);
      break;
    }
    case t_func: {
      obj->fnc = safemalloc(sizeof (func_t));
      obj->fnc->code = ((const func_t *) val)->code;
      obj->fnc->name = ((const func_t *) val)->name;
      break;
    }
    case t_array: {
      obj->ary = array_copy( (const array_t *) val);
      break;
    }
  }

  return obj;
}

void** object_getval (const object_t* const obj) {

  if (NULL == obj) {
    return NULL;
  }

  void** types[] = {
    (void **) (obj->f),
    (void **) (obj->num),
    (void **) (obj->str),
    (void **) (obj->pt),
    (void **) (obj->sp),
    (void **) (obj->fnc),
    (void **) (obj->ary),
    (void *)  (obj->str->data) // t_realchar returns str's realchar
  };

  return types[obj->type];
}

void object_destruct (object_t* obj) {

  objtype_t t = obj->type;
  if (t_array == t) {
    free_ptr_array(
      (void **) obj->ary->data,
      (size_t) obj->ary->len
    );

  } else if (t_func == t) {
    safefree(obj->fnc->code);
    safefree(obj->fnc->name);

  } else if (t_string == t || t_realchar == t) {
    safefree(obj->str->data);
  }

  safefree( object_getval(obj) );
  safefree(obj);
}

char* objtype_repr (const objtype_t t) {
  size_t max = 12;
  char *out = safemalloc(max);

  static const char* const obj_strings[] = {
    "F_t",
    "number_t",
    "string_t",
    "point_t",
    "shape_t",
    "func_t",
    "array_t",
    "char* (string_t.data)",
  };

  _Static_assert(
    (sizeof obj_strings / NUM_OBJTYPES) == NUM_OBJTYPES,
    "not all objtypes handled by objtype_repr"
  );

  const char* const this = obj_strings[t];

  printf("%zu\n", sizeof this);
  out = realloc(out, sizeof this);
  snprintf(out, max, "%s", this);
  return out;
}

object_t* object_copy (const object_t* const obj) {

  if (NULL == obj) {
    return object_new(t_F, NULL);
  }

  return object_new(obj->type, object_getval(obj));
}

bool array_isempty (const array_t* const a) {
  return a->len == -1 || (NULL == a->data);
}

array_t* array_copy (const array_t* const a) {

  array_t* out = safemalloc(sizeof (array_t));

  if ( ! array_isempty(a) ) {
    out->data = safemalloc(sizeof (object_t *) * (size_t) a->len);
    out->len  = a->len;

    for (ssize_t i = 0; i < (out->len); i++) {
      out->data[i] = object_copy(a->data[i]);
    }
    return out;
  }

  out->data = NULL;
  out->len  = -1;

  return out;
}

string_t* string_new (const char* const c) {

  string_t* s = safemalloc(sizeof (string_t));
  size_t len = safestrnlen(c);

  s->len  = len ? (ssize_t) len : -1 ;
  s->data = strndup(c, len);

  return s;
}

string_t* string_copy (const string_t* const s) {
  return string_new(s->data);
}
