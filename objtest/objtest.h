#include "../calc/object/object.h"

void test (void);

define_array_new_fromctype(ssize_t);

static const ssize_t anums[] = {
  1, -3, 5, -7, 9, -11
};

static const ssize_t bnums[] = {
  -2, 4, -6, 8, -10, 12
};

static const char* const literal[] = {
  "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz"
};

array_t *ra, *rb, *b, *a;

char *s, *s2;

bool ok;

void test (void) {

  a = array_new(NULL, -1);

  s = array_see(a);
  dbg_prn("empty array looks like: %s\n", s);

  safefree(s), array_destruct(a);

  a = array_new(NULL, -1);

  array_destruct(a);

  a = array_new(NULL, -1);

  object_t* obj = object_new(t_realchar, (const void* const ) "const void* const val");

  array_append(a, obj);

  s = array_see(a);
  dbg_prn("1array: %s\n", s);

  safefree(s), array_destruct(a), object_destruct(obj);

  a = array_new(NULL, -1);

  ok = array_delete(a, 0);

  array_destruct(a);

  a = array_new(NULL, -1);

  s = array_see(a);
  safefree(s);

  array_clear(a);

  s = array_see(a);

  safefree(s), array_destruct(a);

  size_t objslen = 2;
  object_t** objs = safemalloc( sizeof (object_t*) * objslen );
  ssize_t i = -6, j = 9;
  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, un2signed(objslen));
  object_dtorn(objs, objslen);

  s = array_see(a);
  dbg_prn("fromboactr is %s\n", s);

  safefree(s), array_destruct(a);

  a = array_new_fromcptr(
    (const void* const * const ) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  s = array_see(a);
  dbg_prn("fromptrptr is: %s\n", s);
  safefree(s), array_destruct(a);

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  s = array_see(ra);
  dbg_prn("array from literal is: %s\n", s);
  safefree(s), array_destruct(ra);

  a = array_new_fromcptr(
    (const void* const * const) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar
  );

  b = array_copy(a);

  s = array_see(a);
  s2 = array_see(b);
  dbg_prn("fromptrptr is: %s\nand: %s\n", s, s2);


  safefree(s), safefree(s2), array_destruct(a), array_destruct(b);

  _Static_assert(
    (sizeof anums / sizeof (ssize_t)) == (sizeof bnums / sizeof (ssize_t)),
    "literal arrays should have same lengths"
  );

  ra = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  rb = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  array_concat(&ra, rb);

  s = array_see(ra);
  dbg_prn("concat is: %s\n", s);
  safefree(s), array_destruct(ra), array_destruct(rb);

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  ok = array_delete(a, 3);
  ok = array_delete(a, a->idx);
  ok = array_delete(a, -1);

  s = array_see(a);
  dbg_prn("delete2: %s\n", s);

  safefree(s), array_destruct(a);

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  array_clear(a);
  s = array_see(a);

  safefree(s), array_destruct(a);
}
