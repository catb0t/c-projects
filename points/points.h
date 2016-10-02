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

char* point_see (const point_t* p);
char* shape_see (const shape_t* s, const bool lines);

void free_point_array (point_t** ps, const ssize_t len);
void   point_destruct (point_t* p);
void   shape_destruct (shape_t* s);
void      point_print (point_t* p);
void      shape_print (shape_t* p, const bool lines);

void point_translate (point_t* p, const int64_t x, const int64_t y);
void shape_translate (shape_t* s, const int64_t x, const int64_t y);

void point_reflect (point_t* p, const axis_t axs, const int64_t val);
void shape_reflect (shape_t* s, const axis_t axs, const int64_t val);

sector_t point_get_sector (point_t* p);

point_t* point_new (const int64_t x, const int64_t y, const char id) {
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
  const ssize_t primeness) {

  shape_t* s = safemalloc(sizeof (shape_t));

  if (len < 0) {
    free_point_array(points, len);

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

void shape_destruct (shape_t* s) {
  ssize_t count_ps = s->num_points;

  if (count_ps < 0) {
    safefree(s);
    return;
  }

  free_point_array(s->points, count_ps);
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

  if ( (s->num_points) < 0 ) {
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
    lines ? "\n" : "",
    out
  );

  safefree(primes);
  safefree(out);

  return final;
}

void point_print (point_t* p) {
  char* c = point_see(p);
  printf("%s\n", c);
  safefree(c);
}

void shape_print (shape_t* s, const bool lines) {
  char* c = shape_see(s, lines);
  printf("%s\n", c);
  safefree(c);
}

__attribute_const__ __attribute_pure__
sector_t point_get_sector (point_t* p) {
  int64_t x = p->x, y = p->y;

  if ( y && x ) {
    sector_t qs[2][2] = {
      { QUAD_3, QUAD_4 },
      { QUAD_2, QUAD_1 }
    };
    // get quadrant
    return qs[y > 0][x > 0];
  }

  if ( !x && ( y > 0 ) ) { return HEM_N; }
  if ( !x && ( y < 0 ) ) { return HEM_S; }
  if ( !y && ( x < 0 ) ) { return HEM_W; }
  if ( !y && ( x > 0 ) ) { return HEM_E; }

  // !x && !y
  return ORIGIN;
}

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
  if (s->num_points < 0) {
    return;
  }

  for (ssize_t i = 0; i < s->num_points; i++) {
    point_reflect(s->points[i], axs, val);
  }

  ++(s->primeness);
}
