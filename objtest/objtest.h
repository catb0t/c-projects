#include "../calc/object/object.h"

void test (void);

define_array_new_fromctype(size_t);

void test (void) {

  array_t *ra, *a = array_new(NULL, -1);

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

  static const size_t nums[] = {
    1, 3, 5, 7, 9, 11
  };

  ra = array_new_from_size_t_lit(nums, 6, t_realuint);

  s = array_see(ra);
  dbg_prn("array from literal is: %s\n", s);

  safefree(s), array_destruct(ra);
}
