#include <tgmath.h>
#include "../common.h"

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230
#endif

#define NUM_QUESTIONS 10
#define NUM_OPERATORS 5

typedef long double ldbl;

void print_10stable (const size_t n);
void    circle_data (const ldbl radius);
void           swap (int64_t* a, int64_t* b);
void  convert_temps (const int64_t f, const int64_t c);
void print_counting (const uint64_t n);

uint64_t signed2un_long2uint64_t (long);

void  question1 (void);
void  question2 (void);
void  question3 (void);
void  question4 (void);
void  question5 (void);
void  question6 (void);
void  question7 (void);
void  question8 (void);
void  question9 (void);
void question10 (void);

void (* q_funcs[]) (void) = {
  question1,
  question2,
  question3,
  question4,
  question5,
  question6,
  question7,
  question8,
  question9,
  question10,
};

_Static_assert(NUM_QUESTIONS == (sizeof q_funcs) / (sizeof (void (*) (void))),
  "wrong number of questions");

void question1 (void) {
  // infix math? disgusting.
  printf("%d\n", -5 + (8 * 6) );
  printf("%d\n", (55 + 9) % 9 );
  printf("%d\n", 20 + ( (int) ceil( (-3 * 5) / 8) ) );
  // I can't be bothered trying to convert Java's f*ckery to normal precedence
  printf("%d\n", 13);
}

static ldbl op_add (const ldbl l, const ldbl r) { return l + r; }
static ldbl op_mul (const ldbl l, const ldbl r) { return l * r; }
static ldbl op_sub (const ldbl l, const ldbl r) { return l - r; }
// if r is not 0 then return l op r
// else if r is 0 and l is not 0 return r op l
// else return 0
static ldbl op_div (const ldbl l, const ldbl r) {
  if ( (int64_t) r) { return l / r; }
  errno = EDOM; // the input was not within the domain of the function
  if ( (int64_t) l) { return r / l; }
  return 0.f;
}
static ldbl op_mod (const ldbl l, const ldbl r) {
  int64_t a = (int64_t) l, b = (int64_t) r;
  if (b) { return a % b; }
  errno = EDOM; // the input was not within the domain of the function
  if (a) { return b % a; }
  return 0.f;
}

static ldbl (* const operators[]) (ldbl, ldbl) = {
  op_add, op_mul, op_sub, op_div, op_mod
};

static const char* const opstrs[] = {
  "+", "*", "-", "/", "%"
};

_Static_assert(NUM_OPERATORS == (sizeof operators) / (sizeof (void*)),
  "wrong number of ops");
_Static_assert(NUM_OPERATORS == (sizeof opstrs) / (sizeof (void*)),
  "wrong number of operator strings"
);

void question2 (void) {

  const uint8_t OPERANDS_LEN = 2;

  char
    *buf = input_prompt("Two space-separated numbers: ", 1 + (ULL_DIGITS * 2), NULL),
    **n_tostr;

  size_t len;
  ldbl* nums = (typeof(nums)) safemalloc(sizeof (ldbl) * OPERANDS_LEN);

  n_tostr = str_split(buf, ' ', &len);
  if (NULL == n_tostr && (EINVAL == errno)) {
    printf("\nstr_split: tried to split an empty string\n");
    return;
  }
  safefree(buf);

  for (size_t i = 0; i < OPERANDS_LEN; i++) {
    // I don't actually care about the error
    nums[i] = strtold(n_tostr[i], NULL);
  }

  // a bug in str_split requires this crap
  safefree_args(2, n_tostr[0], n_tostr);

  for (size_t i = 0; i < NUM_OPERATORS; i++) {
    ldbl r = nums[0], l = nums[1];
    ldbl o = ( operators[i] ) ( r, l );
    printf(
      "%LG %s %LG = %LG (%s)\n",
      r,
      opstrs[i],
      l,
      o,
      EDOM == errno
        ? strerror(EDOM)
        : "no error"
    );
  }

  safefree(nums);
}

void print_10stable (const unsigned long n) {
  for (unsigned long i = 0; i < 11; i++) {
    printf("%zu * %zu = %zu\n", n, i, n * i);
  }
}

void question3 (void) {
  char* buf = input_prompt("Enter a number: ", ULL_DIGITS * 2, NULL);

  const unsigned long n = strtoul(buf, NULL, DEC_BASE);

  print_10stable(n);

  safefree(buf);
}

void circle_data (const ldbl radius) {
  ldbl
    dia  = radius * 2,
    circ = dia * PI,
    area = dia * dia;
  printf(
    "diameter: %LG, area: %LG, circumference: %LG\n",
    dia, area, circ
  );
}

void question4 (void) {
  char* buf = input_prompt("Radius of circle: ", ULL_DIGITS * 2, NULL);

  const ldbl rad = strtold(buf, NULL);

  circle_data(rad);

  safefree(buf);
}

void swap (int64_t* a, int64_t* b) {
  // uhhh... okay, C++ *might* be good for *some* things *sometimes*.....
#ifdef __cplusplus
  std::swap(*a, *b);
#else
  const int64_t c = *a;
  *a = *b;
  *b = c;
#endif
}

void question5 (void) {
  int64_t a = -4, b = 9;
  printf("Vars:  %" PRIi64 ", %" PRIi64 "\n", a, b);
  swap(&a, &b);
  printf("After: %" PRIi64 ", %" PRIi64 "\n", a, b);
}

void convert_temps (int64_t f, int64_t c) {
  printf(
    "%" PRIi64 " F -> C: %.1f, %" PRIi64 " C -> F: %.1f\n",
    f,
    ( ( (float) f - 32.f) / (9.f / 5.f) ), // C
    c,
    ( ( (float) c) / (5.f / 9.f) ) + 32.f  // F
  );
}

void question6 (void) {
  char* buf = input_prompt("Enter a number: ", 1 + (ULL_DIGITS * 2), NULL);

  const int64_t n = strtoll(buf, NULL, DEC_BASE);

  convert_temps(n, n);

  safefree(buf);
}

define_signed2un_type(long, uint64_t);

void question7 (void) {
  char* buf = input_prompt("Enter a number! ", ULL_DIGITS, NULL);

  uint64_t res = 0;

  const size_t len = safestrnlen(buf);
  for (size_t i = 0; i < len; i++) {
    res += signed2un_long2uint64_t( ( (signed) buf[i] ) - 48 );
  }

  safefree(buf);

  printf("sum of digits: %" PRIu64 "\n", res);
}

void question8 (void) {
  char* buf = input_prompt("Enter a number! ", 2, NULL);

  // 0 is unsigned but not positive so instead of special casing, word it differently
  printf("The number is %s\n", buf[0] == '-' ? "signed" : "unsigned");
  safefree(buf);
}

void question9 (void) {

  static const char* const daynames[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
  };

  char* buf = input_prompt("Which day number? ", 2, NULL);

  unsigned long index = strtoul(buf, NULL, DEC_BASE) - 1;

  printf("Day name: %s\n", index < 7 ? daynames[index] : "invalid index (1-7)");

  safefree(buf);
}

void print_counting (const uint64_t n) {
  uint64_t need = 1, sofar = 0;
  for (uint64_t i = 0; i < (n + 1); i++) {
    printf("%" PRIu64 " ", i);
    ++sofar;
    if (sofar == need) {
      sofar = 0;
      printf("\n");
      ++need;
    }
  }
}

void question10 (void) {
  char* buf = input_prompt("Enter a number! ", ULL_DIGITS, NULL);

  uint64_t upto = strtoul(buf, NULL, DEC_BASE);

  print_counting(upto);

  safefree(buf);
}
