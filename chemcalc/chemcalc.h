#include "../common.h"

typedef struct st_elem    element_t;
typedef struct st_isotope isotope_t;
typedef long double       amu_t;     // avoids alignment issues (lazy)

struct st_isotope {
  double abun;
  amu_t  mass;
  size_t uid;
};

struct st_elem {
  char*       name;
  char*       symb;
  isotope_t** isos;
  ssize_t     isosidx;
  size_t uid;
};

isotope_t*  isotope_new (const double abun, const amu_t mass);
isotope_t* isotope_copy (const isotope_t* const iso);
void   isotope_destruct (isotope_t* iso);

element_t*  element_new (
  const char* const name,
  const char* const symb,
  const isotope_t* const * const isos,
  const ssize_t isosidx
);
element_t* element_copy (const element_t* const elem);
void element_destruct (element_t* elem);

amu_t       amass_from_isos (const isotope_t* const * const isos, const size_t len);
isotope_t**  abun_from_elem (const amu_t elem_basemass, amu_t* isomasses, const size_t len);

char* isotope_see (const isotope_t* iso);
char* element_see (const element_t* elem);

#define MAX_SEE_LEN 400
#define ISOSEE_LEN  30

isotope_t* isotope_new (const double abun, const amu_t mass) {
  pfn(__FILE__, __LINE__, __func__);

  isotope_t* isotope = safemalloc( sizeof (isotope_t) );
  isotope->abun = abun;
  isotope->mass = mass;

  report_ctor(isotope);

  return isotope;
}

isotope_t* isotope_copy (const isotope_t* const iso) {
  return isotope_new(iso->abun, iso->mass);
}

void isotope_destruct (isotope_t* iso) {

  report_dtor(iso);
  safefree(iso);
}

element_t* element_new (
  const char* const name,
  const char* const symb,
  const isotope_t* const * const isos,
  const ssize_t isosidx
) {
  pfn(__FILE__, __LINE__, __func__);

  element_t* out = safemalloc(sizeof (element_t));

  if (isosidx != -1 && NULL != isos) {
    out->isos = safemalloc(sizeof (isotope_t *) * (size_t) (isosidx + 1) );

    for (ssize_t i = 0; i < isosidx; i++) {
      out->isos[i] = isotope_copy(isos[i]);
    }

  } else {
    out->isos = NULL;
  }

  out->isosidx   = isosidx;
  out->name      = strndup(name, safestrnlen(name));
  // symbols are two characters and strndup adds a null for us
  out->symb      = strndup(symb, 2);

  return out;
}

element_t* element_copy (const element_t* const elem) {
  return element_new(
    elem->name,
    elem->symb,
    (const isotope_t* const * const) elem->isos,
    elem->isosidx
  );
}

void element_destruct (element_t* elem) {
  safefree(elem->name);
  safefree(elem->symb);

  if (elem->isosidx != -1) {
    for (ssize_t i = 0; i < (elem->isosidx); i++) {
      isotope_destruct(elem->isos[i]);
    }
  }
  safefree(elem->isos);

}

char* isotope_see (const isotope_t* iso) {

  char* out;
  if (NULL == iso) {
    out = safemalloc(5);
    snprintf(out, 5, "(null)");
    return out;
  }

  out = safemalloc(ISOSEE_LEN);
  snprintf(
    out,
    ISOSEE_LEN,
    "isotope:\n"
    "\tunid: %zu\n"
    "\tabun: %f\n"
    "\tmass: %LG\n",
    iso->uid,
    iso->abun,
    iso->mass
  );
  return out;
}

char* element_see (const element_t* elem) {
  if (NULL == elem) {
    char* out = safemalloc(5);
    snprintf(out, 5, "(null)");
    return out;
  }

  char **isostrs,
       *isos_str;

  size_t lines = 0, total = 0;

  if ((elem->isosidx) != -1) {

    size_t nc = (size_t) (elem->isosidx);
    isostrs   = safemalloc(sizeof (char *) * nc);

    for (size_t i = 0; i < nc; i++) {
      isostrs[i] = safemalloc(ISOSEE_LEN);

      snprintf(isostrs[i], ISOSEE_LEN, "%s", isotope_see( (elem->isos) [i] ));

      size_t thislen = safestrnlen(isostrs[i]);

      isostrs[i] = realloc(isostrs[i], thislen);
      total += thislen;
      ++lines;
    }

  } else {
    isostrs    = safemalloc(sizeof (char *));
    isostrs[0] = safemalloc(2);
    snprintf(isostrs[0], 2, "%s", "");
    lines = 1, total = 0;
  }
  isos_str = concat_lines(isostrs, lines, total);

  char *out, tmp[MAX_SEE_LEN];
  size_t len = (size_t) snprintf(
    tmp,
    MAX_SEE_LEN,

    "element:\n"
    "\tunid: %zu\n"  // uid
    "\tsymb: %s\n"   // symbol
    "\tname: %s\n"   // name
    "\tisos: {\n%s\n}",  // isos

    elem->uid,
    elem->symb,
    elem->name,
    isos_str
  );

  if (len > MAX_SEE_LEN) {
    len = MAX_SEE_LEN;
  }

  out = safemalloc(len);
  snprintf(
    out,
    len,

    "element:\n"
    "\tunid: %zu\n"  // uid
    "\tsymb: %s\n"   // symbol
    "\tname: %s\n"   // name
    "\tisos: {\n%s\n}",  // isos

    elem->uid,
    elem->symb,
    elem->name,
    isos_str
  );

  safefree(isos_str);
  //safefree(type);

  return out;

}

__attribute_pure__
amu_t amass_from_isos (const isotope_t* const * const isos, const size_t len) {
  amu_t total = 0;

  for (size_t i = 0; i < len; i++) {
    const isotope_t* const this = isos[i];
    total += (this->abun * this->mass);
  }

  return total;
}

/*isotope_t** abun_from_elem (const amu_t elem_basemass, amu_t* isomasses, const size_t len) {

}
*/
