#include "points.h"

int main(void) {

  size_t points = 3;
  point_t** ps = safemalloc(sizeof (point_t *) * points);

  ps[0] = point_new(-12, 6, 'A');
  ps[1] = point_new(-1, 3, 'B');
  ps[2] = point_new(5, -6, 'C');
  ps[3] = point_new(3, 1, 'D');

  shape_t* s = shape_new(ps, un2signed(points), -1);

  shape_print(s, true);

  shape_rotate(s, 270);

  shape_print(s, false);

  shape_destruct(s);

  return 0;
}
