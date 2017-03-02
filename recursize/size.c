#include "../calc/object/object.h"

size_t get_recursize (const array_t* const a);
size_t f (array_t* a);

define_array_new_fromctype(ssize_t);

int main (void) {

  const size_t len = 6;

  static const ssize_t h[6] = { -1, 3, -5, 7, -9, 11 };

  array_t* a = array_new_from_ssize_t_lit(h, len, t_realint);

  printf("Recursive size of a: %zu\n", get_recursize(a));

  object_t* asobj = object_new(t_array, a);
  array_destruct(a);

  array_t* b = array_new(NULL, 0);

  for (size_t j = 0; j < 10; j++) {
    array_append(b, asobj);
  }

  object_destruct(asobj);

  printf("Recursive size of b: %zu\n", get_recursize(b));

  asobj = object_new(t_array, b);
  array_destruct(b);

  array_t* c = array_new(NULL, 0);

  for (size_t i = 0; i < 100; i++) {
    array_append(c, asobj);
  }

  object_destruct(asobj);

  printf("Recursive size of c: %zu\n", get_recursize(c));


  array_t* d = array_new(NULL, 0);

  asobj = object_new(t_array, c);

  array_destruct(c);

  for (size_t i = 0; i < 5000; i++) {
    array_append(d, asobj);
  }

  object_destruct(asobj);

  printf("Recursive size of d: %zu\n", get_recursize(d));

  array_destruct(d);

  return EXIT_SUCCESS;
}

size_t get_recursize (const array_t* const a) {
  pfn();

  object_failnull(a);

  size_t out = 0;

  for (size_t i = 0; i < array_length(a); i++) {

    object_t** o = array_get_ref(a, i, NULL);

    out += (*o)->type == t_array
      ? get_recursize((*o)->ary)
      : 1 ;
  }

  return out;
}

size_t f(array_t*a){size_t t=0,i=0;for(;i<array_length(a);i++){object_t*o=array_get_copy(a,i,0);t+=o->type==6?f(o->ary):1;}return t;}
