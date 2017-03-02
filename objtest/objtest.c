/* BEGIN GENERATED CODE */
#include "testcommon.h"
void test (void);

int main (void) { test(); return EXIT_SUCCESS; }

void test (void) {

//#include <criterion/criterion.h>

//#define NODEBUG
//#include "testcommon.h"

//Test(empty, emptyfromNULL) {
  a = array_new(NULL, 0); // 1

  s = array_see(a); // 2
  dbg_prn("empty array looks like: %s\n", s);
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1 ~2
//}

//Test(empty, isempty) {

  a = array_new(NULL, 0); // 1
  //cr_assert(array_isempty(a));
  //cr_assert(array_length(a) == 0);

  array_destruct(a); // ~1
//}

//Test(empty, append) {
  a = array_new(NULL, 0); // 1

  oa = object_new(t_realchar, (const void* const ) "const void* const val"); // 2

  array_append(a, oa);

  s = array_see(a); // 3
  dbg_prn("1array: %s\n", s);
  //cr_assert_str_eq(s, "{ \"const void* const val\" }");
  //cr_assert(! array_isempty(a));
  //cr_assert(array_length(a) == 1);

  safefree(s), array_destruct(a), object_destruct(oa); // ~1, ~2, ~3
//}

//Test(empty, insert) {
  a = array_new(NULL, 0);

  oa = object_new(t_realint, (const void * const) anums);
  ok = array_insert(a, oa, 0);
  //cr_assert(ok);
  s = array_see(a);
  dbg_prn("s is %s\n", s);
  //cr_assert_str_eq(s, "{ 1 }");

  object_destruct(oa), array_destruct(a), safefree(s);
//}

//Test(empty, deletefails) {
  a = array_new(NULL, 0); // 1

  ok = array_delete(a, 0);
  //cr_assert(! ok);
  s = array_see(a);
  //cr_assert_str_eq(s, "{ }");

  safefree(s);
  array_destruct(a); // ~1
//}

//Test(empty, clear) {
  a = array_new(NULL, 0); // 1

  s = array_see(a); // 2
  //cr_assert_str_eq(s, "{ }");
  safefree(s); // ~2

  array_clear(a);

  s = array_see(a); // 3
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1, ~3
//}

//Test(empty, concat) {
  a = array_new(NULL, 0), b = array_copy(a); // 1, 2

  ra = array_concat(a, b); // 3

  s = array_see(ra); // 4
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct_args(3, a, b, ra); // ~1, ~2, ~3, ~4
//}

//Test(empty, equals) {
  a = array_new(NULL, 0), b = array_copy(a);

  ok = array_equals(a, b);

  //cr_assert( ok );

  array_destruct_args(2, a, b);
//}

//Test(empty, getref) {
  a = array_new(NULL, 0);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t** obj_ra = array_get_ref(a, __LOOPCOUNT, &ok);

    //cr_assert( ! ok );
    //cr_assert( NULL == obj_ra );
    (void) obj_ra;
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
//}

//Test(empty, getcopy) {
  a = array_new(NULL, 0);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t* obj_a = array_get_copy(a, __LOOPCOUNT, &ok);

    //cr_assert( ! ok );
    //cr_assert( object_isinstance(t_F, obj_a) );
    object_destruct(obj_a);
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu copies from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
//}

// NONEMPTY

//Test(nonempty, boa) {

  size_t objslen = 2;

  object_t** objs = (typeof(objs)) safemalloc( sizeof (object_t*) * objslen );

  ssize_t i = -6, j = 9;

  objs[0] = object_new(t_realint, &i);
  objs[1] = object_new(t_realint, &j);

  a = array_new( (const object_t* const * const) objs, objslen);
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

//Test(nonempty, delete) {

  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  ok = array_delete(a, 3);
  //cr_assert(ok);
  ok = array_delete(a, signed2un(a->idx));
  //cr_assert(ok);
  ok = array_delete(a, 0);
  //cr_assert(ok);

  s = array_see(a);
  dbg_prn("delete2: %s\n", s);
  //cr_assert_str_eq(s, "{ -3 5 9 }");

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

//Test(nonempty, concat) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums) / sizeof (ssize_t), t_realint);

  ra = array_concat(a, b);

  s = array_see(ra);
  dbg_prn("concat is: %s", s);
  //cr_assert_str_eq(s, "{ 1 -3 5 -7 9 -11 -2 4 -6 8 -10 12 }");

  safefree(s), array_destruct_args(3, a, b, ra);
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

//Test(nonempty, getref) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t** obj_ra = array_get_ref(a, __LOOPCOUNT, &ok);

    if ( array_isinbounds(a, __LOOPCOUNT) ) {
      //cr_assert( ok );
      //cr_assert( NULL != obj_ra );

    } else {
      //cr_assert( ! ok );
      //cr_assert( NULL == obj_ra );
    }

    (void) obj_ra;
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu refs from nonempty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
//}

//Test(nonempty, getcopy) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums) / sizeof (ssize_t), t_realint);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    object_t* obj_a = array_get_copy(a, __LOOPCOUNT, &ok);

    if ( array_isinbounds(a, __LOOPCOUNT) ) {
      //cr_assert( ok );
      //cr_assert( ! object_isinstance(t_F, obj_a) );

    } else {
      //cr_assert( ! ok );
      //cr_assert( object_isinstance(t_F, obj_a) );
    }

    object_destruct(obj_a);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu copies from empty array took %ld ms", __LOOPCOUNT, msec);

  array_destruct(a);
//}
//#include <criterion/criterion.h>

//#define NODEBUG
//#include "testcommon.h"

//Test(empty, emptyfromNULL) {
  c = assoc_new(NULL, NULL);

  s = assoc_see(c);
  dbg_prn("empty: %s\n", s);
  //cr_assert_str_eq(s, "a{ }");

  safefree(s), assoc_destruct(c);
//}

//Test(empty, isempty) {
  c = assoc_new(NULL, NULL); // 1
  //cr_assert(assoc_isempty(c));
  //cr_assert(assoc_length(c) == 0);

  assoc_destruct(c); // ~1
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

//Test(empty, insert) {
  c = assoc_new(NULL, NULL);

  oa = object_new(t_realchar, (const void* const ) "const void* const val"),
  ob = object_new(t_realuint, (const void* const ) (anums + 2));

  p = pair_new(oa, ob);

  ok = assoc_insert(c, p, 7);

  pair_destruct(p);

  object_destruct_args(2, oa, ob);

  assoc_destruct(c);
//}

//Test(empty, unzip) {
  a = array_new(NULL, 0),
  b = array_copy(a);

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

//Test(empty, deletefails) {
  c = assoc_new(NULL, NULL); // 1

  ok = assoc_delete(c, 0);
  //cr_assert(! ok);

  assoc_destruct(c); // ~1
//}

//Test(empty, concat) {
  c = assoc_new(NULL, NULL), d = assoc_copy(c);

  rc = assoc_concat(c, d);

  s = assoc_see(rc);
  //cr_assert_str_eq(s, "a{ }");
  safefree(s);

  assoc_destruct_args(3, rc, c, d);
//}

//Test(empty, equals) {
  c = assoc_new(NULL, NULL), d = assoc_copy(c);

  ok = assoc_equals(c, d);

  //cr_assert( ok );

  assoc_destruct_args(2, c, d);
//}

//Test(empty, clear) {
  a = array_new(NULL, 0); // 1

  s = array_see(a); // 2
  //cr_assert_str_eq(s, "{ }");
  safefree(s); // ~2

  array_clear(a);

  s = array_see(a); // 3
  //cr_assert_str_eq(s, "{ }");

  safefree(s), array_destruct(a); // ~1, ~3
//}


//Test(empty, getref) {
  c = assoc_new(NULL, NULL);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t** p_refa = assoc_get_ref(c, __LOOPCOUNT, &ok);

    //cr_assert( ! ok );
    //cr_assert( NULL == p_refa );
    (void) p_refa;
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);
//}

