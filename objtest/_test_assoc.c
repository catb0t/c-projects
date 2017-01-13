#include <criterion/criterion.h>

//#define NODEBUG
#include "testcommon.h"

Test(empty, emptyfromNULL) {
  c = assoc_new(NULL, NULL);

  s = assoc_see(c);
  dbg_prn("empty: %s\n", s);
  cr_assert_str_eq(s, "a{ }");

  safefree(s), assoc_destruct(c);
}

Test(empty, isempty) {
  c = assoc_new(NULL, NULL); // 1
  cr_assert(assoc_isempty(c));
  cr_assert(assoc_length(c) == 0);

  assoc_destruct(c); // ~1
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

Test(empty, insert) {
  c = assoc_new(NULL, NULL);

  oa = object_new(t_realchar, (const void* const ) "const void* const val"),
  ob = object_new(t_realuint, (const void* const ) (anums + 2));

  p = pair_new(oa, ob);

  ok = assoc_insert(c, p, 7);

  pair_destruct(p);

  object_destruct_args(2, oa, ob);

  assoc_destruct(c);
}

Test(empty, unzip) {
  a = array_new(NULL, 0),
  b = array_copy(a);

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

Test(empty, deletefails) {
  c = assoc_new(NULL, NULL); // 1

  ok = assoc_delete(c, 0);
  cr_assert(! ok);

  assoc_destruct(c); // ~1
}

Test(empty, concat) {
  c = assoc_new(NULL, NULL), d = assoc_copy(c);

  rc = assoc_concat(c, d);

  s = assoc_see(rc);
  cr_assert_str_eq(s, "a{ }");
  safefree(s);

  assoc_destruct_args(3, rc, c, d);
}

Test(empty, equals) {
  c = assoc_new(NULL, NULL), d = assoc_copy(c);

  ok = assoc_equals(c, d);

  cr_assert( ok );

  assoc_destruct_args(2, c, d);
}

Test(empty, clear) {
  a = array_new(NULL, 0); // 1

  s = array_see(a); // 2
  cr_assert_str_eq(s, "{ }");
  safefree(s); // ~2

  array_clear(a);

  s = array_see(a); // 3
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1, ~3
}


Test(empty, getref) {
  c = assoc_new(NULL, NULL);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t** p_refa = assoc_get_ref(c, __LOOPCOUNT, &ok);

    cr_assert( ! ok );
    cr_assert( NULL == p_refa );
    (void) p_refa;
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);
}

Test(empty, getcopy) {
  c = assoc_new(NULL, NULL);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t *p_copy     = assoc_get_copy(c, __LOOPCOUNT, &ok),
           *empty_pair = pair_new(NULL, NULL);

    cr_assert( ! ok );
    cr_assert( pair_equals(p_copy, empty_pair) );
    (void) p_copy, (void) empty_pair;
    pair_destruct_args(2, p_copy, empty_pair);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

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

Test(nonempty, fromcptrptr) {

  c = assoc_new_fromcptr(
    (const void* const * const) (const char* const * const) literal,
    (const void* const * const) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar, t_realchar
  );

  s = assoc_see(c);
  cr_assert_str_eq(s, "a{ { \"abc\" . \"abc\" } { \"def\" . \"def\" } { \"ghi\" . \"ghi\" } { \"jkl\" . \"jkl\" } { \"mno\" . \"mno\" } { \"pqr\" . \"pqr\" } { \"stu\" . \"stu\" } { \"vwx\" . \"vwx\" } { \"yz\" . \"yz\" } }");
  safefree(s), assoc_destruct(c);
}

Test(nonempty, fromcliteralssize) {

  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  s = assoc_see(c);
  dbg_prn("fromptr is %s\n", s);

  cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), assoc_destruct(c);
}

Test(nonempty, copy) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  d = assoc_copy(c);
  s = assoc_see(c), s2 = assoc_see(d);
  cr_assert_str_eq(s, s2);

  cr_assert_neq(c->uid, d->uid);
  assoc_destruct_args(2, c, d);
  safefree_args(2, s, s2);
}

Test(nonempty, concat) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint),
  d = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  rc = assoc_concat(c, d);

  s = assoc_see(rc);

  cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), assoc_destruct_args(3, rc, d, c);
}

Test(nonempty, delete) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)) - 2, t_realint, t_realint);

  ok = assoc_delete(c, 3);
  cr_assert(ok);
  ok = assoc_delete(c, signed2un(c->idx));
  cr_assert(ok);
  ok = assoc_delete(c, 0);
  cr_assert(ok);

  s = assoc_see(c);
  dbg_prn("delete2: %s\n  ", s);
  cr_assert_str_eq(s, "a{ { -3 . 4 } }");

  safefree(s), assoc_destruct(c);
}

Test(nonempty, clear) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)) - 2, t_realint, t_realint);

  assoc_clear(c);

  cr_assert(assoc_length(c) == 0);

  s = assoc_see(c);
  cr_assert_str_eq(s, "a{ }");

  ok = true;

  p  = assoc_get_copy(c, 2, &ok),
  p1 = pair_new(NULL, NULL);

  cr_assert( ! ok );
  cr_assert( pair_equals(p, p1) );

  safefree(s), assoc_destruct(c);

  pair_destruct_args(2, p, p1);
}

Test(nonempty, append) {
  a = array_new_from_ssize_t_lit(anums, 2, t_realint),
  b = array_new_from_ssize_t_lit(bnums, 2, t_realint);

  c = assoc_new(a, b);

  s = assoc_see(c);

  dbg_prn("before append: %s", s);

  safefree(s);

  oa = object_new(t_realint, &( anums[5] )),
  ob = object_new(t_realint, &( bnums[5] ));

  assoc_append_boa(c, oa, ob);

  s = assoc_see(c);

  dbg_prn("after append: %s", s);

  cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { -11 . 12 } }");

  safefree(s),
  array_destruct_args(2, a, b),
  assoc_destruct(c);

  object_destruct_args(2, oa, ob);
}

Test(nonempty, insert) {

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

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
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

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from nonempty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);
  array_destruct_args(2, a, b);
}

Test(nonempty, getcopy) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t *p_copy     = assoc_get_copy(c, __LOOPCOUNT, &ok),
           *empty_pair = pair_new(NULL, NULL);

    if ( assoc_isinbounds(c, __LOOPCOUNT) ) {
      cr_assert( ok );
      cr_assert( ! pair_equals(p_copy, empty_pair) );
    } else {
      cr_assert( ! ok );
      cr_assert( pair_equals(p_copy, empty_pair) );
    }

    pair_destruct_args(2, p_copy, empty_pair);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);

  array_destruct_args(2, a, b);
}
