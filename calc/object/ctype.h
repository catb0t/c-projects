typedef enum {
  // void*
  CTYPE_VOID_P,
  // void* const
  CTYPE_VOID_CP,

  // const void*
  CTYPE_CVOID_P,
  // const void* const
  CTYPE_CVOID_CP,

  // void**
  CTYPE_VOID_PP,
  // void * const *
  CTYPE_VOID_CPP,
  // void * * const
  CTYPE_VOID_PCP,
  // void * const * const
  CTYPE_VOID_CPCP,

  // const void**
  CTYPE_CVOID_PP,
  // const void * const *
  CTYPE_CVOID_CPP,
  // const void * * cosnt
  CTYPE_CVOID_PCP,
  // const void * const * const
  CTYPE_CVOID_CPCP,

  // char
  CTYPE_CHAR,
  // char*
  CTYPE_CHAR_P,
  // char**
  CTYPE_CHAR_PP,

  // const char
  CTYPE_CCHAR,
  // const char*
  CTYPE_CCHAR_P,
  // const char* *
  CTYPE_CCHAR_PP,

  // const char* const
  CTYPE_CCHAR_CP,
  // const char * const *
  CTYPE_CCHAR_CPP,
  // const char * * const
  CTYPE_CCHAR_PCP,
  // const char * const * const
  CTYPE_CCHAR_CPCP,

  // size_t
  CTYPE_SIZET,
  // const size_t
  CTYPE_CSIZET,

  // size_t*
  CTYPE_SIZET_P,
  // size_t* const
  CTYPE_SIZET_CP,
  // const size_t*
  CTYPE_CSIZET_P,
  // const size_t * const
  CTYPE_CSIZET_CP,

  // const size_t * *
  CTYPE_SIZET_PP,
  // const size_t * const *
  CTYPE_SIZET_CPP,
  // const size_t * * const
  CTYPE_SIZET_PCP,
  // const size_t * const  * const
  CTYPE_SIZET_CPCP,

  // const size_t * *
  CTYPE_CSIZET_PP,
  // const size_t * const *
  CTYPE_CSIZET_CPP,
  // const size_t * * const
  CTYPE_CSIZET_PCP,
  // const size_t * const  * const
  CTYPE_CSIZET_CPCP,

  // size_t
  CTYPE_SSIZET,
  // const size_t
  CTYPE_CSSIZET,

  // size_t*
  CTYPE_SSIZET_P,
  // size_t* const
  CTYPE_SSIZET_CP,
  // const size_t*
  CTYPE_CSSIZET_P,
  // const size_t * const
  CTYPE_CSSIZET_CP,

  // const size_t * *
  CTYPE_SSIZET_PP,
  // const size_t * const *
  CTYPE_SSIZET_CPP,
  // const size_t * * const
  CTYPE_SSIZET_PCP,
  // const size_t * const  * const
  CTYPE_SSIZET_CPCP,

  // const size_t * *
  CTYPE_CSSIZET_PP,
  // const size_t * const *
  CTYPE_CSSIZET_CPP,
  // const size_t * * const
  CTYPE_CSSIZET_PCP,
  // const size_t * const  * const
  CTYPE_CSSIZET_CPCP,

  // long double
  CTYPE_LDBL,
  // const long double
  CTYPE_CLDBL,

  // long double*
  CTYPE_LDBL_P,
  // const long double*
  CTYPE_CLDBL_P,
  // long double * const
  CTYPE_LDBL_CP,
  // const long double * const
  CTYPE_CLDBL_CP,

  // long double * *
  CTYPE_LDBL_PP,
  // const long double * *
  CTYPE_CLDBL_PP,

  // long double * const *
  CTYPE_LDBL_CPP,
  // const long double * const *
  CTYPE_CLDBL_CPP,

  // long double * * const
  CTYPE_LDBL_PCP,
  // const long double * * const
  CTYPE_CLDBL_PCP,

  // long double * const * const
  CTYPE_LDBL_CPCP,
  // const long double * const * const
  CTYPE_CLDBL_CPCP,

  NUM_CTYPES
} ctype_t;

