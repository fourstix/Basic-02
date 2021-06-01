#include "header.h"

void optionFile(char* filename) {
  FILE *file;
  char  line[1024];
  char  token[1024];
  char *pchar;
  int   pos;
  file = fopen(filename,"r");
  if (file == NULL) return;
  while (fgets(line,1024,file) != NULL) {
    pchar = line;
    pchar = trim(pchar);
    while (*pchar >= ' ') {
      pos = 0;
      while (*pchar > ' ') token[pos++] = *pchar++;
      token[pos] = 0;
      if (pos > 0) processOption(token);
      pchar = trim(pchar);
      }
    }
  fclose(file);
  }

