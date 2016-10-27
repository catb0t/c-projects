#include "objcommon.h"

#ifdef GCC
#line __LINE__ "pair"
#endif

func_t* func_new (const char* const code, const char* const name) {
  pfn();

  func_t* func = (typeof(func)) safemalloc(sizeof (func_t));

  func->code = strndup(code, safestrnlen(code));
  func->name = strndup(name, safestrnlen(name));

  report_ctor(func);
  return func;
}

void func_destruct (func_t* const func) {
  report_dtor(func);

  safefree(func->code);
  safefree(func->name);
  safefree(func);
}

char* func_see (const func_t* const f) {
  char *code = f->code,
       *name = f->name, *buf;
  size_t len = safestrnlen(code) + safestrnlen(name) + 2;

  buf = (typeof(buf)) safemalloc(sizeof (char) * len);

  snprintf(buf, len, "%s = [ %s ]", name, code);

  safefree(code), safefree(name);

  return buf;
}