//Test(empty, getcopy) {
  c = assoc_new(NULL, NULL);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t *p_copy     = assoc_get_copy(c, __LOOPCOUNT, &ok),
           *empty_pair = pair_new(NULL, NULL);

    //cr_assert( ! ok );
    //cr_assert( pair_equals(p_copy, empty_pair) );
    (void) p_copy, (void) empty_pair;
    pair_destruct_args(2, p_copy, empty_pair);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

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

//Test(nonempty, fromcptrptr) {

  c = assoc_new_fromcptr(
    (const void* const * const) (const char* const * const) literal,
    (const void* const * const) (const char* const * const) literal,
    (26 / 3) + 1,
    t_realchar, t_realchar
  );

  s = assoc_see(c);
  //cr_assert_str_eq(s, "a{ { \"abc\" . \"abc\" } { \"def\" . \"def\" } { \"ghi\" . \"ghi\" } { \"jkl\" . \"jkl\" } { \"mno\" . \"mno\" } { \"pqr\" . \"pqr\" } { \"stu\" . \"stu\" } { \"vwx\" . \"vwx\" } { \"yz\" . \"yz\" } }");
  safefree(s), assoc_destruct(c);
//}

//Test(nonempty, fromcliteralssize) {

  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  s = assoc_see(c);
  dbg_prn("fromptr is %s\n", s);

  //cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), assoc_destruct(c);
//}

//Test(nonempty, copy) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  d = assoc_copy(c);
  s = assoc_see(c), s2 = assoc_see(d);
  //cr_assert_str_eq(s, s2);

  //cr_assert_neq(c->uid, d->uid);
  assoc_destruct_args(2, c, d);
  safefree_args(2, s, s2);
//}

//Test(nonempty, concat) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint),
  d = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)), t_realint, t_realint);

  rc = assoc_concat(c, d);

  s = assoc_see(rc);

  //cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } { 1 . -2 } { -3 . 4 } { 5 . -6 } { -7 . 8 } { 9 . -10 } { -11 . 12 } }");

  safefree(s), assoc_destruct_args(3, rc, d, c);
