#include "../calc/object/object.h"

void test (void);

#define infer __auto_type

void test (void) {
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
  printf("before dtor\n");
  object_destruct(o2);
  printf("after  dtor\n");

  // see it again
  ca = array_see(a);
  dealloc_printf(ca);

  array_delete(a, 2);

  // see it again
  ca = array_see(a);
  dealloc_printf(ca);

  array_destruct(a);
}
