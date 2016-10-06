#ifdef GCC
#line 2 "points"
#endif

#pragma once
#include <ctype.h>
#include "../common.h"

#define MOST_POSSIBLE_POINTSEE_CHARS 51

typedef struct {
  int64_t x;  // coord x
  int64_t y;  // coord y
  char    id; // a-zA-Z0-9
} point_t;

typedef struct {
  point_t** points;     // a list of points or NULL
  char*     qual_name;  // concatenation of the points' names or NULL
  ssize_t   num_points; // length of points array or -1 if NULL
  ssize_t   primeness;  // the primeness level or -1 if not prime
} shape_t;

typedef enum { x_axis, y_axis, x_is_VAL, y_is_VAL } axis_t;
typedef enum {
  QUAD_1, QUAD_2, QUAD_3, QUAD_4,
  HEM_N,  HEM_W,  HEM_S,  HEM_E,
  ORIGIN
} sector_t;

point_t* point_new (
  const int64_t x,
  const int64_t y,
  const char id
);

shape_t* shape_new (
  point_t** points, /* not const */
  const ssize_t len,
  const ssize_t primeness
);

point_t* point_copy (const point_t* const p);
shape_t* shape_copy (const shape_t* const s);

char* point_see (const point_t* p);
char* shape_see (const shape_t* s, const bool lines);

bool shape_isempty (const shape_t*);

void free_point_array (point_t** ps, const ssize_t len);
void   point_destruct (point_t* p);
void   shape_destruct (shape_t* s);
void      point_print (const point_t* const p);
void      shape_print (const shape_t* const p, const bool lines);

void   shape_isotropic_dilate (shape_t*, const int64_t);
void shape_anisotropic_dilate (shape_t*, const int64_t, const int64_t);
void          point_translate (point_t*, const int64_t, const int64_t);
void          shape_translate (shape_t*, const int64_t, const int64_t);
void            point_reflect (point_t*, const axis_t,  const int64_t);
void            shape_reflect (shape_t*, const axis_t,  const int64_t);
void             point_rotate (point_t*, const uint16_t);
void             shape_rotate (shape_t*, const uint16_t);

sector_t point_get_sector (const point_t* const p);

point_t* point_new (const int64_t x, const int64_t y, const char id) {

  assert ( isalnum(id) );

  point_t* p = safemalloc(sizeof (point_t));

  p->x       = x;
  p->y       = y;
  p->id      = id;
  return p;
}

void point_destruct (point_t* p) {
  safefree(p);
}

void free_point_array (point_t** ps, const ssize_t len) {
  if (len > 0) {
    for (ssize_t i = 0; i < len; i++) {
      point_destruct(ps[i]);
    }
  }

  safefree(ps);
}

shape_t* shape_new (
      point_t** points,
  const ssize_t len,
  const ssize_t primeness
) {

  shape_t* s = safemalloc(sizeof (shape_t));

  if (len < 0) {
    if (points != NULL ) {
      free_point_array(points, len);
    }

    // empty shape
    s->points     = NULL;
    s->num_points = -1;
    s->qual_name  = NULL;
    s->primeness  = -1;
    return s;

  }

  char*     name       = safemalloc((sizeof (char) * (size_t) len) + 1);
  point_t** new_points = safemalloc(sizeof (point_t *) * (size_t) len);

  ssize_t i;
  for (i = 0; i < len; i++) {
    point_t* thisp = points[i];
    point_t* newp  = point_new(thisp->x, thisp->y, thisp->id);

    name[i]       = newp->id;
    new_points[i] = newp;
  }

  name[i] = '\0';

  free_point_array(points, len);

  s->qual_name  = name;
  s->points     = new_points;
  s->num_points = len;
  s->primeness  = primeness;

  return s;
}

point_t* point_copy (const point_t* const p) {

  return point_new(p->x, p->y, p->id);
}

