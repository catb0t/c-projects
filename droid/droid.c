#include "droid.h"

void droid_main (void);

void droid_main (void) {

  droid_t* dr = droid_new();

  dr->activate(dr);

  if (NULL == dr) {
    return;
  }

  dr->hover(dr, 1);

  if (NULL == dr) {
    return;
  }

  dr->charge_battery(dr, 3);

  if (NULL == dr) {
    return;
  }

  dr->recycle(dr);

  printf("%d\n", dr == NULL);

  if (NULL == dr) {
    return;
  }
}

int main(void) {

  droid_main();

  return 0;
}

