/*
  What's this?
  copied from the GNU C library's string.h for platforms that are missing these functions
  strndup is in POSIX 1.2008 strsep is GNU.
*/

/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <string.h>

#undef strsep
#undef strndup

void* malloc(size_t);

char * strsep (char **stringp, const char *delim) {
  char *begin,
       *end;

  begin = *stringp;
  if (begin == NULL) {
    return NULL;
  }

  /* A frequent case is when the delimiter string contains only one
     character.  Here we don't need to call the expensive `strpbrk'
     function and instead work using `strchr'.  */
  if (delim[0] == '\0' || delim[1] == '\0') {
    char ch = delim[0];

    if (ch == '\0') {
      end = NULL;

    } else {

      if (*begin == ch) {
        end = begin;

      } else if (*begin == '\0') {
        end = NULL;
      } else {
        end = strchr (begin + 1, ch);
      }
    }
  } else {
    /* Find the end of the token.  */
    end = strpbrk (begin, delim);
  }

  if (end) {
    /* Terminate the token and set *STRINGP past NUL character.  */
    *end++ = '\0';
    *stringp = end;
  } else {
    /* No more delimiters; this is the last token.  */
    *stringp = NULL;
  }

  return begin;
}

/* Duplicate S, returning an identical malloc'd string.  */
char * strndup (const char *s, size_t const n) {
  size_t len = strnlen (s, n);
  char *news = (char *) malloc (len + 1);

  if (news == NULL) {
    return NULL;
  }

  news[len] = '\0';
  return (char *) memcpy (news, s, len);

}
