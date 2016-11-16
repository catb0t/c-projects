#include "testcommon.h"
void test (void);

void test (void) {

//#include <criterion/criterion.h>

//#define NODEBUG

//#include "testcommon.h"

//Test(empty, emptyfromNULL) {
  a = array_new(NULL, -1); // 1

  s = array_see(a); // 2
  dbg_prn("empty array looks like: %s\n", s);
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1 ~2
//}

//Test(empty, isempty) {

  a = array_new(NULL, -1); // 1
  //cr_assert(array_isempty(a));
  //cr_assert(array_length(a) == 0);

  array_destruct(a); // ~1
//}

//Test(empty, append) {
  a = array_new(NULL, -1); // 1

  oa = object_new(t_realchar, (const void* const ) "const void* const val"); // 2

  array_append(a, oa);

  s = array_see(a); // 3
  dbg_prn("1array: %s\n", s);
  //cr_assert_str_eq(s, "{ \"const void* const val\" }");
  //cr_assert(! array_isempty(a));
  //cr_assert(array_length(a) == 1);

  safefree(s), array_destruct(a), object_destruct(oa); // ~1, ~2, ~3
//}

//Test(empty, deletefails) {
  a = array_new(NULL, -1); // 1

  ok = array_delete(a, 0);
  //cr_assert(! ok);

  array_destruct(a); // ~1
//}

//Test(empty, clear) {
  a = array_new(NULL, -1); // 1

  s = array_see(a); // 2
  //cr_assert_str_eq(s, "{ }");
  safefree(s); // ~2

  array_clear(a);

  s = array_see(a); // 3
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1, ~3
//}

//Test(empty, concat) {
  a = array_new(NULL, -1), b = array_copy(a); // 1, 2

  array_concat(&a, b);

  s = array_see(a); // 3
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct_args(2, a, b); // ~1, ~2, ~3
//}

//Test(empty, equals) {
  a = array_new(NULL, -1), b = array_copy(a);

  ok = array_equals(a, b);

  //cr_assert( ok );

  array_destruct_args(2, a, b);
//}

// NONEMPTY

//Test(nonempty, fromboa) {

  size_t objslen = 2;

  object_t** objs = (typeof(objs)) safemalloc( sizeof (object_t*) * objslen );

  ssize_t i = -6, j = 9;

  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, un2signed(objslen));
  object_dtorn(objs, 2);

  s = array_see(a);
  dbg_prn("fromboaptr is %s\n", s);
  //cr_assert_str_eq(s, "{ -6 9 }");

  safefree(s), array_destruct(a);
//}

