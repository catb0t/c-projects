#include "../common.h"

void runCarLoanMain(void);

void runCarLoanMain(void) {
  int64_t car_price, loan_length, down_payment;
  float interest;

  printf("Enter the car's price! ");
  while ( ( !getint64(&car_price) ) || (car_price < 0) ) {
    printf("BOB says: that price is negative!\nEnter another! ");
  }

  printf("Enter the loan's length! ");
  while ( ( !getint64(&loan_length ) ) || (loan_length < 0) ) {
    printf("BOB says: that timespan is negative!\nEnter another! ");
  }

  printf("Enter the interest rate! ");
  char* in = readln(SHORT_INSTR);
  interest = strtof(in, NULL);
  safefree(in);
  printf("%.16f\n", interest);

  printf("Enter the down payment! ");
  while ( ( !getint64(&down_payment) ) || (down_payment < 0) ) {
    printf("BOB says: that payment is negative!\nEnter another! ");
  }


}
