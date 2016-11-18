#include <criterion/criterion.h>

//#define NODEBUG
#include "testcommon.h"

Test(empty, emptyfromNULL) {
  a = array_new(NULL, -1); // 1

  s = array_see(a); // 2
  dbg_prn("empty array looks like: %s\n", s);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1 ~2
}

Test(empty, isempty) {

  a = array_new(NULL, -1); // 1
  cr_assert(array_isempty(a));
  cr_assert(array_length(a) == 0);

  array_destruct(a); // ~1
}

Test(empty, append) {
  a = array_new(NULL, -1); // 1

  oa = object_new(t_realchar, (const void* const ) "const void* const val"); // 2

  array_append(a, oa);

  s = array_see(a); // 3
  dbg_prn("1array: %s\n", s);
  cr_assert_str_eq(s, "{ \"const void* const val\" }");
  cr_assert(! array_isempty(a));
  cr_assert(array_length(a) == 1);

  safefree(s), array_destruct(a), object_destruct(oa); // ~1, ~2, ~3
}

Test(empty, deletefails) {
  a = array_new(NULL, -1); // 1

  ok = array_delete(a, 0);
  cr_assert(! ok);

  array_destruct(a); // ~1
}

Test(empty, clear) {
  a = array_new(NULL, -1); // 1

  s = array_see(a); // 2
  cr_assert_str_eq(s, "{ }");
  safefree(s); // ~2

  array_clear(a);

  s = array_see(a); // 3
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1, ~3
}

Test(empty, concat) {
  a = array_new(NULL, -1), b = array_copy(a); // 1, 2

  array_concat(&a, b);

  s = array_see(a); // 3
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct_args(2, a, b); // ~1, ~2, ~3
}

Test(empty, equals) {
  a = array_new(NULL, -1), b = array_copy(a);

  ok = array_equals(a, b);

  cr_assert( ok );

  array_destruct_args(2, a, b);
}

Test(empty, getref) {
  a = array_new(NULL, -1);

  refa = array_get_ref(a, 0, &ok);

  cr_assert( ! ok );
  cr_assert(NULL == refa);

  refa = array_get_ref(a, 3, &ok);

  cr_assert( ! ok );
  cr_assert( NULL == refa );

  refa = array_get_ref(a, 90, &ok);

  cr_assert( ! ok );
  cr_assert( NULL == refa );

  array_destruct(a);
}

Test(empty, getcopy) {
  a = array_new(NULL, -1);

  oa = array_get_copy(a, 0, &ok);

  cr_assert( ! ok );
  cr_assert( object_isinstance(t_F, oa) );

  object_destruct(oa);

  oa = array_get_copy(a, 3, &ok);

  cr_assert( ! ok );
  cr_assert( object_isinstance(t_F, oa) );

  object_destruct(oa);

  oa = array_get_copy(a, 90, &ok);

  cr_assert( ! ok );
  cr_assert( object_isinstance(t_F, oa) );

  object_destruct(oa);

  array_destruct(a);
}

// NONEMPTY

Test(nonempty, fromboa) {

  size_t objslen = 2;

  object_t** objs = (typeof(objs)) safemalloc( sizeof (object_t*) * objslen );

  ssize_t i = -6, j = 9;

  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, un2signed(objslen));
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

Test(nonempty, concat2ssize) {

  _Static_assert(
    (sizeof anums / sizeof (ssize_t)) == (sizeof bnums / sizeof (ssize_t)),
    "literal arrays should have same lengths"
  );

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  rb = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  array_concat(&ra, rb);

  s = array_see(ra);
  dbg_prn("concat is: %s\n", s);
  cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");
  safefree(s), array_destruct(ra), array_destruct(rb);
}

Test(nonempty, delete) {

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  ok = array_delete(a, 3);
  cr_assert(ok);
  ok = array_delete(a, signed2un(a->idx));
  cr_assert(ok);
  ok = array_delete(a, 0);
  cr_assert(! ok);

  s = array_see(a);
  dbg_prn("delete2: %s\n", s);
  cr_assert_str_eq(s, "{ 1 -3 5 9 }");

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

Test(nonempty, concat2) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  array_concat(&a, b);

  s = array_see(a);
  dbg_prn("concat is: %s", s);
  cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");

  safefree(s), array_destruct_args(2, a, b);
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

  refa = array_get_ref(a, 0, &ok);

  cr_assert( ok );
  cr_assert(NULL != refa);

  refa = array_get_ref(a, 3, &ok);

  cr_assert( ok );
  cr_assert(NULL != refa);

  refa = array_get_ref(a, 90, &ok);

  cr_assert( ! ok );
  cr_assert(NULL == refa);

  array_destruct(a);
}

Test(nonempty, getcopy) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  oa = array_get_copy(a, 0, &ok);

  cr_assert( ok );
  cr_assert( ! object_isinstance(t_F, oa) );

  object_destruct(oa);

  oa = array_get_copy(a, 3, &ok);

  cr_assert( ok );
  cr_assert( ! object_isinstance(t_F, oa) );

  object_destruct(oa);

  oa = array_get_copy(a, 90, &ok);

  cr_assert( ! ok );
  cr_assert( object_isinstance(t_F, oa) );

  object_destruct(oa);

  array_destruct(a);
}
