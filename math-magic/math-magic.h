#include "../common.h"

void runMathMagic(void);

void runMathMagic(void) {
  int64_t input = 0;
  uint64_t starting, squared, plus_orig, div_orig, add_17, sub_orig, div_6;

  // check for && disallow negative input
  printf("\nEnter a number! ");
  while ( (!getint64(&input)) || (input <= 0) ) {
    printf("BOB says: that number is not greater than 0!\nEnter another! ");
  }

  starting = (uint64_t) input;
  printf("Number is: %" PRIu64 "\n", starting);

  squared = pow_uint64(starting, (uint64_t) 2);
  printf("Squared: %" PRIu64 "\n", squared);

  plus_orig = squared + starting;
  printf("Plus original (%" PRIu64 "): %" PRIu64 "\n", starting, plus_orig);

  div_orig = plus_orig / starting;
  printf("Divided by original (%" PRIu64 "): %" PRIu64 "\n", starting, div_orig);

  add_17 = div_orig + (uint64_t) 17;
  printf("Plus 17: %" PRIu64 "\n", add_17);

  sub_orig = add_17 - starting;
  printf("Minus original (%" PRIu64 "): %" PRIu64 "\n", starting, sub_orig);

  div_6 = sub_orig / 6;
  printf("Divided by 6: your number was: %" PRIu64 "\n", div_6);

  printf("Equal to 3: %s\n", ( div_6 == 3 ) ? "true" : "false" );
  assert(div_6 == 3);
}
