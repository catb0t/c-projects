#ifdef GCC
#line 2 "object"
#endif

#ifdef STACK
#include "../../common.h"
typedef long double number_t;
#else

#include "array.h"
#include "string.h"

object_t* object_new (const objtype_t valtype, const void* const val) {
  pfn(__FILE__, __LINE__, __func__);

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

  report_ctor("obj", obj);

  return obj;
}

object_t* object_copy (const object_t* const obj) {
  pfn(__FILE__, __LINE__, __func__);

  if (NULL == obj) {
    return object_new(t_F, NULL);
  }

  return object_new(obj->type, object_getval(obj));
}

void** object_getval (const object_t* const obj) {
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

  report_dtor("obj", obj);

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
  pfn(__FILE__, __LINE__, __func__);

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
    ((sizeof obj_strings) / NUM_OBJTYPES) == NUM_OBJTYPES,
    "not all objtypes handled by objtype_repr"
  );

  const char* const this = obj_strings[t];
  char* out = safemalloc(safestrnlen(this) + 1);
  snprintf(out, 20, "%s", this);
  return out;
}

#endif
