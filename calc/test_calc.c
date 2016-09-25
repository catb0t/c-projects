#include <criterion/criterion.h>

#undef DEBUG
#include "./calc.h"

Test(stack, base10) {
  cr_assert( is_base10("+0123.4567890") == true, "numeric string is base 10");
  cr_assert( is_base10("-01234567A890.") == false, "non-base 10 string");
}

Test(stack, atoi_strlen) {
  cr_assert( atoi_strlen(-200.003) == 8, "signed fractional thou place");
  cr_assert( atoi_strlen(-200.3) == 6, "signed 10s place dec");
  cr_assert( atoi_strlen(-200) == 4, "signed int");
}
