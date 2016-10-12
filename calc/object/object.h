#ifdef GCC
#line 2 "object"
#endif

#ifdef STACK
#include "../../common.h"
typedef long double number_t;
#else

#include "array.h"
#include "string.h"
#include "hash.h"
#include "number.h"
#include "pair.h"

object_t* nothing_new (void) {
  pfn();

  object_t* False = object_new(t_F, NULL);
  report_ctor(False);
  return False;
}

object_t* object_new (const objtype_t valtype, const void* const val) {
  pfn();

  object_t* obj = safemalloc(sizeof (object_t));
  obj->type     = valtype;

  if ( NULL == val ) {
    obj->type = t_F;
  }

  switch (obj->type) {
    case NUM_OBJTYPES: {
      object_error(NOT_A_TYPE, "object_repr", true);
      break;
    }
    case t_F: {
      obj->f = safemalloc(sizeof (F_t));
      break;
    }
    case t_number: {
      obj->num = number_copy( (const number_t * const) val);
      break;
    }
    case t_realint: {
      //obj->fwi = fixwid_new(const size_t n, bool sign)
      break;
    }
    case t_fixwid: {
      obj->fwi = fixwid_copy( (const fixwid_t * const) val);
      break;
    }
    case t_string: {
      obj->str = string_copy( (const string_t * const) val);
      break;
    }
    case t_realchar: {
      obj->str  = string_new( (const char * const) val);
      obj->type = t_string;
      break;
    }
    case t_point: {
      obj->pt  = point_copy( (const point_t * const) val);
      break;
    }
    case t_shape: {
      obj->sp  = shape_copy( (const shape_t * const) val);
      break;
    }
    case t_func: {
      obj->fnc = safemalloc(sizeof (func_t));
      obj->fnc->code = ((const func_t * const) val)->code;
      obj->fnc->name = ((const func_t * const) val)->name;
      break;
    }
    case t_array: {
      obj->ary = array_copy( (const array_t * const) val);
      break;
    }
    case t_hash: {
      obj->hsh = hash_copy( (const hash_t * const) val);
      break;
    }
    case t_pair: {
      obj->cel = pair_copy( (const pair_t * const) val);
      break;
    }
  }

  report_ctor(obj);

  return obj;
}

object_t* object_copy (const object_t* const obj) {
  pfn();

  if (NULL == obj) {
    return object_new(t_F, NULL);
  }

  return object_new(obj->type, object_getval(obj));
}

void** object_getval (const object_t* const obj) {
  pfn();

  if (NULL == obj) {
    return NULL;
  }

  void** types[] = {
    (void **) (obj->f),
    (void **) (obj->num),
    (void **) (obj->fwi),
    (void **) (obj->str),
    (void **) (obj->pt),
    (void **) (obj->sp),
    (void **) (obj->fnc),
    (void **) (obj->ary),
    (void **) (obj->hsh),
    (void **) (obj->cel),
    (void *)  (obj->str->data) // t_realchar returns str's realchar
  };

  _Static_assert(
    ( (sizeof types) / (sizeof (char *)) == NUM_OBJTYPES),
    "getval types[] has too few or too many values"
  );

  return types[obj->type];
}

void object_destruct (object_t* const obj) {
  pfn();

  report_dtor(obj);

  if ( t_number == obj->type) {
    printf("DESTRUCT NUMBER ID: %zu\n", obj->num->uid);
  }

  switch (obj->type) {
    case t_array: {
      array_destruct(obj->ary);
      break;
    }

    case t_func: {
      safefree(obj->fnc->code);
      safefree(obj->fnc->name);
      break;
    }

    case t_realchar:
    case t_string: {
      string_destruct(obj->str);
      break;
    }

    default: {}
  }


  safefree( object_getval(obj) );
  safefree(obj);
}

char* objtype_repr (const objtype_t t) {
  pfn();

  static const char* const obj_strings [] = {
    "F_t",
    "number_t",
    "fixwid_t",
    "string_t",
    "point_t",
    "shape_t",
    "func_t",
    "array_t",
    "hash_t",
    "pair_t",
    "char* (string_t.data)",
  };

  _Static_assert(
    ( (sizeof obj_strings) / (sizeof (char *)) == NUM_OBJTYPES),
    "repr has too few or too many values"
  );

  const char* const this = obj_strings[t];
  char* out = safemalloc(safestrnlen(this) + 1);
  snprintf(out, 20, "%s", this);
  return out;
}

char* object_repr (const object_t* const obj) {
  pfn();

  char* buf;
  switch (obj->type) {
    case NUM_OBJTYPES: {
      buf = NULL;
      object_error(NOT_A_TYPE, "object_repr", true);
      break;
    }
    case t_F: {
      buf = safemalloc(2);
      snprintf(buf, 1, "%s", "f");
      break;
    }
    case t_number: {
      buf = number_see(obj->num);
      break;
    }

    case t_fixwid: {
      buf = fixwid_see(obj->fwi);
      break;
    }

    case t_realchar: // fallthrough
    case t_string: {
      size_t buflen = sizeof (char) * obj->str->len;
      buf = safemalloc(buflen);
      snprintf(buf, buflen, "%s", obj->str->data);
      break;
    }

    case t_point: {
      buf = point_see(obj->pt);
      break;
    }
    case t_shape: {
      buf = shape_see(obj->sp, false);
      break;
    }
    case t_func: {
      char *code = obj->fnc->code,
           *name = obj->fnc->name;
      size_t len = safestrnlen(code) + safestrnlen(name) + 2;
      buf = safemalloc(sizeof (char) * len);
      snprintf(buf, len, "%s:%s", code, name);
      break;
    }
    case t_array: {
      buf = array_see(obj->ary);
      break;
    }
    case t_hash: {
      buf = hash_see(obj->hsh);
    }
    case t_pair: {
      buf = pair_see(obj->cel);
    }
  }

  return buf;
}

// value equality
bool object_equals (const object_t* const a, const object_t* const b) {
  pfn();

  // can only compare these objects of different types
  if (a->type != b->type) {
    if (
      ( a->type == t_realchar || a->type == t_string )
      && ( b->type == t_realchar || b->type == t_string )
    ) {
      return strcmp(a->str->data, b->str->data) == 0;
    }
    return false;
  }

  // False always compares equal
  if ( a->type == t_F && b->type == t_F ) {
    return true;
  }

  switch (a->type) {
    case NUM_OBJTYPES: {
      object_error(NOT_A_TYPE, "object_equals", false);
      return false;
    }

    case t_fixwid: return fixwid_equals(a->fwi, b->fwi);
    case t_number: return a->num == b->num;
    case t_point:  return point_equals(a->pt, b->pt);
    case t_shape:  return shape_equals(a->sp, b->sp);
    case t_hash:   return hash_equals(a->hsh, b->hsh);
    case t_array:  return array_equals(a->ary, b->ary);
    case t_pair:   return pair_equals(a->cel, b->cel);

    case t_func: {
      bool same;
      char *fa = object_repr(a),
           *fb = object_repr(b);
      same = strcmp(fa, fb) == 0;
      safefree(fa), safefree(fa);
      return same;
    }

    case t_string:
    case t_realchar:
    case t_F: {
      // satisfy the compiler
    }
  }

  return false;
}

bool object_id_equals (const object_t* const a, const object_t* const b) {
  pfn();

  return (a->type == b->type) && (a->uid == b->uid);
}

#endif
