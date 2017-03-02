#pragma once

// iff funcdbg is given, then show stacktraces
#ifdef FUNCDBG
  #define IFUNCDBG 1
#else // otherwise don't
  #define IFUNCDBG 0
#endif

// if nodebug is NOT GIVEN!!
#ifndef NODEBUG
  #define DEBUG // define debug for dbg_prn, et al
#endif

// iff cdtordbg is given, then show de/con -structors
#ifdef CDTORDBG
  #define ICDTORDBG
#endif

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
#include <stdarg.h>
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

#undef strdup

#ifdef GCC_COMPAT
  #pragma GCC poison strcpy strdup sprintf gets atoi // poison unsafe functions
#endif

#define pure  __attribute_pure__
#define const_func __attribute_const__
#define warn_unused __attribute__((warn_unused_result))
#define likely(x) (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))

/*
#define pure
#define const_func
#define warn_unused
#define likely(x)
#define unlikely(x)

*/
#ifdef DEBUG
  #define dbg_prn(fmt, ...) fflush(stdout); printf("|\033[35;1mDEBUG\033[0m|" fmt, __VA_ARGS__)
#else
  #define dbg_prn(...)
#endif

#if IFUNCDBG == 1
  #define _printfunc(file, line, func) printf("\n|\033[36;1mCALLF\033[0m|\033[30;1m%s#%d:\033[36;1m%s\033[0m\n", \
    file, line, func)
  #define pfn() _printfunc(__FILE__, __LINE__, __func__)
#else
  #define pfn()
#endif


#define dealloc_printf(x) do { printf("%s\n", (x)); safefree((x)); } while (0);

#define str_append(dest, len, fmt, ...) (dest) += snprintf((dest), (len), (fmt), (__VA_ARGS__));


#ifdef ICDTORDBG
  #define report_ctor(obj) static size_t uid = 0; dbg_prn("\x1b[33;1mctor \x1b[30;1m%s #%zu\x1b[0m\n", #obj, (obj)->uid = uid++)

  #define report_dtor(obj) dbg_prn("\x1b[33;1mdtor \x1b[30;1m%s #%zu\x1b[0m\n", #obj, obj->uid)
#else 
  #define report_ctor(obj)
  #define report_dtor(obj)
#endif

#ifdef __cplusplus
  #define _Static_assert(expr, diag) static_assert(expr, diag)
  #define typeof(x) decltype(x)
  #define infer auto
#else
  #ifdef GCC_COMPAT
    #define infer __auto_type
  #else
    #error "can't use GNU auto-type"
  #endif
#endif


// utils
char*       strchr_c (const char* const str, const char c);
char*      strncat_c (const char* const a, const char* const b, const size_t maxlen);
char*       vstrncat (const size_t argc, ...);
char*     vstrncat_c (const size_t argc, ...);
char* make_empty_str (void);
void       str_chomp (char* str);
char*         readln (const size_t len);
char*   input_prompt (const char* const prompt, const size_t len, const char* const other);
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
ssize_t str_issubstring (const char* const a, const char* const b);

void free_ptr_array (void** array, const size_t len);
void      _safefree (void*        ptr, const uint64_t lineno, const char* const fname);
void _safefree_args (const uint64_t lineno, const char* const fname, const size_t argc, ...);
void*   _safemalloc (const size_t len, const uint64_t lineno, const char* const fname);
void*  _saferealloc (void* ptr, const size_t len, uint64_t lineno, const char* const fname);
void*   _safecalloc (const size_t nmemb, const size_t len, uint64_t lineno, const char* const fname);

#define safefree(x)         _safefree((x), __LINE__, __func__)
#define safefree_args(n, ...) _safefree_args(__LINE__, __func__, n, __VA_ARGS__)
#define safemalloc(x)     _safemalloc((x), __LINE__, __func__)
#define saferealloc(p,s) _saferealloc((p), (s), __LINE__, __func__)
#define safecalloc(n,l)   _safecalloc((n), (l), __LINE__, __func__)

#define alloc(type, count) (type *) safemalloc(sizeof (type) * count)

#define fdredir(fd, file) fd = freopen(file, "w", fd)

pure const_func
size_t signed2un (const ssize_t val) {
  return val < 0 ? 0 : (size_t) val;
}

pure const_func
ssize_t un2signed (const size_t val) {
  return (ssize_t) (val > (SIZE_MAX / 2) ? SIZE_MAX / 2 : val);
}

