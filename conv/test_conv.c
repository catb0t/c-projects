#include <criterion/criterion.h>
#include "conv.c"

Test(util, udiff) {
  cr_assert_eq(7, udiff(14, 7));
  cr_assert_eq(7, udiff(7, 14));
}

Test(wcs, chomp) {
  wchar_t* a = malloc(sizeof (wchar_t) * 5);
  swprintf(a, 5, L"abc\n");
  wchomp(&a);
  cr_assert(! wcscmp(a, L"abc"));
  free(a);
}

Test(wcs, str_count) {
  const wchar_t* const mystr = L"abccac"; // a = 2, b = 1, c = 3
  size_t  *cts = wstr_count(mystr, L"abc"),
         *cmp2 = malloc(sizeof (size_t) * 3);

  cmp2[0] = 2;
  cmp2[1] = 1;
  cmp2[2] = 3;

  cr_assert(! memcmp(cts, cmp2, sizeof (size_t) * 3));
  
}

