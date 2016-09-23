#include <criterion/criterion.h>
#include "./fxpt.h"

Test(misc, failing) {
  cr_assert(0);
}

Test(misc, passing) {
  cr_assert(1);
}