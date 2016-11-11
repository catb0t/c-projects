#include <criterion/criterion.h>

//#define NODEBUG
#include "../calc/object/object.h"

define_array_new_fromctype(ssize_t);

array_t *a, *b, *ra, *rb;

char *s, *s2;

bool ok;

static const ssize_t anums[] = {
  1, -3, 5, -7, 9, -11
};

static const ssize_t bnums[] = {
  -2, 4, -6, 8, -10, 12
};

static const char* const literal[] = {
  "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz"
};

Test(empty, emptyfromNULL) {
  a = array_new(NULL, -1);

  s = array_see(a);
  dbg_prn("empty array looks like: %s\n", s);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
}

Test(empty, isempty) {

  a = array_new(NULL, -1);
  cr_assert(array_isempty(a));
  cr_assert(array_length(a) == 0);

  array_destruct(a);
}

Test(empty, append) {
  a = array_new(NULL, -1);

  object_t* obj = object_new(t_realchar, (const void* const ) "const void* const val");

  array_append(a, obj);

  s = array_see(a);
  dbg_prn("1array: %s\n", s);
  cr_assert_str_eq(s, "{ \"const void* const val\" }");
  cr_assert(! array_isempty(a));
  cr_assert(array_length(a) == 1);

  safefree(s), array_destruct(a), object_destruct(obj);
}

Test(empty, deletefails) {
  a = array_new(NULL, -1);

  ok = array_delete(a, 0);
  cr_assert(! ok);

  array_destruct(a);
}

Test(empty, clear) {
  a = array_new(NULL, -1);

  s = array_see(a);
  cr_assert_str_eq(s, "{ }");
  safefree(s);

  array_clear(a);

  s = array_see(a);
  cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a);
}

// NONEMPTY

Test(nonempty, fromboa) {

  size_t objslen = 2;
  object_t** objs = safemalloc( sizeof (object_t*) * objslen );
  ssize_t i = -6, j = 9;
  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, un2signed(objslen));
  object_dtorn(objs, 1);

  s = array_see(a);
  dbg_prn("fromboactr is %s\n", s);
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

  safefree(s), safefree(s2), array_destruct(a), array_destruct(b);
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
  ok = array_delete(a, a->idx);
  cr_assert(ok);
  ok = array_delete(a, -1);
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

  ok = array_insert(a, go, 99);
  s = array_see(a);
  cr_assert_str_eq(s, "{ 99999 1 -3 5 -7 9 -11 }");
  cr_assert(! ok);

  safefree(s), array_destruct(a);
}

