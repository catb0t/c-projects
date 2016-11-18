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

  safefree_args(2, s, s2), array_destruct_args(2, a, b),
  assoc_destruct(c);
}

Test(empty, unzip) {
  a = array_new(NULL, -1),
  b = array_new(NULL, -1);

  s3 = array_see(a), s4 = array_see(b);

  c = assoc_new(a, b);

  array_destruct_args(2, a, b);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);

  dbg_prn("empty a: %s, p1: %s, b: %s, p2: %s\n", s, s3, s2, s4);

  cr_assert_str_eq(s3, s);
  cr_assert_str_eq(s4, s2);

  safefree_args(4, s, s2, s3, s4);

  array_destruct_args(2, a, b);

  assoc_destruct(c);
}

Test(empty, getref) {
  c = assoc_new(NULL, NULL);

  freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < 10; __LOOPCOUNT++) {
    pair_t** p_refa = assoc_get_ref(c, __LOOPCOUNT, &ok);

    cr_assert( ! ok );
    cr_assert( NULL == p_refa );
    (void) p_refa;
  }
  clock_stop();

  freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

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

Test(nonempty, append) {
  a = array_new_from_ssize_t_lit(anums, 2, t_realint),
  b = array_new_from_ssize_t_lit(bnums, 2, t_realint);

  c = assoc_new(a, b);

  s = assoc_see(c);

  dbg_prn("before append: %s", s);

  safefree(s);

  oa = object_new(t_realint, anums + 5),
  ob = object_new(t_realint, bnums + 5);

  assoc_append_boa(c, oa, ob);

  s = assoc_see(c);

  dbg_prn("after append: %s", s);

  cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { -11 . 12 } }");

  safefree(s),
  array_destruct_args(2, a, b),
  assoc_destruct(c);

  object_destruct_args(2, oa, ob);
}

Test(nonempty, unzip) {
  a = array_new_from_ssize_t_lit(anums, 2, t_realint),
  b = array_new_from_ssize_t_lit(bnums, 2, t_realint);

  s3 = array_see(a), s4 = array_see(b);

  c = assoc_new(a, b);

  array_destruct_args(2, a, b);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);

  dbg_prn("nonempty a: %s, p1: %s, b: %s, p2: %s\n", s, s3, s2, s4);

  cr_assert_str_eq(s3, s);
  cr_assert_str_eq(s4, s2);

  safefree_args(4, s, s2, s3, s4);

  array_destruct_args(2, a, b);

  assoc_destruct(c);
}

Test(nonempty, getref) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < 10; __LOOPCOUNT++) {
    pair_t** p_refa = assoc_get_ref(c, __LOOPCOUNT, &ok);

    if ( assoc_isinbounds(c, __LOOPCOUNT) ) {
      cr_assert( ok );
      cr_assert( NULL != p_refa );

    } else {
      cr_assert( ! ok );
      cr_assert( NULL == p_refa );
    }

    (void) p_refa;
  }
  clock_stop();

  freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from nonempty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);
  array_destruct_args(2, a, b);
}
