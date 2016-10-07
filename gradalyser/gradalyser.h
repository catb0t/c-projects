#include "../common.h"

typedef uint64_t grade_t;

grade_t grade_getmean (const grade_t* const gs, const size_t len);
grade_t     grade_min (const grade_t* const gs, const size_t len);
grade_t     grade_max (const grade_t* const gs, const size_t len);

void test (void);

grade_t grade_getmean (const grade_t* const gs, const size_t len) {

  if (NULL == gs || len == 0) {
    return 0;
  }

  grade_t k = len;
  grade_t total = 0;

  for (size_t i = 0; i < k; i++) {
    total += gs[i];
  }

  return total / k;
}

grade_t grade_max (const grade_t* const gs, const size_t len) {
  grade_t high = 0;

  for (size_t i = 0; i < len; i++) {
    if (gs[i] > high) {
      high = gs[i];
    }
  }

  return high;
}

grade_t grade_min (const grade_t* const gs, const size_t len) {
  grade_t low = UINT64_MAX;

  for (size_t i = 0; i < len; i++) {
    if (gs[i] < low) {
      low = gs[i];
    }
  }

  return low;
}

void test (void) {

  size_t len;

  char
    *in   = readln(MAX_STR_LEN),
    **spl = str_split(in, ' ', &len);

  grade_t* gs = safemalloc(sizeof (grade_t) * len);

  for (size_t i = 0; i < len; i++) {
    // grades will never be 0 so this is ok
    grade_t j = (grade_t) atoi(spl[i]);
    gs[i] = j;
  }
  safefree(in);
  free_ptr_array( (void **) spl, 1);

  printf(
    "avg: %" PRIu64 "\n"
    "min: %" PRIu64 "\n"
    "max: %" PRIu64 "\n",

    grade_getmean(gs, len),
    grade_min(gs, len),
    grade_max(gs, len)
  );

  safefree(gs);

}
