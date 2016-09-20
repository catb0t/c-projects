#include "../common.h"

enum         el_category {noble_gas, metalloid};
typedef enum el_category el_category_t;

struct s_element_t {
  short         atomic_number;
  char*   symbol;
  char*   full_name;
  el_category_t el_type;
};

typedef struct s_element_t element_t;

void runCOOP     (void);
element_t* new_element (
  short         atomic_number,
  char*         symbol,
  char*         full_name,
  el_category_t el_type
);

element_t* new_element (
  short   atomic_number,
  char*   symbol,
  char*   full_name,
  el_category_t el_type
) {
  element_t* el = malloc(sizeof(element_t));
  el -> atomic_number = atomic_number;
  el -> symbol        = symbol;
  el -> full_name     = full_name;
  el -> el_type       = el_type;
  return el;
}

void runCOOP (void) {
  printf("Building element...\n");
  short amass;
  char *in,
       *sym,
       *fname;
  bool type;

  printf("Atomic mass: ");
  in = readln(SHORT_INSTR);
  amass = (short) strtol(in, NULL, DEC_BASE);
  safefree(in);

  printf("Symbol: ");
  sym = (char *) readln(SHORT_INSTR);

  printf("Full name: ");
  fname = (char *) readln(SHORT_INSTR);

  printf("1 for noble gas or 0 for metalloid: ");
  in = readln(SHORT_INSTR);
  type = (bool) strtol(in, NULL, DEC_BASE);
  safefree(in);

  element_t* user_element = new_element(amass, sym, fname, type ? noble_gas : metalloid);

  printf("%s (symbol %s) has atomic number %d and is of type %s.\n",
    user_element->full_name, user_element->symbol, user_element->atomic_number,
    (user_element->el_type ? "metalloid" : "noble gas")
  );

  safefree(user_element->symbol), safefree(user_element->full_name), safefree(user_element);
}