#define define_signed2un_type(type, other) \
  pure const_func \
  other signed2un_ ## type ## 2 ## other (const type val) { \
    return val < 0 ? 0 : (other) val; \
  } \
  int __IAMALSONOTHING ## type ## other

#define define_un2signed_type(type, other, type_maxvalue) \
  pure const_func \
  other un2signed_ ## type ## 2 ## other (const type val) { \
    return (other) ((val) > (type_maxvalue / 2) ? (type_maxvalue) / 2 : val) \
  } \
  int __IAMNOTHING ## type ## other

pure const_func
size_t usub (const size_t a, const size_t b) {
  return signed2un(un2signed(a) - un2signed(b));
}

pure const_func
size_t  udifference (const size_t x, const size_t y) {
  return (x < y ? y - x : x - y);
}

/*
  "If ptr is a null pointer, no action shall occur." -- POSIX.1-2008
  But if I'm free()-ing a pointer I already free()-d, then something is wrong.
*/
// _safefree -- free a pointer to allocated memory or die freeing NULL
void _safefree (void* ptr, const uint64_t lineno, const char* const fname) {
  pfn();

  if (NULL == ptr) {
    printf("You fool! You have tried to free() a null pointer! (line %" PRIu64 " func %s)\n", lineno, fname);
    assert(NULL != ptr);
  } else {
    free(ptr);
  }
}

void _safefree_args (const uint64_t lineno, const char* const fname, const size_t argc, ...) {
  va_list vl;
  va_start(vl, argc);

  for (size_t i = 0; i < argc; i++) {
    void* ptr = va_arg(vl, void*);

    if (NULL == ptr) {
      printf(
        "You fool! You have tried to free() a null pointer!"
        " (line %" PRIu64 " func %s, arg #%zu to safefree_args)\n",
        lineno, fname, i
      );
      assert(NULL != ptr);
    } else {
      free(ptr);
    }

  }

  va_end(vl);
}

// _safemalloc -- allocate memory or die
void* _safemalloc (const size_t len, const uint64_t lineno, const char* const fname) {
  pfn();

  void* mem = malloc(len);
  if (!mem) {
    printf("Couldn't malloc() %zu bytes (perhaps you have run out of memory?) (line %" PRIu64 " func %s)\n", len, lineno, fname);
    assert(mem);
  }
  if (ENOMEM == errno) {
    perror("safefree");
    abort();
  }
  return mem;
}

void* _saferealloc (void* ptr, const size_t len, uint64_t lineno, const char* const fname) {
  pfn();

  //dbg_prn("reallocing %zu byte%s\n", len, len != 1 ? "s" : "");
  (void) fname, (void) lineno;
  void* mem = realloc(ptr, len);
  if (ENOMEM == errno) {
    perror("saferealloc");
    abort();
  }
  return mem;
}

