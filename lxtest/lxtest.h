#include "../calc/lex.h"

void test (void);

void test (void) {

  char* code = readln(100);

  astnode_t* n = lex_string(code);

  printf("gets here\n");

  char* s = ast_see(n);
  dealloc_printf(s);

  safefree(code);

  ast_destruct_node(n);
}
