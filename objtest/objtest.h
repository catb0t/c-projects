#include "../calc/object/object.h"

void test (void);

define_array_new_fromctype(ssize_t, array_new_fromc_ssize_t)
define_array_new_fromctype(char* const, array_new_fromc_charptr)

void test (void) {

  /*
  // create a new array and print it
  infer a = array_new(NULL, -1);
  infer ca = array_see(a);
  dealloc_printf(ca);

  // add something to it
  infer o1 = object_new(t_realchar, "123");
  array_append(a, o1);
  object_destruct(o1);

  // add something else to it
  infer o2 = object_new(t_realchar, "456");
  array_append(a, o2);
  object_destruct(o2);

  // add something else to it
  infer o3 = object_new(t_realchar, "789");
  array_append(a, o3);
  object_destruct(o3);

  array_inspect(a);

  array_delete(a, 2);

  array_inspect(a);

  // see it again
  ca = array_see(a);
  dealloc_printf(ca);

  array_destruct(a);
  */
  //infer a = readln(80);
  //infer b = readln(80);

  bool ok;

  char* s;

  size_t len = 5;

  ssize_t *nums = (typeof(nums)) safemalloc( sizeof (size_t) * len);

  for (size_t i = 0; i < len; i++) {
    nums[i] = un2signed(i);
  }

  const char* const str[] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno"
  };

  array_t *ra = array_new_fromc_ssize_t(nums, len, t_realint),
          *rb = array_new_fromc_charptr(str, len, t_realchar);

  safefree(nums);

  hash_t* h = hash_new_boa(ra, rb);

  array_destruct(ra), array_destruct(rb);

  hash_inspect(h);

  ok = true;

  s = object_repr( *hash_get_ref(h, *array_get_ref(ra, 2, NULL), &ok) );

  dealloc_printf(s);

  hash_destruct(h);

}
