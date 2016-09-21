#include "../common.h"

void  prompt_positive_double (double* out, const char* const firstp);

bool     get_double (double* out);
void runCarLoanMain (void);

bool get_double (double* out) {
  char* in = readln(SHORT_INSTR);
  if (!in) {
    return false;
  }
  *out = strtod(in, NULL);
  safefree(in);
  assert(out != NULL);
  return true;
}

void prompt_positive_double (double* out, const char* const firstp) {
  printf("%s", firstp);
  while ( (!get_double(out)) || (*out < 0) ) {
    printf("BOB says: that value is junk!\nEnter another! ");
  }
}

void runCarLoanMain (void) {
  double car_price, loan_length, down_payment,
         final_price, monthly_rate, interest;

  prompt_positive_double(&car_price, "Enter the car's price! ");

  prompt_positive_double(&loan_length, "Enter the loan's length (months)! ");

  prompt_positive_double(&interest, "Enter the interest rate! ");

  prompt_positive_double(&down_payment, "Enter the down payment! ");

  car_price -= down_payment;
  loan_length *= 12;
  monthly_rate = interest / 12;
  final_price = (
   car_price * (
     monthly_rate * ( pow( (1.f + monthly_rate), loan_length) )
     /
     ( pow( (1.f + monthly_rate), loan_length) - 1.f)
   )
 );

  printf("Amortization: $%8.3f", final_price);
}

