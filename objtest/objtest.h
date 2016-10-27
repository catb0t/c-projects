#include "../calc/object/object.h"

void test (void);

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


  ssize_t a = 1, b = 2;
  object_t *oa = object_new(t_realint, &a),
           *ob = object_new(t_realint, &b);

  array_t *ra = array_new(NULL, -1),
          *rb = array_new(NULL, -1);

  array_append(ra, oa), object_destruct(oa);
  array_append(rb, ob), object_destruct(ob);

  hash_t* h = hash_new_boa(ra, rb);

  array_destruct(ra), array_destruct(rb);

  hash_inspect(h);

  hash_destruct(h);

}
