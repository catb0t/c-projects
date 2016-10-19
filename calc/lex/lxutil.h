#include "lexcommon.h"

astnode_t* lex_string (const char* const prog) {
  pfn();

  char* s;
  astnode_t*    ast = ast_newtree(prog);


  size_t plen = safestrnlen(prog);

  for (size_t i = 0; i < plen; i++) {
    ssize_t tmp;
    char c = prog[i];

    astnode_t* thisnode = ast_newnode(object_new(t_F, NULL), "");

    switch ( get_srcobj_type(c) ) {
      // ignore
      case DEL:
      case WSPACE:
      case NULCHAR:
      case CNTRL: { break; }

      case PUNC: {
        if ( c == '"' ) {
          tmp = build_string(prog, i, &thisnode);
          if ( tmp == -1 ) {
            return ast;
          }
          i = signed2un(tmp);
        }
        break;
      }

      case ALPHA: {
        // call user func
        break;
      }

      case DIGIT: {
        // break;
        tmp = build_number(prog, i, &thisnode);
      }

      case EASCII: {
        fprintf(stderr, "error: not implemented: EASCII: found Extended ASCII in source\n");
      }

    }

    s = ast_see(thisnode);
    dealloc_printf(s);

    ast->chldn = (typeof(ast->chldn)) realloc(ast->chldn, sizeof (astnode_t *) * (i + 1));
    (ast->chldn)[i] = thisnode;
    ++(ast->chldn_idx);

    dbg_prn("i: %zu\n", i);
  }

  return ast;
}


static char char_inrange (char n, char min, char max) {
  pfn();
  assert (max >= min);
  return (n >= min) && (n <= max);
}

__PURE_FUNC __CONST_FUNC
srcchar_t get_srcobj_type (const char c) {
  pfn();

  assert( ! (c < 0) );

  if ( ! c )         { return NULCHAR; }
  if ( c == '\x7f' ) { return DEL;     }
  // . is legal leading number digit
  if ( c == '.'  )   { return DIGIT;   }

  if ( ( c == ' '  ) // SPC
    || ( c == '\r' ) // CR
    || ( c == '\n' ) // LF
    || ( c == '\t' ) // TAB
  ) {
    return WSPACE;
  }

  if ( char_inrange(c, 1,   31)  ) { return CNTRL; }
  if ( char_inrange(c, 33,  47)  ) { return PUNC;  }
  if ( char_inrange(c, 48,  57)  ) { return DIGIT; }
  if ( char_inrange(c, 58,  64)  ) { return PUNC;  }
  if ( char_inrange(c, 65,  90)  ) { return ALPHA; }
  if ( char_inrange(c, 91,  96)  ) { return PUNC;  }
  if ( char_inrange(c, 97,  122) ) { return ALPHA; }
  if ( char_inrange(c, 123, 126) ) { return PUNC;  }

  return EASCII;
}

static void getfilepos (const char* const prog, const size_t idx, uint64_t* lineno, uint64_t* chrpos) {
  pfn();

  size_t plen = safestrnlen(prog);
  *lineno = 1;
  *chrpos = 0;

  for (size_t i = 0; (i != idx) || i < plen; i++) {
    if (prog[i] == '\n') {
      ++(*lineno);
      *chrpos = 0;
    }
    ++(*chrpos);
  }
}

ssize_t build_string (const char* const code, const size_t idx, astnode_t** out_node) {
  pfn();
  const size_t clen = safestrnlen(code);
  assert (clen > idx);

  const char
    //lastch  = code[ safe_usub(idx, 1) ],
    thisch  = code[idx],
    nextch  = code[ idx + 1 < clen ? idx + 1 : clen ];

  if (nextch == '\0') {
    goto notfound;
  }

  if (nextch == thisch) {

    printf("empty string\n");
    object_t* o = object_new(t_realchar, "");
    *out_node   = ast_newnode(o, "\"\"");
    object_destruct(o);
    return un2signed(idx + 2);

  } else {
    printf("non-empty\n");
    char
      *delim   = (typeof(delim)) safemalloc(2),
      *newstr  = strndup(&(code[idx]), MAX_STR_LEN),
      *str_lit = (typeof(str_lit)) safemalloc(MAX_STR_LEN + 3);

    snprintf(delim, 2, "%c", thisch);

    size_t
      new_len,
      nextd = strcspn(newstr, delim);

    if (nextd == clen) {
      goto notfound;

    }

    printf("found at %zu\n", nextd);
    new_len = udifference(nextd, idx);
    newstr  = (typeof(newstr)) realloc(newstr, (sizeof (char) * new_len) + 2);
    newstr[ new_len + 1 ] = '\0';

    printf("new_len: %zu actual: %zu str: %s\n",
      new_len, safestrnlen(newstr), newstr);

    snprintf(str_lit, MAX_STR_LEN + 3, "\"%s\"", newstr);

    object_t* o = object_new(t_realchar, newstr);
    *out_node = ast_newnode(o, str_lit);
    object_destruct(o);

    return un2signed(nextd);

  }


  notfound: {
    uint64_t ln, ch;
    getfilepos(code, clen, &ln, &ch);
    printf("Unterminated string literal starts at %" PRIu64 ":%" PRIu64 "\n", ln, ch);
    return -1;
  }
}

ssize_t build_number (const char* const code, const size_t idx, astnode_t** out_node) {
  pfn();

  const size_t clen = safestrnlen(code);
  assert (clen > idx);

  char
    *newstr  = (typeof(newstr)) safemalloc(100),
    *str_lit = (typeof(str_lit)) safemalloc(103);

  bool foundpt;
  size_t i;
  for (i = idx; i < clen; i++) {
    char c = code[i],
         *n;

    if (c == '.') {
      if (foundpt) {
        newstr = (typeof(newstr)) realloc(newstr, sizeof (char) * (i + 1));
        newstr[i] = '\0';
        break;
      }
      foundpt = true;
    }

    extern char* strchr_c (const char* const, const char);
    if ( (n = strchr_c(DEC_DIGITS, c)) != NULL) {
      newstr[i] = n[0];
      safefree(n);
    } else {
      newstr = (typeof(newstr)) realloc(newstr, sizeof (char) * (i + 1));
      newstr[i] = '\0';
      break;
    }
  }

  if ( ! safestrnlen(newstr)
      || (safestrnlen(newstr) == 1 && newstr[0] == '.')
    ) {
    return -1;
  }

  printf("%s\n", newstr);

  number_t*  n = (typeof(n)) safemalloc( sizeof (number_t) );
  n->value = strtold(newstr, NULL);
  object_t* o = object_new(t_number, n);

  snprintf(str_lit, 103, "\"%LG\"", n->value);

  *out_node = ast_newnode(o, newstr);
  return un2signed(idx);
}
