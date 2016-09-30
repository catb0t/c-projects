#include "droid.h"

void droid_main (void);

void droid_main (void) {

  droid_t* hal = droid_new();

  if (! droid_activate(hal)) {
    return;
  }

  if (! droid_hover(hal, 1)) {
    return;
  }

  if (! droid_chargebatt(hal, 3)) {
    return;
  }

  if (! droid_recycle(hal)) {
    return;
  }
}

int main(void) {

  droid_main();

  return 0;
}
