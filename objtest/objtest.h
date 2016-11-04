#include "../calc/object/object.h"

void test (void);

void test (void) {

  array_t* a = array_new(NULL, -1);

  char* s = array_see(a);
  dbg_prn("empty array looks like: %s\n", s);

  safefree(s), array_destruct(a);

  object_t** objs = safemalloc( sizeof (object_t*) );
  ssize_t i = -6;
  objs[0] = object_new(t_realint, &i);

  a = array_new( (const object_t* const * const) objs, 1);
  object_dtorn(objs, 1);

  s = array_see(a);
  dbg_prn("fromboactr is %s\n", s);

  safefree(s), array_destruct(a);

  static const char* const literal[] = {
    "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz"
  };

  a = array_new_fromcptr(
    (const void* const * const ) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  s = array_see(a);
  dbg_prn("fromptrptr is: %s\n", s);

  safefree(s), array_destruct(a);

}
