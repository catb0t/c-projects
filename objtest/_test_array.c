#include <criterion/criterion.h>

//#define NODEBUG
#include "../calc/object/object.h"

Test(empty, emptyfromNULL) {
  array_t* a = array_new(NULL, -1);

  char* s = array_see(a);
  dbg_prn("empty array looks like: %s\n", s);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
}

Test(nonempty, fromboa) {
  object_t** objs = safemalloc( sizeof (object_t*) );
  ssize_t i = -6;
  objs[0] = object_new(t_realint, &i);

  array_t* a = array_new( (const object_t* const * const) objs, 1);
  object_dtorn(objs, 1);

  char* s = array_see(a);
  dbg_prn("fromboactr is %s\n", s);
  cr_assert_str_eq(s, "{ -6 }");

  safefree(s), array_destruct(a);
}

Test(nonempty, fromcptrptr) {
  static const char* const literal[] = {
    "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz"
  };

  array_t* a = array_new_fromcptr(
    (const void* const * const ) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  char* s = array_see(a);
  dbg_prn("fromptrptr is: %s\n", s);
  cr_assert_str_eq(s, "{ \"abc\" \"def\" \"ghi\" \"jkl\" \"mno\" \"pqr\" \"stu\" \"vwx\" \"yz\" }");
  safefree(s), array_destruct(a);
}

