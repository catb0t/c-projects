#include "../calc/object/object.h"

void test (void);

void test (void) {

  array_t *titles = array_new(NULL, -1),
          *fins   = array_new(NULL, -1);

  size_t count = 0;

  while (true) {

    printf("Enter a book's name: ");

    char* namebuf = readln(MAX_STR_LEN);

    printf("Completed? [y/n?] ");

    char* cmplt   = readln(3);
    bool finished = cmplt[0] == 'y';

    number_t* n = number_new(1);

    object_t *titleobj = object_new(t_realchar, (const void * const) namebuf),
             *compobj  = finished ?
                         object_new(t_number, (const void * const) n)
                         : object_new(t_F, NULL);

    array_append(titles, titleobj);
    array_append(fins, compobj);

    number_destruct(n);
    object_destruct(titleobj), object_destruct(compobj);

    if ( (cmplt[0] == 4) || (namebuf[0] == 4) ) {
      safefree(namebuf), safefree(cmplt);
      break;
    }
    safefree(namebuf), safefree(cmplt);

    ++count;
  }

  hash_t* books = hash_new(titles, fins, count);

  hash_destruct(books);

  array_destruct(titles), array_destruct(fins);
}
