#include "../calc/object/object.h"

void test (void);

void test (void) {

  array_t *titles = array_new(NULL, -1), // 1
          *fins   = array_new(NULL, -1); // 2

  size_t count = 0;

  while (true) {

    printf("Enter a book's name: ");

    char* namebuf = readln(MAX_STR_LEN); // 3

    printf("Completed? [y/n?] ");

    char* cmplt   = readln(3); // 4

    if ( (cmplt[0] == 4) || (namebuf[0] == 4) ) {
      safefree(namebuf), safefree(cmplt); // ~3, ~4
      break;
    }

    bool finished = cmplt[0] == 'y';

    object_t* t = something_new(); // 5

    // 6, 7
    object_t
      *titleobj = object_new(t_realchar, (const void * const) namebuf),
      *compobj  = finished
                ? object_new(t_T, (const void * const) t)
                : object_new(t_F, NULL);

    array_append(titles, titleobj);
    array_append(fins, compobj);

    object_dtor_args(2, t, titleobj, compobj); // ~5, ~6, ~7

    safefree(namebuf), safefree(cmplt); // ~3, ~4

    ++count;
  }

  hash_t* books = hash_new_boa(titles, fins, count); // 8

  hash_destruct(books); // ~8

  array_destruct(titles), array_destruct(fins); // ~1, ~2
}
