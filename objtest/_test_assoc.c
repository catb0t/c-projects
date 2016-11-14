#include <criterion/criterion.h>

//#define NODEBUG
#include "testcommon.h"

Test(empty, boa) {
  c = assoc_new(NULL, NULL);

  s = assoc_see(c);
  dbg_prn("empty: %s\n", s);
  cr_assert_str_eq(s, "a{ }");

  safefree(s), assoc_destruct(c);
}

Test(empty, append) {
  c = assoc_new(NULL, NULL);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);
  cr_assert_str_eq("{ }", s);
  cr_assert_str_eq("{ }", s2);

  safefree(s), safefree(s2), array_destruct_args(2, a, b),
  assoc_destruct(c);
}

Test(nonempty, boa) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  s = assoc_see(c);

  dbg_prn("boa ab: %s", s);

  cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), array_destruct_args(2, a, b),
  assoc_destruct(c);
}