//}

//Test(nonempty, delete) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)) - 2, t_realint, t_realint);

  ok = assoc_delete(c, 3);
  //cr_assert(ok);
  ok = assoc_delete(c, signed2un(c->idx));
  //cr_assert(ok);
  ok = assoc_delete(c, 0);
  //cr_assert(ok);

  s = assoc_see(c);
  dbg_prn("delete2: %s\n  ", s);
  //cr_assert_str_eq(s, "a{ { -3 . 4 } }");

  safefree(s), assoc_destruct(c);
//}

//Test(nonempty, clear) {
  c = assoc_new_from_ssize_t_lit(anums, bnums, (sizeof anums / sizeof (ssize_t)) - 2, t_realint, t_realint);

  assoc_clear(c);

  //cr_assert(assoc_length(c) == 0);

  s = assoc_see(c);
  //cr_assert_str_eq(s, "a{ }");

  ok = true;

  p  = assoc_get_copy(c, 2, &ok),
  p1 = pair_new(NULL, NULL);

  //cr_assert( ! ok );
  //cr_assert( pair_equals(p, p1) );

  safefree(s), assoc_destruct(c);

  pair_destruct_args(2, p, p1);
//}

//Test(nonempty, append) {
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

  //cr_assert_str_eq(s, "a{ { 1 . -2 } { -3 . 4 } { -11 . 12 } }");

  safefree(s),
  array_destruct_args(2, a, b),
  assoc_destruct(c);

  object_destruct_args(2, oa, ob);
//}

//Test(nonempty, insert) {
  c = assoc_new(NULL, NULL);

  oa = object_new(t_realint, &( anums[5] )),
  ob = object_new(t_realint, &( bnums[5] ));

  p = pair_new(oa, ob);

  object_destruct_args(2, oa, ob);

  ok = assoc_insert(c, p, 0); // ok -- at end

  s = assoc_see(c);
  dbg_prn("s = %s\n", s);
  safefree(s);
  pair_destruct(p);

  //cr_assert( ok );

  oa = object_new(t_realint, &( anums[5] )),
  ob = object_new(t_realint, &( bnums[5] ));

  p = pair_new(oa, ob);

  object_destruct_args(2, oa, ob);

  ok = assoc_insert(c, p, 2); // past end = NOT OK

  s = assoc_see(c);
  dbg_prn("2. s = %s\n", s);
  safefree(s);

  pair_destruct(p);

  //cr_assert( ! ok );

  oa = object_new(t_realint, &( anums[4] )),
  ob = object_new(t_realint, &( bnums[4] ));

  p = pair_new(oa, ob);

  object_destruct_args(2, oa, ob);

  ok = assoc_insert(c, p, 0); // before end = OK

  s = assoc_see(c);
  dbg_prn("3. s = %s\n", s);
  safefree(s);

  pair_destruct(p);

  //cr_assert( ok );

  assoc_destruct(c);
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

//Test(nonempty, getref) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  stderr = freopen("/dev/null", "w", stderr);

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t** p_refa = assoc_get_ref(c, __LOOPCOUNT, &ok);

    if ( assoc_isinbounds(c, __LOOPCOUNT) ) {
      //cr_assert( ok );
      //cr_assert( NULL != p_refa );

    } else {
      //cr_assert( ! ok );
      //cr_assert( NULL == p_refa );
    }

    (void) p_refa;
  }
  clock_stop();

  stderr = freopen("/dev/stderr", "w", stderr);

  dbg_prn("get %zu refs from nonempty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);
  array_destruct_args(2, a, b);
//}

//Test(nonempty, getcopy) {
  a = array_new_from_ssize_t_lit(anums, (sizeof anums / sizeof (ssize_t)), t_realint),
  b = array_new_from_ssize_t_lit(bnums, (sizeof bnums / sizeof (ssize_t)), t_realint);

  c = assoc_new(a, b);

  fdredir(stderr, "/dev/null");

  clock_start();
  for (__LOOPCOUNT = 0; __LOOPCOUNT < GETTER_LOOP_LENGTH; __LOOPCOUNT++) {
    pair_t *p_copy     = assoc_get_copy(c, __LOOPCOUNT, &ok),
           *empty_pair = pair_new(NULL, NULL);

    if ( assoc_isinbounds(c, __LOOPCOUNT) ) {
      //cr_assert( ok );
      //cr_assert( ! pair_equals(p_copy, empty_pair) );
    } else {
      //cr_assert( ! ok );
      //cr_assert( pair_equals(p_copy, empty_pair) );
    }

    pair_destruct_args(2, p_copy, empty_pair);
  }
  clock_stop();

  fdredir(stderr, "/dev/stderr");

  dbg_prn("get %zu refs from empty assoc took %ld ms", __LOOPCOUNT, msec);

  assoc_destruct(c);

  array_destruct_args(2, a, b);
//}
} /* END GENERATED CODE */ 
