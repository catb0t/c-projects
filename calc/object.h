#ifdef GCC
#line 2 "object"
#endif

#include "../points/points.h"

typedef long double number_t;

typedef struct {
  char* code;
  char* name;
} func_t;

typedef enum {
  number,
  string,
  point,
  shape,
  func,
  array
} objtype_t;

typedef struct sobj_t object_t;

typedef struct {
  object_t** data;
  ssize_t len;
} array_t;

struct sobj_t {
  objtype_t type;
  union {
    number_t*  num;
    char*      str;
    point_t*   pt;
    shape_t*   sp;
    func_t*    fnc;
    array_t* ary;
  };
};

object_t* object_new (objtype_t valtype, void* val);

void object_destruct (object_t* obj);

object_t* object_new (objtype_t valtype, void* val) {

  object_t* obj = safemalloc(sizeof (object_t));
  obj->type     = valtype;

  switch (valtype) {
    case number: {
      obj->num = (number_t *) val;
      break;
    }
    case string: {
      obj->str = (char *) val;
      break;
    }
    case point: {
      obj->pt  = (point_t *) val;
      break;
    }
    case shape: {
      obj->sp  = (shape_t *) val;
      break;
    }
    case func: {
      obj->fnc = (func_t *) val;
      break;
    }
    case array: {
      obj->ary = (array_t *) val;
      break;
    }
  }

  return obj;
}

void object_destruct (object_t* obj) {
  switch (obj->type) {
    case number: {
      safefree(obj->num);
      break;
    }
    case string: {
      safefree(obj->str);
      break;
    }
    case point: {
      safefree(obj->pt);
      break;
    }
    case shape: {
      safefree(obj->sp);
      break;
    }
    case func: {
      safefree(obj->fnc);
      break;
    }
    case array: {
      free_ptr_array(
        (void **) obj->ary->data,
        (size_t) obj->ary->len
      );
      safefree(obj->ary);
      break;
    }
  }
  safefree(obj);
}
