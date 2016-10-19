#include "compilecommon.h"

#ifdef GCC
#line __LINE__ "compile"
#endif

ssize_t code_writer (
  const char* const code,
  const char* const filename,
  const char* const cflags,
  const char* const libmouse
) {

  if ( (NULL == code) || (NULL == filename) ) {
    return -1;
  }

  size_t
    cflen    = safestrnlen(cflags),
    fnamelen = safestrnlen(filename),
    libmlen  = safestrnlen(libmouse),
    cmdlen   = (40 + cflen + fnamelen + libmlen);

  char*  cmdline = (typeof(cmdline)) safemalloc( sizeof (char) * cmdlen );


  /*

    cc -std=c11 -O3 libmouse.a $(cflags) -xc -o $(filename) -

  */

  snprintf(
    cmdline,
    cmdlen,
    "cc -std=c11 -xc %s %s -o %s - ",
    libmouse, cflags, filename
  );

  filehandle_t cc = popen(cmdline, "r");

  if ( NULL == cc ) {
    perror("popen");
  }

  int fp = fprintf(cc, "%s\n", code);

  if ( fp < 0 ) {
    perror("fprintf");
  }

  if ( 0 > pclose(cc) ) {
    perror("pclose");
  }

  safefree(cmdline);
  return fp;
}
