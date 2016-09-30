#include "../common.h"

#define MOST_POSSIBLE_POINTSEE_CHARS 44

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
char* shape_see (const shape_t* s);

void free_point_array (point_t** ps, const ssize_t len);
void   point_destruct (point_t* p);
void   shape_destruct (shape_t* s);

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

  char*     name       = safemalloc(sizeof (char) * (size_t) len);
  point_t** new_points = safemalloc(sizeof (point_t *) * (size_t) len);

  for (ssize_t i = 0; i < len; i++) {
    point_t* thisp = points[i];
    point_t* newp  = point_new(thisp->x, thisp->y, thisp->id);

    name[i]       = newp->id;
    new_points[i] = newp;
  }

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

  safefree(s);
}

char* point_see (const point_t* p) {
  char t[MOST_POSSIBLE_POINTSEE_CHARS];
  size_t len = (size_t) snprintf(
    t,
    MOST_POSSIBLE_POINTSEE_CHARS,
    "%c(%" PRIi64 " %" PRIi64 ")\n",
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
    "%c(%" PRIi64 " %" PRIi64 ")\n",
    p->id,
    p->x,
    p->y
  );
  return o;
}

char* shape_see (const shape_t* s) {

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
    new_len   += safestrnlen(st) + 4;
  }

  char *out    = safemalloc(sizeof (char) * new_len),
       *bufend = out;

  for (size_t i = 0; i < count_ps; i++) {
    bufend += snprintf(bufend, MOST_POSSIBLE_POINTSEE_CHARS + 2, "\t%s\n", pts_tos[i]);
  }

  free_ptr_array( (void **) pts_tos, count_ps);

  size_t flen = new_len + safestrnlen(s->qual_name);
  char* final = safemalloc(sizeof (char) * flen);
  snprintf(final, flen, "%s(\n%s)", s->qual_name, out);

  return final;
}