shape_t* shape_copy (const shape_t* const s) {

  if ( ! shape_isempty(s) ) {
    point_t** points = safemalloc(sizeof (point_t *) * (size_t) s->num_points);

    for (size_t i = 0; i < ((size_t) s->num_points); i++) {
      points[i] = point_copy( (s->points) [i]);
    }

    return shape_new(points, s->num_points, s->primeness);

  }

  return shape_new(NULL, -1, s->primeness);
}

__PURE_FUNC
bool shape_isempty (const shape_t* s) {
  return s->num_points == -1;
}

void shape_destruct (shape_t* s) {
  if ( ! shape_isempty(s) ) {
    free_point_array(s->points, s->num_points);
  }

  safefree(s->qual_name);
  safefree(s);
}

char* point_see (const point_t* p) {
  char t[MOST_POSSIBLE_POINTSEE_CHARS];
  size_t len = (size_t) snprintf(
    t,
    MOST_POSSIBLE_POINTSEE_CHARS,
    "%c(x=%" PRIi64 " y=%" PRIi64 ")\n",
    p->id,
    p->x,
    p->y
  );

  /*
  "If the output was truncated due to this limit, then
  the return value is the number of characters (excluding
  the terminating null byte) which would have been written
  to the final string if enough space had been available.
  Thus, a return value of size or more means that the output
  was truncated."
  -- man 3 sprintf
  */
  if (len > MOST_POSSIBLE_POINTSEE_CHARS) {
    len = MOST_POSSIBLE_POINTSEE_CHARS;
  }

  char* o = safemalloc(sizeof (char) * len);

  snprintf(
    o,
    len,
    "%c(x=%" PRIi64 " y=%" PRIi64 ")\n",
    p->id,
    p->x,
    p->y
  );
  return o;
}

char* shape_see (const shape_t* s, const bool lines) {

#define STR_ERRMARGIN 8

  if ( shape_isempty(s) ) {
    char* o = safemalloc(sizeof (char));
    snprintf(o, 1, "%c", 0);
    return o;
  }

  size_t count_ps = (size_t) s->num_points;
  size_t new_len = 0;

  char** pts_tos = safemalloc(sizeof (char *) * count_ps);

  for (size_t i = 0; i < count_ps; i++) {

    point_t* thisp = (s->points)[i];
    char* st       = point_see(thisp);

    pts_tos[i] = st;
    new_len   += safestrnlen(st) + STR_ERRMARGIN;
  }

  char *out    = safemalloc(sizeof (char) * new_len),
       *bufend = out;

  for (size_t i = 0; i < count_ps; i++) {
    bufend += snprintf(
      bufend,
      MOST_POSSIBLE_POINTSEE_CHARS + STR_ERRMARGIN,
      "%s%s%s",
      lines ? "\t" : "",
      pts_tos[i],
      lines ? "\n" : " "
    );
  }

  free_ptr_array( (void **) pts_tos, count_ps);

  size_t len,
         flen = new_len + safestrnlen(s->qual_name);
  char* final = safemalloc(sizeof (char) * flen);

  char* primes;
  if ( (s->primeness) >= 0 ) {
    primes = str_repeat("'", (size_t) s->primeness + 1, &len);

  } else {
    primes = safemalloc(1);
    snprintf(primes, 1, "%s", "\0");
  }

  snprintf(
    final,
    flen,
    "%s%s(%s%s)",
    s->qual_name,
    primes,
    lines ? "\n" : " ",
    out
  );

  safefree(primes);
  safefree(out);

  return final;
}

void point_print (const point_t* const p) {
  char* c = point_see(p);
  printf("%s\n", c);
  safefree(c);
}

void shape_print (const shape_t* const s, const bool lines) {
  char* c = shape_see(s, lines);
  printf("%s\n", c);
  safefree(c);
}

