#include "../common.h"

void if_continents (void);

const char* outputs[] = {
  "North America: Mexico City, Mexico",
  "South America: Sao Paulo, Brazil",
  "Europe: Moscow, Russia",
  "Africa: Lagos, Nigeria",
  "Asia: Shanghai, China",
  "Australia: Sydney, Australia",
  "Antarctica: McMurdo Station, US",
  "Undefined continent!",
  NULL
};

// write out a place based on some input
void if_continents (void) {
  int64_t input;
  printf("Enter a number! ");
  while ( (!getint64(&input)) || (input <= 0) ) {
    printf("BOB says: that number is not greater than 0!\nEnter another! ");
  }

  printf("%s\n", outputs[ input - 1 ] );
}