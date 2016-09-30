#include "points.h"

int main(void) {

  size_t points = 4;
  point_t** ps = safemalloc(sizeof (point_t *) * points);

  for (size_t i = 0; i < points; i++) {
    ps[i] = point_new((int64_t) i, (int64_t) i, (char) (i + 65) );
  }

  shape_t* s = shape_new(ps, (ssize_t) points, -1);

  shape_print(s);

  shape_translate(s, 5, -6);

  shape_print(s);

  shape_destruct(s);

  return 0;
}
