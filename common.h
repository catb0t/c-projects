#pragma once

// unistd.h
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux__)

  #define HAVE_POSIX

#elif defined(_WIN32)

  //#pragma message "Windows"
  #include <windows.h>
  #define WINDOWS
  #define NO_POSIX

#endif

// clang defines all the macros gcc does but gcc doesn't define __clang__
#if !defined(__clang__) && defined(__GNUC__)

  #define GCC
  #define COMPILER "GCC"

#elif defined(__GNUC__) && defined(__clang__)

  #define CLANG
  #define COMPILER "Clang"

#else
  // Something else (?)
  #define NONGNU
  #define COMPILER "nongnu"
#endif

#if defined(GCC) || defined(CLANG)
  #define GCC_COMPAT
#endif

#ifdef GCC
#line __LINE__ "common"
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEC_BASE    10
#define DEC_DIGITS  "0123456789"
#define MAX_STR_LEN 4096
#define SHORT_INSTR 256
#define ULL_DIGITS  20

#ifndef __GLIBC__

  #include "gnustring.h"
  #define NOGLIBC
  extern char* strndup(const char* const, const size_t);
  typedef uint64_t u_int64_t;
  typedef uint32_t u_int32_t;

#endif

#ifdef GCC_COMPAT
  #pragma GCC poison strcpy strdup sprintf gets atoi // poison unsafe functions

  #ifndef NOGLIBC
    #define __PURE_FUNC  __attribute_pure__
    #define __CONST_FUNC __attribute_const__

  #else
    #define __PURE_FUNC
    #define __CONST_FUNC
  #endif
#endif

#ifndef NODEBUG
  #define DEBUG
#endif

#ifdef DEBUG
  #define dbg_prn(...) printf(__VA_ARGS__)

  #define _printfunc(file, line, func) printf("\n\033[30;1m%s#%d:%s\033[0m\n", \
    file, line, func)
  #define pfn() _printfunc(__FILE__, __LINE__, __func__)
#else
  #define dbg_prn(...)
  #define pfn()
#endif

#define dealloc_printf(x) do { printf("%s\n", (x)); safefree((x)); } while (0);

#define str_append(dest, len, fmt, ...) (dest) += snprintf((dest), (len), (fmt), (__VA_ARGS__));