__CONST_FUNC __PURE_FUNC
sector_t point_get_sector (const point_t* const p) {
  int64_t x = p->x, y = p->y;

  if ( y && x ) {
    sector_t qs[2][2] = {
      { QUAD_3, QUAD_4 },
      { QUAD_2, QUAD_1 }
    };
    // get quadrant
    return qs[y > 0][x > 0];
  }

  if ( !x && y ) {
    return y > 0 ? HEM_N : HEM_S;
  }
  if ( !y && x ) {
    return x > 0 ? HEM_E : HEM_W;
  }

  // !x && !y
  return ORIGIN;
}

// TRANSFORMATIONS

void point_translate (point_t* p, const int64_t x, const int64_t y) {
  p->x += x;
  p->y += y;
}

void shape_translate (shape_t* s, const int64_t x, const int64_t y) {
  if ( (s->num_points) < 0) {
    return;
  }

  for (ssize_t i = 0; i < s->num_points; i++) {
    point_translate( (s->points) [i], x, y);
  }

  ++(s->primeness);
}

void point_reflect (point_t* p, const axis_t axs, const int64_t val) {
  int64_t x, y;
  switch (axs) {
    case x_axis: {
      p->y = -(p->y);
      break;
    }

    case y_axis: {
      p->x = -(p->x);
      break;
    }

    case y_is_VAL: {
      x = p->x;

      if (x > val) {
        p->x -= (x - val) * 2;

      }
      if (x < val) {
        p->x += (val - x) * 2;
      }

      break;
    }

    case x_is_VAL: {
      y = p->y;

      if (y > val) {
        p->y -= (y - val) * 2;

      }
      if (y < val) {
        p->y += (val - y) * 2;
      }

      break;
    }

  }
}

void shape_reflect (shape_t* s, const axis_t axs, const int64_t val) {
  if ( shape_isempty(s) ) {
    return;
  }

  for (ssize_t i = 0; i < s->num_points; i++) {
    point_reflect(s->points[i], axs, val);
  }

  ++(s->primeness);
}

// inclusive
static bool uint16_inrange (const uint16_t n, const uint16_t min, const uint16_t max) {
  return (n >= min) && (n <= max);
}

void point_rotate (point_t* p, const uint16_t degrees) {

  uint16_t dg = degrees;

  if ( dg % 90 ) {

    if ( uint16_inrange(dg, 0, 89) ) {
      dg = 0;
    }
    else if ( uint16_inrange(dg, 90, 179) ) {
      dg = 90;
    }
    else if ( uint16_inrange(dg, 180, 269) ) {
      dg = 180;
    }
    else if ( uint16_inrange(dg, 270, 360) ) {
      dg = 270;
    }
    else {
      dg = 0;
    }

  }

  switch ( dg ) {
    case 90: {
      p->y = -(p->y);
      break;
    }

    case 180: {
      p->x = -(p->x);
      p->y = -(p->y);
      break;
    }

    case 270: {
      int64_t x = p->x, y = p->y;
      p->x = y;
      p->y = -x;
      break;
    }
  }

}

void shape_rotate (shape_t* s, const uint16_t dg) {
  if ( shape_isempty(s) ) {
    return;
  }

  for (ssize_t i = 0; i < (s->num_points); i++) {
    point_rotate( (s->points) [i], dg);
  }
}

void shape_isotropic_dilate (shape_t* s, const int64_t factor) {
  if ( shape_isempty(s) ) {
    return;
  }

  shape_anisotropic_dilate(s, factor, factor);
}

void shape_anisotropic_dilate (shape_t* s, const int64_t xscale, const int64_t yscale) {
  if ( shape_isempty(s) ) {
    return;
  }

  for (ssize_t i = 0; i < (s->num_points); i++) {
    point_t** thispt = &((s->points) [i]);
    (*thispt)->x *= xscale;
    (*thispt)->y *= yscale;
    assert((*thispt)->x == ((s->points)[i])->x);
  }
}
