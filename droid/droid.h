#include "../common.h"

struct s_droid_type {
  uint8_t batt_lvl;
};

typedef struct s_droid_type droid_t;

droid_t* droid_new (void);

bool droid_activate (droid_t* dr);
bool  droid_recycle (droid_t* dr);

bool droid_set_battlvl (droid_t* dr, uint8_t battlvl);
bool  droid_chargebatt (droid_t* dr, uint8_t hours);
bool   droid_drainbatt (droid_t* dr, uint8_t amt);
bool       droid_hover (droid_t* dr, uint8_t height);

uint8_t droid_get_battlvl (droid_t* dr);
uint8_t   droid_checkbatt (droid_t* dr);

droid_t* droid_new (void) {
  droid_t* out = safemalloc(sizeof (droid_t));
  out->batt_lvl = 100;
  return out;
}

bool droid_recycle (droid_t* dr) {
  assert (dr != NULL);
  safefree(dr);
  
  printf("Recycling droid...\n");
  printf("Recycled %zu bytes of droid.\n", sizeof (droid_t));
  return false;
}

bool droid_activate (droid_t* dr) {

  printf(
    "Activating droid...\n"
    "Droid activated.\n"
  );

  return droid_drainbatt(dr, 5);
}

uint8_t droid_get_battlvl (droid_t* dr) {
  assert (dr != NULL);
  return dr->batt_lvl;
}

bool droid_set_battlvl (droid_t* dr, uint8_t battlvl) {
  assert (dr != NULL);

  dr->batt_lvl = (battlvl > 100) ? 100 : battlvl;

  if (! battlvl) {
    return droid_recycle(dr);
  }
  return true;
}

bool droid_drainbatt (droid_t* dr, uint8_t amt) {
  int new_lvl = (int8_t) ( (int8_t) droid_get_battlvl(dr)) - 5;

  printf("Draining battery by %d%%...\n", amt);

  if ( new_lvl <= 0 ) {
    printf("Ded droid. Collecting garbage...\n");
    return droid_recycle(dr);
  }

  bool ok;
  ok = droid_set_battlvl(dr, (uint8_t) new_lvl);
  if (! ok) { return false; }
  return droid_checkbatt(dr);
}

bool droid_chargebatt (droid_t* dr, uint8_t hours) {
  printf("Charging droid for %d hours...\n", hours);
  bool ok;
  ok = droid_set_battlvl(dr, hours);
  if (! ok) { return false; }
  return droid_checkbatt(dr);
}

uint8_t droid_checkbatt (droid_t* dr) {
  uint8_t cb = droid_get_battlvl(dr);
  printf("Current battery level is %d%%.\n", cb);
  return cb;
}

bool droid_hover (droid_t* dr, uint8_t height) {
  if (height > 2) {
    printf("Error: can't hover more than 2 feet.\n");
    return true;
  }

  printf("Hovering at %d feet...\n", height);
  return droid_drainbatt(dr, 20);
}
