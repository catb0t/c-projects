#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>

#define NLEN 2048
#define Out

#undef wcslen
#define wcslen(s) wcsnlen(s, NLEN)
#undef wcsdup
#define wcsdup(s) wcsndup(s, NLEN)

size_t udiff (const size_t x, const size_t y);

void     wchomp (wchar_t** buf_ref);

wchar_t*     wcsndup (const wchar_t* str, const size_t maxlen);
wchar_t* wreadln (const size_t chars, FILE* const stream);
wchar_t** wstr_split (const wchar_t* const str, const wchar_t* const delims, Out size_t* const out_len);

size_t* size_t_min (size_t* const ls, const size_t len);
size_t* wstr_count (const wchar_t* const hsk, const wchar_t* const ndl);

//const wchar_t* deg_syms[3] = { L"°" L"d" L"deg" };
//const wchar_t* rad_syms[3] = { L"ᶜ" L"r" L"rad" };

size_t udiff (const size_t x, const size_t y) {
  return x < y ? y - x : x - y;
}

wchar_t* wreadln (const size_t chars, FILE* const stream) {
  wchar_t *buf = (wchar_t *) malloc(chars * sizeof (wchar_t)),
          *sts;

  fflush(stream);

  sts = fgetws(buf, (int) chars, stream);

  fflush(stdin);

  if ( (! sts) || '\04' == buf[0] ) {
    free(buf);
    errno = EINVAL;
    return NULL;
  }

  wchomp(&buf);

  return buf;
}

void wchomp (wchar_t** buf_ref) {
  if (! buf_ref) { return; }

  (* buf_ref) [ wcscspn(*buf_ref, L"\n") ] = '\0';
}

size_t* wstr_count (const wchar_t* const hsk, const wchar_t* const ndl) {
  size_t hlen = wcslen(hsk), nlen = wcslen(ndl);

  size_t* res = (size_t *) calloc(nlen, sizeof (size_t));

  for (size_t h = 0; h < hlen; h++) {
    wchar_t hc = hsk[h];
    for (size_t n = 0; n < nlen; n++) {
      wchar_t nc = ndl[n];
      if (hc == nc) { ++res[n]; }
    }
  }

  return res;
}

/* Duplicate S, returning an identical malloc'd string.  */
wchar_t* wcsndup (const wchar_t* str, const size_t maxlen) {
  size_t   len = wcsnlen(str, maxlen);
  wchar_t* cpy = (wchar_t *) malloc (sizeof (wchar_t) * (len + 1) );

  if (NULL == cpy) {
    return NULL;
  }

  cpy[len] = '\0';
  return (wchar_t *) memcpy (cpy, str, len);
}

size_t* size_t_min (size_t* const ls, const size_t len) {
  if (! ls || ! len) { return NULL; }

  size_t* minptr = ls;

  for (size_t i = 0; i < len; i++) {
    minptr = ls[i] < *minptr ? ls + i : minptr;
  }

  return minptr;
}

wchar_t** wstr_split (const wchar_t* const str, const wchar_t* const delims, Out size_t* const len) {

  if (! str || ! delims || ! len) {
    errno = EINVAL;
    return NULL;
  }

  wchar_t** out;

  size_t slen = wcslen(str), dlen = wcslen(delims);

  // empty input gives an array with one element, the empty string
  if (! slen) {
    out = (wchar_t **) malloc(sizeof (wchar_t *) * 1);
    out[0] = (wchar_t *) malloc(sizeof (wchar_t) * 3);
    swprintf(out[0], 2, L"");
    *len = 1;
    return out;
  }

  // empty delimiter string gives array<wchar_t *> of each char of str
  if (! dlen) {
    out = (wchar_t **) malloc(sizeof (wchar_t*) * slen);
    for (size_t i = 0; i < slen; i++) {
      out[i] = (wchar_t *) malloc(sizeof (wchar_t) * 3);
      swprintf(out[i], 2, L"%lc", str[i]);
    }
    *len = slen;
    return out;
  }

  // list of counts of each delimiter
  size_t *delimct = wstr_count(str, delims),
           dctsum = 0;

  // sum the counts
  for (size_t i = 0; i < dlen; i++) {
    dctsum += delimct[i];
  }

  // if the sum is 0, just return an array with one element, the original string
  if (! dctsum) {
    free(delimct);
    out = (wchar_t **) malloc(sizeof (wchar_t*) * 1);
    out[0] = wcsdup(str);
    *len = 1;
    return out;
  }

  // else find the delimiters

  wchar_t *scopy = wcsdup(str), // copy of (const * const) str
           *sptr = scopy;//,       // pointer we're going to change
          //*next;                // temp. pointer to the next delimiter

  out = (wchar_t **) malloc(sizeof (wchar_t *) * dctsum);

  size_t* lens_to_next = malloc(sizeof (size_t) * dlen);

  for (size_t i = 0; i < dctsum; i++) {
    for (size_t ns = 0; ns < dlen; ns++) {
      lens_to_next[ns] = (size_t) (wcschr(sptr, delims[ns]) - sptr);
    }

    size_t *minptr = size_t_min(lens_to_next, dlen),
              diff = (size_t) (minptr - lens_to_next);


    out[i] = memcpy(out[i], sptr, diff);
    sptr += diff + 1;
  }

  free(scopy);
  free(delimct);
  free(lens_to_next);

  *len = dctsum;
  return out;
}
