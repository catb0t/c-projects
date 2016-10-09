#ifdef GCC
#line 2 "lexcommon"
#endif

#pragma once

#include "../../common.h"
#include "../object/object.h"

typedef struct st_astnode astnode_t;

struct st_astnode {
  objtype_t   type;
  object_t*   obj;
  char*       code;
  astnode_t** chldn;
  ssize_t     chldn_idx;
  size_t      uid;
};

typedef enum { NULCHAR, CNTRL, DIGIT, ALPHA, WSPACE, PUNC, DEL, EASCII } srcchar_t;

astnode_t* ast_newnode (const object_t* const obj, const char* const code);
astnode_t*  lex_string (const char* const prog);
astnode_t* ast_newtree (const char* const prog);

void ast_destruct_node (astnode_t* n);

char* ast_see (astnode_t* n);

ssize_t build_string (const char* const code, const size_t idx, astnode_t** out_node);
ssize_t build_number (const char* const code, const size_t idx, astnode_t** out_node);

srcchar_t get_srcobj_type (const char c);
