#pragma once

#include "../../common.h"
#include "../object/object.h"
#include "../lex/lex.h"
#include "../stack/stack.h"

#ifdef HAVE_POSIX

#include <unistd.h>

#endif

#ifdef GCC
#line __LINE__ "compilecommon"
#endif

typedef FILE* filehandle_t;

#define MAX_CCODE_LEN     20000
#define MAX_MOUSECODE_LEN 7000  // idk

char* mouse2c (const char* const mcode);
ssize_t code_writer (const char* const code, const char* const filename, const char* const cflags, const char* const libmouse);

