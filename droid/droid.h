#include "../common.h"

typedef struct s_droid_type droid_t;
typedef void (* droid_func_t) (droid_t*);
typedef void (* droid_u8func_t) (droid_t*, uint8_t);

struct s_droid_type {
  uint8_t battery_level;
  bool    is_recycled;

  droid_func_t activate;
  droid_func_t recycle;


  droid_u8func_t set_battery;
  uint8_t (* get_battery) (droid_t*);

  uint8_t (* check_battery) (droid_t*);
  droid_u8func_t charge_battery;
  droid_u8func_t drain_battery;

  droid_u8func_t hover;
};

droid_t* droid_new (void);

void droid_activate (droid_t* dr);
void  droid_recycle (droid_t* dr);

void droid_set_battlvl (droid_t* dr, uint8_t battlvl);
void  droid_chargebatt (droid_t* dr, uint8_t hours);
void   droid_drainbatt (droid_t* dr, uint8_t amt);
void       droid_hover (droid_t* dr, uint8_t height);

uint8_t droid_get_battlvl (droid_t* dr);
uint8_t   droid_checkbatt (droid_t* dr);

droid_t* droid_new (void) {
  droid_t* out = safemalloc(sizeof (droid_t));

  out->battery_level = 100;
  out->is_recycled   = false;

  out->activate       = &droid_activate;
  out->recycle        = &droid_recycle;

  out->set_battery    = &droid_set_battlvl;
  out->get_battery    = &droid_get_battlvl;

  out->check_battery  = &droid_checkbatt;
  out->charge_battery = &droid_chargebatt;
  out->drain_battery  = &droid_drainbatt;
  out->hover          = &droid_hover;

  return out;
}

void droid_recycle (droid_t* dr) {
  assert( ! dr->is_recycled );

  safefree(dr);

  printf("Recycling droid...\n");
  printf("Recycled %zu bytes of droid.\n", sizeof (droid_t));

  dr = NULL;
}

void droid_activate (droid_t* dr) {
  assert( ! dr->is_recycled );

  printf(
    "Activating droid...\n"
    "Droid activated.\n"
  );

  droid_drainbatt(dr, 5);
}

uint8_t droid_get_battlvl (droid_t* dr) {
  assert( ! dr->is_recycled );

  return dr->battery_level;
}

void droid_set_battlvl (droid_t* dr, uint8_t battlvl) {
  assert( ! dr->is_recycled );

  dr->battery_level = (battlvl > 100) ? 100 : battlvl;

  if ( ! battlvl ) {
    dr->recycle(dr);
  }
}

void droid_drainbatt (droid_t* dr, uint8_t amt) {
  assert( ! dr->is_recycled );

  int new_lvl = (int8_t) ( (int8_t) dr->get_battery(dr)) - 5;

  printf("Draining battery by %d%%...\n", amt);

  if ( new_lvl <= 0 ) {
    printf("Ded droid. Collecting garbage...\n");
    dr->recycle(dr);
    return;
  }

  dr->set_battery(dr, (uint8_t) new_lvl);
  if ( ! dr->battery_level ) {
    return;
  }
  dr->check_battery(dr);
}

void droid_chargebatt (droid_t* dr, uint8_t hours) {
  assert( ! dr->is_recycled );

  printf("Charging droid for %d hours...\n", hours);

  dr->set_battery(dr, (uint8_t) (hours + dr->battery_level));

  if ( ! dr->battery_level ) {
    return;
  }
  dr->check_battery(dr);
}

uint8_t droid_checkbatt (droid_t* dr) {
  assert( ! dr->is_recycled );

  uint8_t cb = dr->get_battery(dr);
  printf("Current battery level is %d%%.\n", cb);
  return cb;
}

void droid_hover (droid_t* dr, uint8_t height) {
  assert( ! dr->is_recycled );

  if (height > 2) {
    printf("Error: can't hover more than 2 feet.\n");
    return;
  }

  printf("Hovering at %d feet...\n", height);
  dr->drain_battery(dr, 20);
}
