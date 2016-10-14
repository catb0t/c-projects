#ifdef GCC
#line 2 "object"
#endif

#ifdef STACK
#include "../../common.h"
typedef long double number_t;
#else

#include "array.h"
#include "fixwid.h"
#include "hash.h"
#include "number.h"
#include "pair.h"
#include "string.h"

/*
  nothing_new returns a new "nothing" object
  it is the only value which represents a boolean false
  in a rather lispy / functional-inspired way.
*/
object_t* nothing_new (void) {
  pfn();

  object_t* False = object_new(t_F, NULL);
  report_ctor(False);
  return False;
}

/*
  object_new returns a new object with the given objtype_t from the val argument
  which must be either a heap allocated object type structure pointer
  or a char* or ssize_t* pointer, if valtype is t_realchar or t_realint

  if valtype is t_F or val is NULL, a new false singleton will be returned.
*/
object_t* object_new (const objtype_t valtype, const void* const val) {
  pfn();

  object_t* obj = safemalloc(sizeof (object_t));
  obj->type     = valtype;

  if ( NULL == val ) {
    obj->type = t_F;
  }

  switch (obj->type) {
    case NUM_OBJTYPES: {
      object_error(NOT_A_TYPE, __func__, true);
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
      obj->fwi = fixwid_copy( (const fixwid_t* const) val);
      break;
    }
    case t_fixwid: {
      // i'm an awful person
      obj->fwi = fixwid_new( *(const ssize_t* const) val);
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

/*
  returns a new object constructed with the same values and type as the argument.
  this is a value-only copy, that is, obj->uid will not be copied; moreover
  because it calls the constructor explicitly rather than say, memcpy, there is no
  reason it will have all the same bytes.
*/
object_t* object_copy (const object_t* const obj) {
  pfn();

  if (NULL == obj) {
    return object_new(t_F, NULL);
  }

  return object_new(obj->type, object_getval(obj));
}

/*
  object_getval returns a reference to a heap-allocated object's "active" value
  this reads obj->type to determine which slot of the anonymous union to read
*/
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
    (void **) (obj->fwi),
    (void **) (obj->str) // t_realchar returns str's realchar
  };

  _Static_assert(
    ( (sizeof types) / (sizeof (char *)) == NUM_OBJTYPES),
    "getval types[] has too few or too many values"
  );

  return types[obj->type];
}

/*
  destructs an object by calling its type's specific destructor and then freeing the
  object itself.

  mutates obj, such that it may be NULL or in an invalid state after a call.
*/
void object_destruct (object_t* const obj) {
  pfn();

  report_dtor(obj);

  switch (obj->type) {
    case t_array: {
      array_destruct(obj->ary);
      safefree(obj);
      break;
    }

    case t_func: {
      safefree(obj->fnc->code);
      safefree(obj->fnc->name);
      safefree(obj->fnc);
      break;
    }

    case t_realchar:
    case t_string: {
      string_destruct(obj->str);
      break;
    }

    case t_hash: {
      hash_destruct(obj->hsh);
      break;
    }

    case t_pair: {
      pair_destruct(obj->cel);
      break;
    }

    case t_fixwid: {
      fixwid_destruct(obj->fwi);
      break;
    }

    default: {
      safefree( object_getval(obj) );
    }
  }

  safefree(obj);
}

/*
  convenience version of object_destruct which destructs an argc number of object argument objects by reference
  rather than calling object_destruct twice or more times for objects in the same
  scope, just call this.
*/
void object_dtor_args (size_t argc, ...) {
  va_list vl;
  va_start(vl, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully this just takes the address
    object_t** v = alloca( sizeof (object_t) );
    *v = va_arg(vl, object_t*);

    // 0 allocs, 1 free
    object_destruct( *v );

  }

  va_end(vl);
}

/*
  return an object's typename as a string
*/
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
    "ssize_t (fixwid_t.value)",
    "char* (string_t.data)",
  };

  _Static_assert(
    ( (sizeof obj_strings) / (sizeof (char *)) == NUM_OBJTYPES),
    "repr has too few or too many values"
  );

  const char* const this = obj_strings[t];
  const size_t       len = safestrnlen(this) + 1;

  char* out = safemalloc(sizeof (char) * len);
  snprintf(out, len, "%s", this);

  return out;
}

