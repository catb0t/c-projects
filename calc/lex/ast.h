  #include "lexcommon.h"

astnode_t* ast_newtree (const char* const prog) {
  pfn();


  return ast_newnode(NULL, prog);
}

astnode_t* ast_newnode (const object_t* const obj, const char* const code) {

  pfn();

  astnode_t* ast    = safemalloc( sizeof (astnode_t) );
  ast->code         = strndup(code, MAX_STR_LEN);
  ast->obj          = object_copy(obj);
  ast->type         = ast->obj->type;
  ast->chldn        = safemalloc( sizeof (astnode_t *) );
  ast->chldn_idx    = -1;

  report_ctor(ast);
  return ast;
}

void ast_destruct_node (astnode_t* ast) {
  pfn();

  report_dtor(ast);

  if ((ast->chldn_idx) != -1) {

    for (ssize_t i = 0; i < (ast->chldn_idx); i++) {
      ast_destruct_node( (ast->chldn)[i] );
    }
  }
  if (NULL != ast->chldn) {
    safefree(ast->chldn);
  }

  safefree(ast->code);
  object_destruct(ast->obj);
  safefree(ast);
}

char* ast_see (astnode_t* n) {
  pfn();

#define MAX_ASTSEE_LEN 2048

  if (NULL == n) {
    n = ast_newnode(NULL, "(null)");
  }

  char **chldlns,
       *chlds,
       *type = objtype_repr(n->type);

  size_t lines = 0, total = 0;
  if ((n->chldn_idx) != -1) {

    size_t nc = signed2un(n->chldn_idx);
    chldlns   = safemalloc(sizeof (char *) * 2);

    for (size_t i = 0; i < nc; i++) {
      chldlns    = realloc(chldlns, sizeof (char *) * (i + 1));
      chldlns[i] = safemalloc(MAX_ASTSEE_LEN);

      snprintf(chldlns[i], MAX_ASTSEE_LEN, "%s", ast_see( (n->chldn)[i] ));
      ++lines;
      total += safestrnlen(chldlns[i]);
    }

  } else {
    chldlns    = safemalloc(sizeof (char *));
    chldlns[0] = safemalloc(2);
    snprintf(chldlns[0], 2, "%s", "");
    lines = 1, total = 0;
  }
  chlds = concat_lines(chldlns, lines, total);

  char *out, tmp[MAX_ASTSEE_LEN];
  size_t len = signed2un(snprintf(
    tmp,
    MAX_ASTSEE_LEN,

    "NODE:\n"
    "\tunid: %zu\n"  // uid
    "\ttype: %s\n"   // type
    "\tcode: %s\n"   // code
    "\tnumc: %zd\n"  // num_childs
    "\tchld: {\n%s\n}",  // chldn

    n->uid,
    type,
    n->code,
    n->chldn_idx,
    chlds
  ));

  if (len > MAX_ASTSEE_LEN) {
    len = MAX_ASTSEE_LEN;
  }

  out = safemalloc(len);
  snprintf(
    out,
    len,
    "NODE:\n"
    "\tunid: %zu\n"   // uid
    "\ttype: %s\n"  // type
    "\tcode: %s\n"  // code
    "\tnumc: %zd\n"  // num_childs
    "\tchld: {\n%s\n}", // chldn

    n->uid,
    type,
    n->code,
    n->chldn_idx,
    chlds

  );

  safefree(chlds);
  safefree(type);

  return out;
}
