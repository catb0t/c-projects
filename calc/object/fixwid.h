#include "objcommon.h"

#ifdef GCC
#line __LINE__ "fixwid"
#endif

fixwid_t* fixwid_new (const ssize_t v, const size_t u, const bool signed_active) {
  pfn();

  fixwid_t* fixwid = (typeof(fixwid)) safemalloc( sizeof(fixwid_t) );

  if (signed_active) {
    fixwid->value = v;
  } else {
    fixwid->uvalue = u;
  }

  fixwid->signed_active = signed_active;

  report_ctor(fixwid);

  return fixwid;
}

void  fixwid_destruct (fixwid_t* const fixwid) {
  pfn();

  report_dtor(fixwid);
  safefree(fixwid);
}

fixwid_t* fixwid_copy (const fixwid_t* const n) {
  pfn();

  object_failnull(n);

  ssize_t a = -1;
  size_t  b = 0;

  if (n->signed_active) {
    a = n->value;
  } else {
    b = n->uvalue;
  }

  return fixwid_new(a, b, n->signed_active);
}

char* fixwid_see (const fixwid_t* const n) {
  pfn();

  object_failnull(n);

  char*  buf = (typeof(buf)) safemalloc( ULL_DIGITS + 1 );

  if (n->signed_active) {
    snprintf( buf, ULL_DIGITS + 1, "%zd", n->value );
  } else {
    snprintf( buf, ULL_DIGITS, "%zu", n->uvalue );
  }

  buf = (typeof(buf)) saferealloc(buf, safestrnlen(buf) + 1);
  return buf;
}

bool fixwid_eq (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  object_failnull(a);

  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) == b->uvalue;

    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) == a->uvalue;
    }
    return false;
  }

  return a->signed_active
    ? a->value  == b->value
    : a->uvalue == b->uvalue;
}

bool    fixwid_gt (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  object_failnull(a);

  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) > b->uvalue;

    // not a bug
    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) < a->uvalue;
    }
    return false;
  }

  return a->signed_active
    ? a->value  > b->value
    : a->uvalue > b->uvalue;
}

bool    fixwid_lt (const fixwid_t* const a, const fixwid_t* const b) {
  pfn();

  object_failnull(a);

  if (a->signed_active != b->signed_active) {
    if (a->signed_active && (a->value >= 0)) {
      return signed2un(a->value) < b->uvalue;

    // not a bug
    } else if (b->signed_active && (b->value >= 0) ) {
      return signed2un(b->value) > a->uvalue;
    }
    return false;
  }

  return a->signed_active
    ? a->value  < b->value
    : a->uvalue < b->uvalue;
}

