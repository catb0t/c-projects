#include "points.h"

int main(void) {

  size_t points = 4;
  point_t** ps = safemalloc(sizeof (point_t *) * points);

  ps[0] = point_new(1, 1, 'A');
  ps[1] = point_new(1, 3, 'B');
  ps[2] = point_new(3, 3, 'C');
  ps[3] = point_new(3, 1, 'D');

  shape_t* s = shape_new(ps, (ssize_t) points, -1);

  shape_print(s, true);

  shape_reflect(s, y_is_VAL, 4);

  shape_print(s, false);

  shape_isotropic_dilate(s, 3);

  shape_print(s, false);

  shape_destruct(s);

  return 0;
}
