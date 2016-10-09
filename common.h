#ifdef GCC
#line 2 "common"
#endif

#pragma once
#define _GNU_SOURCE

#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEC_BASE    10
#define DEC_DIGITS  "0123456789"
#define ULL_DIGITS  20
#define NUM_PROBS   5
#define MAX_STR_LEN 4096
#define SHORT_INSTR 256

#ifndef NODEBUG
#define DEBUG
#endif

#ifdef DEBUG
  #define dbg_prn(...) printf(__VA_ARGS__)
  #define pfn(file, line, func) printf("\n\033[30;1m%s#%d:%s\033[0m\n", file, line, func)
  #define __PURE_FUNC
  #define __CONST_FUNC
  #define report_ctor(obj) \
    static size_t uid = 0;              \
    ++uid;                              \
    (obj)->uid = uid;               \
    printf("ctor %s #%zu\n", #obj, uid)

  #define report_dtor(obj) printf("dtor %s #%zu\n", #obj, obj->uid)
#else
  #define dbg_prn(...)
  #define pfn(file, line, func)
  #define __PURE_FUNC  __attribute_pure__
  #define __CONST_FUNC __attribute_const__
  #define report_ctor(x, y)
  #define report_dtor(x, y)
#endif

#define dealloc_printf(x) do { printf("%s\n", (x)); safefree((x)); } while (0);

#undef strdup
#pragma GCC poison strcpy strdup sprintf gets atoi // poison unsafe functions

// utils
char* make_empty_str (void);

char* str_reverse (const char*  const str);
void    str_chomp (char* str);
char*      readln (const size_t len);
char*    str_copy (const char* str);
char*      str_rm (
  const char*   str,
  const char*   omit,
        size_t* out_len
);
char** str_split (
  const char*   str,
  const char    delim,
        size_t* out_len
);
char*  str_repeat (
  const char* const str,
  const size_t      times,
  size_t*           out_len
);
char* concat_lines (
        char** string_lines,
  const size_t lines_len,
  const size_t total_len
);

bool     isEOL (const char* const str);
bool  getint64 (int64_t*    restrict dest);
bool getuint64 (uint64_t*   restrict dest);

uint64_t        pow_uint64 (uint64_t in, uint64_t power);
uint64_t* str_to_ull_array (
  const char* const str,
  const size_t      len,
  const char* const remove_at,
  const char        split_at,
        size_t*     out_len
);

size_t   str_count (
  const char* const haystack,
  const char* const needle
);

size_t safestrnlen (const char* const str);
__attribute_const__
size_t   safe_usub (size_t x, size_t y);

void free_ptr_array (void**, size_t);
void      _safefree (void* ptr,  uint64_t lineno);
void*   _safemalloc (size_t len, uint64_t lineno);

#define safefree(x)   _safefree(x, __LINE__)
#define safemalloc(x) _safemalloc(x, __LINE__)


/*
  "If ptr is a null pointer, no action shall occur." -- POSIX.1-2008
  But if I'm free()-ing a pointer I already free()-d, then something is wrong.
*/
// _safefree -- free a pointer to allocated memory or die freeing NULL
void _safefree (void* ptr, uint64_t lineno) {
  pfn(__FILE__, __LINE__, __func__);

  if (!ptr) {
    printf("You fool! You have tried to free() a null pointer! (line %" PRIu64 ")\n", lineno);
    assert(ptr);
  } else {
    free(ptr);
  }
}

// _safemalloc -- allocate memory or die
void* _safemalloc (size_t len, uint64_t lineno) {
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

  for (size_t i = 0; i < len; i++) {
    safefree(ptr[i]);
  }
  safefree(ptr);
}

// safe_usub -- perform safe unsigned subtraction
__attribute_const__
size_t safe_usub (size_t x, size_t y) {
  pfn(__FILE__, __LINE__, __func__);

  return x > y ? x - y : y - x ;
}

char* str_reverse (const char* const str) {
  pfn(__FILE__, __LINE__, __func__);

  if (!str) { return NULL; }

  size_t len = safestrnlen(str);
  char*  new = safemalloc( sizeof(char) * len );

  size_t i;
  for (i = 0; i < len; i++) {
    new[i] = str[ safe_usub(i + 1, len) ];
  }

  return new;
}

// chomp -- cuts the last char (a newline?) from a string
void str_chomp (char* str) {
  pfn(__FILE__, __LINE__, __func__);

  if (str && (strchr(str, '\n') != NULL) ) {
    str[ strcspn(str, "\n") ] = 0;
  }
}

// readln -- returns a line of chomped STDIN, or NULL on blank line / EOF
char* readln (const size_t len) {
  pfn(__FILE__, __LINE__, __func__);

  char *ret,
       *buf = safemalloc( sizeof(char) * len );

  ret = fgets(buf, len > INT_MAX ? INT_MAX : (int) len, stdin);

  if ( ret == NULL ) {
    safefree(buf);
    char* out = safemalloc(2);
    snprintf(out, 2, "%c", '\04');
    return out;
  }

  str_chomp(buf);

  return buf;
}

char* str_copy (const char* str) {
  pfn(__FILE__, __LINE__, __func__);

  size_t len = safestrnlen(str);
  char* new = safemalloc(sizeof (char) * len);

  for (size_t i = 0; i < len; i++) {
    new[i] = str[i];
  }
  return new;
}

char** str_split (
  const char*   str,
  const char    delim,
        size_t* out_len
) {
  pfn(__FILE__, __LINE__, __func__);

  char delim_str[2],
       *scopy = strndup(str, MAX_STR_LEN);

  snprintf(delim_str, 2, "%c", delim);


  size_t len = safestrnlen(str);
  size_t num_delim = str_count(str, delim_str);

  char** new;

  if (0 == num_delim) {
    // no separator found
    new      = safemalloc( sizeof (char *) );
    new[0]   = scopy;
    *out_len = 1;

  } else if (1 == num_delim) {

    // one separator
    new = safemalloc( sizeof (char *) * 2 );
    size_t i;
    for (
      i = 0;
      (i < len) && str[i] != delim;
      i++
    );
    scopy[i] = '\0';
    new[0] = scopy;
    new[1] = &(scopy[i + 1]);
    *out_len = 2;

  } else {
    // separators found, alloc two more
    size_t num_pieces = num_delim + 1;

    new = safemalloc( sizeof (char *) * num_pieces );

    size_t i;
    char* token;

    for (i = 0;
      (token = strsep(&scopy, delim_str)) != NULL;
      i++
    ) {
      dbg_prn("i: %zu, token: %s\n", i, token);
      new[i] = token;
    }

    *out_len = i;

  }

  return new;
}

/*
  str_rm -- remove all instances of the contents of *omit from str and return new memory
  result must be freed!
*/
char*     str_rm (
  const char*   str,
  const char*   omit,
        size_t* out_len
) {
  pfn(__FILE__, __LINE__, __func__);

  size_t len_str = safestrnlen(str);
  // malloc one more than exactly enough for the new string
  const size_t len_new = ( ( ( sizeof(char) * len_str ) - str_count(str, omit) ) );
  char*            new = safemalloc( len_new + 1 );

  char c[3];

  size_t i, j;
  for (i = 0, j = 0; j < len_new; i++) {
    snprintf(c, 3, "%c%c", str[i], 0);
    if (!str_count(omit, c)) {
      new[j] = str[i];
      j++;
    }
  }
  new[j] = 0;
  *out_len = len_new;
  assert(out_len != NULL);
  return new;
}

__PURE_FUNC
size_t str_count (
  const char*   haystack,
  const char*   needles
) {
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

  size_t in_len = safestrnlen(in_str);
  *out_len = in_len * times;

  char *out = safemalloc( 1 + *out_len ),
       *bufptr = out;

  for (size_t i = 0; i < *out_len; i++) {
    bufptr += snprintf(bufptr, in_len + 1, "%s", in_str);
  }

  return out;
}

// safestrnlen -- find the length of a string, defaulting to SHORT_INSTR, without segfaulting
__PURE_FUNC
size_t safestrnlen (const char* str) {
  pfn(__FILE__, __LINE__, __func__);

  // it seems gnu strnlen segfaults on null pointer
  return str != NULL? strnlen(str, SHORT_INSTR) : 0;
}

__PURE_FUNC
bool isEOL (const char* str) {
  pfn(__FILE__, __LINE__, __func__);

  return !str || !safestrnlen(str) || str[0] == '\n';
}

bool getint64 (int64_t* restrict dest) {
  pfn(__FILE__, __LINE__, __func__);

  char* in = readln(ULL_DIGITS);
  if (!in) {
    return false;
  }
  *dest    = strtoll(in, NULL, DEC_BASE);
  assert(dest != NULL);
  safefree(in);
  return true;
}

bool getuint64 (uint64_t* restrict dest) {
  pfn(__FILE__, __LINE__, __func__);

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
  pfn(__FILE__, __LINE__, __func__);

  uint64_t out = 1;
  for (uint64_t i = 0; i < power; i++) {
    out *= in;
  }
  return out;
}

char* concat_lines (char** string_lines, const size_t lines_len, const size_t total_len) {
  pfn(__FILE__, __LINE__, __func__);

  char *output = safemalloc( (sizeof (char) * total_len) + 1),
       *bufptr = output;

  for (size_t i = 0; i < lines_len; i++) {
    char* tl = string_lines[i];
    dbg_prn("tl: %s len: %zu", tl, safestrnlen(tl));
    bufptr += snprintf(bufptr, safestrnlen(tl) + 2, "%s ", tl);
  }
  printf("o: %s total_len: %zu\n", output, total_len);
  //output[total_len] = '\0';

  free_ptr_array( (void **) string_lines, lines_len);

  return output;
}

char* make_empty_str (void) {
  pfn(__FILE__, __LINE__, __func__);

  char* out = safemalloc(1);
  snprintf(out, 1, "%s", "");
  return out;
}
