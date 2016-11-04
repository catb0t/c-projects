#include <criterion/criterion.h>

//#define NODEBUG
#include "../calc/object/object.h"

array_t *a, *ra, *rb;

char* s;

Test(empty, emptyfromNULL) {
  a = array_new(NULL, -1);

  s = array_see(a);
  dbg_prn("empty array looks like: %s\n", s);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
}

Test(nonempty, fromboa) {
  object_t** objs = safemalloc( sizeof (object_t*) );
  ssize_t i = -6;
  objs[0] = object_new(t_realint, &i);

  a = array_new( (const object_t* const * const) objs, 1);
  object_dtorn(objs, 1);

  s = array_see(a);
  dbg_prn("fromboactr is %s\n", s);
  cr_assert_str_eq(s, "{ -6 }");

  safefree(s), array_destruct(a);
}

Test(nonempty, fromcptrptr) {
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
  cr_assert_str_eq(s, "{ \"abc\" \"def\" \"ghi\" \"jkl\" \"mno\" \"pqr\" \"stu\" \"vwx\" \"yz\" }");
  safefree(s), array_destruct(a);
}

define_array_new_fromctype(size_t);

Test(nonempty, fromcliteral) {
  static const size_t a[] = {
    1, 3, 5, 7, 9, 11
  };

  ra = array_new_from_size_t_lit(a, 6, t_realuint);

  s = array_see(ra);
  dbg_prn("array from literal is: %s\n", s);
  cr_assert_str_eq(s, "{ 1 3 5 7 9 11 }");
  safefree(s), array_destruct(ra);
}


/*Test(nonempty, concat) {

  static const size_t a[] = {
    1, 3, 5, 7, 9, 11
  };

  static const size_t b[] = {
    2, 4, 6, 8, 10, 12
  };

  _Static_assert(
    (sizeof a / sizeof (size_t)) == (sizeof b / sizeof (size_t)),
    "literal arrays should have same lengths"
  );

  ra = array_new_from_size_t_lit(a, sizeof a, t_realuint),
  rb = array_new_from_size_t_lit(b, sizeof a, t_realuint);

  array_concat(&ra, rb);

  s = array_see(ra);
  dbg_prn("concat is: %s\n", s);
  cr_assert_str_eq(s, "{ 1 3 5 7 9 11 2 4 6 8 10 12 }");
  safefree(s), array_destruct(ra);
}
*/