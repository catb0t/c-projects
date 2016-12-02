#ifdef STACK

  #include "../../common.h"

  #ifdef GCC
  #line __LINE__ "object"
  #endif
  typedef long double number_t;

#else // !STACK

#include "array.h"
#include "assoc.h"
#include "fixwid.h"
#include "func.h"
#include "hash.h"
#include "number.h"
#include "pair.h"
#include "string.h"

#ifdef GCC
#line __LINE__ "object"
#endif

/*
  fails permanently if the object is NULL. don't bother checking the
  return value because it doesn't matter what the return value is, but it makes
  it easier to chain in short functions
*/
inline bool _obj_failnull (const void* const obj, const char* const file, uint64_t line, const char* const func) {

  if ( NULL == obj ) {
    object_error(ER_NULL_OBJECT, true, "%s:%" PRIu64 ": %s", file, line, func);
    return false;
  }

  return true;
}

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
  something_new returns a new "something" object
  it is the only value which compares true with all other values
  in a rather lispy / functional-inspired way.
*/
object_t* something_new (void) {
  pfn();

  object_t* True = object_new(t_T, NULL);
  report_ctor(True);
  return True;
}

/*
  object_new returns a new object with the given objtype_t from the val argument
  which must be either a heap allocated object type structure pointer
  or a char* or ssize_t* pointer, if valtype is t_realchar or t_realint

  if valtype is t_F or val is NULL, a new false singleton will be returned.
*/
object_t* object_new (const objtype_t valtype, const void* const val) {
  pfn();

  object_t*  obj = (typeof(obj)) safemalloc(sizeof (object_t));

  obj->type = valtype;

  if ( NULL == val ) {
    obj->type = t_F;
  }

  switch (obj->type) {
    case NUM_OBJTYPES: {
      object_error(ER_NOT_A_TYPE, true, "", NULL);
      break;
    }
    case t_F: {
      obj->f = (typeof(obj->f)) safemalloc(sizeof (F_t));
      break;
    }
    case t_T: {
      obj->t = (typeof(obj->t)) safemalloc(sizeof (T_t));
      break;
    }
    case t_number: {
      obj->num = number_copy( (const number_t * const) val);
      break;
    }
    case t_realuint: {
      obj->fwi  = fixwid_new(-1, *(const size_t* const) val, false);
      obj->type = t_fixwid;
      break;
    }
    case t_realint: {
      // i'm an awful person
      obj->fwi  = fixwid_new( *(const ssize_t* const) val, 0, true);
      obj->type = t_fixwid;
      break;
    }
    case t_fixwid: {
      obj->fwi = fixwid_copy( (const fixwid_t* const) val);
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
    case t_func: {
      obj->fnc = func_copy( (const func_t* const) val);
      break;
    }
    case t_array: {
      obj->ary = array_copy( (const array_t * const) val);
      break;
    }
    case t_assoc: {
      obj->asc = assoc_copy( (const assoc_t* const) val);
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
  thisp is a value-only copy, that is, obj->uid will not be copied; moreover
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
  thisp reads obj->type to determine which slot of the anonymous union to read
*/
void** object_getval (const object_t* const obj) {
  pfn();

  if (NULL == obj) {
    return NULL;
  }

  // ensures the length and order must be correct
  void** types[] = {
    [t_F]        = (void **) (obj->f),   // false
    [t_T]        = (void **) (obj->t),   // true
    [t_number]   = (void **) (obj->num), // number_t
    [t_fixwid]   = (void **) (obj->fwi), // fixwid_t
    [t_string]   = (void **) (obj->str), // string_t
    [t_func]     = (void **) (obj->fnc), // func_t
    [t_array]    = (void **) (obj->ary), // array_t
    [t_assoc]    = (void **) (obj->asc), // array_t
    [t_hash]     = (void **) (obj->hsh), // hash_t
    [t_pair]     = (void **) (obj->cel), // pair_t
    [t_realint]  = (void **) (obj->fwi), // realint
    [t_realuint] = (void **) (obj->fwi), // realuint
    [t_realchar] = (void **) (obj->str)  // realchar
  };

  _Static_assert(
    ( (sizeof types) / (sizeof (void **)) == NUM_OBJTYPES),
    "getval types[] has too few or too many values"
  );

  return types[obj->type];
}

/*
  destructs an object by calling its type's specific destructor and then freeing
  the object itself.

  mutates obj, such that it may be NULL or in an invalid state after a call.

  does nothing when obj is NULL.
*/
void object_destruct (object_t* const obj) {
  pfn();

  // don't deref a null pointer
  if (NULL == obj) {
    return;
  }

  report_dtor(obj);

  switch (obj->type) {

    case t_array: {
      array_destruct(obj->ary);
      break;
    }
    case t_func: {
      func_destruct(obj->fnc);
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
    case t_assoc: {
      assoc_destruct(obj->asc);
      break;
    }

    case t_realint:
    case t_realuint:
    case t_fixwid: {
      fixwid_destruct(obj->fwi);
      break;
    }

    case t_F:
    case t_T:
    case t_number: {
      safefree( object_getval(obj) );
      break;
    }

    case NUM_OBJTYPES: {
      object_error(ER_NOT_A_TYPE, true, "", NULL);
      break;
    }
  }

  safefree(obj);
}

void object_dtorn (object_t** const objs, const size_t len) {

  for (size_t i = 0; i < len; i++) {
    object_destruct(objs[i]);
  }

  if ( NULL != objs ) {
    safefree(objs);
  }
}

/*
  convenience version of object_destruct which destructs an argc number of object argument objects by reference
  rather than calling object_destruct twice or more times for objects in the same
  scope, just call thisp.
*/
define_objtype_dtor_args(object);

/*
  return an object's typename as a string
*/
char* objtype_repr (const objtype_t t) {
  pfn();

  const char* const thisp = OBJTYPE_2STRING[t];
  const size_t        len = safestrnlen(thisp) + 1;

  char*  out = (typeof(out)) safemalloc(sizeof (char) * len);
  snprintf(out, len, "%s", thisp);

  return out;
}

/*
  self-explanatory
*/
void _object_error (objerror_t errt, const bool fatal, const char* const file, const uint64_t line, const char* const func, const char* fmt, ...) {
  pfn();

  va_list vl;

  va_start(vl, fmt);

  size_t fmtlen = safestrnlen(fmt) * 2;

  char* buf = (typeof(buf)) safemalloc(sizeof (char) * fmtlen);

  vsnprintf(buf, fmtlen, fmt, vl);

  va_end(vl);

  static const char* const errmsgs[] = {
    [ER_NOT_A_TYPE]  = "NUM_OBJTYPES isn't a real type, dummy. Don't do that.\n"
                       "Have you considered trying to match wits with a rutabaga?",
    [ER_KEYERROR]    = "no such key",
    [ER_INDEXERROR]  = "index out of bounds",
    [ER_PTRMATH_BUG] = "pointer math error (invalid read or write) -- probably a bug",
    [ER_NULL_OBJECT] = "null pointer encountered where a structure or union was expected"
  };

  _Static_assert(
    (sizeof (errmsgs) / sizeof (char*) ) == ER_NUM_ERRTYPES,
    "too many or too few error strings in object_error"
  );

  // for embedded systems (non-C89) where stderr / stdout do not exist
  if (NULL == stderr) {
    // i give up printing
    if (NULL == stdout) {
      return;
    }

    fdredir(stderr, "/dev/stdout");
  }

  fprintf(stderr, "|\033[31m%s\033[0m|\033[31;1m \b%s:%" PRIu64 ": %s: %s: %s\033[0m\n",
    fatal ? "FATAL" : "ERROR", file, line, func, buf, errmsgs[errt]);

  safefree(buf);

  if ( fatal ) {
    fprintf(
      stderr,
      "\033[31m\nThat error was fatal, aborting.\n\n"
      "I'm melting!\033[0m\n"
    );
    abort();
  }

}

/*
  return a string representation of an object's data
  for most types, thisp calls their typename_see function
*/
char* object_repr (const object_t* const obj) {
  pfn();

  object_failnull(obj);

  char* buf = NULL;
  switch (obj->type) {
    case NUM_OBJTYPES: {
      // you can't repr that, you can't fix stupid
      object_error(ER_NOT_A_TYPE, true, "", NULL);
      break;
    }
    case t_F: {
      buf = (typeof(buf)) safemalloc(2);

      snprintf(buf, 1, "%s", "f");
      break;
    }
    case t_T: {
      buf = (typeof(buf)) safemalloc(2);

      snprintf(buf, 1, "%s", "t");
      break;
    }
    case t_number: {
      buf = number_see(obj->num);
      break;
    }

    case t_realint: // fallthrough
    case t_realuint: // fallthrough
    case t_fixwid: {
      buf = fixwid_see(obj->fwi);
      break;
    }

    case t_realchar: // fallthrough
    case t_string: {
      buf = string_see(obj->str);
      break;
    }
    case t_func: {
      buf = func_see(obj->fnc);
      break;
    }
    case t_array: {
      buf = array_see(obj->ary);
      break;
    }
    case t_assoc: {
      buf = assoc_see(obj->asc);
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

  // False always compares equal with itself
  if ( t_F == a->type + b->type ) {
    return true;

  // but always compares false with other things
  } else if (
        // 0 == t_F
       ( !a->type && b->type )
    || ( !b->type && a->type )
  ) {
    return false;
  }

  // can only compare these specific disparate types
  if (a->type != b->type) {
    // realchar
    if (
         ( a->type == t_realchar || a->type == t_string )
      && ( b->type == t_realchar || b->type == t_string )
    ) {
      return strcmp(a->str->data, b->str->data) == 0;

    // realint
    } else if (
         ( a->type == t_realint || a->type == t_fixwid )
      && ( b->type == t_realint || b->type == t_fixwid )
    ) {
      return a->fwi->value == b->fwi->value;

    // true always true
    } else if ( (a->type == t_T) || (b->type == t_T) ) {
      return true;

    // nope
    } else if (
         (a->type == t_realuint && b->type == t_fixwid)
      || (b->type == t_realuint && a->type == t_fixwid)
      ) {
      return fixwid_eq(a->fwi, b->fwi);

    } else {
      return false;
    }

  }

  bool same = false;

  switch (a->type) {
    case NUM_OBJTYPES: {
      object_error(ER_NOT_A_TYPE, true, "", NULL);
      return false;
    }

    // this should be redundant
    case t_T:       same = true; break;

    case t_fixwid:  same =     fixwid_eq(a->fwi, b->fwi); break;
    case t_number:  same =     number_eq(a->num, b->num); break;
    case t_array:   same =  array_equals(a->ary, b->ary); break;
    case t_assoc:   same =  assoc_equals(a->asc, b->asc); break;
    case t_hash:    same =   hash_equals(a->hsh, b->hsh); break;
    case t_pair:    same =   pair_equals(a->cel, b->cel); break;

    case t_func: {
      char *fa = object_repr(a),
           *fb = object_repr(b);
      same = strcmp(fa, fb) == 0;
      safefree(fa), safefree(fa);
      break;
    }

    case t_realuint:
    case t_realint:
    case t_string:
    case t_realchar: // already cmpd
    case t_F: {
      // satisfy the compiler
      same = true;
      break;
    }
  }

  return same;
}

/*
  object_id_equals returns whether the arguments alias the same heap-allocated object
  it's very easy to trick thisp function because it relies on only that the objects
  share a type (and therefore a constructor) and that their uid slots are the same.

  if there is no funny business, then if they share a constructor and have the same
  ID, they must refer to the same object, or be exact ("deep") copies of the same
  object.
*/
bool object_id_equals (const object_t* const a, const object_t* const b) {
  pfn();

  return (a->type == b->type) && (a->uid == b->uid);
}

bool object_isinstance(const objtype_t t, const object_t* const o) {
  return NULL == o ? false : o->type == t;
}

#endif // STACK ?