static const ctype_t CTYPE_ARRAY[NUM_CTYPES] = {
  // void*
  CTYPE_VOID_P,
  // void* const
  CTYPE_VOID_CP,

  // const void*
  CTYPE_CVOID_P,
  // const void* const
  CTYPE_CVOID_CP,

  // void**
  CTYPE_VOID_PP,
  // void * const *
  CTYPE_VOID_CPP,
  // void * * const
  CTYPE_VOID_PCP,
  // void * const * const
  CTYPE_VOID_CPCP,

  // const void**
  CTYPE_CVOID_PP,
  // const void * const *
  CTYPE_CVOID_CPP,
  // const void * * cosnt
  CTYPE_CVOID_PCP,
  // const void * const * const
  CTYPE_CVOID_CPCP,

  // char
  CTYPE_CHAR,
  // char*
  CTYPE_CHAR_P,
  // char**
  CTYPE_CHAR_PP,

  // const char
  CTYPE_CCHAR,
  // const char*
  CTYPE_CCHAR_P,
  // const char* *
  CTYPE_CCHAR_PP,

  // const char* const
  CTYPE_CCHAR_CP,
  // const char * const *
  CTYPE_CCHAR_CPP,
  // const char * * const
  CTYPE_CCHAR_PCP,
  // const char * const * const
  CTYPE_CCHAR_CPCP,

  // size_t
  CTYPE_SIZET,
  // const size_t
  CTYPE_CSIZET,

  // size_t*
  CTYPE_SIZET_P,
  // size_t* const
  CTYPE_SIZET_CP,
  // const size_t*
  CTYPE_CSIZET_P,
  // const size_t * const
  CTYPE_CSIZET_CP,

  // const size_t * *
  CTYPE_SIZET_PP,
  // const size_t * const *
  CTYPE_SIZET_CPP,
  // const size_t * * const
  CTYPE_SIZET_PCP,
  // const size_t * const  * const
  CTYPE_SIZET_CPCP,

  // const size_t * *
  CTYPE_CSIZET_PP,
  // const size_t * const *
  CTYPE_CSIZET_CPP,
  // const size_t * * const
  CTYPE_CSIZET_PCP,
  // const size_t * const  * const
  CTYPE_CSIZET_CPCP,

  // size_t
  CTYPE_SSIZET,
  // const size_t
  CTYPE_CSSIZET,

  // size_t*
  CTYPE_SSIZET_P,
  // size_t* const
  CTYPE_SSIZET_CP,
  // const size_t*
  CTYPE_CSSIZET_P,
  // const size_t * const
  CTYPE_CSSIZET_CP,

  // const size_t * *
  CTYPE_SSIZET_PP,
  // const size_t * const *
  CTYPE_SSIZET_CPP,
  // const size_t * * const
  CTYPE_SSIZET_PCP,
  // const size_t * const  * const
  CTYPE_SSIZET_CPCP,

  // const size_t * *
  CTYPE_CSSIZET_PP,
  // const size_t * const *
  CTYPE_CSSIZET_CPP,
  // const size_t * * const
  CTYPE_CSSIZET_PCP,
  // const size_t * const  * const
  CTYPE_CSSIZET_CPCP,

  // long double
  CTYPE_LDBL,
  // const long double
  CTYPE_CLDBL,

  // long double*
  CTYPE_LDBL_P,
  // const long double*
  CTYPE_CLDBL_P,
  // long double * const
  CTYPE_LDBL_CP,
  // const long double * const
  CTYPE_CLDBL_CP,

  // long double * *
  CTYPE_LDBL_PP,
  // const long double * *
  CTYPE_CLDBL_PP,

  // long double * const *
  CTYPE_LDBL_CPP,
  // const long double * const *
  CTYPE_CLDBL_CPP,

  // long double * * const
  CTYPE_LDBL_PCP,
  // const long double * * const
  CTYPE_CLDBL_PCP,

  // long double * const * const
  CTYPE_LDBL_CPCP,
  // const long double * const * const
  CTYPE_CLDBL_CPCP,
};

#define get_ctype(x) _Generic( (x), \
  char: CTYPE_CHAR, const char: CTYPE_CCHAR, \
  char*: CTYPE_CHAR_P, const char*: CTYPE_CCHAR_P, char* const: CTYPE_CHAR_CP, const char* const: CTYPE_CCHAR_CP, \
  char**: CTYPE_CHAR_PP, const char**: CTYPE_CCHAR_PP, const char* const *: CTYPE_CCHAR_CPP, const char* const *: CTYPE_CCHAR_PCP, const char* const * const: CTYPE_CCHAR_CPCP \
  )

void f (void ) { (void) CTYPE_ARRAY; }