void* _safecalloc (const size_t nmemb, const size_t len, uint64_t lineno, const char* const fname) {
  pfn();

  (void) fname, (void) lineno;
  void* mem = calloc(nmemb, len);
  if (ENOMEM == errno) {
    perror("safecalloc");
    abort();
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
  char* nw = strndup(str, safestrnlen(str));
  while ( (++*nw) != c);
  return nw;
}

char* strncat_c (const char* const a, const char* const b, const size_t maxlen) {
  size_t tlen   = safestrnlen(a) + safestrnlen(b),
         outlen = (tlen > maxlen ? maxlen : tlen) - 1;

  char* outbuf = alloc(char, outlen);

  snprintf(outbuf, outlen, "%s%s", a, b);

  return outbuf;
}

/*
  a variadic strncat that frees its arguments
*/
char*       vstrncat (const size_t argc, ...) {
  va_list vl;
  va_start(vl, argc);

  size_t tlen = 0;
  char** outbuf = alloc(char *, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully thisp just takes the address
    char** v = alloc(char *, 1);
    *v       = va_arg(vl, char*);
    size_t l = safestrnlen(*v);

    outbuf[i] = strndup(*v, l);
    tlen     += l;

    safefree(*v), safefree(v);
  }

  va_end(vl);

  return concat_lines(outbuf, argc, tlen);
}

/*
  doesn't free its const char* const arguments hence *_c
*/
char*     vstrncat_c (const size_t argc, ...) {
  va_list vl;
  va_start(vl, argc);

  size_t tlen = 0;
  char** outbuf = alloc(char *, argc);

  for (size_t i = 0; i < argc; i++) {
    // hopefully thisp just takes the address
    char*  v = va_arg(vl, char*);
    size_t l = safestrnlen(v);

    outbuf[i] = strndup(v, l);
    tlen += l;

    safefree(v);
  }

  va_end(vl);

  return concat_lines(outbuf, argc, tlen);
}

ssize_t str_issubstring (const char* const a, const char* const b) {
  if ( NULL == a ) {
    if ( NULL == b ) {
      return 0;
    }
    return -1;
  }

  size_t lena = safestrnlen(a),
         lenb = safestrnlen(b);

  if ( ( !str_count(a, "\0") ) || (!str_count(b, "\0")) ) {
    errno = EINVAL;
    perror(__func__);
    assert (false);
  }

  ssize_t begin = -1, end;

  char *ca = strndup(a, lena),
       *cb = strndup(b, lenb);

  while ( (*++ca) != *cb ) {
    ++begin;
  }
  end = begin;

  while ( *ca == *cb ) {
    ++ca, ++cb, ++end;
  }

  if ( signed2un(end) != lenb ) {
    begin = -1;
  }

  safefree(ca), safefree(cb);

  return begin;
}

char* str_reverse (const char* const str) {
  pfn();

  if (!str) { return NULL; }

  size_t len = safestrnlen(str);
  char* newp = (typeof(newp)) safemalloc( sizeof(char) * len );

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
    *buf = (typeof(buf)) safemalloc( sizeof(char) * len ),
    *ret = fgets(buf, len > INT_MAX ? INT_MAX : (int) len, stdin);

  if ( NULL == ret ) {
    safefree(buf);
    buf = alloc(char, 2);
    snprintf(buf, 2, "%c", '\4');

  } else {
    str_chomp(buf);
  }

  assert(NULL != buf);

  return buf;
}

char* input_prompt (const char* const prompt, const size_t len, char const* const retry_prt) {
  printf("%s", prompt);

  char* buf;

  const char* const retry = NULL == retry_prt ? "Retry (bad input): " : retry_prt;

  while ( true ) {

    buf = readln(len);

    if (4 == buf[0]) { safefree(buf); return make_empty_str(); }
    if ( buf[0] ) { return buf; }

    safefree(buf);

    printf("%s", retry);

  }
}

char* str_copy (const char* const str) {
  pfn();

  size_t len = safestrnlen(str);
  char* newp = alloc(char, len);

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

  if (! str[0]) {
    errno = EINVAL;
    return NULL;
  }

  char delim_str[2],
       *scopy = strndup(str, MAX_STR_LEN);

  snprintf(delim_str, 2, "%c", delim);


  size_t       len = safestrnlen(str);
  size_t num_delim = str_count(str, delim_str);

  char** newp;

  if (0 == num_delim) {
    // no separator found
    newp      = alloc(char *, 1);
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

     newp = alloc(char *, num_pieces);

    size_t i;
    char* token;

    for (
      i = 0;
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
  char*            newp = alloc(char, len_newp + 1);

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
  return newp;
}

pure
size_t str_count (
  const char*   haystack,
  const char*   needles
) {
  pfn();

  size_t s = 0;
  size_t len_haystack = safestrnlen(haystack),
         len_needles = safestrnlen(needles);

  for (size_t i = 0; i < len_haystack; i++) {
    for (size_t h = 0; h < len_needles; h++) {
      if (haystack[i] == needles[h]) {
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

  char *out = alloc(char, 1 + *out_len),
    *bufptr = out;

  for (size_t i = 0; i < *out_len; i++) {
    str_append(bufptr, in_len + 1, "%s", in_str);
  }

  return out;
}

// safestrnlen -- find the length of a string, defaulting to SHORT_INSTR, without segfaulting
pure
size_t safestrnlen (const char* const str) {
  pfn();

  // it seems gnu strnlen segfaults on null pointer
  return str != NULL? strnlen(str, SHORT_INSTR) : 0;
}

pure
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
  safefree(in);
  return true;
}

const_func pure
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

  char *output = alloc(char, total_len + 1),
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

  char*  out = alloc(char, 1);
  snprintf(out, 1, "%s", "");
  return out;
}