//Test(nonempty, fromcptrptr) {

  a = array_new_fromcptr(
    (const void* const * const ) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  s = array_see(a);
  dbg_prn("fromptrptr is: %s\n", s);
  //cr_assert_str_eq(s, "{ \"abc\" \"def\" \"ghi\" \"jkl\" \"mno\" \"pqr\" \"stu\" \"vwx\" \"yz\" }");
  safefree(s), array_destruct(a);
//}


//Test(nonempty, fromcliteralssize) {

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  s = array_see(ra);
  dbg_prn("array from literal is: %s\n", s);
  //cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 }");
  safefree(s), array_destruct(ra);
//}

//Test(nonempty, copy) {

  a = array_new_fromcptr(
    (const void* const * const) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  b = array_copy(a);

  s = array_see(a);
  s2 = array_see(b);
  dbg_prn("fromptrptr is: %s\nand: %s\n", s, s2);
  //cr_assert_str_eq(s, s2);

  //cr_assert_neq(a->uid, b->uid);

  array_destruct_args(2, a, b);
  safefree_args(2, s, s2);
//}

//Test(nonempty, concat2ssize) {

  _Static_assert(
    (sizeof anums / sizeof (ssize_t)) == (sizeof bnums / sizeof (ssize_t)),
    "literal arrays should have same lengths"
  );

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  rb = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  array_concat(&ra, rb);

  s = array_see(ra);
  dbg_prn("concat is: %s\n", s);
  //cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");
  safefree(s), array_destruct(ra), array_destruct(rb);
//}

//Test(nonempty, delete) {

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  ok = array_delete(a, 3);
  //cr_assert(ok);
  ok = array_delete(a, a->idx);
  //cr_assert(ok);
  ok = array_delete(a, -1);
  //cr_assert(! ok);

  s = array_see(a);
  dbg_prn("delete2: %s\n", s);
  //cr_assert_str_eq(s, "{ 1 -3 5 9 }");

  safefree(s), array_destruct(a);
//}

//Test(nonempty, clear) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  array_clear(a);
  s = array_see(a);
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
//}

//Test(nonempty, insert) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  size_t g = 99999;
  object_t* go = object_new(t_realuint, &g);
  ok = array_insert(a, go, 0);
  s = array_see(a);

  //cr_assert_str_eq(s, "{ 99999 1 -3 5 -7 9 -11 }");
  //cr_assert(ok);

  safefree(s);

  ok = array_insert(a, go, 99);
  s = array_see(a);

  //cr_assert_str_eq(s, "{ 99999 1 -3 5 -7 9 -11 }");
  //cr_assert(! ok);

  safefree(s),
  array_destruct(a), object_destruct(go);
//}

//Test(nonempty, concat2) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  array_concat(&a, b);

  s = array_see(a);
  dbg_prn("concat is: %s", s);
  //cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");

  safefree(s), array_destruct_args(2, a, b);
//}

//Test(nonempty, equals) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_copy(a);

  ok = array_equals(a, b);

  //cr_assert( ok );

  array_destruct(b);

  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  ok = array_equals(a, b);

  //cr_assert( ! ok );

  array_destruct_args(2, a, b);
//}
//#include <criterion/criterion.h>

//#define NODEBUG
//#include "testcommon.h"

//Test(empty, boa) {
  c = assoc_new(NULL, NULL);

  s = assoc_see(c);
  dbg_prn("empty: %s\n", s);
  //cr_assert_str_eq(s, "a{ }");

  safefree(s), assoc_destruct(c);
//}

//Test(empty, append) {
  c = assoc_new(NULL, NULL);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);
  //cr_assert_str_eq("{ }", s);
  //cr_assert_str_eq("{ }", s2);

  safefree_args(2, s, s2), array_destruct_args(2, a, b),
  assoc_destruct(c);
//}

//Test(empty, unzip) {
  a = array_new(NULL, -1),
  b = array_new(NULL, -1);

  s3 = array_see(a), s4 = array_see(b);

  c = assoc_new(a, b);

  array_destruct_args(2, a, b);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);

  dbg_prn("empty a: %s, p1: %s, b: %s, p2: %s\n", s, s3, s2, s4);

  //cr_assert_str_eq(s3, s);
  //cr_assert_str_eq(s4, s2);

  safefree_args(4, s, s2, s3, s4);

  array_destruct_args(2, a, b);

  assoc_destruct(c);
//}

//Test(nonempty, boa) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  s = assoc_see(c);

  dbg_prn("boa ab: %s", s);

  //cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), array_destruct_args(2, a, b),
  assoc_destruct(c);
//}

//Test(nonempty, append) {
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

  //cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { -11 . 12 } }");

  safefree(s),
  array_destruct_args(2, a, b),
  assoc_destruct(c);

  object_dtor_args(2, oa, ob);
//}

//Test(nonempty, unzip) {
  a = array_new_from_ssize_t_lit(anums, 2, t_realint),
  b = array_new_from_ssize_t_lit(bnums, 2, t_realint);

  s3 = array_see(a), s4 = array_see(b);

  c = assoc_new(a, b);

  array_destruct_args(2, a, b);

  assoc_unzip(c, &a, &b);

  s = array_see(a), s2 = array_see(b);

  dbg_prn("nonempty a: %s, p1: %s, b: %s, p2: %s\n", s, s3, s2, s4);

  //cr_assert_str_eq(s3, s);
  //cr_assert_str_eq(s4, s2);

  safefree_args(4, s, s2, s3, s4);

  array_destruct_args(2, a, b);

  assoc_destruct(c);
//}
}