/*
  return a string representation of an object's data
  for most types, this calls their typename_see function
*/
char* object_repr (const object_t* const obj) {
  pfn();

  char* buf;
  switch (obj->type) {
    case NUM_OBJTYPES: {
      buf = NULL;
      // you can't repr that, you can't fix stupid
      object_error(NOT_A_TYPE, __func__, true);
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

    case t_realint: // fallthrough
    case t_fixwid: {
      buf = fixwid_see(obj->fwi);
      break;
    }

    case t_realchar: // fallthrough
    case t_string: {
      size_t buflen = sizeof (char) * (obj->str->len + 3);
      buf = safemalloc(buflen);
      snprintf(buf, buflen, "\"%s\"", obj->str->data);
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
      safefree(code), safefree(name);
      break;
    }
    case t_array: {
      buf = array_see(obj->ary);
      break;
    }
    case t_hash: {
      buf = hash_see(obj->hsh);
      break;
    }
    case t_pair: {
      buf = pair_see(obj->cel);
      break;
    }
  }

  return buf;
}

/*
  object_equals tests if two objects, possibly of disparate type, are equal by value
  for types other than t_realint, t_realchar, t_fixwid and t_string, typename_equals
  (or, for arithmetic types, typename_eq) is called

  if the arguments are of disparate type, then they will compare false, except
  t_realint with t_fixwid and t_realchar with t_string, in which case obj->type is obviously lying about its actual type (or someone compiled without warnings and
  violated strict aliasing / alignment rules)
*/
bool object_equals (const object_t* const a, const object_t* const b) {
  pfn();

  // can only compare these specific disparate types
  if (a->type != b->type) {
    if (
      ( a->type == t_realchar || a->type == t_string )
      && ( b->type == t_realchar || b->type == t_string )
    ) {
      return strcmp(a->str->data, b->str->data) == 0;

    } else if (
      ( a->type == t_realint || a->type == t_fixwid )
      && ( b->type == t_realint || b->type == t_fixwid )
    ) {
      return a->fwi->value == b->fwi->value;

    } else {
      return false;

    }

  }

  // False always compares equal
  if ( a->type == t_F && b->type == t_F ) {
    return true;
  }

  object_t *oa = object_copy(a),
           *ob = object_copy(b);

  bool same;

  switch (a->type) {
    case NUM_OBJTYPES: {
      object_error(NOT_A_TYPE, __func__, true);
      return false;
    }

    case t_fixwid:  same =     fixwid_eq(oa->fwi, ob->fwi); break;
    case t_number:  same =     number_eq(a->num, b->num);   break;
    case t_point:   same =  point_equals(a->pt, b->pt);     break;
    case t_shape:   same =  shape_equals(a->sp, b->sp);     break;
    case t_hash:    same =   hash_equals(a->hsh, b->hsh);   break;
    case t_array:   same =  array_equals(a->ary, b->ary);   break;
    case t_pair:    same =   pair_equals(a->cel, b->cel);   break;

    case t_func: {
      char *fa = object_repr(a),
           *fb = object_repr(b);
      same = strcmp(fa, fb) == 0;
      safefree(fa), safefree(fa);
      break;
    }

    case t_realint:
    case t_string:
    case t_realchar: // already cmpd
    case t_F: {
      // satisfy the compiler
      same = true;
    }
  }

  object_dtor_args(2, oa, ob);

  return same;
}

/*
  object_id_equals returns whether the arguments alias the same heap-allocated object
  it's very easy to trick this function because it relies on only that the objects
  share a type (and therefore a constructor) and that their uid slots are the same.

  if there is no funny business, then if they share a constructor and have the same
  ID, they must refer to the same object, or be exact ("deep") copies of the same
  object.
*/
bool object_id_equals (const object_t* const a, const object_t* const b) {
  pfn();

  return (a->type == b->type) && (a->uid == b->uid);
}

#endif
