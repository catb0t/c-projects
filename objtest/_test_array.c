#include <criterion/criterion.h>

//#define NODEBUG
#include "testcommon.h"

Test(empty, emptyfromNULL) {
  a = array_new(NULL, 0); // 1

  s = array_see(a); // 2
  dbg_prn("empty array looks like: %s\n", s);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1 ~2
}

Test(empty, isempty) {

  a = array_new(NULL, 0); // 1
  cr_assert(array_isempty(a));
  cr_assert(array_length(a) == 0);

  array_destruct(a); // ~1
}

Test(empty, append) {
  a = array_new(NULL, 0); // 1

  oa = object_new(t_realchar, (const void* const ) "const void* const val"); // 2

  array_append(a, oa);

  s = array_see(a); // 3
  dbg_prn("1array: %s\n", s);
  cr_assert_str_eq(s, "{ \"const void* const val\" }");
  cr_assert(! array_isempty(a));
  cr_assert(array_length(a) == 1);

  safefree(s), array_destruct(a), object_destruct(oa); // ~1, ~2, ~3
}

Test(empty, insert) {
  a = array_new(NULL, 0);

  oa = object_new(t_realint, (const void * const) anums);
  ok = array_insert(a, oa, 0);
  cr_assert(ok);
  s = array_see(a);
  printf("s is %s\n", s);
  cr_assert_str_eq(s, "{ 1 }");

  object_destruct(oa), array_destruct(a), safefree(s);
}

Test(empty, deletefails) {
  a = array_new(NULL, 0); // 1

  ok = array_delete(a, 0);
  cr_assert(! ok);
  s = array_see(a);
  cr_assert_str_eq(s, "{ }");

  safefree(s);
  array_destruct(a); // ~1
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

Test(empty, concat) {
  a = array_new(NULL, 0), b = array_copy(a); // 1, 2

  ra = array_concat(a, b); // 3

  s = array_see(ra); // 4
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct_args(3, a, b, ra); // ~1, ~2, ~3, ~4
}

Test(empty, equals) {
  a = array_new(NULL, 0), b = array_copy(a);

  ok = array_equals(a, b);

  cr_assert( ok );

  array_destruct_args(2, a, b);
}

Test(empty, getref) {
  a = array_new(NULL, 0);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t** obj_ra = array_get_ref(a, __LOOPCOUNT, &ok);

    cr_assert( ! ok );
    cr_assert( NULL == obj_ra );
    (void) obj_ra;
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
}

Test(empty, getcopy) {
  a = array_new(NULL, 0);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t* obj_a = array_get_copy(a, __LOOPCOUNT, &ok);

    cr_assert( ! ok );
    cr_assert( object_isinstance(t_F, obj_a) );
    object_destruct(obj_a);
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu copies from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
}

// NONEMPTY

Test(nonempty, boa) {

  size_t objslen = 2;

  object_t** objs = (typeof(objs)) safemalloc( sizeof (object_t*) * objslen );

  ssize_t i = -6, j = 9;

  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, objslen);
  object_dtorn(objs, 2);

  s = array_see(a);
  dbg_prn("fromboaptr is %s\n", s);
  cr_assert_str_eq(s, "{ -6 9 }");

  safefree(s), array_destruct(a);
}

Test(nonempty, fromcptrptr) {

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


Test(nonempty, fromcliteralssize) {

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  s = array_see(ra);
  dbg_prn("array from literal is: %s\n", s);
  cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 }");
  safefree(s), array_destruct(ra);
}

Test(nonempty, copy) {

  a = array_new_fromcptr(
    (const void* const * const) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  b = array_copy(a);

  s = array_see(a);
  s2 = array_see(b);
  dbg_prn("fromptrptr is: %s\nand: %s\n", s, s2);
  cr_assert_str_eq(s, s2);

  cr_assert_neq(a->uid, b->uid);

  array_destruct_args(2, a, b);
  safefree_args(2, s, s2);
}

Test(nonempty, delete) {

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  ok = array_delete(a, 3);
  cr_assert(ok);
  ok = array_delete(a, signed2un(a->idx));
  cr_assert(ok);
  ok = array_delete(a, 0);
  cr_assert(ok);

  s = array_see(a);
  dbg_prn("delete2: %s\n", s);
  cr_assert_str_eq(s, "{ -3 5 9 }");

  safefree(s), array_destruct(a);
}

Test(nonempty, clear) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  array_clear(a);
  s = array_see(a);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
}

Test(nonempty, insert) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  size_t g = 99999;
  object_t* go = object_new(t_realuint, &g);
  ok = array_insert(a, go, 0);
  s = array_see(a);

  cr_assert_str_eq(s, "{ 99999 1 -3 5 -7 9 -11 }");
  cr_assert(ok);

  safefree(s);

  ok = array_insert(a, go, 99);
  s = array_see(a);

  cr_assert_str_eq(s, "{ 99999 1 -3 5 -7 9 -11 }");
  cr_assert(! ok);

  safefree(s),
  array_destruct(a), object_destruct(go);
}

Test(nonempty, concat) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  ra = array_concat(a, b);

  s = array_see(ra);
  dbg_prn("concat is: %s", s);
  cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");

  safefree(s), array_destruct_args(3, a, b, ra);
}

Test(nonempty, equals) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_copy(a);

  ok = array_equals(a, b);

  cr_assert( ok );

  array_destruct(b);

  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  ok = array_equals(a, b);

  cr_assert( ! ok );

  array_destruct_args(2, a, b);
}

Test(nonempty, getref) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t** obj_ra = array_get_ref(a, __LOOPCOUNT, &ok);

    if ( array_isinbounds(a, __LOOPCOUNT) ) {
      cr_assert( ok );
      cr_assert( NULL != obj_ra );

    } else {
      cr_assert( ! ok );
      cr_assert( NULL == obj_ra );
    }

    (void) obj_ra;
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu refs from nonempty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
}

Test(nonempty, getcopy) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t* obj_a = array_get_copy(a, __LOOPCOUNT, &ok);

    if ( array_isinbounds(a, __LOOPCOUNT) ) {
      cr_assert( ok );
      cr_assert( ! object_isinstance(t_F, obj_a) );

    } else {
      cr_assert( ! ok );
      cr_assert( object_isinstance(t_F, obj_a) );
    }

    object_destruct(obj_a);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu copies from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
}
