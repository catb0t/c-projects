#include "conv.c"

int main(void) {

  char* locale = setlocale(LC_ALL, "");

  wprintf(L"using locale %s\n", locale);

  size_t len;

  wchar_t** strs = wstr_split(L"", L"asd", &len);

  for (size_t i = 0; i < len; i++) {
    wprintf(L"strs[i] = %ls ", strs[i]);
    for (size_t j = 0; j < wcslen(strs[i]); j++) {
      wprintf(L"%d", strs[i][j]);
    }
    wprintf(L"\n");
  }


/*  wprintf(L"Enter space-separated values (optional trailing symbol): ");

  wchar_t* in = wreadln(2000, stdin);

  if (NULL == in) { return EXIT_FAILURE; }

  size_t len;

  wchar_t** strs = wstr_split(in, L" ,", &len);

  free(in);
  */

  for (size_t i = 0; i < len; i++) {
    free(strs[i]);
  }

  free(strs);

  return EXIT_SUCCESS;
}
