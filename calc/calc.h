#ifdef GCC
#line 2 "calc"
#endif

#include <sys/stat.h>
#include "stack.h"

char** file_lines (const char* const fname, size_t* out_len);

void interpret (void);
void    run_str(const char* const, stack_t* stk);

void interpret (void) {
  pfn(__FILE__, __LINE__, __func__);

  printf(
    "Stack-based calculator\n"
    "Enter a list of commands to run.\n\n"
  );

  stack_t* stk = stack_new();

  while (true) {

    printf("> ");

    char* in = readln(MAX_STR_LEN);

    if ( ! safestrnlen(in) ) {
      safefree(in);
      continue;
    } else if ( in[0] == 4 ) {
      safefree(in);
      break;
    } else {
      run_str(in, stk);
      safefree(in);
    }
  }

  char* o = stack_see(stk);
  printf("data stack: %s\n", o);
  safefree(o);
  stack_destruct(stk);
}

void run_str (const char* const prog, stack_t* stk) {
  pfn(__FILE__, __LINE__, __func__);

  if (prog == NULL) {
    return;
  }

  size_t len;
  number_t tmp = 0;

  char *val,
       *error = NULL,
       **spl_prog = str_split(prog, ' ', &len);

  dbg_prn("LEN: %zu\n", len);

  for (size_t i = 0; i < len; i++) {
    val = spl_prog[i];
    dbg_prn("%s\n", val);
    tmp = strtold(val, &error);

    if ( ! safestrnlen(error) ) {
      stack_push(stk, tmp);

    } else {
      //perform_op(stk, val);
      ssize_t opidx = get_stackop(val);

      if ( opidx > -1 ) {
        stack_ops[opidx](stk);

      } else {
        printf("%s: operator not defined\n", val);
      }

    }

  }

  free_ptr_array( (void **) spl_prog, 1);

  char* o = stack_see(stk);
  printf("< %s\n", o);
  safefree(o);
}

char** file_lines (const char* const fname, size_t* out_len) {
  struct stat finfo;

  if ( stat(fname, &finfo) == -1 ) {
    perror(fname);
    exit(EXIT_FAILURE);
  }

  FILE* fp;

  if ( (fp = fopen(fname, "r")) == NULL ) {
    perror(fname);
  }

  size_t lines_idx = 0;
  char **in_lines = safemalloc( sizeof (char *) );

  while ( true ) {

    char *line = NULL;
    size_t len = 0;
    ssize_t bytes_read = getline(&line, &len, fp);

    if (-1 == bytes_read) {
      safefree(line);
      break;
    }

    in_lines = realloc(in_lines, sizeof (char *) * (lines_idx + 1));
    in_lines[lines_idx] = safemalloc( (size_t) bytes_read);

    snprintf(in_lines[lines_idx], (size_t) bytes_read, "%s", line);

    ++lines_idx;
    safefree(line);
  }

  fclose(fp);

  *out_len = lines_idx;
  return in_lines;
}