#define report_ctor(obj) \
  static size_t uid = 0; \
  ++uid;                 \
  (obj)->uid = uid;      \
  dbg_prn("ctor %s #%zu\n", #obj, uid)

#define report_dtor(obj) dbg_prn("dtor %s #%zu\n", #obj, obj->uid)

#ifdef __cplusplus
  #define _Static_assert(expr, diag) static_assert(expr, diag)
  #define typeof(x) decltype(x)
#endif

// utils
char*       strchr_c (const char* const str, const char c);
char* make_empty_str (void);
void       str_chomp (char* str);
char*         readln (const size_t len);
char*    str_reverse (const char* const str);
char*       str_copy (const char* const str);
char*     str_repeat (const char* const str, const size_t times,     size_t* out_len);
char**     str_split (const char* const str, const char   delim,     size_t* out_len);
char*         str_rm (const char* const str, const char* const omit, size_t* out_len);
char*   concat_lines (char** string_lines,   const size_t lines_len, const size_t total_len);

bool     isEOL (const char* const str);
bool  getint64 (int64_t*    dest);
bool getuint64 (uint64_t*   dest);

uint64_t        pow_uint64 (uint64_t in, uint64_t power);
uint64_t* str_to_ull_array (
  const char* const str,
  const size_t      len,
  const char* const remove_at,
  const char        split_at,
        size_t*     out_len
);

size_t   str_count (const char* const haystack, const char* const needle);
size_t safestrnlen (const char* const str);
size_t udifference (const size_t x, const size_t y);
size_t        usub (const size_t a, const size_t b);
size_t   signed2un (const ssize_t val);
ssize_t  un2signed (const  size_t val);

void free_ptr_array (void** array, const size_t len);
void      _safefree (void*    ptr, const uint64_t lineno);
void*   _safemalloc (size_t   len, const uint64_t lineno);


#define safefree(x)     _safefree(x, __LINE__)
#define safemalloc(x) _safemalloc(x, __LINE__)

__PURE_FUNC __CONST_FUNC
size_t signed2un (const ssize_t val) {
  return val < 0 ? 0 : (size_t) val;
}

__PURE_FUNC __CONST_FUNC
ssize_t un2signed (const size_t val) {
  return (ssize_t) (val > (SIZE_MAX / 2) ? SIZE_MAX / 2 : val);
}

__PURE_FUNC __CONST_FUNC
size_t usub (const size_t a, const size_t b) {

  return signed2un(un2signed(a) - un2signed(b));
}

__PURE_FUNC __CONST_FUNC
size_t  udifference (const size_t x, const size_t y) {
  return (x < y ? y - x : x - y);
}

/*
  "If ptr is a null pointer, no action shall occur." -- POSIX.1-2008
  But if I'm free()-ing a pointer I already free()-d, then something is wrong.
*/
// _safefree -- free a pointer to allocated memory or die freeing NULL
void _safefree (void* ptr, uint64_t lineno) {
  pfn();

  if (NULL == ptr) {
    printf("You fool! You have tried to free() a null pointer! (line %" PRIu64 ")\n", lineno);
    assert(NULL != ptr);
  } else {
    free(ptr);
  }
}

// _safemalloc -- allocate memory or die
void* _safemalloc (size_t len, uint64_t lineno) {
  pfn();

  void* mem = malloc(len);
  if (!mem) {
    printf("Couldn't malloc() %zu bytes (perhaps you have run out of memory?) (line %" PRIu64 ")\n", len, lineno);
    assert(mem);
  }
  if (ENOMEM == errno) {
    perror("safefree");
  }
  return mem;
}

void free_ptr_array (void** ptr, const size_t len) {
  pfn();

  for (size_t i = 0; i < len; i++) {
    safefree(ptr[i]);
  }
  safefree(ptr);
}

char* strchr_c (const char* const str, const char c) {
  char* nw = (typeof(nw)) strndup (str, safestrnlen(str));
  while ( (++*nw) != c);
  return nw;
}

char* str_reverse (const char* const str) {
  pfn();

  if (!str) { return NULL; }

  size_t len = safestrnlen(str);
  char*   newp = (typeof(newp)) safemalloc( sizeof(char) * len );

  size_t i;
  for (i = 0; i < len; i++) {
    newp[i] = str[ udifference(i + 1, len) ];
  }

  return newp;
}

// chomp -- cuts the last char (a newpline?) from a string
void str_chomp (char* str) {
  pfn();

  if (str && (strchr(str, '\n') != NULL) ) {
    str[ strcspn(str, "\n") ] = 0;
  }
}

// readln -- returns a line of chomped STDIN, or NULL on blank line / EOF
char* readln (const size_t len) {
  pfn();

  char
    *ret,
    *buf = (typeof(buf)) safemalloc( sizeof(char) * len );

  ret = fgets(buf, len > INT_MAX ? INT_MAX : (int) len, stdin);

  if ( ret == NULL ) {
    safefree(buf);
    char*  out = (typeof(out)) safemalloc(2);
    snprintf(out, 2, "%c", '\04');
    return out;
  }

  str_chomp(buf);

  return buf;
}

char* str_copy (const char* str) {
  pfn();

  size_t len = safestrnlen(str);
  char*  newp = (typeof(newp)) safemalloc(sizeof (char) * len);

  for (size_t i = 0; i < len; i++) {
    newp[i] = str[i];
  }
  return newp;
}

char** str_split (
  const char*   str,
  const char    delim,
        size_t* out_len
) {
  pfn();

  char delim_str[2],
       *scopy = strndup(str, MAX_STR_LEN);

  snprintf(delim_str, 2, "%c", delim);


  size_t len = safestrnlen(str);
  size_t num_delim = str_count(str, delim_str);

  char** newp;

  if (0 == num_delim) {
    // no separator found
    newp      = (typeof(newp)) safemalloc( sizeof (char *) );
    newp[0]   = scopy;
    *out_len = 1;

  } else if (1 == num_delim) {

    // one separator
     newp = (typeof(newp)) safemalloc( sizeof (char *) * 2 );
    size_t i;
    for (
      i = 0;
      (i < len) && str[i] != delim;
      i++
    );
    scopy[i] = '\0';
    newp[0] = scopy;
    newp[1] = &(scopy[i + 1]);
    *out_len = 2;

  } else {
    // separators found, alloc two more
    size_t num_pieces = num_delim + 1;

     newp = (typeof(newp)) safemalloc( sizeof (char *) * num_pieces );

    size_t i;
    char* token;

    for (i = 0;
      (token = strsep(&scopy, delim_str)) != NULL;
      i++
    ) {
      dbg_prn("i: %zu, token: %s\n", i, token);
      newp[i] = token;
    }

    *out_len = i;

  }

  return newp;
}

/*
  str_rm -- remove all instances of the contents of *omit from str and return newp memory
  result must be freed!
*/
char*     str_rm (
  const char*   str,
  const char*   omit,
        size_t* out_len
) {
  pfn();

  size_t len_str = safestrnlen(str);
  // malloc one more than exactly enough for the newp string
  const size_t len_newp = ( ( ( sizeof(char) * len_str ) - str_count(str, omit) ) );
  char*             newp = (typeof(newp)) safemalloc( len_newp + 1 );

  char c[3];

  size_t i, j;
  for (i = 0, j = 0; j < len_newp; i++) {
    snprintf(c, 3, "%c%c", str[i], 0);
    if (!str_count(omit, c)) {
      newp[j] = str[i];
      j++;
    }
  }
  newp[j] = 0;
  *out_len = len_newp;
  assert(out_len != NULL);
  return newp;
}

__PURE_FUNC
size_t str_count (
  const char*   haystack,
  const char*   needles
) {
  pfn();

  size_t s = 0;
  size_t len_haystack = safestrnlen(haystack),
         len_needles = safestrnlen(needles);

  for (size_t i = 0; i < len_haystack; i++) {
    char c = haystack[i];
    for (size_t h = 0; h < len_needles; h++) {
      if (c == needles[h]) {
         s++;
       }
    }
  }
  return s;
}

char*  str_repeat (
  const char* const in_str,
  const size_t      times,
  size_t*           out_len
) {
  pfn();

  size_t in_len = safestrnlen(in_str);
  *out_len = in_len * times;

  char *out = (typeof(out)) safemalloc( 1 + *out_len ),
       *bufptr = out;

  for (size_t i = 0; i < *out_len; i++) {
    str_append(bufptr, in_len + 1, "%s", in_str);
  }

  return out;
}

// safestrnlen -- find the length of a string, defaulting to SHORT_INSTR, without segfaulting
__PURE_FUNC
size_t safestrnlen (const char* const str) {
  pfn();

  // it seems gnu strnlen segfaults on null pointer
  return str != NULL? strnlen(str, SHORT_INSTR) : 0;
}

__PURE_FUNC
bool isEOL (const char* str) {
  pfn();

  return !str || !safestrnlen(str) || str[0] == '\n';
}

bool getint64 (int64_t* dest) {
  pfn();

  char* in = readln(ULL_DIGITS);
  if (!in) {
    return false;
  }
  *dest    = strtoll(in, NULL, DEC_BASE);
  assert(dest != NULL);
  safefree(in);
  return true;
}

bool getuint64 (uint64_t* dest) {
  pfn();

  char* in = readln(ULL_DIGITS);
  if (!in) {
    return false;
  }
  *dest = strtoull(in, NULL, DEC_BASE);
  assert(dest != NULL);
  safefree(in);
  return true;
}

__CONST_FUNC __PURE_FUNC
uint64_t pow_uint64 (const uint64_t in, const uint64_t power) {
  pfn();

  uint64_t out = 1;
  for (uint64_t i = 0; i < power; i++) {
    out *= in;
  }
  return out;
}

char* concat_lines (char** string_lines, const size_t lines_len, const size_t total_len) {
  pfn();

  char *output = (typeof(output)) safemalloc( (sizeof (char) * total_len) + 1),
       *bufptr = output;

  for (size_t i = 0; i < lines_len; i++) {
    char* tl = string_lines[i];
    dbg_prn("tl: %s len: %zu", tl, safestrnlen(tl));
    str_append(bufptr, safestrnlen(tl) + 2, "%s ", tl);
  }
  printf("o: %s total_len: %zu\n", output, total_len);
  //output[total_len] = '\0';

  free_ptr_array( (void **) string_lines, lines_len);

  return output;
}

char* make_empty_str (void) {
  pfn();

  char*  out = (typeof(out)) safemalloc(1);
  snprintf(out, 1, "%s", "");
  return out;
}
