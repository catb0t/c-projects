#include "../calc/object/object.h"

void test (void);

define_array_new_fromctype(char* const, array_new_fromc_charptr)

void test (void) {

  //infer a = readln(80);
  //printf("values: ");
  //infer b = readln(80);
  //infer sa = safestrnlen(a);
  //infer sb = safestrnlen(b);

  size_t len = 4;

  char
    **keys = safemalloc( sizeof (char *) * len),
    **vals = safemalloc( sizeof (char *) * len);

  printf("keys\n");
  for (size_t i = 0; i < len; i++) {
    printf("\n%zu: ", i);
    keys[i] = readln(34);
  }

  printf("vals\n");
  for (size_t i = 0; i < len; i++) {
    printf("\n%zu: ", i);
    vals[i] = readln(34);
  }

  array_t *keya = array_new_fromc_charptr( (const char* const * const) keys, len, t_realchar),
          *vala = array_new_fromc_charptr( (const char* const * const) vals, len, t_realchar);

  free_ptr_array((void**) keys, len), free_ptr_array((void**) vals, len);

  array_inspect(keya);
  array_inspect(vala);

  hash_t* h = hash_new_boa(keya, vala);

  array_destruct(keya), array_destruct(vala);

  hash_inspect(h);

  hash_destruct(h);

/*  safefree(nums);

  hash_t* h = hash_new_boa(ra, rb);

  array_destruct(ra), array_destruct(rb);

  hash_inspect(h);

  ok = true;

  s = object_repr( *hash_get_ref(h, *array_get_ref(ra, 2, NULL), &ok) );

  dealloc_printf(s);

  hash_destruct(h);
*/
}
