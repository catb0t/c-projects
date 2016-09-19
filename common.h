#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define DEC_BASE    10
#define DEC_DIGITS  "0123456789"
#define INT_DIGITS  10
#define ULL_DIGITS  20
#define NUM_PROBS   5
#define MAX_STR_LEN 1024
#define SHORT_INSTR 256

// utils
char* str_reverse (const char*  const str);
char*   str_chomp (const char*  const str);
char*      readln (const size_t len);
char*      str_rm (
  const char* const str,
  const size_t      len_str,
  const char* const omit,
  const size_t      len_omit,
        size_t*     out_len
);
char**  str_split (
  const char*   const str,
  const size_t  len,
  const char    delim,
        size_t* out_len
);

bool     isEOL (const char* const str);
bool  getint64 (int64_t*    restrict dest);
bool getuint64 (uint64_t*   restrict dest);

uint64_t pow_uint64 (uint64_t in, uint64_t power);
uint64_t* str_to_ull_array (
  const char* const str,
  const size_t      len,
  const char* const remove_at,
  const char        split_at,
        size_t*     out_len
);

size_t   str_count (
  const char* const haystack,
  const size_t      len_haystack,
  const char* const needle,
  const size_t      len_needle
);
size_t safestrnlen (const char* const str);
size_t   safe_usub (size_t x, size_t y);

void      _safefree (void* ptr,  uint64_t lineno);
void*   _safemalloc (size_t len, uint64_t lineno);

#define safefree(x)   _safefree(x, __LINE__)
#define safemalloc(x) _safemalloc(x, __LINE__)


// IMPLEMENTATIONS
void   runMathMagic (void);


/*
  "If ptr is a null pointer, no action shall occur." -- POSIX.1-2008
  But if I'm free()-ing a pointer I already free()-d, then something is wrong.
*/
// _safefree -- free a pointer to allocated memory or die freeing NULL
void _safefree (void* ptr, uint64_t lineno) {
  if (!ptr) {
    printf("You fool! You have tried to free() a null pointer! (line %" PRIu64 ")\n", lineno);
    assert(ptr);
  } else {
    free(ptr);
  }
}

// _safemalloc -- allocate memory or die
void* _safemalloc (size_t len, uint64_t lineno) {
  void* mem = malloc(len);
  if (!mem) {
    printf("Couldn't malloc() %zu bytes (perhaps you have run out of memory?) (line %" PRIu64 ")\n", len, lineno);
    assert(mem);
  }
  return mem;
}


// safe_usub -- perform safe unsigned subtraction
size_t safe_usub (size_t x, size_t y) {
  return x > y ? x - y : y - x ;
}

char* str_reverse (const char* const str) {
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
char* str_chomp (const char* str) {
  char* new = strndup(str, MAX_STR_LEN);
  new[ safestrnlen(new) - 1 ] = 0;
  return new;
}

// readln -- returns a line of chomped STDIN, or NULL on blank line / EOF
char* readln (const size_t len) {
  char *chomped_buf,
       *buf = safemalloc( sizeof(char) * len );
  fgets(buf, MAX_STR_LEN, stdin);
  chomped_buf = str_chomp(buf);
  safefree(buf);
  if (!isEOL(chomped_buf)) {
    return chomped_buf;
  }
  return NULL;
}

char** str_split (
  const char*   str,
  const size_t  len,
  const char    delim,
        size_t* out_len
) {
  char delim_str[2],
      *str_copy = strndup(str, MAX_STR_LEN);

  sprintf(delim_str, "%c%c", delim, 0);

  size_t num_delim = str_count(str, len, delim_str, 1);

  char** new;

  if (num_delim < 2) {
    // no separator found
    new      = safemalloc( sizeof(char*) * 2 );
    new[0]   = str_copy;
    new[1]   = 0;
    *out_len = 1;

  } else {
    // separator found
    new = safemalloc( ( sizeof(char*) * num_delim ) + 1 );

    size_t i;
    char* token;

    for (i = 0; (token = strsep(&str_copy, delim_str)) != NULL; i++) {
      new[i] = token;
    }

    new[i + 1] = 0;
    *out_len   = i;
  }

  assert(out_len != NULL);
  return new;
}

/*
  str_rm -- remove all instances of the contents of *omit from str and return new memory
  result must be freed!
*/
char*     str_rm (
  const char*   str,
  const size_t  len_str,
  const char*   omit,
  const size_t  len_omit,
        size_t* out_len
) {
  // malloc one more than exactly enough for the new string
  const size_t len_new = ( ( ( sizeof(char) * len_str ) - str_count(str, len_str, omit, len_omit) ) );
  char*            new = safemalloc( len_new + 1 );

  char c[2];

  size_t i, j;
  for (i = 0, j = 0; j < len_new; i++) {
    sprintf(c, "%c%c", str[i], 0);
    if (!str_count(omit, len_omit, c, 1)) {
      new[j] = str[i];
      j++;
    }
  }
  new[j] = 0;
  *out_len = len_new;
  assert(out_len != NULL);
  return new;
}

size_t str_count (
  const char*   haystack,
  const size_t  len_haystack,
  const char*   needles,
  const size_t  len_needles
) {
  size_t s = 0;
  char c;

  for (size_t i = 0; i < len_haystack; i++) {
    c = haystack[i];
    for (size_t h = 0; h < len_needles; h++) {
      if (c == needles[h]) {
         s++;
       }
    }
  }
  return s;
}

// safestrnlen -- find the length of a string, defaulting to MAX_STR_LEN, without segfaulting
size_t safestrnlen (const char* str) {
  // it seems gnu strnlen segfaults on null pointer (aka empty string), so let's fix that
  if (!str) { return 0; }
  return strnlen(str, MAX_STR_LEN);
}


bool isEOL (const char* str) {
  return !str
    || !safestrnlen(str)
    || str[0] == '\n';
}

bool getint64 (int64_t* restrict dest) {
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
  char* in = readln(ULL_DIGITS);
  if (!in) {
    return false;
  }
  *dest = strtoull(in, NULL, DEC_BASE);
  assert(dest != NULL);
  safefree(in);
  return true;
}

uint64_t pow_uint64 (uint64_t in, uint64_t power) {
  uint64_t out = 1;
  for (uint64_t i = 0; i < power; i++) {
    out *= in;
  }
  return out;
}
